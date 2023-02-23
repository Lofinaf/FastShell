#include "../include/unit.h"

void test_startWith() {
    assert(startWith("hello world", "hello") == 1);
    assert(startWith("hello world", "world") == 0);
    assert(startWith("hello world", "") == 1);
}

void test_getClipBoard() {
    char* clipboard = getClipBoard();
    assert(clipboard != NULL);
}

void test() {
	test_startWith();
    test_getClipBoard();
    printf("All tests passed successfully!\n");
}