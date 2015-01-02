#include <stdio.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "stack.h"

typedef void (*case_t)();

static void test_case(const char *, case_t);

void case_stack_new();
void case_stack_free();
void case_stack_clear();
void case_stack_grow();
void case_stack_push();
void case_stack_pop();
void case_stack_top();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("stack_new", &case_stack_new);
    test_case("stack_free", &case_stack_free);
    test_case("stack_clear", &case_stack_clear);
    test_case("stack_grow", &case_stack_grow);
    test_case("stack_push", &case_stack_push);
    test_case("stack_pop", &case_stack_pop);
    test_case("stack_top", &case_stack_top);
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_stack_new()
{
    stack_t *stack = stack_new(10);
    assert(stack != NULL && stack->size == 0 &&
            stack->cap == 10 && stack->data != NULL);
    stack_free(stack);
}

void
case_stack_free()
{
    stack_t *stack = stack_new(10);
    stack_free(stack);
}

void
case_stack_clear()
{
    stack_t *stack = stack_new(10);
    int item = 1;
    stack_push(stack, (void *)&item);
    stack_clear(stack);
    assert(stack->size == 0 && stack->cap == 0 &&
            stack->data == NULL);
    stack_free(stack);
}

void
case_stack_grow()
{
    stack_t *stack = stack_new(10);
    assert(stack_grow(stack, 20) == STACK_OK);
    assert(stack->data != NULL && stack->size == 0
            && stack->cap == 20);
    stack_free(stack);
}

void
case_stack_push()
{
    stack_t *stack = stack_new(0);
    char *s1 = "s1";
    char *s2 = "s2";
    assert(stack_push(stack, (void *)s1) == STACK_OK);
    assert(stack_push(stack, (void *)s2) == STACK_OK);
    assert(stack->size == 2 && stack->cap == 2);
    assert(stack_top(stack) == s2);
    assert(stack_pop(stack) == s2);
    assert(stack_pop(stack) == s1);
    assert(stack->size == 0 && stack->cap == 2);
    stack_free(stack);
}

void
case_stack_pop()
{
    stack_t *stack = stack_new(8);
    char *s1 = "s1";
    char *s2 = "s2";
    assert(stack_push(stack, (void *)s1) == STACK_OK);
    assert(stack_push(stack, (void *)s2) == STACK_OK);
    assert(stack->size == 2 && stack->cap == 8);
    assert(stack_pop(stack) == s2);
    assert(stack_pop(stack) == s1);
    assert(stack->size == 0 && stack->cap == 8);
    stack_free(stack);
}

void
case_stack_top()
{
    stack_t *stack = stack_new(8);
    char *s1 = "s1";
    char *s2 = "s2";
    assert(stack_push(stack, (void *)s1) == STACK_OK);
    assert(stack_push(stack, (void *)s2) == STACK_OK);
    assert(stack_top(stack) == s2);
    assert(stack_pop(stack) == s2);
    assert(stack_top(stack) == s1);
    assert(stack->size == 1 && stack->cap == 8);
    stack_free(stack);
}
