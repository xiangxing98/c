#include <stdio.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "list.h"

typedef void (*case_t)();

static void test_case(const char *, case_t);

void case_list_new();
void case_list_free();
void case_list_clear();
void case_list_lpush();
void case_list_rpush();
void case_list_lpop();
void case_list_rpop();
void case_list_first();
void case_list_last();
void case_list_get();
void case_list_set();
void case_list_del();
void case_list_iter();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("list_new", &case_list_new);
    test_case("list_free", &case_list_free);
    test_case("list_clear", &case_list_clear);
    test_case("list_lpush", &case_list_lpush);
    test_case("list_rpush", &case_list_rpush);
    test_case("list_lpop", &case_list_lpop);
    test_case("list_rpop", &case_list_rpop);
    test_case("list_first", &case_list_first);
    test_case("list_last", &case_list_last);
    test_case("list_get", &case_list_get);
    test_case("list_set", &case_list_set);
    test_case("list_del", &case_list_del);
    test_case("list_iter", &case_list_iter);
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_list_new()
{
    list_t *list = list_new();
    assert(list->head == NULL && list->tail == NULL &&
            list->size == 0);
    list_free(list);
}

void
case_list_free()
{
    list_t *list = list_new();
    list_free(list);
}

void
case_list_clear()
{
    list_t *list = list_new();
    char *s1 = "s", *s2 = "s2", *s3 = "s3";
    assert(list_lpush(list, (void *)s1) == LIST_OK);
    assert(list_rpush(list, (void *)s2) == LIST_OK);
    assert(list_rpush(list, (void *)s3) == LIST_OK);
    assert(list->size == 3);
    list_clear(list);
    assert(list->size == 0 && list->head == NULL
            && list->tail == NULL);
    list_free(list);
}

void
case_list_lpush()
{
    list_t *list = list_new();
    char *s1 = "s", *s2 = "s2", *s3 = "s3";
    assert(list_lpush(list, (void *)s1) == LIST_OK);
    assert(list_lpush(list, (void *)s2) == LIST_OK);
    assert(list_lpush(list, (void *)s3) == LIST_OK);
    assert(list_lpush(list, (void *)s1) == LIST_OK);
    assert(list_lpush(list, (void *)s2) == LIST_OK);
    assert(list_lpush(list, (void *)s3) == LIST_OK);
    assert(list->size == 6);
    assert(list->head != NULL && list->tail != NULL);
    assert(list->head->prev == NULL && list->tail->next == NULL);
    assert(list_lpop(list) == (void *)s3);
    assert(list_lpop(list) == (void *)s2);
    assert(list_lpop(list) == (void *)s1);
    assert(list_rpop(list) == (void *)s1);
    assert(list_rpop(list) == (void *)s2);
    assert(list_rpop(list) == (void *)s3);
    assert(list->size == 0);
    list_free(list);
}

void
case_list_rpush()
{
    list_t *list = list_new();
    char *s1 = "s", *s2 = "s2", *s3 = "s3";
    assert(list_rpush(list, (void *)s1) == LIST_OK);
    assert(list_rpush(list, (void *)s2) == LIST_OK);
    assert(list_rpush(list, (void *)s3) == LIST_OK);
    assert(list_rpush(list, (void *)s1) == LIST_OK);
    assert(list_rpush(list, (void *)s2) == LIST_OK);
    assert(list_rpush(list, (void *)s3) == LIST_OK);
    assert(list->size == 6);
    assert(list->head != NULL && list->tail != NULL);
    assert(list->head->prev == NULL && list->tail->next == NULL);
    assert(list_rpop(list) == (void *)s3);
    assert(list_rpop(list) == (void *)s2);
    assert(list_rpop(list) == (void *)s1);
    assert(list_lpop(list) == (void *)s1);
    assert(list_lpop(list) == (void *)s2);
    assert(list_lpop(list) == (void *)s3);
    assert(list->size == 0);
    list_free(list);
}

void
case_list_lpop()
{
    list_t *list = list_new();
    char *s1 = "s", *s2 = "s2", *s3 = "s3";
    assert(list_rpush(list, (void *)s1) == LIST_OK);
    assert(list_rpush(list, (void *)s2) == LIST_OK);
    assert(list_rpush(list, (void *)s3) == LIST_OK);
    assert(list_lpop(list) == (void *)s1);
    assert(list_lpop(list) == (void *)s2);
    assert(list_lpop(list) == (void *)s3);
    list_free(list);
}

void
case_list_rpop()
{
    list_t *list = list_new();
    char *s1 = "s", *s2 = "s2", *s3 = "s3";
    assert(list_rpush(list, (void *)s1) == LIST_OK);
    assert(list_rpush(list, (void *)s2) == LIST_OK);
    assert(list_rpush(list, (void *)s3) == LIST_OK);
    assert(list_rpop(list) == (void *)s3);
    assert(list_rpop(list) == (void *)s2);
    assert(list_rpop(list) == (void *)s1);
    list_free(list);
}

void
case_list_first()
{
    list_t *list = list_new();
    char *s1 = "s", *s2 = "s2", *s3 = "s3";
    assert(list_rpush(list, (void *)s1) == LIST_OK);
    assert(list_rpush(list, (void *)s2) == LIST_OK);
    assert(list_rpush(list, (void *)s3) == LIST_OK);
    assert(list_first(list) == (void *)s1);
    assert(list_lpop(list) == (void *)s1);
    assert(list_first(list) == (void *)s2);
    list_free(list);
}

void
case_list_last()
{

    list_t *list = list_new();
    char *s1 = "s", *s2 = "s2", *s3 = "s3";
    assert(list_rpush(list, (void *)s1) == LIST_OK);
    assert(list_rpush(list, (void *)s2) == LIST_OK);
    assert(list_rpush(list, (void *)s3) == LIST_OK);
    assert(list_last(list) == (void *)s3);
    assert(list_rpop(list) == (void *)s3);
    assert(list_last(list) == (void *)s2);
    list_free(list);
}

void
case_list_get()
{
    list_t *list = list_new();
    assert(list_get(list, 1) == NULL);
    char *s1 = "s", *s2 = "s2", *s3 = "s3";
    assert(list_rpush(list, (void *)s1) == LIST_OK);
    assert(list_rpush(list, (void *)s2) == LIST_OK);
    assert(list_rpush(list, (void *)s3) == LIST_OK);
    assert(list_get(list, 0) == (void *)s1);
    assert(list_get(list, 1) == (void *)s2);
    assert(list_get(list, 2) == (void *)s3);
    assert(list_get(list, 3) == NULL);
    list_free(list);
}

void
case_list_set()
{
    list_t *list = list_new();
    assert(list_set(list, 1, "") == LIST_EINDEX);
    char *s1 = "s", *s2 = "s2", *s3 = "s3", *s4 = "s4";
    assert(list_rpush(list, (void *)s1) == LIST_OK);
    assert(list_rpush(list, (void *)s2) == LIST_OK);
    assert(list_rpush(list, (void *)s3) == LIST_OK);
    assert(list_set(list, 0, (void *)s4) == LIST_OK);
    assert(list_get(list, 0) == (void *)s4);
    list_free(list);
}

void
case_list_del()
{
    list_t *list = list_new();
    assert(list_del(list, 1) == LIST_EINDEX);
    char *s1 = "s", *s2 = "s2", *s3 = "s3";
    assert(list_rpush(list, (void *)s1) == LIST_OK);
    assert(list_rpush(list, (void *)s2) == LIST_OK);
    assert(list_rpush(list, (void *)s3) == LIST_OK);
    assert(list_del(list, 0) == LIST_OK);
    assert(list->size == 2);
    assert(list_first(list) == (void *)s2);
    assert(list_del(list, 3) == LIST_EINDEX);
    assert(list_del(list, 0) == LIST_OK);
    assert(list->size == 1);
    assert(list_del(list, 0) == LIST_OK);
    assert(list->size == 0);
    assert(list_last(list) == NULL && list_first(list) == NULL);
    list_free(list);
}

void
case_list_iter()
{
    list_t *list = list_new();
    char *s1 = "s1", *s2 = "s2", *s3 = "s3";
    assert(list_rpush(list, (void *)s1) == LIST_OK);
    assert(list_rpush(list, (void *)s2) == LIST_OK);
    assert(list_rpush(list, (void *)s3) == LIST_OK);

    list_iterator_t *iterator = list_iterator_new(list);
    assert(list_iterator_next(iterator) == s1);
    assert(list_iterator_next(iterator) == s2);
    assert(list_iterator_next(iterator) == s3);
    assert(list_iterator_next(iterator) == NULL);

    list_iterator_seek_tail(list, iterator);
    assert(list_iterator_prev(iterator) == s3);
    assert(list_iterator_prev(iterator) == s2);
    assert(list_iterator_prev(iterator) == s1);
    assert(list_iterator_prev(iterator) == NULL);
    list_iterator_free(iterator);
    list_free(list);
}
