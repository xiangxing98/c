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

#ifndef __HDICT_H

#include <memory.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HDICT_LOAD_LIMIT 0.75 // load factor limit

typedef enum {
    HDICT_OK = 0,
    HDICT_ENOMEM = -1,      /* No memory error */
    HDICT_ENOTFOUND = -2,   /* Key was not found */
} hdict_error_t;

typedef struct hdict_node_st {
    uint8_t *key;
    size_t key_len;
    void *val;
    struct hdict_node_st *next;
} hdict_node_t;

typedef struct {
    hdict_node_t **table;            /* buckets table */
    size_t size;                     /* buckets table size */
    size_t table_size_index;         /* index in table_sizes */
} hdict_t;

hdict_t *hdict_new();
void hdict_free(hdict_t *);
void hdict_clear(hdict_t *);
int hdict_set(hdict_t *, uint8_t *, size_t, void *);
void *hdict_get(hdict_t *, uint8_t *, size_t);
int hdict_has(hdict_t *, uint8_t *, size_t);
int hdict_del(hdict_t *, uint8_t *, size_t);

#ifdef __cplusplus
}
#endif
#endif
