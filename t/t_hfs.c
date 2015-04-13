#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "hfs.h"

#define BUF_UNIT 128
#define FILE_READ_BUF_UNIT 1024

typedef void (*case_t)();

void case_hfs_open();
void case_hfs_close();
void case_hfs_touch();
void case_hfs_remove();
void case_hfs_read();
void case_hfs_write();
void case_hfs_append();
void case_hfs_exists();
void case_hfs_isdir();
void case_hfs_isfile();
void case_hfs_rename();
void case_hfs_mkdir();
void case_hfs_rename();
void case_hfs_mkdir();

static void test_case(const char *, case_t);

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("hfs_open", &case_hfs_open);
    test_case("hfs_close", &case_hfs_close);
    test_case("hfs_touch", &case_hfs_touch);
    test_case("hfs_remove", &case_hfs_remove);
    test_case("hfs_read", &case_hfs_read);
    test_case("hfs_write", &case_hfs_write);
    test_case("hfs_append", &case_hfs_append);
    test_case("hfs_exists", &case_hfs_exists);
    test_case("hfs_isdir", &case_hfs_isdir);
    test_case("hfs_isfile", &case_hfs_isfile);
    test_case("hfs_rename", &case_hfs_rename);
    /* test_case("hfs_mkdir", &case_hfs_mkdir); */
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_hfs_open()
{
    assert(hfs_touch("hfs_") == HFS_OK &&
            hfs_exists("hfs_") == true);

    hfs_t *stream = hfs_open("hfs_", "r");
    assert(stream != NULL);
    hfs_close(stream);

    assert(hfs_remove("hfs_") == HFS_OK &&
            hfs_exists("hfs_") == false);
}

void
case_hfs_close()
{
    assert(hfs_touch("hfs_") == HFS_OK &&
            hfs_exists("hfs_") == true);

    hfs_t *stream = hfs_open("hfs_", "r");
    hfs_close(stream);

    assert(hfs_remove("hfs_") == HFS_OK &&
            hfs_exists("hfs_") == false);
}

void
case_hfs_touch()
{
    assert(hfs_touch("hfs_") == HFS_OK &&
            hfs_exists("hfs_") == true);
    assert(hfs_remove("hfs_") == HFS_OK &&
            hfs_exists("hfs_") == false);
}

void
case_hfs_remove()
{
    assert(hfs_touch("hfs_") == HFS_OK &&
            hfs_exists("hfs_") == true);
    assert(hfs_remove("hfs_") == HFS_OK &&
            hfs_exists("hfs_") == false);
}

void
case_hfs_read()
{
    hbuf_t *buf = hbuf_new(BUF_UNIT);
    hbuf_puts(buf, "hello world");

    assert(hfs_write("hfs_", buf) == HFS_OK);

    hbuf_clear(buf);

    assert(hfs_read(buf, "hfs_", FILE_READ_BUF_UNIT) == HFS_OK);
    assert(strcmp(hbuf_str(buf), "hello world") == 0);
    assert(hfs_remove("hfs_") == HFS_OK &&
            hfs_exists("hfs_") == false);

    hbuf_free(buf);
}

void
case_hfs_write()
{
    hbuf_t *buf = hbuf_new(BUF_UNIT);
    hbuf_puts(buf, "你好世界！");

    assert(hfs_write("hfs_", buf) == HFS_OK);
    assert(hfs_isfile("hfs_") == true);

    hbuf_clear(buf);

    assert(hfs_read(buf, "hfs_", FILE_READ_BUF_UNIT) == HFS_OK);
    assert(strcmp(hbuf_str(buf), "你好世界！") == 0);

    assert(hfs_remove("hfs_") == HFS_OK &&
            hfs_exists("hfs_") == false);
    hbuf_free(buf);
}

void
case_hfs_append()
{
    hbuf_t *buf = hbuf_new(BUF_UNIT);
    hbuf_puts(buf, "abc");

    assert(hfs_append("hfs_", buf) == HFS_OK &&
            hfs_isfile("hfs_") == true);
    assert(hfs_append("hfs_", buf) == HFS_OK &&
            hfs_isfile("hfs_") == true);

    hbuf_clear(buf);

    assert(hfs_read(buf, "hfs_", FILE_READ_BUF_UNIT) == HFS_OK);
    assert(strcmp(hbuf_str(buf), "abcabc") == 0);

    assert(hfs_remove("hfs_") == HFS_OK &&
            hfs_exists("hfs_") == false);
    hbuf_free(buf);
}

void
case_hfs_exists()
{
    assert(hfs_exists("hfs_") == false);
    assert(hfs_touch("hfs_") == HFS_OK &&
            hfs_exists("hfs_") == true);
}

void
case_hfs_isdir()
{
    assert(hfs_isdir("./") == true);
    assert(hfs_isdir("./hfs_") == false);
}

void
case_hfs_isfile()
{
    assert(hfs_isfile("./") == false);
    assert(hfs_touch("hfs_") == HFS_OK &&
            hfs_isfile("hfs_") == true);
    assert(hfs_remove("hfs_") == HFS_OK);
}

void
case_hfs_rename()
{
    assert(hfs_touch("hfs_") == HFS_OK &&
            hfs_isfile("hfs_") == true);
    assert(hfs_rename("hfs_", "hfs__") == HFS_OK &&
            hfs_exists("hfs_") == false &&
            hfs_exists("hfs__") == true);
    assert(hfs_remove("hfs__") == HFS_OK);
}

void
case_hfs_mkdir()
{
    assert(hfs_mkdir("hfs_", 777) == HFS_OK);
    assert(hfs_touch("hfs_/hfs") == HFS_OK);
    assert(hfs_rmdir("hfs_") == HFS_OK);
}
