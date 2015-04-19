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

#include "list.h"

/**
 * New list node.
 */
list_node_t *
list_node_new(void *data)
{
    list_node_t *node = malloc(sizeof(list_node_t));

    if (node != NULL) {
        node->data = data;
        node->prev = NULL;
        node->next = NULL;
    }
    return node;
}

/**
 * Free list node.
 */
void
list_node_free(list_node_t *node)
{
    if (node != NULL)
        free(node);
}

/**
 * New list.
 */
list_t *
list_new(void)
{
    list_t *list = malloc(sizeof(list_t));

    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
    return list;
}

/**
 * Free list.
 */
void
list_free(list_t *list)
{
    if (list != NULL) {
        list_clear(list);
        free(list);
    }
}

/**
 * Clear list.
 */
void
list_clear(list_t *list)
{
    assert(list != NULL);
    while(list_lpop(list) != NULL);
}

/**
 * Push an item to list on the left end, O(1).
 */
int
list_lpush(list_t *list, void *item)
{
    assert(list != NULL);

    list_node_t *node = list_node_new(item);

    if (node == NULL)
        return LIST_ENOMEM;

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        list->head = node;
        list->tail = node;
    } else {
        assert(list->head != NULL && list->tail != NULL);
        list_node_t *head = list->head;
        assert(head->prev == NULL && node->prev == NULL);
        head->prev = node;
        node->next = head;
        list->head = node;
    }

    list->size += 1;
    return LIST_OK;
}

/**
 * Push an item to list on the right end, O(1).
 */
int
list_rpush(list_t *list, void *item)
{
    assert(list != NULL);

    list_node_t *node = list_node_new(item);

    if(node == NULL)
        return LIST_ENOMEM;

    if(list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        list->head = node;
        list->tail = node;
    } else {
        assert(list->head != NULL && list->tail != NULL);
        list_node_t *tail = list->tail;
        assert(tail->next == NULL && node->next == NULL);
        tail->next = node;
        node->prev = tail;
        list->tail = node;
    }

    list->size += 1;
    return LIST_OK;
}

/**
 * Pop an item from list on the left end, O(1).
 */
void *
list_lpop(list_t *list)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return NULL;
    }

    assert(list->head != NULL && list->tail != NULL);

    list_node_t *head = list->head;
    list_node_t *node = head->next;

    if (node == NULL) {
        list->tail = NULL;
    } else {
        node->prev = NULL;
    }

    list->head = node;
    list->size -= 1;

    void *data = head->data;
    list_node_free(head);
    return data;
}

/**
 * Pop an item from list on the right end, O(1).
 */
void *
list_rpop(list_t *list)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return NULL;
    }

    assert(list->head != NULL && list->tail != NULL);

    list_node_t *tail = list->tail;
    list_node_t *node = tail->prev;

    if (node == NULL) {
        list->head = NULL;
    } else {
        node->next = NULL;
    }

    list->tail = node;
    list->size -= 1;

    void *data = tail->data;
    list_node_free(tail);
    return data;
}

/**
 * Get the first item in the list, O(1).
 */
void *
list_first(list_t *list)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return NULL;
    }
    assert(list->head != NULL && list->tail != NULL);
    return list->head->data;
}

/**
 * Get the last item in the list, O(1).
 */
void *
list_last(list_t *list)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return NULL;
    }
    assert(list->head != NULL && list->tail != NULL);
    return list->tail->data;
}

/**
 * Get an item by index, O(n).
 */
void *
list_get(list_t *list, size_t index)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return NULL;
    }

    assert(list->head != NULL && list->tail != NULL);

    list_node_t *node = list->head;
    size_t idx = 0;

    while (node != NULL) {
        if (idx++ == index)
            return node->data;
        node = node->next;
    }

    return NULL;
}


/**
 * Set an item by index, O(n)
 */
int
list_set(list_t *list, size_t index, void *data)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return LIST_EINDEX;
    }

    assert(list->head != NULL && list->tail != NULL);

    list_node_t *node = list->head;
    size_t idx = 0;

    while (node != NULL) {
        if (idx++ == index) {
            node->data = data;
            return LIST_OK;
        }
        node = node->next;
    }

    return LIST_EINDEX;
}

/**
 * Delete an item by index, O(n)
 */
int
list_del(list_t *list, size_t index)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return LIST_EINDEX;
    }

    assert(list->head != NULL && list->tail != NULL);

    list_node_t *node = list->head;
    list_node_t *prev, *next;
    size_t idx = 0;

    while (node != NULL) {
        if (idx++ == index) {
            prev = node->prev;
            next = node->next;
            if (prev != NULL)
                prev->next = next;
            else
                list->head = next;
            if (next != NULL)
                next->prev = prev;
            else
                list->tail = prev;
            list->size -= 1;
            list_node_free(node);
            return LIST_OK;
        }
        node = node->next;
    }

    return LIST_EINDEX;
}

/**
 * New iterator
 */
list_iterator_t *
list_iterator_new(list_t *list)
{
    assert(list != NULL);

    list_iterator_t *iterator = malloc(sizeof(list_iterator_t));

    if (iterator != NULL) {
        iterator->node = list->head;
    }
    return iterator;
}

/**
 * Free iterator.
 */
void
list_iterator_free(list_iterator_t *iterator)
{
    if (iterator != NULL)
        free(iterator);
}

/**
 * Get current node's data and seek next, O(1)
 */
void *
list_iterator_next(list_iterator_t *iterator)
{
    assert(iterator != NULL);

    list_node_t *node = iterator->node;

    if (node == NULL)
        return NULL;

    iterator->node = node->next;
    return node->data;
}

/**
 * Get current node's data and seek prev, O(1)
 */
void *
list_iterator_prev(list_iterator_t *iterator)
{
    assert(iterator != NULL);

    list_node_t *node = iterator->node;

    if (node == NULL)
        return NULL;

    iterator->node = node->prev;
    return node->data;
}


/**
 * Seek iterator to a list's head, O(1)
 */
void
list_iterator_seek_head(list_t *list, list_iterator_t *iterator)
{
    assert(list != NULL && iterator != NULL);
    iterator->node = list->head;
}

/**
 * Seek iterator to a list's tail, O(1)
 */
void
list_iterator_seek_tail(list_t *list, list_iterator_t *iterator)
{
    assert(list != NULL && iterator != NULL);
    iterator->node = list->tail;
}
