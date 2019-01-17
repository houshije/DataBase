#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ringbuffer.h"

#define offsetAddr(obj, offset, data)                   \
    ((void *)(((unsigned char *)(data)) + ((offset) * (obj)->itemSize)))

#define headAddr(obj)                                   \
    offsetAddr(obj, (obj)->head, (obj)->buffer)

#define endAddr(obj)                                    \
    offsetAddr(obj, (obj)->end, (obj)->buffer)

#define freeItemLength(obj)                             \
    ((obj)->length - (obj)->itemCount)

#define ringbufferItemLength(obj)                       \
    ((obj)->itemCount)

#define incItemCount(obj, c)                            \
    if (((c) + (obj)->itemCount) <= (obj)->length) {    \
        do {                                            \
            (obj)->head += (c);                         \
            if ((obj)->head >= (obj)->length) {         \
                (obj)->head = 0;                        \
            }                                           \
            (obj)->itemCount += (c);                    \
        } while(0);                                     \
    }

#define decItemCount(obj, c)                            \
    if ((c) <= (obj)->itemCount) {                      \
        do {                                            \
            (obj)->end += (c);                          \
            if ((obj)->end >= (obj)->length) {          \
                (obj)->end = 0;                         \
            }                                           \
            (obj)->itemCount -= (c);                    \
        } while(0);                                     \
    }
#define RBFree(obj)             \
    if (obj) {                  \
        free(obj);              \
    }
#define resetRingBuffer(obj)    \
    do {                        \
        (obj)->itemCount = 0;   \
        (obj)->head = 0;        \
        (obj)->end = 0;         \
    } while(0)

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

static unsigned int copiableInItemCount(RingBuffer_CTX *inRingBuffer)
{
    if (inRingBuffer->itemCount == 0) {
        return inRingBuffer->length;
    } else if (inRingBuffer->head > inRingBuffer->end) {
        return inRingBuffer->length - inRingBuffer->head;
    } else {
        return inRingBuffer->end - inRingBuffer->head;
    }
}

static unsigned int copiableOutItemCount(RingBuffer_CTX *inRingBuffer)
{
    if (inRingBuffer->itemCount == 0) {
        return 0;
    } else if (inRingBuffer->head > inRingBuffer->end) {
        return (inRingBuffer->head - inRingBuffer->end);
    } else {
        return (inRingBuffer->length - inRingBuffer->end + inRingBuffer->head);
    }
}

RingBuffer_CTX *RingBufferCreate(unsigned int inLength, unsigned int inItemSize)
{
    RingBuffer_CTX *rbuf = NULL;
    rbuf = (RingBuffer_CTX *)calloc(1, sizeof(RingBuffer_CTX));
    if (rbuf) {
        rbuf->buffer = (void *)calloc(inLength, inItemSize);
        if (rbuf->buffer) {
            rbuf->itemSize = inItemSize;
            rbuf->length = inLength;
            resetRingBuffer(rbuf);
        } else {
            RBFree(rbuf);
        }
    }

    return rbuf;
}

void RingBufferDestory(RingBuffer_CTX *inRingBuffer)
{
    if (inRingBuffer) {
        if (inRingBuffer->buffer) {
            RBFree(inRingBuffer->buffer);
        }
        RBFree(inRingBuffer);
    }
}

unsigned int RingBufferWrite(RingBuffer_CTX *inRingBuffer, void *inData, unsigned int inItemCount)
{
    unsigned  int writeableCount = 0;
    unsigned  int copiableCount = 0;
    copiableCount = copiableInItemCount(inRingBuffer);

    if (freeItemLength(inRingBuffer) == inRingBuffer->length) {
        resetRingBuffer(inRingBuffer);
        writeableCount = MIN(copiableCount, inItemCount);
        strncpy(inRingBuffer->buffer, inData, writeableCount * inRingBuffer->itemSize);
        incItemCount(inRingBuffer, writeableCount);
    } else if (copiableCount >= inItemCount) {
        writeableCount = MIN(copiableCount, inItemCount);
        strncpy(headAddr(inRingBuffer), inData, writeableCount * inRingBuffer->itemSize);
        incItemCount(inRingBuffer, writeableCount);
    } else {
        strncpy(headAddr(inRingBuffer), inData, copiableCount * inRingBuffer->itemSize);
        incItemCount(inRingBuffer, copiableCount);
        writeableCount = MIN(copiableInItemCount(inRingBuffer), (inItemCount - copiableCount));
        if (writeableCount) {
            strncpy(headAddr(inRingBuffer), offsetAddr(inRingBuffer, copiableCount, inData),
                    writeableCount * inRingBuffer->itemSize);
            incItemCount(inRingBuffer, writeableCount);
        }

        writeableCount += copiableCount;
    }

    return writeableCount;
}

unsigned int RingBufferRead(RingBuffer_CTX *inRingBuffer, void *outData, unsigned int inItemCount)
{
    unsigned int readableCount = 0;
    unsigned int copiableCount = 0;

    copiableCount = copiableOutItemCount(inRingBuffer);
    if (copiableCount >= inItemCount) {
        readableCount = MIN(copiableCount, inItemCount);

        strncpy(outData, endAddr(inRingBuffer), readableCount * inRingBuffer->itemSize);
        decItemCount(inRingBuffer, readableCount);
    } else {
        strncpy(outData, endAddr(inRingBuffer), copiableCount * inRingBuffer->itemSize);
        decItemCount(inRingBuffer, copiableCount);
        readableCount = MIN(copiableOutItemCount(inRingBuffer), (inItemCount - copiableCount));
        if (readableCount) {
            strncpy(offsetAddr(inRingBuffer, copiableCount, outData), endAddr(inRingBuffer),
                    readableCount * inRingBuffer->itemSize);
            decItemCount(inRingBuffer, readableCount);
        }
        readableCount += copiableCount;
    }
}

BOOL RingBufferISEmpty(RingBuffer_CTX *inRingBuffer)
{
    return (ringbufferItemLength(inRingBuffer) ? FALSE :TRUE);
}

BOOL RingBufferISFull(RingBuffer_CTX *inRingBuffer)
{
    return (freeItemLength(inRingBuffer) ? FALSE : TRUE);
}

unsigned int RingBufferFreeItemCount(RingBuffer_CTX *inRingBuffer)
{
    return freeItemLength(inRingBuffer);
}

unsigned int RingBufferItemCount(RingBuffer_CTX *inRingBuffer)
{
    return ringbufferItemLength(inRingBuffer);
}

void RingBufferReset(RingBuffer_CTX *inRingBuffer)
{
    if (inRingBuffer) {
        resetRingBuffer(inRingBuffer);
    }
}
