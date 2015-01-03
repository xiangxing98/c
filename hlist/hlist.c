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

#include "hlist.h"

/**
 * New list node.
 */
hlist_node_t *
hlist_node_new(void *data)
{
    hlist_node_t *node = malloc(sizeof(hlist_node_t));

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
hlist_node_free(hlist_node_t *node)
{
    if (node != NULL)
        free(node);
}

/**
 * New list.
 */
hlist_t *
hlist_new(void)
{
    hlist_t *list = malloc(sizeof(hlist_t));

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
hlist_free(hlist_t *list)
{
    if (list != NULL) {
        hlist_clear(list);
        free(list);
    }
}

/**
 * Clear list.
 */
void
hlist_clear(hlist_t *list)
{
    assert(list != NULL);
    while(hlist_lpop(list) != NULL);
}

/**
 * Push an item to list on the left end, O(1).
 */
int
hlist_lpush(hlist_t *list, void *item)
{
    assert(list != NULL);

    hlist_node_t *node = hlist_node_new(item);

    if (node == NULL)
        return HLIST_ENOMEM;

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        list->head = node;
        list->tail = node;
    } else {
        assert(list->head != NULL && list->tail != NULL);
        list->head->prev = node;
        list->head = node;
    }

    list->size += 1;
    return HLIST_OK;
}

/**
 * Push an item to list on the right end, O(1).
 */
int
hlist_rpush(hlist_t *list, void *item)
{
    assert(list != NULL);

    hlist_node_t *node = hlist_node_new(item);

    if(node == NULL)
        return HLIST_ENOMEM;

    if(list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        list->head = node;
        list->tail = node;
    } else {
        assert(list->head != NULL && list->tail != NULL);
        list->tail->next = node;
        list->tail = node;
    }

    list->size += 1;
    return HLIST_OK;
}

/**
 * Pop an item from list on the left end, O(1).
 */
int
hlist_lpop(hlist_t *list, void *item)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return NULL;
    }

    assert(list->head != NULL && list->tail != NULL);
    hlist_node_t *head = list->head;
    void *data = head->data;
    list->head = head->next;
    list->size -= 1;
    if (list->head == NULL)
        list->tail = NULL;
    hlist_node_free(head);
    return data;
}

/**
 * Pop an item from list on the right end, O(1).
 */
int
hlist_rpop(hlist_t *list, void *item)
{
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL && list->tail == NULL);
        return NULL;
    }

    assert(list->head != NULL && list->tail != NULL);
    hlist_node_t *tail = list->tail;
    void *data = tail->data;
    list->tail = tail->prev;
    list->size -= 1;
    if (list->tail == NULL)
        list->head = NULL;
    hlist_node_free(tail);
    return data;
}
