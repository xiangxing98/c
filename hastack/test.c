#include <stdio.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "hastack.h"

typedef void (*case_t)();

static void test_case(const char *, case_t);

void case_hastack_new();
void case_hastack_free();
void case_hastack_clear();
void case_hastack_grow();
void case_hastack_push();
void case_hastack_pop();
void case_hastack_top();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("hastack_new", &case_hastack_new);
    test_case("hastack_free", &case_hastack_free);
    test_case("hastack_clear", &case_hastack_clear);
    test_case("hastack_grow", &case_hastack_grow);
    test_case("hastack_push", &case_hastack_push);
    test_case("hastack_pop", &case_hastack_pop);
    test_case("hastack_top", &case_hastack_top);
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_hastack_new()
{
    hastack_t *stack = hastack_new(10);
    assert(stack != NULL && stack->size == 0 &&
            stack->cap == 10 && stack->data != NULL);
    hastack_free(stack);
}

void
case_hastack_free()
{
    hastack_t *stack = hastack_new(10);
    hastack_free(stack);
}

void
case_hastack_clear()
{
    hastack_t *stack = hastack_new(10);
    int item = 1;
    hastack_push(stack, (void *)&item);
    hastack_clear(stack);
    assert(stack->size == 0 && stack->cap == 0 &&
            stack->data == NULL);
    hastack_free(stack);
}

void
case_hastack_grow()
{
    hastack_t *stack = hastack_new(10);
    assert(hastack_grow(stack, 20) == HASTACK_OK);
    assert(stack->data != NULL && stack->size == 0
            && stack->cap == 20);
    hastack_free(stack);
}

void
case_hastack_push()
{
    hastack_t *stack = hastack_new(0);
    char *s1 = "s1";
    char *s2 = "s2";
    assert(hastack_push(stack, (void *)s1) == HASTACK_OK);
    assert(hastack_push(stack, (void *)s2) == HASTACK_OK);
    assert(stack->size == 2 && stack->cap == 2);
    assert(hastack_top(stack) == s2);
    assert(hastack_pop(stack) == s2);
    assert(hastack_pop(stack) == s1);
    assert(stack->size == 0 && stack->cap == 2);
    hastack_free(stack);
}

void
case_hastack_pop()
{
    hastack_t *stack = hastack_new(8);
    char *s1 = "s1";
    char *s2 = "s2";
    assert(hastack_push(stack, (void *)s1) == HASTACK_OK);
    assert(hastack_push(stack, (void *)s2) == HASTACK_OK);
    assert(stack->size == 2 && stack->cap == 8);
    assert(hastack_pop(stack) == s2);
    assert(hastack_pop(stack) == s1);
    assert(stack->size == 0 && stack->cap == 8);
    hastack_free(stack);
}

void
case_hastack_top()
{
    hastack_t *stack = hastack_new(8);
    char *s1 = "s1";
    char *s2 = "s2";
    assert(hastack_push(stack, (void *)s1) == HASTACK_OK);
    assert(hastack_push(stack, (void *)s2) == HASTACK_OK);
    assert(hastack_top(stack) == s2);
    assert(hastack_pop(stack) == s2);
    assert(hastack_top(stack) == s1);
    assert(stack->size == 1 && stack->cap == 8);
    hastack_free(stack);
}
