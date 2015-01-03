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

#ifndef __HLIST_H
#define __HLIST_H

#include <assert.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HLIST_MAX_SIZE 16 * 1024 * 1024  //16mb

typedef enum {
    HLIST_OK = 0,
    HLIST_ENOMEM = -1,
} hlist_error_t;

typedef struct hlist_node_st {
    void *data;
    struct hlist_node_st *prev;
    struct hlist_node_st *next;
} hlist_node_t;

typedef struct hlist_st {
    hlist_node_t *head;
    hlist_node_t *tail;
    size_t size;
    size_t cap;
} hlist_t;

hlist_t *hlist_new(size_t);
void hlist_free(hlist_t *);
void hlist_clear(hlist_t *);

#ifdef __cplusplus
}
#endif
#endif
