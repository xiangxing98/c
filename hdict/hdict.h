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
#include <stdlib.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HDICT_LOAD_LIMIT 0.75 // load factor limit

typedef enum {
    HDICT_OK = 0,
    HDICT_ENOMEM = -1,      /* No memory error */
} hdict_error_t;

typedef struct hdict_bucket_st {
    void *key;
    void *val;
    struct hdict_bucket_st *next;
} hdict_bucket_t;

typeof struct {
    bucket_t **table;                /* bucket list table */
    size_t size;                     /* buckets number */
    size_t size_index;               /* index in primes */
    int (* keycmp)(void *, void *);  /* like strcmp */
} hdict_t;

hdict_t *hdict_new(int (*)(void *, void *));
void hdict_free(hdict_t *);
void hdict_clear(hdict_t *);
int hdict_set(hdict_t *, void *, void *);
void *hdict_get(hdict_t *, void *);
int hdict_del(hdict_t *, void *);

#ifdef __cplusplus
}
#endif
#endif
