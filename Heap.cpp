#include "Heap.h"

using namespace std;

#define NUM_KB 100

typedef struct mem_info_t {
    mem_info_t *next;
    size_t size;
    bool is_free;
} mem_info_t;

mem_info_t *root;
char *heap_end;

static const size_t max_heap_size = NUM_KB * 1024;

static char heap_memory[max_heap_size];

static char heap[sizeof(Heap)];


Heap::Heap() {
    clear_mem();

//    set up the root
    root = reinterpret_cast<mem_info_t *>(&heap_memory[0]);
    root->next = nullptr;
    root->size = max_heap_size;
    root->is_free = true;

    heap_end = &heap_memory[max_heap_size - 1];
}

Heap::~Heap() {
    clear_mem();
}

void Heap::clear_mem() {
    for (auto &byte: heap_memory) {
        byte = static_cast<char>(0);
    }
}

// TODO: implement this
void *Heap::alloc_mem(size_t size) {
}

// TODO: implement this
bool Heap::dealloc_mem(void *mem) {
}

void *Heap::operator new(size_t size) {
    return reinterpret_cast<void *>(heap);
}

string Heap::dump() {
    string dump = "Heap dump:\n";
    dump += "Heap size: " + to_string(max_heap_size) + " bytes\n";
    dump += "Heap start: " + to_string(reinterpret_cast<size_t>(&heap_memory[0])) + "\n";
    dump += "Heap end: " + to_string(reinterpret_cast<size_t>(heap_end)) + "\n";
    dump += "Heap memory:\n";
    for (auto &byte: heap_memory) {
        dump += to_string(static_cast<size_t>(byte)) + " ";
    }
    dump += "\n";
    return dump;
}
