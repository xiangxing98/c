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
    hqueue_node_t *node = queue->head;

    while (hqueue_pop(queue) != NULL);

    if (queue != NULL)
        free(queue);
}

void
hqueue_clear(hqueue_t *queue)
{
    assert(queue != NULL);
    while (hqueue_pop(queue) != NULL);
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

    if (queue->size == 0) {
        assert(queue->head == NULL && queue->tail == NULL);
        queue->head = node;
        queue->tail = node;
    } else {
        assert(queue->head != NULL && queue->tail != NULL);
        queue->tail->next = node;
        queue->tail = node;
    }

    queue->size += 1;
    return HQUEUE_OK;
}

void *
hqueue_pop(hqueue_t *queue)
{
    assert(queue != NULL);

    if (queue->size == 0) {
        assert(queue->head == NULL && queue->tail == NULL);
        return NULL;
    }
    assert(queue->head != NULL && queue->tail != NULL);
    hqueue_node_t *head = queue->head;
    void *data = head->data;
    queue->head = head->next;
    queue->size -= 1;
    if (queue->head == NULL)
        queue->tail = NULL;
    hqueue_node_free(head);
    return data;
}

void *
hqueue_top(hqueue_t *queue)
{
    assert(queue != NULL);

    if (queue->size == 0) {
        assert(queue->head == NULL && queue->tail == NULL);
        return NULL;
    }
    assert(queue->head != NULL && queue->tail != NULL);
    return queue->head->data;
}
