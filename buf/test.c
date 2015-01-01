#include <assert.h>
#include <stdio.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "buf.h"

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    buf_t *buf = buf_new(1024);
    buf_putc(buf, 'c');
    buf_puts(buf, "hello");
    buf_print(buf);
    buf_free(buf);
    return 0;
}
