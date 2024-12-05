#include "index.h"

void
dict_test(void) {
    printf("<dict_test>\n");

    dict_t *dict = dict_new_with((destructor_t *) string_destroy);

    dict_set(dict, "a", string_dup("A"));
    dict_set(dict, "b", string_dup("B"));
    dict_set(dict, "c", string_dup("C"));

    assert(dict_has(dict, "a"));
    assert(dict_has(dict, "b"));
    assert(dict_has(dict, "c"));
    assert(!dict_has(dict, "d"));

    assert(string_equal(dict_get(dict, "a"), "A"));
    assert(string_equal(dict_get(dict, "b"), "B"));
    assert(string_equal(dict_get(dict, "c"), "C"));

    dict_destroy(&dict);

    printf("</dict_test>\n");
}