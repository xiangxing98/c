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

#include "queue.h"

/**
 * New queue.
 */
queue_t *
queue_new(void)
{
    queue_t *queue = malloc(sizeof(queue_t));

    if (queue != NULL) {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
    }
    return queue;
}

/**
 * Free queue.
 */
void
queue_free(queue_t *queue)
{
    if (queue != NULL) {
        queue_clear(queue);
        free(queue);
    }
}

/**
 * Clear queue, O(n)
 */
void
queue_clear(queue_t *queue)
{
    assert(queue != NULL);
    while (queue_pop(queue) != NULL);
}

/**
 * New queue node.
 */
queue_node_t *
queue_node_new(void *data) {
    queue_node_t *node = malloc(sizeof(queue_node_t));

    if (node != NULL) {
        node->next = NULL;
        node->data = data;
    }
    return node;
}

/**
 * Free queue node.
 */
void
queue_node_free(queue_node_t *node)
{
    if (node != NULL)
        free(node);
}

/**
 * Push an item into queue, O(1);
 */
int
queue_push(queue_t *queue, void *item)
{
    assert(queue != NULL);

    queue_node_t *node = queue_node_new(item);

    if (node == NULL)
        return QUEUE_ENOMEM;

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
    return QUEUE_OK;
}

/**
 * Pop an item from queue, O(1);
 */
void *
queue_pop(queue_t *queue)
{
    assert(queue != NULL);

    if (queue->size == 0) {
        assert(queue->head == NULL && queue->tail == NULL);
        return NULL;
    }
    assert(queue->head != NULL && queue->tail != NULL);
    queue_node_t *head = queue->head;
    void *data = head->data;
    queue->head = head->next;
    queue->size -= 1;
    if (queue->head == NULL)
        queue->tail = NULL;
    queue_node_free(head);
    return data;
}

/**
 * Get the top item in queue, O(1);
 */
void *
queue_top(queue_t *queue)
{
    assert(queue != NULL);

    if (queue->size == 0) {
        assert(queue->head == NULL && queue->tail == NULL);
        return NULL;
    }
    assert(queue->head != NULL && queue->tail != NULL);
    return queue->head->data;
}
