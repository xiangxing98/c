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

#include "dict.h"

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
    44917381,
    89834777,
    179669557,
    359339171,
    718678369,
    1437356741,
    2147483647
};

static size_t table_size_index_max = sizeof(table_sizes) / \
                                     sizeof(table_sizes[0]) - 1;  // 28

/**
 * BKDRHash
 */
static size_t
bkdrhash(uint8_t *key, size_t key_len)
{
    size_t seed = 13131;  // 31 131 1313 13131..
    size_t hash = 0;

    for(; key_len > 0; key_len--)
        hash = hash * seed + (*key++);
    return (hash & 0x7FFFFFFF);
}

/**
 * Get table size index.
 */
size_t
get_table_index(size_t table_size_index, uint8_t *key, size_t key_len)
{
    assert(table_size_index <= table_size_index_max);
    return bkdrhash(key, key_len) % table_sizes[table_size_index];
}

/**
 * New node.
 */
dict_node_t *
dict_node_new(uint8_t *key, size_t key_len, void *val)
{
    dict_node_t *node = malloc(sizeof(dict_node_t));

    if (node != NULL) {
        node->key = key;
        node->key_len = key_len;
        node->val = val;
        node->next = NULL;
    }
    return node;
}

/**
 * Free node.
 */
void
dict_node_free(dict_node_t *node)
{
    if (node != NULL)
        free(node);
}

/**
 * Resize && Rehash
 */
int
dict_resize(dict_t *dict)
{
    assert(dict != NULL &&
            dict->table_size_index <= table_size_index_max);

    size_t new_table_size_index = dict->table_size_index + 1;

    if (new_table_size_index > table_size_index_max)
        return DICT_ENOMEM;

    // new empty table
    size_t new_table_size = table_sizes[new_table_size_index];
    dict_node_t **new_table = malloc(new_table_size *
            sizeof(dict_node_t *));

    size_t index;

    for (index = 0; index < new_table_size; index++)
        new_table[index] = NULL;

    size_t table_size = table_sizes[dict->table_size_index];

    // for each bucket in table
    for (index = 0; index < table_size; index++) {
        // for each node in this bucket
        dict_node_t *node = (dict->table)[index];

        while (node != NULL) {
            dict_node_t *new_node = dict_node_new(node->key,
                    node->key_len, node->val);

            if (new_node == NULL)
                return DICT_ENOMEM;

            size_t new_index = get_table_index(
                    new_table_size_index, new_node->key, new_node->key_len);
            dict_node_t *cursor = new_table[new_index];

            if (cursor == NULL)
                // set head node
                new_table[new_index] = new_node;
            else {
                while (cursor->next != NULL)
                    cursor = cursor->next;
                // set tail node
                cursor->next = new_node;
            }

            dict_node_t *next_node = node->next;
            dict_node_free(node);
            node = next_node;
        }
    }

    free(dict->table);

    dict->table = new_table;
    dict->table_size_index = new_table_size_index;
    return DICT_OK;
}

/**
 * New dict.
 */
dict_t *
dict_new()
{
    dict_t *dict = malloc(sizeof(dict_t));

    if (dict != NULL) {
        dict->table_size_index = 0;

        size_t table_size = table_sizes[dict->table_size_index];
        dict->table = malloc(table_size * sizeof(dict_node_t *));

        if (dict->table == NULL)
            return NULL;

        size_t index;

        for (index = 0; index < table_size; index++)
            (dict->table)[index] = NULL;
    }

    return dict;
}

/**
 * Clear dict.
 */
void
dict_clear(dict_t *dict)
{
    assert(dict != NULL && dict->table_size_index <= table_size_index_max);

    size_t index;
    size_t table_size = table_sizes[dict->table_size_index];

    for (index = 0; index < table_size; index++) {
        dict_node_t *node = (dict->table)[index];

        while (node != NULL) {
            dict_node_t *next_node = node->next;
            dict_node_free(node);
            dict->size -= 1;
            node = next_node;
        }

        (dict->table)[index] = NULL;
    }
}

/**
 * Free dict.
 */
void dict_free(dict_t *dict)
{
    dict_clear(dict);

    if (dict->table != NULL)
        free(dict->table);
    if (dict != NULL)
        free(dict);
}

/**
 * Set a key to dict.
 */
int
dict_set(dict_t *dict, uint8_t *key, size_t key_len, void *val)
{
    assert(dict != NULL);

    if ((table_sizes[dict->table_size_index] * DICT_LOAD_LIMIT < dict->size) &&
            dict_resize(dict) != DICT_OK)
        return DICT_ENOMEM;

    size_t index = get_table_index(dict->table_size_index, key, key_len);
    dict_node_t *node = (dict->table)[index];

    // try to find this key
    while (node != NULL) {
        if (memcmp(node->key, key, key_len) == 0) {
            node->key = key;
            node->key_len = key_len;
            node->val = val;
            return DICT_OK;
        }
        node = node->next;
    }

    // new node if not found
    dict_node_t *new_node = dict_node_new(key, key_len, val);

    if (new_node == NULL)
        return DICT_ENOMEM;

    node = (dict->table)[index]; // rewind to head

    if (node == NULL) {
        // if head node is empty
        (dict->table)[index] = new_node;
    } else {
        // append new node to tail
        while (node->next != NULL)
            node = node->next;
        node->next = new_node;
    }
    dict->size += 1;
    return DICT_OK;
}

/**
 * Get val from dict by key.
 */
void *
dict_get(dict_t *dict, uint8_t *key, size_t key_len)
{
    assert(dict != NULL);

    size_t index = get_table_index(dict->table_size_index, key, key_len);
    dict_node_t *node = (dict->table)[index];

    while (node != NULL) {
        if (memcmp(node->key, key, key_len) == 0)
            return node->val;
        node = node->next;
    }

    return NULL;
}

/**
 * Test if a key is in the dict.
 */
bool
dict_has(dict_t *dict, uint8_t *key, size_t key_len)
{
    assert(dict != NULL);

    size_t index = get_table_index(dict->table_size_index, key, key_len);
    dict_node_t *node = (dict->table)[index];

    while (node != NULL) {
        if (memcmp(node->key, key, key_len) == 0)
            return true;
        node = node->next;
    }

    return false;
}

/**
 * Del val from dict by key.
 */
int
dict_del(dict_t *dict, uint8_t *key, size_t key_len)
{
    assert(dict != NULL);

    size_t index = get_table_index(dict->table_size_index, key, key_len);
    dict_node_t *node = (dict->table)[index];
    dict_node_t *prev = NULL;

    while (node != NULL) {
        if (memcmp(node->key, key, key_len) == 0) {
            if (prev == NULL)
                // if the first node
                (dict->table)[index] = node->next;
            else
                prev->next = node->next;
            free(node);
            dict->size -= 1;
            return DICT_OK;
        }

        prev = node;
        node = node->next;
    }

    return DICT_ENOTFOUND;
}

/**
 * Get dict size.
 */
size_t
dict_size(dict_t *dict)
{
    assert(dict != NULL);
    return dict->size;
}

/**
 * New dict iterator.
 */
dict_iterator_t *
dict_iterator_new(dict_t *dict)
{
    assert(dict != NULL);

    dict_iterator_t *iterator = malloc(sizeof(dict_iterator_t));

    if (iterator != NULL) {
        iterator->node = NULL;
        iterator->index = 0;
        iterator->dict = dict;
    }
    return iterator;
}

/**
 * Free dict iterator.
 */
void
dict_iterator_free(dict_iterator_t *iterator)
{
    if (iterator != NULL)
        free(iterator);
}

/**
 * Get next key and val
 */
int
dict_iterator_next(dict_iterator_t *iterator, uint8_t **key_addr, \
        size_t *key_len_addr, void **val_addr)
{
    assert(iterator != NULL && iterator->dict != NULL &&
            iterator->dict->table != NULL &&
            iterator->dict->table_size_index <= table_size_index_max);

    size_t table_size = table_sizes[iterator->dict->table_size_index];

    // seek to a Non-NULL node
    while(iterator->node == NULL) {
        if (iterator->index == table_size)
            return DICT_ENOTFOUND;
        iterator->node = (iterator->dict->table)[iterator->index++];
    }

    // fetch data
    *key_addr = iterator->node->key;
    *key_len_addr = iterator->node->key_len;
    *val_addr = iterator->node->val;

    // go to next node
    iterator->node = iterator->node->next;

    return DICT_OK;
}

/**
 * Reset a dict iterator.
 */
void
dict_iterator_reset(dict_iterator_t *iterator)
{
    assert(iterator != NULL);

    iterator->node = NULL;
    iterator->index = 0;
}
