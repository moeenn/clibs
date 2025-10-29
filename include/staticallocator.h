#pragma once
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    size_t size;
    size_t idx;
    uint8_t* buf;
} staticAllocator_t;

void staticAllocator_init(staticAllocator_t* self, uint8_t* buf, const size_t size)
{
    self->size = size;
    self->idx = 0;
    self->buf = buf;
}

void staticAllocator_deinit(staticAllocator_t* self)
{
    self->idx = 0;
    self->size = 0;
    self->buf = NULL;
}

[[nodiscard]] void* staticAllocator_reserve(staticAllocator_t* self, size_t bytes)
{
    if ((self->idx + bytes) > self->size) {
        return NULL;
    }

    void* out = &self->buf[self->idx];
    self->idx += bytes;
    return out;
}
