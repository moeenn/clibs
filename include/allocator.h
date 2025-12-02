#pragma once

#include "fixedheapallocator.h"
#include "staticallocator.h"

typedef enum
{
    ALLOCATOR_STATIC,
    ALLOCATOR_FIXED_HEAP,
    // ALLOCATOR_VARIABLE_HEAP,
} allocatorKind_e;

typedef union {
    staticAllocator_t static_alloc;
    fixedHeapAllocator_t fixedh_alloc;
} allocator_u;

typedef struct
{
    allocatorKind_e kind;
    allocator_u alloc;
} allocator_t;

void allocator_setFixedHeap(allocator_t *self, fixedHeapAllocator_t *alloc)
{
    self->kind = ALLOCATOR_FIXED_HEAP;
    self->alloc.fixedh_alloc = *alloc;
}

void allocator_setStatic(allocator_t *self, staticAllocator_t *alloc)
{
    self->kind = ALLOCATOR_STATIC;
    self->alloc.static_alloc = *alloc;
}

[[nodiscard]]
void *allocator_reserve(allocator_t *self, size_t bytes)
{
    void *r = NULL;
    switch (self->kind)
    {
    case ALLOCATOR_STATIC:
        r = staticAllocator_reserve(&self->alloc.static_alloc, bytes);
        break;

    case ALLOCATOR_FIXED_HEAP:
        r = fixedHeapAllocator_reserve(&self->alloc.fixedh_alloc, bytes);
        break;
    };

    return r;
}

void allocator_deinit(allocator_t *self)
{
    switch (self->kind)
    {
    case ALLOCATOR_STATIC:
        staticAllocator_deinit(&self->alloc.static_alloc);
        break;

    case ALLOCATOR_FIXED_HEAP:
        fixedHeapAllocator_deinit(&self->alloc.fixedh_alloc);
        break;
    }
}
