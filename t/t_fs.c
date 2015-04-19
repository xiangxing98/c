#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "fs.h"

#define BUF_UNIT 128
#define FILE_READ_BUF_UNIT 1024

typedef void (*case_t)();

void case_fs_open();
void case_fs_close();
void case_fs_touch();
void case_fs_remove();
void case_fs_read();
void case_fs_write();
void case_fs_append();
void case_fs_exists();
void case_fs_isdir();
void case_fs_isfile();
void case_fs_rename();
void case_fs_mkdir();
void case_fs_rename();
void case_fs_mkdir();

static void test_case(const char *, case_t);

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("fs_open", &case_fs_open);
    test_case("fs_close", &case_fs_close);
    test_case("fs_touch", &case_fs_touch);
    test_case("fs_remove", &case_fs_remove);
    test_case("fs_read", &case_fs_read);
    test_case("fs_write", &case_fs_write);
    test_case("fs_append", &case_fs_append);
    test_case("fs_exists", &case_fs_exists);
    test_case("fs_isdir", &case_fs_isdir);
    test_case("fs_isfile", &case_fs_isfile);
    test_case("fs_rename", &case_fs_rename);
    /* test_case("fs_mkdir", &case_fs_mkdir); */
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_fs_open()
{
    assert(fs_touch("fs_") == FS_OK &&
            fs_exists("fs_") == true);

    fs_t *stream = fs_open("fs_", "r");
    assert(stream != NULL);
    fs_close(stream);

    assert(fs_remove("fs_") == FS_OK &&
            fs_exists("fs_") == false);
}

void
case_fs_close()
{
    assert(fs_touch("fs_") == FS_OK &&
            fs_exists("fs_") == true);

    fs_t *stream = fs_open("fs_", "r");
    fs_close(stream);

    assert(fs_remove("fs_") == FS_OK &&
            fs_exists("fs_") == false);
}

void
case_fs_touch()
{
    assert(fs_touch("fs_") == FS_OK &&
            fs_exists("fs_") == true);
    assert(fs_remove("fs_") == FS_OK &&
            fs_exists("fs_") == false);
}

void
case_fs_remove()
{
    assert(fs_touch("fs_") == FS_OK &&
            fs_exists("fs_") == true);
    assert(fs_remove("fs_") == FS_OK &&
            fs_exists("fs_") == false);
}

void
case_fs_read()
{
    buf_t *buf = buf_new(BUF_UNIT);
    buf_puts(buf, "hello world");

    assert(fs_write("fs_", buf) == FS_OK);

    buf_clear(buf);

    assert(fs_read(buf, "fs_", FILE_READ_BUF_UNIT) == FS_OK);
    assert(strcmp(buf_str(buf), "hello world") == 0);
    assert(fs_remove("fs_") == FS_OK &&
            fs_exists("fs_") == false);

    buf_free(buf);
}

void
case_fs_write()
{
    buf_t *buf = buf_new(BUF_UNIT);
    buf_puts(buf, "你好世界！");

    assert(fs_write("fs_", buf) == FS_OK);
    assert(fs_isfile("fs_") == true);

    buf_clear(buf);

    assert(fs_read(buf, "fs_", FILE_READ_BUF_UNIT) == FS_OK);
    assert(strcmp(buf_str(buf), "你好世界！") == 0);

    assert(fs_remove("fs_") == FS_OK &&
            fs_exists("fs_") == false);
    buf_free(buf);
}

void
case_fs_append()
{
    buf_t *buf = buf_new(BUF_UNIT);
    buf_puts(buf, "abc");

    assert(fs_append("fs_", buf) == FS_OK &&
            fs_isfile("fs_") == true);
    assert(fs_append("fs_", buf) == FS_OK &&
            fs_isfile("fs_") == true);

    buf_clear(buf);

    assert(fs_read(buf, "fs_", FILE_READ_BUF_UNIT) == FS_OK);
    assert(strcmp(buf_str(buf), "abcabc") == 0);

    assert(fs_remove("fs_") == FS_OK &&
            fs_exists("fs_") == false);
    buf_free(buf);
}

void
case_fs_exists()
{
    assert(fs_exists("fs_") == false);
    assert(fs_touch("fs_") == FS_OK &&
            fs_exists("fs_") == true);
}

void
case_fs_isdir()
{
    assert(fs_isdir("./") == true);
    assert(fs_isdir("./fs_") == false);
}

void
case_fs_isfile()
{
    assert(fs_isfile("./") == false);
    assert(fs_touch("fs_") == FS_OK &&
            fs_isfile("fs_") == true);
    assert(fs_remove("fs_") == FS_OK);
}

void
case_fs_rename()
{
    assert(fs_touch("fs_") == FS_OK &&
            fs_isfile("fs_") == true);
    assert(fs_rename("fs_", "fs__") == FS_OK &&
            fs_exists("fs_") == false &&
            fs_exists("fs__") == true);
    assert(fs_remove("fs__") == FS_OK);
}

void
case_fs_mkdir()
{
    assert(fs_mkdir("fs_", 777) == FS_OK);
    assert(fs_touch("fs_/fs") == FS_OK);
    assert(fs_rmdir("fs_") == FS_OK);
}
