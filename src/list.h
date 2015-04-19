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
 *   list_iterator_t *iterator = list_iterator_new(list);
 *
 *   void *data;
 *
 *   while((data = list_iterator_next(iterator)) != NULL) {
 *     ...
 *   }
 */

#ifndef __LIST_H
#define __LIST_H

#include <assert.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LIST_OK = 0,
    LIST_ENOMEM = -1,  /* No memory error */
    LIST_EINDEX = -2,  /* Invalid index error */
} list_error_t;

typedef struct list_node_st {
    void *data;
    struct list_node_st *prev;
    struct list_node_st *next;
} list_node_t;

typedef struct list_st {
    list_node_t *head;
    list_node_t *tail;
    size_t size;
} list_t;

typedef struct list_iterator_st {
    list_node_t *node;
} list_iterator_t;

list_node_t *list_node_new(void *);
void list_node_free(list_node_t *);
list_t *list_new(void);
void list_free(list_t *);
void list_clear(list_t *);
int list_lpush(list_t *, void *);
int list_rpush(list_t *, void *);
void *list_lpop(list_t *);
void *list_rpop(list_t *);
void *list_first(list_t *);
void *list_last(list_t *);
void *list_get(list_t *, size_t);
int list_set(list_t *, size_t, void *);
int list_del(list_t *, size_t);
list_iterator_t *list_iterator_new(list_t *);
void list_iterator_free(list_iterator_t *);
void *list_iterator_next(list_iterator_t *);
void *list_iterator_prev(list_iterator_t *);
void list_iterator_seek_head(list_t *, list_iterator_t *);
void list_iterator_seek_tail(list_t *, list_iterator_t *);

#ifdef __cplusplus
}
#endif
#endif
