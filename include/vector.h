#pragma once
#include "allocator.h"
#include "common.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    size_t capacity;
    size_t size;
    uint8_t *buf;
} vector_t;

result_e vector_init(vector_t *self, allocator_t *allocator, size_t capacity)
{
    self->capacity = capacity;
    self->size = 0;
    self->buf = allocator_reserve(allocator, capacity);
    if (self->buf == NULL)
    {
        return RESULT_ERR;
    }

    return RESULT_OK;
}

void vector_deinit(vector_t *self)
{
    self->capacity = 0;
    self->size = 0;
    self->buf = NULL;
}

[[nodiscard]]
result_e vector_resize(vector_t *self, allocator_t *allocator)
{
    bool shouldResize = self->size >= self->capacity;
    if (!shouldResize)
    {
        return RESULT_OK;
    }

    size_t newCapacity = self->capacity * 2;
    void *newBuf = allocator_reserve(allocator, newCapacity);
    if (newBuf == NULL)
    {
        return RESULT_ERR;
    }

    memcpy(self->buf, newBuf, self->size);
    self->capacity = newCapacity;
    self->buf = newBuf;
    return RESULT_OK;
}

// TODO: make generic.
[[nodiscard]]
result_e vector_push(vector_t *self, allocator_t *allocator, int data)
{
    bool shouldResize = self->size >= self->capacity;
    if (shouldResize)
    {
        if (vector_resize(self, allocator) == RESULT_ERR)
        {
            return RESULT_ERR;
        }
    }

    self->buf[self->size] = data;
    self->size += sizeof(data);
    return RESULT_OK;
}

// TODO: make generic.
inline void vector_iter(vector_t *self, size_t stepSize, void (*callback)(size_t, int))
{
    size_t i;
    for (i = 0; i < self->size; i += stepSize)
    {
        callback(i / stepSize, self->buf[i]);
    }
}
