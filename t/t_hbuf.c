#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "hbuf.h"

#define HBUF_UNIT 8

typedef void (*case_t)();

static void test_case(const char *, case_t);

void case_hbuf_new();
void case_hbuf_free();
void case_hbuf_clear();
void case_hbuf_grow();
void case_hbuf_str();
void case_hbuf_put();
void case_hbuf_putc();
void case_hbuf_puts();
void case_hbuf_lrm();
void case_hbuf_rrm();
void case_hbuf_sprintf();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("hbuf_new", &case_hbuf_new);
    test_case("hbuf_free", &case_hbuf_free);
    test_case("hbuf_clear", &case_hbuf_clear);
    test_case("hbuf_grow", &case_hbuf_grow);
    test_case("hbuf_str", &case_hbuf_str);
    test_case("hbuf_put", &case_hbuf_put);
    test_case("hbuf_putc", &case_hbuf_putc);
    test_case("hbuf_puts", &case_hbuf_puts);
    test_case("hbuf_lrm", &case_hbuf_lrm);
    test_case("hbuf_rrm", &case_hbuf_rrm);
    test_case("hbuf_sprintf", &case_hbuf_sprintf);
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_hbuf_new()
{
    hbuf_t *buf = hbuf_new(HBUF_UNIT);
    assert(buf != NULL && buf->unit != 0);
    hbuf_free(buf);
}

void
case_hbuf_free()
{
    hbuf_t *buf = hbuf_new(HBUF_UNIT);
    hbuf_free(buf);
}

void
case_hbuf_clear()
{
    hbuf_t *buf = hbuf_new(HBUF_UNIT);
    hbuf_puts(buf, "test_hbuf_clear");
    hbuf_clear(buf);
    assert(buf->size == 0 && buf->size == 0 && buf->cap == 0);
    hbuf_free(buf);
}


void
case_hbuf_grow()
{
    hbuf_t *buf = hbuf_new(HBUF_UNIT);
    hbuf_grow(buf, HBUF_UNIT * 2);
    assert(buf->size == 0 && buf->cap >= HBUF_UNIT * 2);
    hbuf_free(buf);
}


void
case_hbuf_str()
{
    hbuf_t *buf = hbuf_new(HBUF_UNIT);
    char *str = "test_hbuf_str";
    assert(hbuf_puts(buf, str) == HBUF_OK);
    assert(strcmp(hbuf_str(buf), str) == 0);
    hbuf_free(buf);
}

void
case_hbuf_put()
{
    hbuf_t *buf1 = hbuf_new(HBUF_UNIT);
    hbuf_t *buf2 = hbuf_new(HBUF_UNIT);
    char *str = "test_hbuf_put";
    assert(hbuf_puts(buf1, str) == HBUF_OK);
    assert(hbuf_put(buf2, buf1->data, buf1->size) == HBUF_OK);
    hbuf_free(buf1);
    hbuf_free(buf2);
}

void
case_hbuf_putc()
{
    hbuf_t *buf = hbuf_new(HBUF_UNIT);
    assert(hbuf_putc(buf, 'c') == HBUF_OK);
    assert(hbuf_putc(buf, 'h') == HBUF_OK);
    assert(strcmp(hbuf_str(buf), "ch") == 0);
    hbuf_free(buf);
}

void
case_hbuf_puts()
{
    hbuf_t *buf = hbuf_new(HBUF_UNIT);
    assert(hbuf_puts(buf, "hello") == HBUF_OK);
    assert(hbuf_puts(buf, "world") == HBUF_OK);
    assert(strcmp(hbuf_str(buf), "helloworld") == 0);
    hbuf_free(buf);
}

void
case_hbuf_lrm()
{
    hbuf_t *buf = hbuf_new(HBUF_UNIT);
    assert(hbuf_puts(buf, "hihello") == HBUF_OK);
    hbuf_lrm(buf, 2);
    assert(strcmp(hbuf_str(buf), "hello") == 0);
    hbuf_lrm(buf, 100);
    assert(strcmp(hbuf_str(buf), "") == 0);
    hbuf_free(buf);
}

void
case_hbuf_rrm()
{
    hbuf_t *buf = hbuf_new(HBUF_UNIT);
    assert(hbuf_puts(buf, "hellohi") == HBUF_OK);
    hbuf_rrm(buf, 2);
    assert(strcmp(hbuf_str(buf), "hello") == 0);
    hbuf_rrm(buf, 100);
    assert(strcmp(hbuf_str(buf), "") == 0);
    hbuf_free(buf);
}

void
case_hbuf_sprintf()
{
    hbuf_t *buf = hbuf_new(HBUF_UNIT);
    hbuf_sprintf(buf, "Hello %s!", "World");
    assert(buf->size == 12);
    assert(strcmp(hbuf_str(buf), "Hello World!") == 0);
    hbuf_free(buf);
}
