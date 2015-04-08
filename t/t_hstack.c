#include <stdio.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "hstack.h"

typedef void (*case_t)();

static void test_case(const char *, case_t);

void case_hstack_new();
void case_hstack_free();
void case_hstack_clear();
void case_hstack_grow();
void case_hstack_push();
void case_hstack_pop();
void case_hstack_top();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("hstack_new", &case_hstack_new);
    test_case("hstack_free", &case_hstack_free);
    test_case("hstack_clear", &case_hstack_clear);
    test_case("hstack_grow", &case_hstack_grow);
    test_case("hstack_push", &case_hstack_push);
    test_case("hstack_pop", &case_hstack_pop);
    test_case("hstack_top", &case_hstack_top);
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_hstack_new()
{
    hstack_t *stack = hstack_new(10);
    assert(stack != NULL && stack->size == 0 &&
            stack->cap == 10 && stack->data != NULL);
    hstack_free(stack);
}

void
case_hstack_free()
{
    hstack_t *stack = hstack_new(10);
    hstack_free(stack);
}

void
case_hstack_clear()
{
    hstack_t *stack = hstack_new(10);
    int item = 1;
    hstack_push(stack, (void *)&item);
    hstack_clear(stack);
    assert(stack->size == 0 && stack->cap == 0 &&
            stack->data == NULL);
    hstack_free(stack);
}

void
case_hstack_grow()
{
    hstack_t *stack = hstack_new(10);
    assert(hstack_grow(stack, 20) == HSTACK_OK);
    assert(stack->data != NULL && stack->size == 0
            && stack->cap == 20);
    hstack_free(stack);
}

void
case_hstack_push()
{
    hstack_t *stack = hstack_new(0);
    char *s1 = "s1";
    char *s2 = "s2";
    assert(hstack_push(stack, (void *)s1) == HSTACK_OK);
    assert(hstack_push(stack, (void *)s2) == HSTACK_OK);
    assert(stack->size == 2 && stack->cap == 2);
    assert(hstack_top(stack) == s2);
    assert(hstack_pop(stack) == s2);
    assert(hstack_pop(stack) == s1);
    assert(stack->size == 0 && stack->cap == 2);
    hstack_free(stack);
}

void
case_hstack_pop()
{
    hstack_t *stack = hstack_new(8);
    char *s1 = "s1";
    char *s2 = "s2";
    assert(hstack_push(stack, (void *)s1) == HSTACK_OK);
    assert(hstack_push(stack, (void *)s2) == HSTACK_OK);
    assert(stack->size == 2 && stack->cap == 8);
    assert(hstack_pop(stack) == s2);
    assert(hstack_pop(stack) == s1);
    assert(stack->size == 0 && stack->cap == 8);
    hstack_free(stack);
}

void
case_hstack_top()
{
    hstack_t *stack = hstack_new(8);
    char *s1 = "s1";
    char *s2 = "s2";
    assert(hstack_push(stack, (void *)s1) == HSTACK_OK);
    assert(hstack_push(stack, (void *)s2) == HSTACK_OK);
    assert(hstack_top(stack) == s2);
    assert(hstack_pop(stack) == s2);
    assert(hstack_top(stack) == s1);
    assert(stack->size == 1 && stack->cap == 8);
    hstack_free(stack);
}
