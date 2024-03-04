#include "Heap.h"

using namespace std;

#define NUM_KB 100

static const size_t max_heap_size = NUM_KB * 1024;

static char heap_mem[max_heap_size];

static char heap_obj[sizeof(Heap)];


Heap::Heap() {
    clear_mem();

//    set up the root block
    root = reinterpret_cast<mem_info_t *>(&heap_mem[0]);
    root->next = nullptr;
    root->size = max_heap_size;
    root->is_free = true;

    heap_end = &heap_mem[max_heap_size - 1];
}

Heap::~Heap() {
    clear_mem();
}

Heap *Heap::get_heap() {
    static bool is_initialized = false;
    static Heap *heap = nullptr;

    if (!is_initialized) {
        heap = new Heap();
        is_initialized = true;
    }

    return heap;
}

void Heap::clear_mem() {
    for (auto &byte: heap_mem) {
        byte = static_cast<char>(0);
    }
}

void *Heap::alloc_mem(size_t size) {
    char *mem = nullptr;
    mem_info_t *block = root;

//    search for a free block of memory
    do {
//        if the block is free and large enough, allocate memory and update the block info
        if (block->is_free && block->size >= size) {
            mem = reinterpret_cast<char *>(block + 1);
            block->is_free = false;
            block->size = size;

//            if there is one update the block info for the remaining memory
            if (block->next != nullptr) {
                mem_info_t *next_block = reinterpret_cast<mem_info_t *>(block->next);
                size_t remaining_size = block->size - size + 1;

                if (remaining_size > sizeof(mem_info_t)) {
                    mem_info_t *new_block = reinterpret_cast<mem_info_t *>(mem + size);
                    new_block->next = next_block;
                    new_block->size = remaining_size - sizeof(mem_info_t);
                    new_block->is_free = true;
                    block->next = new_block;
                }
            } else if (size_t(mem) + size < size_t(heap_end)) {
//                if there is no block check if there is enough memory to create a new block
                size_t remaining_size = size_t(heap_end) - size_t(mem) - size + 1;
                if (remaining_size > sizeof(mem_info_t)) {
                    mem_info_t *new_block = reinterpret_cast<mem_info_t *>(mem + size);
                    new_block->next = nullptr;
                    new_block->size = remaining_size - sizeof(mem_info_t);
                    new_block->is_free = true;
                    block->next = new_block;
                }
            }

            break;
        }

        block = block->next;
    } while (block != nullptr);

    return reinterpret_cast<void *>(mem);
}

bool Heap::dealloc_mem(void *memory) {
    char *mem = reinterpret_cast<char *>(memory);
    bool status = false;
    if (mem < &heap_mem[0] || mem > heap_end) {
        return status;
    }

    mem_info_t *block = root;
    mem_info_t *required_block = reinterpret_cast<mem_info_t *>(mem) - 1;

    do {
        if (block == required_block) {
            block->is_free = true;
            for (int i = 0; i < block->size; i++) {
                *mem = static_cast<char>(0);
            }
            status = true;
            break;
        }
        block = block->next;
    } while (block != nullptr);

    return status;
}

void *Heap::operator new(size_t size) {
    return reinterpret_cast<void *>(heap_obj);
}

string Heap::dump() {
    string dump = "Heap dump:\n";
    dump += "Heap size: " + to_string(max_heap_size) + " bytes\n";
    dump += "Heap start: " + to_string(reinterpret_cast<size_t>(&heap_mem[0])) + "\n";
    dump += "Heap end: " + to_string(reinterpret_cast<size_t>(heap_end)) + "\n";
    dump += "Heap memory:\n";
    for (auto &byte: heap_mem) {
        dump += to_string(static_cast<size_t>(byte)) + " ";
    }
    dump += "\n";
    return dump;
}
