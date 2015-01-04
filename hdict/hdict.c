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

/**
 * New dict.
 */
hdict_t *
hdict_new(size_t size)
{
    hdict_t *dict = malloc(sizeof(hdict_t));

    if (dict != NULL) {
        dict->bucket_t = NULL;
        dict->size = 0;
        dict->cap = 0;
        if (size > 0 &&
                hdict_grow(dict, size) != HDICT_OK)
            return NULL;
    }
    return dict;
}

/**
 * Free dict.
 */
void
hdict_free(hdict_t *dict)
{
    // TODO: free buckets.
    if (dict != NULL)
        free(dict);
}

/**
 * Clear dict.
 */
void
hdict_clear(hdict_t *dict)
{
    // TODO: free buckets
}

/**
 * Grow dict allocation memory to given size, O(1), O(n)
 */
int
hdict_grow(hdict_t *dict, size_t size)
{
    assert(hdict != NULL);

    if (size > HDICT_MAX_SIZE)
        return HDICT_ENOMEM;

    if (size < dict->cap)
        return HDICT_OK;

    void *data = realloc(dict->data,
            size * sizeof(bucket_t *));

    if (dict->data == NULL)
        return HDICT_ENOMEM;

    dict->data = data;
    dict->cap = size;

    if (dict->size > size)
        dict->size = size;

    return HDICT_OK;
}

/**
 * Rehash.
 */

/**
 * Set an item into dict, O(1)
 */
int
hdict_set(hdict_t *dict, char *key, void *data)
{

}

/**
 * Get val by key from dict, O(1)
 */
void *
hdict_set(hdict_t *dict, char *key)
{

}

/**
 * Del key from dict, O(1)
 */
int
hdict_del(hdict_t *dict, char *key)
{

}
