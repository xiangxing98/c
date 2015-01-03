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

#include "hlqueue.h"

hlqueue_t *
hlqueue_new(void)
{
    hlqueue_t *queue = malloc(sizeof(hlqueue_t));

    if (queue != NULL) {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
    }
    return queue;
}

void
hlqueue_free(hlqueue_t *queue)
{
    hlqueue_clear(queue);

    if (queue != NULL)
        free(queue);
}

void
hlqueue_clear(hlqueue_t *queue)
{
    assert(queue != NULL);

    hlqueue_node_t *node = queue->head;

    while (node != NULL) {
        hlqueue_node_free(node);
        node = node->next;
    }

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

hlqueue_node_t *
hlqueue_node_new(void *data) {
    hlqueue_node_t *node = malloc(sizeof(hlqueue_node_t));

    if (node != NULL) {
        node->next = NULL;
        node->data = data;
    }
    return node;
}

void
hlqueue_node_free(hlqueue_node_t *node)
{
    if (node != NULL)
        free(node);
}

int hlqueue_push(hlqueue_t *queue, void *item)
{
    assert(queue != NULL);

    hlqueue_node_t *node = hlqueue_node_new(item);

    if (node == NULL)
        return HLQUEUE_ENOMEM;

    if (queue->tail == NULL)
        queue->tail = node;
    else
        queue->tail->next = node;

    if (queue->head == NULL)
        queue->head = node;

    queue->size += 1;
    return HLQUEUE_OK;
}

void *
hlqueue_pop(hlqueue_t *queue)
{
    assert(queue != NULL);

    if (queue->head == NULL || queue->size == 0)
        return NULL;

    hlqueue_node_t *node = queue->head;
    queue->head = node->next;
    void *data = node->data;
    hlqueue_node_free(node);
    queue->size -= 1;
    return data;
}

void *
hlqueue_top(hlqueue_t *queue)
{
    assert(queue != NULL);

    if (queue->head == NULL || queue->size == 0)
        return NULL;
    return queue->head->data;
}
