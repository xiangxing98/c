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

/**
 * BKDRHash hashtable implementation (list based).
 */

#ifndef __DICT_H

#include <memory.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "bool.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DICT_LOAD_LIMIT 0.75 // load factor limit

typedef enum {
    DICT_OK = 0,
    DICT_ENOMEM = -1,      /* No memory error */
    DICT_ENOTFOUND = -2,   /* Key was not found */
} dict_error_t;

typedef struct dict_node_st {
    uint8_t *key;
    size_t key_len;
    void *val;
    struct dict_node_st *next;
} dict_node_t;

typedef struct dict_st {
    dict_node_t **table;            /* buckets table */
    size_t size;                     /* buckets table size */
    size_t table_size_index;         /* index in table_sizes */
} dict_t;

typedef struct dict_iterator_st {
    dict_node_t *node;
    dict_t *dict;
    size_t index;
} dict_iterator_t;

dict_t *dict_new();
void dict_free(dict_t *);
void dict_clear(dict_t *);
int dict_set(dict_t *, uint8_t *, size_t, void *);
void *dict_get(dict_t *, uint8_t *, size_t);
bool dict_has(dict_t *, uint8_t *, size_t);
int dict_del(dict_t *, uint8_t *, size_t);
size_t dict_size(dict_t *);
dict_iterator_t *dict_iterator_new(dict_t *);
void dict_iterator_free(dict_iterator_t *);
int dict_iterator_next(dict_iterator_t *, uint8_t **, size_t *, void **);
void dict_iterator_reset(dict_iterator_t *);

#ifdef __cplusplus
}
#endif
#endif
