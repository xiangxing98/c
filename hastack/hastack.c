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


#include "hastack.h"

hastack_t *
hastack_new(size_t size)
{
    hastack_t *stack = malloc(sizeof(hastack_t));

    if (stack != NULL) {
        stack->data = NULL;
        stack->size = 0;
        stack->cap = 0;
        if (size > 0 &&
                hastack_grow(stack, size) != HASTACK_OK)
            return NULL;
    }
    return stack;
}

void
hastack_free(hastack_t *stack)
{
    if (stack->data != NULL)
        free(stack->data);
    if (stack != NULL)
        free(stack);
}

void
hastack_clear(hastack_t *stack)
{
    assert(stack != NULL);

    if (stack->data != NULL)
        free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->cap = 0;
}

int
hastack_grow(hastack_t *stack, size_t size)
{
    assert(stack != NULL);

    if (size > HASTACK_MAX_SIZE)
        return HASTACK_ENOMEM;

    if (size <= stack->cap)
        return HASTACK_OK;

    void **data = realloc(stack->data,
            size * sizeof(void *));

    if (data == NULL)
        return HASTACK_ENOMEM;

    stack->data = data;
    stack->cap = size;

    if (stack->size > size)
        stack->size = size;
    return HASTACK_OK;
}

int
hastack_push(hastack_t *stack, void *item)
{
    assert(stack != NULL);

    if (stack->size == stack->cap &&
            hastack_grow(stack, stack->size + 1) != HASTACK_OK)
        return HASTACK_ENOMEM;

    stack->data[stack->size++] = item;
    return HASTACK_OK;
}

void *
hastack_pop(hastack_t *stack)
{
    assert(stack != NULL);

    if (stack->size == 0 || stack->data == NULL)
        return NULL;

    return stack->data[--stack->size];
}

void *
hastack_top(hastack_t *stack)
{

    assert(stack != NULL);

    if (stack->size == 0 || stack->data == NULL)
        return NULL;

    return stack->data[stack->size - 1];
}
