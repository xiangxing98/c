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

#include "hqueue.h"

hqueue_t *
hqueue_new(void)
{
    hqueue_t *queue = malloc(sizeof(hqueue_t));

    if (queue != NULL) {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
    }
    return queue;
}

void
hqueue_free(hqueue_t *queue)
{
    hqueue_clear(queue);

    if (queue != NULL)
        free(queue);
}

void
hqueue_clear(hqueue_t *queue)
{
    assert(queue != NULL);

    hqueue_node_t *node = queue->head;

    while (node != NULL) {
        hqueue_node_free(node);
        node = node->next;
    }

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

hqueue_node_t *
hqueue_node_new(void *data) {
    hqueue_node_t *node = malloc(sizeof(hqueue_node_t));

    if (node != NULL) {
        node->next = NULL;
        node->data = data;
    }
    return node;
}

void
hqueue_node_free(hqueue_node_t *node)
{
    if (node != NULL)
        free(node);
}

int hqueue_push(hqueue_t *queue, void *item)
{
    assert(queue != NULL);

    hqueue_node_t *node = hqueue_node_new(item);

    if (node == NULL)
        return HQUEUE_ENOMEM;

    if (queue->tail == NULL)
        queue->tail = node;
    else
        queue->tail->next = node;

    if (queue->head == NULL)
        queue->head = node;

    queue->size += 1;
    return HQUEUE_OK;
}

void *
hqueue_pop(hqueue_t *queue)
{
    assert(queue != NULL);

    if (queue->head == NULL || queue->size == 0)
        return NULL;

    hqueue_node_t *node = queue->head;
    queue->head = node->next;
    void *data = node->data;
    hqueue_node_free(node);
    queue->size -= 1;
    return data;
}

void *
hqueue_top(hqueue_t *queue)
{
    assert(queue != NULL);

    if (queue->head == NULL || queue->size == 0)
        return NULL;
    return queue->head->data;
}
