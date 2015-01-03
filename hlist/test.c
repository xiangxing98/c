#include <stdio.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "hlist.h"

typedef void (*case_t)();

static void test_case(const char *, case_t);

void case_hlist_new();
void case_hlist_free();
void case_hlist_clear();
void case_hlist_lpush();
void case_hlist_rpush();
void case_hlist_lpop();
void case_hlist_rpop();
void case_hlist_first();
void case_hlist_last();
void case_hlist_get();
void case_hlist_set();
void case_hlist_del();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("hlist_new", &case_hlist_new);
    test_case("hlist_free", &case_hlist_free);
    test_case("hlist_clear", &case_hlist_clear);
    test_case("hlist_lpush", &case_hlist_lpush);
    test_case("hlist_rpush", &case_hlist_rpush);
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_hlist_new()
{
    hlist_t *list = hlist_new();
    assert(list->head == NULL && list->tail == NULL &&
            list->size == 0);
    hlist_free(list);
}

void
case_hlist_free()
{
    hlist_t *list = hlist_new();
    hlist_free(list);
}

void
case_hlist_clear()
{
    hlist_t *list = hlist_new();
    char *s1 = "s", *s2 = "s2", *s3 = "s3";
    assert(hlist_lpush(list, (void *)s1) == HLIST_OK);
    assert(hlist_rpush(list, (void *)s2) == HLIST_OK);
    assert(hlist_rpush(list, (void *)s3) == HLIST_OK);
    assert(list->size == 3);
    hlist_clear(list);
    assert(list->size == 0 && list->head == NULL
            && list->tail == NULL);
    hlist_free(list);
}

void
case_hlist_lpush()
{
    hlist_t *list = hlist_new();
    char *s1 = "s", *s2 = "s2", *s3 = "s3";
    assert(hlist_lpush(list, (void *)s1) == HLIST_OK);
    assert(hlist_lpush(list, (void *)s2) == HLIST_OK);
    assert(hlist_lpush(list, (void *)s3) == HLIST_OK);
    assert(hlist_lpush(list, (void *)s1) == HLIST_OK);
    assert(hlist_lpush(list, (void *)s2) == HLIST_OK);
    assert(hlist_lpush(list, (void *)s3) == HLIST_OK);
    assert(list->size == 6);
    assert(list->head != NULL && list->tail != NULL);
    assert(list->head->prev == NULL && list->tail->next == NULL);
    assert(hlist_lpop(list) == (void *)s3);
    assert(hlist_lpop(list) == (void *)s2);
    assert(hlist_lpop(list) == (void *)s1);
    assert(hlist_rpop(list) == (void *)s1);
    assert(hlist_rpop(list) == (void *)s2);
    assert(hlist_rpop(list) == (void *)s3);
    assert(list->size == 0);
    hlist_free(list);
}

void
case_hlist_rpush()
{
    hlist_t *list = hlist_new();
    char *s1 = "s", *s2 = "s2", *s3 = "s3";
    assert(hlist_rpush(list, (void *)s1) == HLIST_OK);
    assert(hlist_rpush(list, (void *)s2) == HLIST_OK);
    assert(hlist_rpush(list, (void *)s3) == HLIST_OK);
    assert(hlist_rpush(list, (void *)s1) == HLIST_OK);
    assert(hlist_rpush(list, (void *)s2) == HLIST_OK);
    assert(hlist_rpush(list, (void *)s3) == HLIST_OK);
    assert(list->size == 6);
    assert(list->head != NULL && list->tail != NULL);
    assert(list->head->prev == NULL && list->tail->next == NULL);
    assert(hlist_rpop(list) == (void *)s3);
    assert(hlist_rpop(list) == (void *)s2);
    assert(hlist_rpop(list) == (void *)s1);
    assert(hlist_lpop(list) == (void *)s1);
    assert(hlist_lpop(list) == (void *)s2);
    assert(hlist_lpop(list) == (void *)s3);
    assert(list->size == 0);
    hlist_free(list);
}

void
case_hlist_lpop()
{

}
