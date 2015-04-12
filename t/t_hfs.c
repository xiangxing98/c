#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "hfs.h"

#define FILE_READ_BUF_UNIT 1024

typedef void (*case_t)();

void case_hfs_open();
void case_hfs_close();
void case_hfs_touch();

static void test_case(const char *, case_t);

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif
    test_case("hfs_open", &case_hfs_open);
    test_case("hfs_close", &case_hfs_close);
    test_case("hfs_touch", &case_hfs_touch);
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
    hfs_t *stream = hfs_open("hfs_open", "r");
    assert(stream != NULL);
    hfs_close(stream);
}

void
case_hfs_close()
{
    hfs_t *stream = hfs_open("hfs_close", "r");
    hfs_close(stream);
}

void
case_hfs_touch()
{
    assert(hfs_touch("hfs_touch") == HFS_OK);
}
