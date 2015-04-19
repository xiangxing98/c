#include <stdio.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "queue.h"

typedef void (*case_t)();

static void test_case(const char *, case_t);

void case_queue_new();
void case_queue_free();
void case_queue_clear();
void case_queue_push();
void case_queue_pop();
void case_queue_top();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("queue_new", &case_queue_new);
    test_case("queue_free", &case_queue_free);
    test_case("queue_clear", &case_queue_clear);
    test_case("queue_push", &case_queue_push);
    test_case("queue_pop", &case_queue_pop);
    test_case("queue_top", &case_queue_top);
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_queue_new()
{
    queue_t *queue = queue_new();
    assert(queue != NULL && queue->size == 0 &&
            queue->head == NULL && queue->tail == NULL);
    queue_free(queue);
}

void
case_queue_free()
{
    queue_t *queue = queue_new();
    queue_free(queue);
}

void
case_queue_clear()
{
    queue_t *queue = queue_new();
    char *s = "s";
    assert(queue_push(queue, (void *)s) == QUEUE_OK);
    assert(queue->size == 1);
    assert(queue_top(queue) == (void *)s);
    queue_clear(queue);
    assert(queue->size == 0 && queue->head == NULL
            && queue->tail == NULL);
    queue_free(queue);
}

void
case_queue_push()
{
    queue_t *queue = queue_new();
    char *s1 = "s1";
    char *s2 = "s2";
    char *s3 = "s3";
    assert(queue_push(queue, (void *)s1) == QUEUE_OK);
    assert(queue_push(queue, (void *)s2) == QUEUE_OK);
    assert(queue_push(queue, (void *)s3) == QUEUE_OK);
    assert(queue->size == 3);
    assert(queue_top(queue) == (void *)s1);
    assert(queue->size == 3);
    queue_free(queue);
}

void
case_queue_pop()
{
    queue_t *queue = queue_new();
    char *s1 = "s1";
    char *s2 = "s2";
    char *s3 = "s3";
    assert(queue_push(queue, (void *)s1) == QUEUE_OK);
    assert(queue_push(queue, (void *)s2) == QUEUE_OK);
    assert(queue_push(queue, (void *)s3) == QUEUE_OK);
    assert(queue->size == 3);
    assert(queue_pop(queue) == (void *)s1 && queue->size == 2);
    assert(queue_pop(queue) == (void *)s2 && queue->size == 1);
    assert(queue_pop(queue) == (void *)s3 && queue->size == 0);
    queue_free(queue);
}

void
case_queue_top()
{
    queue_t *queue = queue_new();
    char *s1 = "s1";
    char *s2 = "s2";
    assert(queue_push(queue, (void *)s1) == QUEUE_OK);
    assert(queue_push(queue, (void *)s2) == QUEUE_OK);
    assert(queue_top(queue) == (void *)s1 && queue->size == 2);
    assert(queue_top(queue) == (void *)s1 && queue->size == 2);
    queue_free(queue);
}
