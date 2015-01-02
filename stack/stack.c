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


#include "stack.h"

stack_t *
stack_new(size_t size)
{
    stack_t *stack = malloc(sizeof(stack_t));

    if (stack != NULL) {
        stack->data = NULL;
        stack->size = 0;
        stack->cap = 0;
        if (size > 0)
            stack_grow(stack, size);
    }
    return stack;
}

void
stack_free(stack_t *stack)
{
    if (stack->data != NULL)
        free(stack->data);
    if (stack != NULL)
        free(stack);
}

void
stack_clear(stack_t *stack)
{
    assert(stack != NULL);

    if (stack->data)
        free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->cap = 0;
}

int
stack_grow(stack_t *stack, size_t size)
{
    assert(stack != NULL);

    if (size > STACK_MAX_SIZE)
        return STACK_ENOMEM;

    if (size <= stack->cap)
        return STACK_OK;

    void **data = realloc(stack->data,
            size * sizeof(void *));

    if (data == NULL)
        return STACK_ENOMEM;

    stack->data = data;
    stack->cap = size;

    if (stack->size > size)
        stack->size = size;
    return STACK_OK;
}

int
stack_push(stack_t *stack, void *item)
{
    assert(stack != NULL);

    if (stack->size == stack->cap &&
            stack_grow(stack, stack->size + 1) != STACK_OK)
        return STACK_ENOMEM;

    stack->data[stack->size++] = item;
    return STACK_OK;
}

void *
stack_pop(stack_t *stack)
{
    assert(stack != NULL);

    if (stack->size == 0 || stack->data == NULL)
        return NULL;

    return stack->data[--stack->size];
}


void *
stack_top(stack_t *stack)
{
    if (stack->size == 0 || stack->data == NULL)
        return NULL;
    return stack->data[stack->size - 1];
}
