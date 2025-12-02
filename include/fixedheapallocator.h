#pragma once
#include "common.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    size_t size;
    size_t idx;
    uint8_t *buf;
} fixedHeapAllocator_t;

[[nodiscard]]
result_e fixedHeapAllocator_init(fixedHeapAllocator_t *self, const size_t size)
{
    self->size = size;
    self->idx = 0;
    self->buf = calloc(size, 1);
    if (self->buf == NULL)
    {
        return RESULT_ERR;
    }

    return RESULT_OK;
}

void fixedHeapAllocator_deinit(fixedHeapAllocator_t *self)
{
    self->idx = 0;
    self->size = 0;
    free(self->buf);
    self->buf = NULL;
}

[[nodiscard]] void *fixedHeapAllocator_reserve(fixedHeapAllocator_t *self, size_t bytes)
{
    if ((self->idx + bytes) > self->size)
    {
        return NULL;
    }

    void *out = &self->buf[self->idx];
    self->idx += bytes;
    return out;
}
