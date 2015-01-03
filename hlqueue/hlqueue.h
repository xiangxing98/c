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

#ifndef __HLQUEUE_H
#define __HLQUEUE_H

#include <assert.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HLQUEUE_OK = 0,
    HLQUEUE_ENOMEM = -1,
} hlqueue_error_t;

typedef struct hlqueue_node_st {
    void *data;
    struct hlqueue_node_st *next;
} hlqueue_node_t;

typedef struct hlqueue_st {
    size_t size;
    struct hlqueue_node_st *head;
    struct hlqueue_node_st *tail;
} hlqueue_t;

hlqueue_t *hlqueue_new(void);
void hlqueue_free(hlqueue_t *);
void hlqueue_clear(hlqueue_t *);
hlqueue_node_t *hlqueue_node_new(void *);
void hlqueue_node_free(hlqueue_node_t *);
int hlqueue_push(hlqueue_t *, void *);
void *hlqueue_pop(hlqueue_t *);
void *hlqueue_top(hlqueue_t *);

#ifdef __cplusplus
}
#endif
#endif
