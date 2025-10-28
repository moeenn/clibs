#pragma once

/*
typedef enum {
    ALLOCATOR_STACK,
    // ALLOCATOR_FIXED_HEAP,
    // ALLOCATOR_VARIABLE_HEAP,
    // ALLOCATOR_STATIC,
} allocatorKind_e;

typedef union {
    stackAllocator_t stack;
} allocator_u;

typedef struct {
    allocatorKind_e kind;
    allocator_u alloc;
} allocator_t;

[[nodiscard]]
void* allocator_reserve(allocator_t* self, size_t bytes)
{
    void* r = NULL;
    switch (self->kind) {
    case ALLOCATOR_STACK:
        r = stackAllocator_reserve(&self->alloc.stack, bytes);
        break;
    }

    return r;
}

void allocator_deinit(allocator_t* self)
{
    switch (self->kind) {
    case ALLOCATOR_STACK:
        stackAllocator_deinit(&self->alloc.stack);
    }
}
*/
