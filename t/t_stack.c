#include <stdio.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "stack.h"

typedef void (*case_t)();

static void test_case(const char *, case_t);

void case_stk_new();
void case_stk_free();
void case_stk_clear();
void case_stk_grow();
void case_stk_push();
void case_stk_pop();
void case_stk_top();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("stk_new", &case_stk_new);
    test_case("stk_free", &case_stk_free);
    test_case("stk_clear", &case_stk_clear);
    test_case("stk_grow", &case_stk_grow);
    test_case("stk_push", &case_stk_push);
    test_case("stk_pop", &case_stk_pop);
    test_case("stk_top", &case_stk_top);
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_stk_new()
{
    stk_t *stack = stk_new(10);
    assert(stack != NULL && stack->size == 0 &&
            stack->cap == 10 && stack->data != NULL);
    stk_free(stack);
}

void
case_stk_free()
{
    stk_t *stack = stk_new(10);
    stk_free(stack);
}

void
case_stk_clear()
{
    stk_t *stack = stk_new(10);
    int item = 1;
    stk_push(stack, (void *)&item);
    stk_clear(stack);
    assert(stack->size == 0 && stack->cap == 0 &&
            stack->data == NULL);
    stk_free(stack);
}

void
case_stk_grow()
{
    stk_t *stack = stk_new(10);
    assert(stk_grow(stack, 20) == STK_OK);
    assert(stack->data != NULL && stack->size == 0
            && stack->cap == 20);
    stk_free(stack);
}

void
case_stk_push()
{
    stk_t *stack = stk_new(0);
    char *s1 = "s1";
    char *s2 = "s2";
    assert(stk_push(stack, (void *)s1) == STK_OK);
    assert(stk_push(stack, (void *)s2) == STK_OK);
    assert(stack->size == 2 && stack->cap == 2);
    assert(stk_top(stack) == s2);
    assert(stk_pop(stack) == s2);
    assert(stk_pop(stack) == s1);
    assert(stack->size == 0 && stack->cap == 2);
    stk_free(stack);
}

void
case_stk_pop()
{
    stk_t *stack = stk_new(8);
    char *s1 = "s1";
    char *s2 = "s2";
    assert(stk_push(stack, (void *)s1) == STK_OK);
    assert(stk_push(stack, (void *)s2) == STK_OK);
    assert(stack->size == 2 && stack->cap == 8);
    assert(stk_pop(stack) == s2);
    assert(stk_pop(stack) == s1);
    assert(stack->size == 0 && stack->cap == 8);
    stk_free(stack);
}

void
case_stk_top()
{
    stk_t *stack = stk_new(8);
    char *s1 = "s1";
    char *s2 = "s2";
    assert(stk_push(stack, (void *)s1) == STK_OK);
    assert(stk_push(stack, (void *)s2) == STK_OK);
    assert(stk_top(stack) == s2);
    assert(stk_pop(stack) == s2);
    assert(stk_top(stack) == s1);
    assert(stack->size == 1 && stack->cap == 8);
    stk_free(stack);
}
