#ifndef CUSTOM_HEAP_HEAP_H
#define CUSTOM_HEAP_HEAP_H

#include <cstddef>
#include <string>

class Heap {
private:
    typedef struct mem_info_t {
        mem_info_t *next;
        size_t size;
        bool is_free;
    } mem_info_t;

    mem_info_t *root;
    char *heap_end;

    static Heap* heapPointer;

private:
    Heap();
    static void *operator new(size_t size);

public:
    ~Heap();
    static Heap *get_heap();
    void clear_mem();
    void *alloc_mem(size_t size);
    bool dealloc_mem(void *memory);
    std::string dump();
};


#endif //CUSTOM_HEAP_HEAP_H
