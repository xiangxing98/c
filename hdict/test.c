#include <stdio.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "hdict.h"

typedef void (*case_t)();

static void test_case(const char *, case_t);

void case_hdict_new();
void case_hdict_free();
void case_hdict_clear();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif

    test_case("hdict_new", &case_hdict_new);
    test_case("hdict_free", &case_hdict_free);
    test_case("hdict_clear", &case_hdict_clear);
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_hdict_new()
{
    hdict_t *dict = hdict_new();
    assert(dict->size == 0 && dict->table_size_index == 0 &&
            dict->table != NULL);
    hdict_free(dict);
}

void
case_hdict_free()
{
    hdict_t *dict = hdict_new();
    hdict_set(dict, (uint8_t *)"key1", 4, NULL);
    hdict_set(dict, (uint8_t *)"key2", 4, NULL);
    hdict_set(dict, (uint8_t *)"key3", 4, NULL);
    hdict_set(dict, (uint8_t *)"key4", 4, NULL);
    hdict_free(dict);
}

void
case_hdict_clear()
{
    hdict_t *dict = hdict_new();
    hdict_set(dict, (uint8_t *)"key1", 4, NULL);
    hdict_set(dict, (uint8_t *)"key2", 4, NULL);
    hdict_set(dict, (uint8_t *)"key3", 4, NULL);
    hdict_set(dict, (uint8_t *)"key4", 4, NULL);
    assert(dict->size == 4);
    hdict_clear(dict);
    assert(dict->size == 0);
    hdict_free(dict);
}
