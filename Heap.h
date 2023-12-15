#ifndef CUSTOM_HEAP_HEAP_H
#define CUSTOM_HEAP_HEAP_H

#include <cstddef>
#include <string>

class Heap {
private:
    Heap();
    static void *operator new(size_t size);

public:
    ~Heap();
    static void clear_mem();
    static void *alloc_mem(size_t size);
    static bool dealloc_mem(void *mem);
    static std::string dump();
};


#endif //CUSTOM_HEAP_HEAP_H
