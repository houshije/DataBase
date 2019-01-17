#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

#ifdef _cplusplus
extern "c" {
#endif

    typedef enum {
        FALSE = 0,
        TRUE  = 1
    }BOOL;

    typedef struct {
        void            *buffer;
        unsigned int    head;
        unsigned int    end;
        unsigned int    length;
        unsigned int    itemSize;
        unsigned int    itemCount;
    }RingBuffer_CTX;

    RingBuffer_CTX *RingBufferCreate(unsigned int inLength, unsigned int inItemSize);
    void RingBufferDestory(RingBuffer_CTX *inRingBuffer);
    unsigned int RingBufferWrite(RingBuffer_CTX *inRingBuffer, void *inData, unsigned int inItemCount);
    unsigned int RingBufferRead(RingBuffer_CTX *inRingBuffer, void *outData, unsigned int inItemCount);
    unsigned int RingBufferFreeItemCount(RingBuffer_CTX *inRingBuffer);
    unsigned int RingBufferItemCount(RingBuffer_CTX *inRingBuffer);
    BOOL RingBufferisEmpty(RingBuffer_CTX *inRingBuffer);
    BOOL RingBufferisFull(RingBuffer_CTX *inRingBuffer);
    void RingBufferReset(RingBuffer_CTX *inRingBuffer);


#ifdef _cplusplus
}
#endif

#endif
