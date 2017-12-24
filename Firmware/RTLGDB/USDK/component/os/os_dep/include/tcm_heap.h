#ifndef STRUCT_HEAP_H
#define STRUCT_HEAP_H

//#include <stdio.h>
#include <stdint.h>
#include <osdep_service.h>



#define TCM_HEAP_SIZE	(42*1024) // min size

// MAX_BACKUP_SIZE in hal_soc_ps_monitor = 129*4, 0x1FFFFFFC - 129*4 = 0x1FFFFD18 !
#define tcm_heap_size ((0x20000000 - (uint32_t)&tcm_heap - 768 + sizeof(heap_buf_t) - 1)/sizeof(heap_buf_t))*sizeof(heap_buf_t)

/* NOTE: struct size must be a 2's power! */
typedef struct _MemChunk
{
	struct _MemChunk *next;
	int size;
} MemChunk;

typedef MemChunk heap_buf_t;

/// A heap
typedef struct Heap
{
	struct _MemChunk *FreeList;     ///< Head of the free list
} Heap;

/**
 * Utility macro to allocate a heap of size \a size.
 *
 * \param name Variable name for the heap.
 * \param size Heap size in bytes.
 */
#define HEAP_DEFINE_BUF(name, size) \
	heap_buf_t name[((size) + sizeof(heap_buf_t) - 1) / sizeof(heap_buf_t)]

/// Initialize \a heap within the buffer pointed by \a memory which is of \a size bytes
void tcm_heap_init(void);

/// Allocate a chunk of memory of \a size bytes from the heap
// void *tcm_heap_allocmem(int size);

/// Free a chunk of memory of \a size bytes from the heap
// void tcm_heap_freemem(void *mem, int size);

int tcm_heap_freeSpace(void);

#define HNEW(heap, type) \
	(type*)tcm_heap_allocmem(heap, sizeof(type))

#define HNEWVEC(heap, type, nelem) \
	(type*)tcm_heap_allocmem(heap, sizeof(type) * (nelem))

#define HDELETE(heap, type, mem) \
	tcm_heap_freemem(heap, mem, sizeof(type))

#define HDELETEVEC(heap, type, nelem, mem) \
	tcm_heap_freemem(heap, mem, sizeof(type) * (nelem))

extern HEAP_DEFINE_BUF(tcm_heap, TCM_HEAP_SIZE);

/**
 * \name Compatibility interface with C standard library
 * \{
 */
void *tcm_heap_malloc(int size);
void *tcm_heap_calloc(int size);
void tcm_heap_free(void * mem);
void tcm_heap_dump(void);
/** \} */

#endif /* STRUCT_HEAP_H */
