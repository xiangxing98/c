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
 * Double linked list implementation
 *
 * example iterate a list:
 *
 *   hlist_iterator_t *iterator = hlist_iterator_new(list);
 *
 *   void *data;
 *
 *   while((data = hlist_iterator_next(iterator)) != NULL) {
 *     ...
 *   }
 */

#ifndef __HLIST_H
#define __HLIST_H

#include <assert.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HLIST_OK = 0,
    HLIST_ENOMEM = -1,  /* No memory error */
    HLIST_EINDEX = -2,  /* Invalid index error */
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
} hlist_t;

typedef struct hlist_iterator_st {
    hlist_node_t *node;
} hlist_iterator_t;

hlist_node_t *hlist_node_new(void *);
void hlist_node_free(hlist_node_t *);
hlist_t *hlist_new(void);
void hlist_free(hlist_t *);
void hlist_clear(hlist_t *);
int hlist_lpush(hlist_t *, void *);
int hlist_rpush(hlist_t *, void *);
void *hlist_lpop(hlist_t *);
void *hlist_rpop(hlist_t *);
void *hlist_first(hlist_t *);
void *hlist_last(hlist_t *);
void *hlist_get(hlist_t *, size_t);
int hlist_set(hlist_t *, size_t, void *);
int hlist_del(hlist_t *, size_t);
hlist_iterator_t *hlist_iterator_new(hlist_t *);
void hlist_iterator_free(hlist_iterator_t *);
void *hlist_iterator_next(hlist_iterator_t *);
void *hlist_iterator_prev(hlist_iterator_t *);
void hlist_iterator_seek_head(hlist_t *, hlist_iterator_t *);
void hlist_iterator_seek_tail(hlist_t *, hlist_iterator_t *);

#ifdef __cplusplus
}
#endif
#endif
