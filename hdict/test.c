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
void case_hdict_set_get_del_has();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif

    test_case("hdict_new", &case_hdict_new);
    test_case("hdict_free", &case_hdict_free);
    test_case("hdict_clear", &case_hdict_clear);
    test_case("hdict_set_get_del_hash", &case_hdict_set_get_del_has);
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

void
case_hdict_set_get_del_has()
{
    int val1 = 1, val2 = 2, val3 = 3, val4 = 4, val5 = 5,
        val6 = 6, val7 = 7, val8 = 8, val9 = 9;

    char *key1 = "key1", *key2 = "key2", *key3 = "key3", *key4 = "key4",
         *key5 = "key5", *key6 = "key6", *key7 = "key7", *key8 = "key8",
         *key9 = "key9";

    hdict_t *dict = hdict_new();

    /* hdict_set */
    hdict_set(dict, (uint8_t *)key1, strlen(key1), &val1);
    hdict_set(dict, (uint8_t *)key2, strlen(key2), &val2);
    hdict_set(dict, (uint8_t *)key3, strlen(key3), &val3);
    hdict_set(dict, (uint8_t *)key4, strlen(key4), &val4);
    hdict_set(dict, (uint8_t *)key5, strlen(key5), &val5);
    hdict_set(dict, (uint8_t *)key6, strlen(key6), &val6);
    hdict_set(dict, (uint8_t *)key7, strlen(key7), &val7);
    hdict_set(dict, (uint8_t *)key8, strlen(key8), &val8);
    hdict_set(dict, (uint8_t *)key9, strlen(key9), &val9);

    assert(dict->size == 9 && dict->table != NULL);

    /* hdict_get */
    assert(hdict_get(dict, (uint8_t *)key1, strlen(key1)) == &val1);
    assert(hdict_get(dict, (uint8_t *)key2, strlen(key2)) == &val2);
    assert(hdict_get(dict, (uint8_t *)key3, strlen(key3)) == &val3);
    assert(hdict_get(dict, (uint8_t *)key4, strlen(key4)) == &val4);
    assert(hdict_get(dict, (uint8_t *)key5, strlen(key5)) == &val5);
    assert(hdict_get(dict, (uint8_t *)key6, strlen(key6)) == &val6);
    assert(hdict_get(dict, (uint8_t *)key7, strlen(key7)) == &val7);
    assert(hdict_get(dict, (uint8_t *)key8, strlen(key8)) == &val8);
    assert(hdict_get(dict, (uint8_t *)key9, strlen(key9)) == &val9);

    /* hdict_has */
    assert(hdict_has(dict, (uint8_t *)key1, strlen(key1)) == HDICT_OK);
    assert(hdict_has(dict, (uint8_t *)key2, strlen(key2)) == HDICT_OK);
    assert(hdict_has(dict, (uint8_t *)key3, strlen(key3)) == HDICT_OK);
    assert(hdict_has(dict, (uint8_t *)key4, strlen(key4)) == HDICT_OK);
    assert(hdict_has(dict, (uint8_t *)key5, strlen(key5)) == HDICT_OK);
    assert(hdict_has(dict, (uint8_t *)key6, strlen(key6)) == HDICT_OK);
    assert(hdict_has(dict, (uint8_t *)key7, strlen(key7)) == HDICT_OK);
    assert(hdict_has(dict, (uint8_t *)key8, strlen(key8)) == HDICT_OK);
    assert(hdict_has(dict, (uint8_t *)key9, strlen(key9)) == HDICT_OK);

    /* hdict_del */
    assert(hdict_del(dict, (uint8_t *)key1, strlen(key1)) == HDICT_OK);
    assert(hdict_del(dict, (uint8_t *)key2, strlen(key2)) == HDICT_OK);
    assert(hdict_del(dict, (uint8_t *)key3, strlen(key3)) == HDICT_OK);
    assert(hdict_del(dict, (uint8_t *)key4, strlen(key4)) == HDICT_OK);
    assert(hdict_has(dict, (uint8_t *)key1, strlen(key1)) == HDICT_ENOTFOUND);
    assert(hdict_has(dict, (uint8_t *)key2, strlen(key2)) == HDICT_ENOTFOUND);
    assert(hdict_has(dict, (uint8_t *)key3, strlen(key3)) == HDICT_ENOTFOUND);
    assert(hdict_has(dict, (uint8_t *)key4, strlen(key4)) == HDICT_ENOTFOUND);

    assert(dict->size == 5 && dict->table != NULL);

    hdict_free(dict);
}
