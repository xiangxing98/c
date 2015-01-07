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

static size_t primes[] = {
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

static size_t size_index_max = sizeof(primes) / sizeof(primes[0]);  // 29

/**
 * BKDRHash.
 */
static size_t
bkdrhash(void *key)
{
    size_t seed = 131; // 31, 131, 1313, 13131, 131313 ..
    size_t hash = 0;

    while (*key)
        hash = hash * seed + (*key++);
    return (hash & 0x7FFFFFFF);
}

/**
 * Get index.
 */
size_t
get_index(size_t size_index, void *key)
{
    assert(size_index < size_index_max);
    return  bkdrhash(key) % primes[size_index];
}

/**
 * Grow allocation memory
 */
int
hdict_grow(hdict_t *dict, size_t size_index)
{
    if (size_index_max < size_index)
        return HDICT_ENOMEM;

    if (size_index <= dict->size_index)
        return HDICT_OK;

    size_t size = primes[size_index];

    hdict_bucket_t **table = realloc(dict->table,
            sizeof(hdict_bucket_t *) * size);

    if (table == NULL)
        return HDICT_ENOMEM;

    dict->size_index = size_index;
    dict->table = table;
    return HDICT_OK;
}

/**
 * Rehash
 */
int
hdict_rehash(hdict_t *dict)
{
    assert(dict != NULL && dict->size_index < size_index_max);

    size_t new_size_index = dict->size_index + 1;

    if (size_index_max < new_size_index)
        return HDICT_ENOMEM;

    size_t new_size = primes[new_size_index];
    hdict_bucket_t **new_table = malloc(
            new_size * sizeof(hdict_bucket_t *));

    memset(new_table, NULL, new_size * sizeof(hdict_bucket_t *));

    size_t i;
    hdict_bucket_t *bucket, *cursor;

    for (i = 0; i < dict->size; i++) {
        bucket = (dict->table)[i];

        while (bucket != NULL) {
            hdict_bucket_t *new_bucket = hdict_bucket_new(
                    bucket->key, bucket->val);

            if (new_bucket == NULL)
                return HDICT_ENOMEM;

            size_t new_index = get_index(size_index, new_bucket->key);
            cursor = new_table[new_index];

            if (cursor == NULL)
                new_table[new_index] = new_bucket;
            else {
                while (cursor->next != NULL)
                    cursor = cursor->next;
                cursor->next = new_bucket;
            }
            hdict_bucket_t *temp = bucket;
            bucket = bucket->next;
            hdict_bucket_free(temp);
        }
    }
    free(dict->table);

    dict->table = new_table;
    dict->size_index = new_size_index;
    return HDICT_OK;
}

/**
 * New dict bucket.
 */
hdict_bucket_t *
hdict_bucket_new(void *key, void *val)
{
    hdict_bucket_t *bucket = malloc(sizeof(hdict_bucket_t));

    if (bucket != NULL) {
        bucket->key = key;
        bucket->val = val;
        bucket->next = NULL;
    }
    return bucket;
}

/**
 * Free dict bucket.
 */
void
hdict_bucket_free(hdict_bucket_t *bucket)
{
    if (bucket != NULL)
        free(bucket);
}

/**
 * New dict.
 */
hdict_t *
hdict_new(int (* keycmp)(void *, void *))
{
    hdict_t *dict = malloc(sizeof(hdict_t));

    if (dict != NULL) {
        dict->table = NULL;
        dict->size = 0;
        dict->size_index = 0;
        dict->keycmp = keycmp;

        if (hdict_grow(dict, dict->size_index) != HDICT_OK)
            return NULL;
    }
    return dict;
}

/**
 * Set a key into dict.
 */
int
hdict_set(hdict_t *dict, void *key, void *val)
{
    assert(dict != NULL && dict->keycmp != NULL);

    if (primes[dict->size_index] * HDICT_LOAD_LIMIT < dict->size &&
            hdict_rehash(dict) != HDICT_OK)
        return HDICT_ENOMEM;
}
