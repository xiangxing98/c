#include <stdio.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "hqueue.h"

typedef void (*case_t)();

static void test_case(const char *, case_t);

void case_hqueue_new();
void case_hqueue_free();
void case_hqueue_clear();
void case_hqueue_push();
void case_hqueue_pop();
void case_hqueue_top();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("hqueue_new", &case_hqueue_new);
    test_case("hqueue_free", &case_hqueue_free);
    test_case("hqueue_clear", &case_hqueue_clear);
    test_case("hqueue_push", &case_hqueue_push);
    test_case("hqueue_pop", &case_hqueue_pop);
    test_case("hqueue_top", &case_hqueue_top);
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_hqueue_new()
{
    hqueue_t *queue = hqueue_new();
    assert(queue != NULL && queue->size == 0 &&
            queue->head == NULL && queue->tail == NULL);
    hqueue_free(queue);
}

void
case_hqueue_free()
{
    hqueue_t *queue = hqueue_new();
    hqueue_free(queue);
}

void
case_hqueue_clear()
{
    hqueue_t *queue = hqueue_new();
    char *s = "s";
    assert(hqueue_push(queue, (void *)s) == HQUEUE_OK);
    assert(queue->size == 1);
    assert(hqueue_top(queue) == (void *)s);
    hqueue_clear(queue);
    assert(queue->size == 0 && queue->head == NULL
            && queue->tail == NULL);
    hqueue_free(queue);
}

void
case_hqueue_push()
{
    hqueue_t *queue = hqueue_new();
    char *s1 = "s1";
    char *s2 = "s2";
    char *s3 = "s3";
    assert(hqueue_push(queue, (void *)s1) == HQUEUE_OK);
    assert(hqueue_push(queue, (void *)s2) == HQUEUE_OK);
    assert(hqueue_push(queue, (void *)s3) == HQUEUE_OK);
    assert(queue->size == 3);
    assert(hqueue_top(queue) == (void *)s1);
    assert(queue->size == 3);
    hqueue_free(queue);
}

void
case_hqueue_pop()
{
    hqueue_t *queue = hqueue_new();
    char *s1 = "s1";
    char *s2 = "s2";
    char *s3 = "s3";
    assert(hqueue_push(queue, (void *)s1) == HQUEUE_OK);
    assert(hqueue_push(queue, (void *)s2) == HQUEUE_OK);
    assert(hqueue_push(queue, (void *)s3) == HQUEUE_OK);
    assert(queue->size == 3);
    assert(hqueue_pop(queue) == (void *)s1 && queue->size == 2);
    assert(hqueue_pop(queue) == (void *)s2 && queue->size == 1);
    assert(hqueue_pop(queue) == (void *)s3 && queue->size == 0);
    hqueue_free(queue);
}

void
case_hqueue_top()
{
    hqueue_t *queue = hqueue_new();
    char *s1 = "s1";
    char *s2 = "s2";
    assert(hqueue_push(queue, (void *)s1) == HQUEUE_OK);
    assert(hqueue_push(queue, (void *)s2) == HQUEUE_OK);
    assert(hqueue_top(queue) == (void *)s1 && queue->size == 2);
    assert(hqueue_top(queue) == (void *)s1 && queue->size == 2);
    hqueue_free(queue);
}
