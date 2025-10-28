#include "common.h"
#include "fixedheapallocator.h"
#include "vector.h"

void print_nums(size_t idx, int n)
{
    printf("%zu -> %d\n", idx, n);
}

int main()
{
    fixedHeapAllocator_t sa;
    if (RESULT_ERR == fixedHeapAllocator_init(&sa, 20)) {
        fprintf(stderr, "error: failed to init allcator.\n");
        return RESULT_ERR;
    }

    vector_t v;
    if (RESULT_ERR == vector_init(&v, &sa, 20)) {
        fprintf(stderr, "error: failed to allocate vector.\n");
        return RESULT_ERR;
    }

    if (RESULT_ERR == vector_push(&v, &sa, 10)) {
        fprintf(stderr, "error: failed to push into vector.\n");
        return RESULT_ERR;
    }

    if (RESULT_ERR == vector_push(&v, &sa, 20)) {
        fprintf(stderr, "error: failed to push into vector.\n");
        return RESULT_ERR;
    }

    if (RESULT_ERR == vector_push(&v, &sa, 30)) {
        fprintf(stderr, "error: failed to push into vector.\n");
        return RESULT_ERR;
    }
    if (RESULT_ERR == vector_push(&v, &sa, 40)) {
        fprintf(stderr, "error: failed to push into vector.\n");
        return RESULT_ERR;
    }

    vector_iter(&v, sizeof(int), print_nums);
    fixedHeapAllocator_deinit(&sa);

    return RESULT_OK;
}
