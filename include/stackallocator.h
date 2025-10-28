#pragma once
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    size_t size;
    size_t idx;
    uint8_t buf[];
} stackAllocator_t;

void stackAllocator_init(stackAllocator_t* self, const size_t size)
{
    self->size = size;
    self->idx = 0;
    // memset(self->buf, 0, size);
}

void stackAllocator_deinit(stackAllocator_t* self)
{
    self->idx = 0;
    self->size = 0;
    // memset(self->buf, 0, self->size);
}

[[nodiscard]] void* stackAllocator_reserve(stackAllocator_t* self, size_t bytes)
{
    if ((self->idx + bytes) > self->size) {
        return NULL;
    }

    void* out = &self->buf[self->idx];
    self->idx += bytes;
    return out;
}
