/**
 * Copyright (c) 2015, Chao Wang (hit9 <hit9@icloud.com>)
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "hdict.h"

static size_t table_sizes[] = {
    7,
    17,
    37,
    79,
    163,
    331,
    673,
    1361,
    2729,
    5471,
    10949,
    21911,
    43853,
    87719,
    175447,
    350899,
    701819,
    1403641,
    2807303,
    5614657,
    11229331,
    22458671,
    44917381,
    89834777,
    179669557,
    359339171,
    718678369,
    1437356741,
    2147483647
};

static size_t table_size_index_max = sizeof(table_sizes) / sizeof(table_sizes[0]) - 1;  // 28

/**
 * BKDRHash
 */
static size_t
bkdrhash(void *key)
{
    size_t seed = 131;  // 31 131 1313 13131..
    size_t hash = 0;

    while(*key)
        hash = hash * seed + (*key++);
    return (hash & 0x7fffffff);
}

/**
 * Get table size index.
 */
size_t
get_table_index(size_t table_size_index, void *key)
{
    assert(table_size_index <= table_size_index_max);
    return bkdrhash(key) % table_sizes[table_size_index];
}

/**
 * New node.
 */
hdict_node_t *
hdict_node_new(void *key, void *val)
{
    hdict_node_t *node = malloc(sizeof(hdict_node_t));

    if (node != NULL) {
        node->key = key;
        node->val = val;
        node->next = NULL;
    }
    return node;
}

/**
 * Free node.
 */
void
hdict_node_free(hdict_node_t *node)
{
    if (node != NULL)
        free(node);
}

/**
 * Resize && Rehash
 */
int
hdict_resize(hdict_t *dict)
{
    assert(dict != NULL &&
            dict->table_size_index <= table_size_index_max);

    size_t new_table_size_index = dict->table_size_index + 1;

    if (new_table_size_index > table_size_index_max)
        return HDICT_ENOMEM;

    // new empty table
    size_t new_table_size = table_sizes[new_table_size_index];
    hdict_node_t **new_table = malloc(new_table_size *
            sizeof(hdict_node_t *));
    memset(new_table, NULL, new_table_size * sizeof(hdict_node_t *));

    size_t index;
    size_t table_size = table_sizes[dict->table_size_index];

    // for each bucket in table
    for (index = 0; index < table_size; index++) {
        // for each node in this bucket
        hdict_node_t *node = (dict->table)[index];

        while (node != NULL) {
            hdict_node_t *new_node = hdict_node_new(node->key,
                    node->val);

            if (new_node == NULL)
                return HDICT_ENOMEM;

            size_t new_index = get_table_index(
                    new_table_size_index, new_node->key);
            hdict_node_t *cursor = new_table[new_index];

            if (cursor == NULL)  // if head node is empty
                new_table[new_index] = node;
            else {
                while (cursor->next != NULL)  // find last node
                    cursor = cursor->next;
                cursor->next = node;
            }

            hdict_node_t *next_node = node->next;
            hdict_node_free(node);
            node = new_node;
        }
    }

    free(dict->table);

    dict->table = new_table;
    dict->table_size_index = new_table_size_index;
    return HDICT_OK;
}

/**
 * New dict.
 */
hdict_t *
hdict_new(int (* keycmp)(void *, void *))
{
    assert(keycmp != NULL);

    hdict_t *dict = malloc(sizeof(hdict_t));

    if (dict != NULL) {
        dict->table_size_index = 0;
        dict->keycmp = keycmp;

        size_t table_size = table_sizes[dict->table_size_index];
        dict->table = malloc(table_size * sizeof(hdict_node_t *));

        if (dict->table == NULL)
            return NULL;

        memset(dict->table, NULL, table_size * sizeof(hdict_node_t *));
    }

    return dict;
}

/**
 * Clear dict.
 */
void
hdict_clear(hdict_t *dict)
{
    assert(dict != NULL && table_size_index <= table_size_index_max);

    size_t index;
    size_t table_size = table_sizes[dict->table_size_index];

    for (index = 0; index < table_size; index++) {
        hdict_node_t *node = (dict->table)[index];

        while (node != NULL) {
            hdict_node_t *next_node = node->next;
            free(node);
            node = next_node;
        }
    }

    free(dict->table);
}

/**
 * Free dict.
 */
void hdict_free(hdict_t *dict)
{
    hdict_clear(dict);
    if (dict != NULL)
        free(dict);
}

/**
 * Set a key to dict.
 */
int
hdict_set(hdict_t *dict, void *key, void *val)
{
    assert(dict != NULL && dict->keycmp != NULL);

    if (table_sizes[dict->table_size_index] * HDICT_LOAD_LIMIT < dict->size &&
            hdict_resize(dict) != HDICT_OK)
        return HDICT_ENOMEM;

    size_t index = get_table_index(dict->table_size_index, key);
    hdict_node_t *node = (dict->table)[index];

    // try to find this key
    while (node != NULL) {
        if ((dict->keycmp)(node->key, key) == 0) {
            node->key = key;
            node->val = val;
            return HDICT_OK;
        }
        node = node->next;
    }

    // new node if not found
    hdict_node_t *new_node = hdict_node_new(key, val);

    if (new_node == NULL)
        return HDICT_ENOMEM;

    if (node == NULL) {
        // if head node is empty
        (dict->table)[index] = new_node;
        return HDICT_OK;
    } else {
        // append new node to tail
        while (node->next != NULL)
            node = node->next;
        node->next = new_node;
    }
    dict->size += 1;
    return HDICT_OK;
}

/**
 * Get val from dict by key.
 */
void *
hdict_get(hdict_t *dict, void *key)
{
    assert(dict != NULL && dict->keycmp != NULL);

    size_t index = get_table_index(dict->table_size_index, key);
    hdict_node_t *node = (dict->table)[index];

    while (node != NULL) {
        if ((dict->keycmp)(node->key, key) == 0)
            return node->val;
        node = node->next;
    }
    return NULL;
}

/**
 * Del val from dict by key.
 */
int
hdict_del(hdict_t *dict, void *key)
{
    assert(dict != NULL && dict->keycmp != NULL);

    size_t index = get_table_index(dict->table_size_index, key);
    hdict_node_t *node = (dict->table)[index];
    hdict_node_t *prev = NULL;

    while (node != NULL) {
        if ((dict->keycmp)(node->key, key) == 0) {
            if (prev == NULL)
                // if the first node
                (dict->table)[index] = node->next;
            else
                prev->next = node->next;
            free(node);
            return HDICT_OK;
        }

        prev = node;
        node = node->next;
    }

    return HDICT_ENOTFOUND;
}
