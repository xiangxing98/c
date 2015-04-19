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

/**
 * New stack.
 */
stk_t *
stk_new(size_t size)
{
    stk_t *stack = malloc(sizeof(stk_t));

    if (stack != NULL) {
        stack->data = NULL;
        stack->size = 0;
        stack->cap = 0;
        if (size > 0 &&
                stk_grow(stack, size) != STK_OK)
            return NULL;
    }
    return stack;
}

/**
 * Free stack.
 */
void
stk_free(stk_t *stack)
{
    if (stack->data != NULL)
        free(stack->data);
    if (stack != NULL)
        free(stack);
}

/**
 * Clear stack, O(1)
 */
void
stk_clear(stk_t *stack)
{
    assert(stack != NULL);

    if (stack->data != NULL)
        free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->cap = 0;
}

/**
 * Grow stack allocation memory to given size, O(1), O(n)
 */
int
stk_grow(stk_t *stack, size_t size)
{
    assert(stack != NULL);

    if (size > STK_MAX_SIZE)
        return STK_ENOMEM;

    if (size <= stack->cap)
        return STK_OK;

    void **data = realloc(stack->data,
            size * sizeof(void *));

    if (data == NULL)
        return STK_ENOMEM;

    stack->data = data;
    stack->cap = size;

    if (stack->size > size)
        stack->size = size;
    return STK_OK;
}

/**
 * Push an item into stack, O(1), O(n).
 */
int
stk_push(stk_t *stack, void *item)
{
    assert(stack != NULL);

    if (stack->size == stack->cap &&
            stk_grow(stack, stack->size + 1) != STK_OK)
        return STK_ENOMEM;

    stack->data[stack->size++] = item;
    return STK_OK;
}

/**
 * Pop an item from stack, O(1)
 */
void *
stk_pop(stk_t *stack)
{
    assert(stack != NULL);

    if (stack->size == 0 || stack->data == NULL)
        return NULL;

    return stack->data[--stack->size];
}

/**
 * Get the top item in stack, O(1).
 */
void *
stk_top(stk_t *stack)
{

    assert(stack != NULL);

    if (stack->size == 0 || stack->data == NULL)
        return NULL;

    return stack->data[stack->size - 1];
}
