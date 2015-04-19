#include <stdio.h>
#ifdef __linux
#include <mcheck.h>
#endif
#include "dict.h"

typedef void (*case_t)();

static void test_case(const char *, case_t);

void case_dict_new();
void case_dict_free();
void case_dict_clear();
void case_dict_set_get_del_has_size();

int main(int argc, const char *argv[])
{
#ifdef __linux
    mtrace();
#endif

    test_case("dict_new", &case_dict_new);
    test_case("dict_free", &case_dict_free);
    test_case("dict_clear", &case_dict_clear);
    test_case("dict_set_get_del_has_size", &case_dict_set_get_del_has_size);
    return 0;
}

static void
test_case(const char *name, case_t case_func)
{
    case_func();
    printf("OK CASE(%s)\n", name);
}

void
case_dict_new()
{
    dict_t *dict = dict_new();
    assert(dict->size == 0 && dict->table_size_index == 0 &&
            dict->table != NULL);
    dict_free(dict);
}

void
case_dict_free()
{
    dict_t *dict = dict_new();
    dict_set(dict, (uint8_t *)"key1", 4, NULL);
    dict_set(dict, (uint8_t *)"key2", 4, NULL);
    dict_set(dict, (uint8_t *)"key3", 4, NULL);
    dict_set(dict, (uint8_t *)"key4", 4, NULL);
    dict_free(dict);
}

void
case_dict_clear()
{
    dict_t *dict = dict_new();
    dict_set(dict, (uint8_t *)"key1", 4, NULL);
    dict_set(dict, (uint8_t *)"key2", 4, NULL);
    dict_set(dict, (uint8_t *)"key3", 4, NULL);
    dict_set(dict, (uint8_t *)"key4", 4, NULL);
    assert(dict->size == 4);
    dict_clear(dict);
    assert(dict->size == 0);
    dict_free(dict);
}

void
case_dict_set_get_del_has_size()
{
    int val1 = 1, val2 = 2, val3 = 3, val4 = 4, val5 = 5,
        val6 = 6, val7 = 7, val8 = 8, val9 = 9;

    char *key1 = "key1", *key2 = "key2", *key3 = "key3", *key4 = "key4",
         *key5 = "key5", *key6 = "key6", *key7 = "key7", *key8 = "key8",
         *key9 = "key9";

    dict_t *dict = dict_new();

    /* dict_set */
    dict_set(dict, (uint8_t *)key1, strlen(key1), &val1);
    dict_set(dict, (uint8_t *)key2, strlen(key2), &val2);
    dict_set(dict, (uint8_t *)key3, strlen(key3), &val3);
    dict_set(dict, (uint8_t *)key4, strlen(key4), &val4);
    dict_set(dict, (uint8_t *)key5, strlen(key5), &val5);
    dict_set(dict, (uint8_t *)key6, strlen(key6), &val6);
    dict_set(dict, (uint8_t *)key7, strlen(key7), &val7);
    dict_set(dict, (uint8_t *)key8, strlen(key8), &val8);
    dict_set(dict, (uint8_t *)key9, strlen(key9), &val9);

    assert(dict->size == 9 && dict->table != NULL);

    /* dict_get */
    assert(dict_get(dict, (uint8_t *)key1, strlen(key1)) == &val1);
    assert(dict_get(dict, (uint8_t *)key2, strlen(key2)) == &val2);
    assert(dict_get(dict, (uint8_t *)key3, strlen(key3)) == &val3);
    assert(dict_get(dict, (uint8_t *)key4, strlen(key4)) == &val4);
    assert(dict_get(dict, (uint8_t *)key5, strlen(key5)) == &val5);
    assert(dict_get(dict, (uint8_t *)key6, strlen(key6)) == &val6);
    assert(dict_get(dict, (uint8_t *)key7, strlen(key7)) == &val7);
    assert(dict_get(dict, (uint8_t *)key8, strlen(key8)) == &val8);
    assert(dict_get(dict, (uint8_t *)key9, strlen(key9)) == &val9);

    /* dict_has */
    assert(dict_has(dict, (uint8_t *)key1, strlen(key1)) == true);
    assert(dict_has(dict, (uint8_t *)key2, strlen(key2)) == true);
    assert(dict_has(dict, (uint8_t *)key3, strlen(key3)) == true);
    assert(dict_has(dict, (uint8_t *)key4, strlen(key4)) == true);
    assert(dict_has(dict, (uint8_t *)key5, strlen(key5)) == true);
    assert(dict_has(dict, (uint8_t *)key6, strlen(key6)) == true);
    assert(dict_has(dict, (uint8_t *)key7, strlen(key7)) == true);
    assert(dict_has(dict, (uint8_t *)key8, strlen(key8)) == true);
    assert(dict_has(dict, (uint8_t *)key9, strlen(key9)) == true);

    assert(dict_size(dict) == 9);

    /* dict_del */
    assert(dict_del(dict, (uint8_t *)key1, strlen(key1)) == DICT_OK);
    assert(dict_del(dict, (uint8_t *)key2, strlen(key2)) == DICT_OK);
    assert(dict_del(dict, (uint8_t *)key3, strlen(key3)) == DICT_OK);
    assert(dict_del(dict, (uint8_t *)key4, strlen(key4)) == DICT_OK);
    assert(dict_has(dict, (uint8_t *)key1, strlen(key1)) == false);
    assert(dict_has(dict, (uint8_t *)key2, strlen(key2)) == false);
    assert(dict_has(dict, (uint8_t *)key3, strlen(key3)) == false);
    assert(dict_has(dict, (uint8_t *)key4, strlen(key4)) == false);

    assert(dict->size == 5 && dict->table != NULL);

    assert(dict_size(dict) == 5);

    dict_iterator_t *iterator = dict_iterator_new(dict);

    uint8_t *key;
    size_t key_len;
    void *val;

    while (dict_iterator_next(iterator, &key, &key_len, &val) == DICT_OK) {
        printf("%.*s => %d\n", (int)key_len, key, *(int *)val);
    }

    dict_iterator_free(iterator);

    dict_free(dict);
}
