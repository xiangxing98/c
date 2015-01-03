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

#ifndef __HQUEUE_H
#define __HQUEUE_H

#include <assert.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HQUEUE_OK = 0,
    HQUEUE_ENOMEM = -1,
} hqueue_error_t;

typedef struct hqueue_node_st {
    void *data;
    struct hqueue_node_st *next;
} hqueue_node_t;

typedef struct hqueue_st {
    size_t size;
    struct hqueue_node_st *head;
    struct hqueue_node_st *tail;
} hqueue_t;

hqueue_t *hqueue_new(void);
void hqueue_free(hqueue_t *);
void hqueue_clear(hqueue_t *);
hqueue_node_t *hqueue_node_new(void *);
void hqueue_node_free(hqueue_node_t *);
int hqueue_push(hqueue_t *, void *);
void *hqueue_pop(hqueue_t *);
void *hqueue_top(hqueue_t *);

#ifdef __cplusplus
}
#endif
#endif
