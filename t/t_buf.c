#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "buf.h"

#define BUF_UNIT 8

typedef void (*case_t)();

static void test_case(const char *, case_t);

void case_buf_new();
void case_buf_free();
void case_buf_clear();
void case_buf_grow();
void case_buf_str();
void case_buf_put();
void case_buf_putc();
void case_buf_puts();
void case_buf_lrm();
void case_buf_rrm();
void case_buf_sprintf();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("buf_new", &case_buf_new);
    test_case("buf_free", &case_buf_free);
    test_case("buf_clear", &case_buf_clear);
    test_case("buf_grow", &case_buf_grow);
    test_case("buf_str", &case_buf_str);
    test_case("buf_put", &case_buf_put);
    test_case("buf_putc", &case_buf_putc);
    test_case("buf_puts", &case_buf_puts);
    test_case("buf_lrm", &case_buf_lrm);
    test_case("buf_rrm", &case_buf_rrm);
    test_case("buf_sprintf", &case_buf_sprintf);
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_buf_new()
{
    buf_t *buf = buf_new(BUF_UNIT);
    assert(buf != NULL && buf->unit != 0);
    buf_free(buf);
}

void
case_buf_free()
{
    buf_t *buf = buf_new(BUF_UNIT);
    buf_free(buf);
}

void
case_buf_clear()
{
    buf_t *buf = buf_new(BUF_UNIT);
    buf_puts(buf, "test_buf_clear");
    buf_clear(buf);
    assert(buf->size == 0 && buf->size == 0 && buf->cap == 0);
    buf_free(buf);
}


void
case_buf_grow()
{
    buf_t *buf = buf_new(BUF_UNIT);
    buf_grow(buf, BUF_UNIT * 2);
    assert(buf->size == 0 && buf->cap >= BUF_UNIT * 2);
    buf_free(buf);
}


void
case_buf_str()
{
    buf_t *buf = buf_new(BUF_UNIT);
    char *str = "test_buf_str";
    assert(buf_puts(buf, str) == BUF_OK);
    assert(strcmp(buf_str(buf), str) == 0);
    buf_free(buf);
}

void
case_buf_put()
{
    buf_t *buf1 = buf_new(BUF_UNIT);
    buf_t *buf2 = buf_new(BUF_UNIT);
    char *str = "test_buf_put";
    assert(buf_puts(buf1, str) == BUF_OK);
    assert(buf_put(buf2, buf1->data, buf1->size) == BUF_OK);
    buf_free(buf1);
    buf_free(buf2);
}

void
case_buf_putc()
{
    buf_t *buf = buf_new(BUF_UNIT);
    assert(buf_putc(buf, 'c') == BUF_OK);
    assert(buf_putc(buf, 'h') == BUF_OK);
    assert(strcmp(buf_str(buf), "ch") == 0);
    buf_free(buf);
}

void
case_buf_puts()
{
    buf_t *buf = buf_new(BUF_UNIT);
    assert(buf_puts(buf, "hello") == BUF_OK);
    assert(buf_puts(buf, "world") == BUF_OK);
    assert(strcmp(buf_str(buf), "helloworld") == 0);
    buf_free(buf);
}

void
case_buf_lrm()
{
    buf_t *buf = buf_new(BUF_UNIT);
    assert(buf_puts(buf, "hihello") == BUF_OK);
    buf_lrm(buf, 2);
    assert(strcmp(buf_str(buf), "hello") == 0);
    buf_lrm(buf, 100);
    assert(strcmp(buf_str(buf), "") == 0);
    buf_free(buf);
}

void
case_buf_rrm()
{
    buf_t *buf = buf_new(BUF_UNIT);
    assert(buf_puts(buf, "hellohi") == BUF_OK);
    buf_rrm(buf, 2);
    assert(strcmp(buf_str(buf), "hello") == 0);
    buf_rrm(buf, 100);
    assert(strcmp(buf_str(buf), "") == 0);
    buf_free(buf);
}

void
case_buf_sprintf()
{
    buf_t *buf = buf_new(BUF_UNIT);
    buf_sprintf(buf, "Hello %s!", "World");
    assert(buf->size == 12);
    assert(strcmp(buf_str(buf), "Hello World!") == 0);
    buf_free(buf);
}