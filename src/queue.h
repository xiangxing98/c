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
 * List based queue implementation
 */

#ifndef __QUEUE_H
#define __QUEUE_H

#include <assert.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    QUEUE_OK = 0,
    QUEUE_ENOMEM = -1,
} queue_error_t;

typedef struct queue_node_st {
    void *data;
    struct queue_node_st *next;
} queue_node_t;

typedef struct queue_st {
    struct queue_node_st *head;
    struct queue_node_st *tail;
    size_t size;
} queue_t;

queue_t *queue_new(void);
void queue_free(queue_t *);
void queue_clear(queue_t *);
queue_node_t *queue_node_new(void *);
void queue_node_free(queue_node_t *);
int queue_push(queue_t *, void *);
void *queue_pop(queue_t *);
void *queue_top(queue_t *);

#ifdef __cplusplus
}
#endif
#endif
