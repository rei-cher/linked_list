# YOU SHOULD NOT PUSH ANY MODIFICATION TO THE FILES IN THIS DIRECTORY

- If you identify a problem with any of the tests in this directory, make an issue on your repo.

# Notes
Linked lists make great stacks and queues. For minimal functionality, a stack needs a create(), destroy(), push(), and pop() function(s), and a queue needs a create(), destroy(), enqueue(), and dequeue() function(s). In keeping with this minimalist approach, and trying to ensure that the linked list is fast, none of the user defined functions are stored in the linked list struct. Also, keeping track of the head and tail pointers in the linked list struct is the best way to ensure O(1) insertion and removal. The additional functions for this library, peek(), size(), contains(), iter(), and sort() function(s) are great for a generic linked list (a collection of non-contiguous data), but wouldn't necessarily be included in a stack or queue library.

## llist_tests.c
- my_strcmp() - this function is a wrapper around strcmp for comparing string values (helps to silence void*/char* pointer warning differences)

- my_print() - this function is a print function for simple integers. It is used to verify that you are actually sorting nodes correctly. If your linked list is built correctly, you won't actually see any prints from this function. You will only see the prints when your linked list is messed up. 

- my_assert_string() - this function is a way to actually see what string value is expected vs what was provided since these unit tests don't provide that by default.

- If you remove `-fsanitize=address` from your compilation flags. You can run the entire test suite in valgrind as well to make sure that you are not leaking any memory. (10/10 would recommend you check for leaks.)

Here is a breakdown of the tests in this file. They are broken down into 2 suites. The first suite tests all functions that would be needed for a basic stack or queue. The second suite tests the additional functions that are included in the library peek(), size(), contains(), iter(), and sort().

### test_create_destroy_empty()
This test validates the create function and destruction of an empty linked list.

- p_list should be successfully created when the create function is called. p_list is checked to be non NULL. p_list should then be successfully destroyed when NULL is passed as the destroy function. p_list is then checked to be NULL.
- p_list2 should be successfully created when the create function is called. p_list2 is checked to be non NULL. p_list2 should then be successfully destroyed when free is passed as the destroy function. p_list2 is then checked to be NULL.
- llist_destroy() is passed 2 NULLs. The function should immediately exit. No asserts are ran, but the program should also not crash.
- p_list3 is set to NULL. The address of p_list3 is then passed to llist_destroy() along with NULL as the free function. The function shouldn't do anything to this pointer, the pointer is checked to still be NULL after the function call, and the program should not crash.

### test_basic_queue()
This test validates the enqueue and dequeue functions.

- p_list is created. "hello", "hello1", and "hello2" are enqueue'd. There are then 3 asserts (wrapped around the custom string assertion) to make sure that when dequeue is called 3 times in a row, that you get back "hello" first, then "hello1" second, then "hello2" last. The list is then destroyed.

### test_basic_stack()
This test validates the push and pop functions.

- This test does the same thing as test_basic_enqueue, but when "hello", "hello1", and "hello2" are pushed to the stack and then popped the order they are returned in is "hello2", "hello1", and lastly "hello".

### test_advanced_queue()
This test makes sure that you implementation of enqueue and dequeue is fast. 

- 1 million strings are enqueue'd and then immediately dequeue'd. On my dev computer this takes less than 1 second. If your test starts to take longer than 10 seconds and you aren't coding on a potato, it's time to stop the test and reevaluate your code. These strings are heap allocated (but thats mostly just for convenience). When this test base is run in valgrind, this suite takes about 7 seconds. So, when running in valgrind if this suite takes longer than 30 seconds, stop and look at your code.

### test_advanced_stack()
This test does the same as test_advanced_queue(), but with push and pop. 

- Similarly, if this starts to take some time, you might need to rethink the codebase.

### test_stack_alloc_cleanup()
This test validates the destroy function for when the list is not empty and data is stack allocated. 

- Strings are added at random to the list. The list is then destroyed. There should be no invalid free's called.

### test_heap_alloc_cleanup()
This test validates the destroy function for when the list is not empty and data is heap allocated.

- Heap allocated strings are added at random to the list. The list is then destroyed. All data should be properly freed.

### test_peek_size()
This test validates the peek and size function.

- p_list is created. We then immediately peek to make sure that NULL is returned. "hello", "hello1", and "hello2" are all enqueued. We then peak to see "hello" then dequeue it. We then peak to see "hello1" then dequeue it. We then peak to see "hello2" and then dequeue it. These strings are all stack allocated. The tests are then repeated with heap allocated strings. The size is checked as things are added to and removed from the list.

### test_contains()
This test validates the contains function.

- p_list is created. Checks are then conducted to verify proper return values based on missing function parameters.

- "pizza", "pineapple", and "potato" are added to the list. The list is then checked to see that it contains "pizza", "pineapple", and "potato" one time each. The list is then checked to make sure that it contains "apple" and "banana" 0 times each. "pizza" is added to the list again. The list is then checked to see that "pizza" is contained in the list twice. The list is then emptied of its stack allocated strings.

- The test is then repeated with heap allocated strings.

### test_iter()
This test validates the iter function.

- p_list is created. Checks are then conducted to verify proper return values based on missing function parameters.

- The pointers to the numbers 1, 2, 3, 4, and 5 are enqueue'd on the list. An iter function that adds 1 to an integer is then passed to the iter function. The pointers are all dequeue'd to make sure that you now get 2, 3, 4, 5, and 6.

### test_sort()
This test validates the sort function.

- p_list is created. Checks are then conducted to verify proper return values based on missing function parameters.

- A heap allocated animal string is enqueue'd for each letter of the alphabet. The list is then sorted (alphabetically) and then each animal is dequeue'd, checking to make sure that they are dequeue'd in alphabetical order.
