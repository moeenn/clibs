#include "allocator.h"
#include "common.h"
#include "fixedheapallocator.h"
#include "staticallocator.h"
#include "vector.h"
#include <stdint.h>

inline void print_nums(size_t idx, int n)
{
    printf("%zu -> %d\n", idx, n);
}

int main()
{
    static uint8_t buf[10000];
    staticAllocator_t sa;
    staticAllocator_init(&sa, buf, 100);

    fixedHeapAllocator_t fha;
    if (RESULT_ERR == fixedHeapAllocator_init(&fha, 100))
    {
        fprintf(stderr, "error: failed to initialize FHA.\n");
        return RESULT_ERR;
    }

    allocator_t a;
    allocator_setFixedHeap(&a, &fha);

    vector_t v;
    if (RESULT_ERR == vector_init(&v, &a, 20))
    {
        fprintf(stderr, "error: failed to allocate vector.\n");
        goto cleanup;
        return RESULT_ERR;
    }

    if (RESULT_ERR == vector_push(&v, &a, 10))
    {
        fprintf(stderr, "error: failed to push into vector.\n");
        goto cleanup;
        return RESULT_ERR;
    }

    if (RESULT_ERR == vector_push(&v, &a, 20))
    {
        fprintf(stderr, "error: failed to push into vector.\n");
        goto cleanup;
        return RESULT_ERR;
    }

    if (RESULT_ERR == vector_push(&v, &a, 30))
    {
        fprintf(stderr, "error: failed to push into vector.\n");
        goto cleanup;
        return RESULT_ERR;
    }
    if (RESULT_ERR == vector_push(&v, &a, 40))
    {
        fprintf(stderr, "error: failed to push into vector.\n");
        goto cleanup;
        return RESULT_ERR;
    }

    vector_iter(&v, sizeof(int), print_nums);

cleanup:
    allocator_deinit(&a);

    return RESULT_OK;
}
