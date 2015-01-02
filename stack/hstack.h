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

#ifndef __STACK_H
#define __STACK_H

#include <assert.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STACK_MAX_SIZE 16 * 1024 * 1024  //16mb

typedef enum {
    STACK_OK = 0,
    STACK_ENOMEM = -1,
} hstack_error_t;

typedef struct hstack_st {
    void **data;
    size_t size;
    size_t cap;
} hstack_t;

hstack_t *hstack_new(size_t);
void hstack_free(hstack_t *);
void hstack_clear(hstack_t *);
int hstack_grow(hstack_t *, size_t);
int hstack_push(hstack_t *, void *);
void *hstack_pop(hstack_t *);
void *hstack_top(hstack_t *);

#ifdef __cplusplus
}
#endif
#endif
