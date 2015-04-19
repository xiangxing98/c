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
 * Array-based implementation stack.
 */

#ifndef __STK_H
#define __STK_H

#include <assert.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STK_MAX_SIZE 16 * 1024 * 1024  //16mb

typedef enum {
    STK_OK = 0,
    STK_ENOMEM = -1,
} stk_error_t;

typedef struct stk_st {
    void **data;
    size_t size;
    size_t cap;
} stk_t;

stk_t *stk_new(size_t);
void stk_free(stk_t *);
void stk_clear(stk_t *);
int stk_grow(stk_t *, size_t);
int stk_push(stk_t *, void *);
void *stk_pop(stk_t *);
void *stk_top(stk_t *);

#ifdef __cplusplus
}
#endif
#endif
