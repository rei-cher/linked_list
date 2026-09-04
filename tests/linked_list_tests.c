/**
 * Linked list test suite
 */

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

static char p_buff[512] = { 0 };
static int  print_idx   = 0;

int my_strcmp(const void * p_str1, const void * p_str2)
{
    return strcmp((const char *)p_str1, (const char *)p_str2);
}

void my_print(void * data)
{
    print_idx += snprintf(
        p_buff + print_idx, sizeof(p_buff) - print_idx, "%d -> ", *(int *)data);
}

void my_assert_string(const char * p_expected, const char * p_actual)
{
    if (strcmp(p_expected, p_actual) != 0)
    {
        fprintf(stderr,
                "\n  Expected: \"%s\"\n  Got:      \"%s\"\n",
                p_expected,
                p_actual);
    }

    CU_ASSERT_STRING_EQUAL(p_expected, p_actual);

    memset(p_buff, 0, sizeof(p_buff));
    print_idx = 0;
}

void add_one(void * p_data)
{
    int * p_int = (int *)p_data;
    (*p_int)++;
}

void test_create_destroy_empty()
{
    llist_t * p_list = llist_create();
    CU_ASSERT_PTR_NOT_NULL(p_list);
    llist_destroy(&p_list, NULL);
    CU_ASSERT_PTR_NULL(p_list);

    llist_t * p_list2 = llist_create();
    CU_ASSERT_PTR_NOT_NULL(p_list2);
    llist_destroy(&p_list2, free);
    CU_ASSERT_PTR_NULL(p_list2);

    llist_destroy(NULL, NULL);

    llist_t * p_list3 = NULL;
    llist_destroy(&p_list3, NULL);
    CU_ASSERT_PTR_NULL(p_list3);
}

void test_basic_queue()
{
    llist_t * p_list = llist_create();
    llist_enqueue(p_list, "hello");
    llist_enqueue(p_list, "hello1");
    llist_enqueue(p_list, "hello2");
    my_assert_string("hello", llist_dequeue(p_list));
    my_assert_string("hello1", llist_dequeue(p_list));
    my_assert_string("hello2", llist_dequeue(p_list));
    llist_destroy(&p_list, NULL);
}

void test_basic_stack()
{
    llist_t * p_list = llist_create();
    llist_push(p_list, "hello");
    llist_push(p_list, "hello1");
    llist_push(p_list, "hello2");
    my_assert_string("hello2", llist_pop(p_list));
    my_assert_string("hello1", llist_pop(p_list));
    my_assert_string("hello", llist_pop(p_list));
    llist_destroy(&p_list, NULL);
}

void test_advanced_queue()
{
    llist_t * p_list = llist_create();

    for (int idx = 0; idx < 1000000; idx++)
    {
        char * p_buff = malloc(12);
        snprintf(p_buff, 12, "str%08d", idx);
        llist_enqueue(p_list, p_buff);
    }

    for (int idx = 0; idx < 1000000; idx++)
    {
        snprintf(p_buff, sizeof(p_buff), "str%08d", idx);
        char * p_tmp = llist_dequeue(p_list);
        my_assert_string(p_buff, p_tmp);
        free(p_tmp);
    }

    llist_destroy(&p_list, NULL);
}

void test_advanced_stack()
{
    llist_t * p_list = llist_create();

    char p_buff[12] = "\0";

    for (int idx = 0; idx < 1000000; idx++)
    {
        char * p_buff = malloc(12);
        snprintf(p_buff, 12, "str%08d", idx);
        llist_push(p_list, p_buff);
    }

    for (int idx = 999999; idx > -1; idx--)
    {
        snprintf(p_buff, sizeof(p_buff), "str%08d", idx);
        char * p_tmp = llist_pop(p_list);
        my_assert_string(p_buff, p_tmp);
        free(p_tmp);
    }

    llist_destroy(&p_list, NULL);
}

void test_stack_alloc_cleanup()
{
    llist_t * p_list = llist_create();
    llist_push(p_list, "hello");
    llist_push(p_list, "hello1");
    llist_push(p_list, "hello2");
    llist_push(p_list, "hello3");
    llist_push(p_list, "hello4");
    llist_push(p_list, "hello5");
    llist_push(p_list, "hello6");
    llist_push(p_list, "hello7");
    llist_push(p_list, "hello8");
    llist_enqueue(p_list, "hello9");
    llist_enqueue(p_list, "hello10");
    llist_destroy(&p_list, NULL);
    CU_ASSERT_PTR_NULL(p_list);
}

void test_heap_alloc_cleanup()
{
    llist_t * p_list = llist_create();
    llist_push(p_list, strdup("hello"));
    llist_push(p_list, strdup("hello1"));
    llist_push(p_list, strdup("hello2"));
    llist_push(p_list, strdup("hello3"));
    llist_push(p_list, strdup("hello4"));
    llist_push(p_list, strdup("hello5"));
    llist_push(p_list, strdup("hello6"));
    llist_push(p_list, strdup("hello7"));
    llist_push(p_list, strdup("hello8"));
    llist_enqueue(p_list, strdup("hello9"));
    llist_enqueue(p_list, strdup("hello10"));
    llist_destroy(&p_list, free);
    CU_ASSERT_PTR_NULL(p_list);
}

void test_peek_size()
{
    llist_t * p_list = llist_create();
    CU_ASSERT_PTR_NULL(llist_peek(p_list));
    CU_ASSERT_EQUAL(llist_size(p_list), 0);
    llist_enqueue(p_list, "hello");
    CU_ASSERT_EQUAL(llist_size(p_list), 1);
    llist_enqueue(p_list, "hello1");
    CU_ASSERT_EQUAL(llist_size(p_list), 2);
    llist_enqueue(p_list, "hello2");
    CU_ASSERT_EQUAL(llist_size(p_list), 3);
    my_assert_string("hello", llist_peek(p_list));
    llist_dequeue(p_list);
    CU_ASSERT_EQUAL(llist_size(p_list), 2);
    my_assert_string("hello1", llist_peek(p_list));
    llist_dequeue(p_list);
    CU_ASSERT_EQUAL(llist_size(p_list), 1);
    my_assert_string("hello2", llist_peek(p_list));
    llist_dequeue(p_list);
    CU_ASSERT_EQUAL(llist_size(p_list), 0);

    char * p_tmp = NULL;
    llist_enqueue(p_list, strdup("hello"));
    CU_ASSERT_EQUAL(llist_size(p_list), 1);
    llist_enqueue(p_list, strdup("hello1"));
    CU_ASSERT_EQUAL(llist_size(p_list), 2);
    llist_enqueue(p_list, strdup("hello2"));
    CU_ASSERT_EQUAL(llist_size(p_list), 3);

    p_tmp = llist_peek(p_list);
    my_assert_string("hello", p_tmp);
    llist_dequeue(p_list);
    CU_ASSERT_EQUAL(llist_size(p_list), 2);
    free(p_tmp);

    p_tmp = llist_peek(p_list);
    my_assert_string("hello1", p_tmp);
    llist_dequeue(p_list);
    CU_ASSERT_EQUAL(llist_size(p_list), 1);
    free(p_tmp);

    p_tmp = llist_peek(p_list);
    my_assert_string("hello2", p_tmp);
    llist_dequeue(p_list);
    CU_ASSERT_EQUAL(llist_size(p_list), 0);
    free(p_tmp);

    llist_destroy(&p_list, NULL);
}

void test_contains()
{
    llist_t * p_list = llist_create();

    CU_ASSERT_EQUAL(llist_contains(NULL, "hello", my_strcmp), 0);
    CU_ASSERT_EQUAL(llist_contains(p_list, NULL, my_strcmp), 0);
    CU_ASSERT_EQUAL(llist_contains(p_list, "hello", NULL), 0);

    llist_enqueue(p_list, "pizza");
    llist_enqueue(p_list, "pineapple");
    llist_enqueue(p_list, "potato");

    CU_ASSERT_EQUAL(llist_contains(p_list, "pizza", my_strcmp), 1);
    CU_ASSERT_EQUAL(llist_contains(p_list, "pineapple", my_strcmp), 1);
    CU_ASSERT_EQUAL(llist_contains(p_list, "potato", my_strcmp), 1);
    CU_ASSERT_EQUAL(llist_contains(p_list, "apple", my_strcmp), 0);
    CU_ASSERT_EQUAL(llist_contains(p_list, "banana", my_strcmp), 0);
    llist_enqueue(p_list, "pizza");
    CU_ASSERT_EQUAL(llist_contains(p_list, "pizza", my_strcmp), 2);

    llist_dequeue(p_list);
    llist_dequeue(p_list);
    llist_dequeue(p_list);
    llist_dequeue(p_list);

    char * p_pizza     = strdup("pizza");
    char * p_pizza1    = strdup("pizza");
    char * p_pizza2    = strdup("pizza");
    char * p_pizza3    = strdup("pizza");
    char * p_pineapple = strdup("pineapple");
    char * p_potato    = strdup("potato");
    char * p_apple     = strdup("apple");
    char * p_banana    = strdup("banana");

    llist_enqueue(p_list, p_pizza);
    llist_enqueue(p_list, p_pineapple);
    llist_enqueue(p_list, p_potato);

    CU_ASSERT_EQUAL(llist_contains(p_list, p_pizza, my_strcmp), 1);
    CU_ASSERT_EQUAL(llist_contains(p_list, p_pizza1, my_strcmp), 1);
    CU_ASSERT_EQUAL(llist_contains(p_list, p_pizza2, my_strcmp), 1);
    CU_ASSERT_EQUAL(llist_contains(p_list, p_pizza3, my_strcmp), 1);
    CU_ASSERT_EQUAL(llist_contains(p_list, p_pineapple, my_strcmp), 1);
    CU_ASSERT_EQUAL(llist_contains(p_list, p_potato, my_strcmp), 1);
    llist_enqueue(p_list, p_pizza1);
    CU_ASSERT_EQUAL(llist_contains(p_list, p_pizza2, my_strcmp), 2);
    CU_ASSERT_EQUAL(llist_contains(p_list, p_pizza3, my_strcmp), 2);
    CU_ASSERT_EQUAL(llist_contains(p_list, p_apple, my_strcmp), 0);
    CU_ASSERT_EQUAL(llist_contains(p_list, p_banana, my_strcmp), 0);

    free(p_pizza);
    free(p_pizza1);
    free(p_pizza2);
    free(p_pizza3);
    free(p_pineapple);
    free(p_potato);
    free(p_apple);
    free(p_banana);

    llist_destroy(&p_list, NULL);
}

void test_iter()
{
    llist_t * p_list = llist_create();

    CU_ASSERT_EQUAL(llist_iter(NULL, add_one), EXIT_FAILURE);
    CU_ASSERT_EQUAL(llist_iter(p_list, NULL), EXIT_FAILURE);

    int my_int1 = 1;
    int my_int2 = 2;
    int my_int3 = 3;
    int my_int4 = 4;
    int my_int5 = 5;

    int * p_int1 = calloc(1, sizeof(int));
    int * p_int2 = calloc(1, sizeof(int));
    int * p_int3 = calloc(1, sizeof(int));
    int * p_int4 = calloc(1, sizeof(int));
    int * p_int5 = calloc(1, sizeof(int));

    *p_int1 = my_int1;
    *p_int2 = my_int2;
    *p_int3 = my_int3;
    *p_int4 = my_int4;
    *p_int5 = my_int5;

    llist_enqueue(p_list, p_int1);
    llist_enqueue(p_list, p_int2);
    llist_enqueue(p_list, p_int3);
    llist_enqueue(p_list, p_int4);
    llist_enqueue(p_list, p_int5);

    llist_iter(p_list, add_one);

    int * p_tmp = NULL;
    p_tmp       = llist_dequeue(p_list);
    CU_ASSERT_EQUAL(*p_tmp, 2);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    CU_ASSERT_EQUAL(*p_tmp, 3);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    CU_ASSERT_EQUAL(*p_tmp, 4);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    CU_ASSERT_EQUAL(*p_tmp, 5);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    CU_ASSERT_EQUAL(*p_tmp, 6);
    free(p_tmp);

    llist_destroy(&p_list, NULL);
}

void test_sort()
{
    llist_t * p_list = llist_create();

    CU_ASSERT_EQUAL(llist_sort(NULL, my_strcmp), EXIT_FAILURE);
    CU_ASSERT_EQUAL(llist_sort(p_list, NULL), EXIT_FAILURE);

    llist_enqueue(p_list, strdup("Koala"));
    llist_enqueue(p_list, strdup("Zebra"));
    llist_enqueue(p_list, strdup("Antelope"));
    llist_enqueue(p_list, strdup("Giraffe"));
    llist_enqueue(p_list, strdup("Elephant"));
    llist_enqueue(p_list, strdup("Tiger"));
    llist_enqueue(p_list, strdup("Bear"));
    llist_enqueue(p_list, strdup("Yak"));
    llist_enqueue(p_list, strdup("Dolphin"));
    llist_enqueue(p_list, strdup("Iguana"));
    llist_enqueue(p_list, strdup("Xerus"));
    llist_enqueue(p_list, strdup("Monkey"));
    llist_enqueue(p_list, strdup("Cheetah"));
    llist_enqueue(p_list, strdup("Rabbit"));
    llist_enqueue(p_list, strdup("Vulture"));
    llist_enqueue(p_list, strdup("Falcon"));
    llist_enqueue(p_list, strdup("Octopus"));
    llist_enqueue(p_list, strdup("Horse"));
    llist_enqueue(p_list, strdup("Lion"));
    llist_enqueue(p_list, strdup("Penguin"));
    llist_enqueue(p_list, strdup("Urchin"));
    llist_enqueue(p_list, strdup("Jaguar"));
    llist_enqueue(p_list, strdup("Narwhal"));
    llist_enqueue(p_list, strdup("Quokka"));
    llist_enqueue(p_list, strdup("Wolf"));
    llist_enqueue(p_list, strdup("Squirrel"));

    llist_sort(p_list, my_strcmp);

    char * p_tmp = NULL;

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Antelope", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Bear", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Cheetah", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Dolphin", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Elephant", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Falcon", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Giraffe", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Horse", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Iguana", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Jaguar", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Koala", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Lion", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Monkey", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Narwhal", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Octopus", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Penguin", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Quokka", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Rabbit", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Squirrel", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Tiger", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Urchin", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Vulture", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Wolf", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Xerus", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Yak", p_tmp);
    free(p_tmp);

    p_tmp = llist_dequeue(p_list);
    my_assert_string("Zebra", p_tmp);
    free(p_tmp);

    llist_destroy(&p_list, NULL);
}

int main(void)
{
    CU_TestInfo suite1_tests[] = {
        { "Testing creation and destruction:", test_create_destroy_empty },
        { "Testing basic queue functionality:", test_basic_queue },
        { "Testing basic stack functionality:", test_basic_stack },
        { "Testing advanced queue functionality:", test_advanced_queue },
        { "Testing advanced stack functionality:", test_advanced_stack },
        { "Testing stack allocated cleanup:", test_stack_alloc_cleanup },
        { "Testing heap allocated cleanup:", test_heap_alloc_cleanup },
        CU_TEST_INFO_NULL
    };

    CU_TestInfo suite2_tests[] = { { "Testing peek and size:", test_peek_size },
                                   { "Testing contains:", test_contains },
                                   { "Testing iter:", test_iter },
                                   { "Testing sort:", test_sort },
                                   CU_TEST_INFO_NULL };

    CU_SuiteInfo suites[] = {
        { "Suite-1:", NULL, NULL, .pTests = suite1_tests },
        { "Suite-2:", NULL, NULL, .pTests = suite2_tests },
        CU_SUITE_INFO_NULL
    };

    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    if (0 != CU_register_suites(suites))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());
    int num_failed = CU_get_number_of_failures();
    CU_cleanup_registry();
    printf("\n");
    return num_failed;
}

// end of linked_list_tests.c
