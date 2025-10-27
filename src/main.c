#include "common.h"
#include "stackallocator.h"

int main()
{
    stackallocator_t a;
    stackallocator_init(&a, 20);

    int* first = stackallocator_reserve(&a, 4);
    *first = 10;
    printf("first = %d\n", *first);

    stackallocator_deinit(&a);
    return RESULT_OK;
}
