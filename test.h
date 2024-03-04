#ifndef CUSTOM_HEAP_TEST_H
#define CUSTOM_HEAP_TEST_H

#include <iostream>
#include "Heap.h"

using namespace std;

class TestClass {
private:
    int value;

public:
    TestClass(int value) : value(value) {
        cout << "TestClass(" << value << ") created." << endl;
    }

    ~TestClass() {
        cout << "TestClass(" << value << ") destroyed." << endl;
    }

    static void *operator new(size_t size) {
        cout << "TestClass::new(" << size << ")" << endl;
        Heap *heap = Heap::get_heap();
        return heap->alloc_mem(size);
    }

    static void operator delete(void *memory) {
        cout << "TestClass::delete(" << memory << ")" << endl;
        Heap *heap = Heap::get_heap();
        heap->dealloc_mem(memory);
    }
};

void test() {
    char *mem1, *mem2;
    Heap *heap = Heap::get_heap();

    mem1 = reinterpret_cast<char *>(heap->alloc_mem(100));
    if (mem1 != nullptr) {
        cout << "mem1 allocated at " << static_cast<void *>(mem1) << endl;
        for (int i = 0; i < 99; i++) {
            mem1[i] = static_cast<char>(i + 1);
        }
        mem1[99] = '\0';
        cout << "mem1: " << mem1 << endl;
    } else {
        throw std::runtime_error("mem1 allocation failed.");
    }
    cout << endl;

    mem2 = reinterpret_cast<char *>(heap->alloc_mem(200));
    if (mem2 != nullptr) {
        cout << "mem2 allocated at " << static_cast<void *>(mem2) << endl;
        for (int i = 0; i < 199; i++) {
            mem2[i] = static_cast<char>(i + 1);
        }
        mem2[199] = '\0';
        cout << "mem2: " << mem2 << endl;
    } else {
        throw std::runtime_error("mem2 allocation failed.");
    }
    cout << endl;

    if (heap->dealloc_mem(mem1)) {
        cout << "mem1 deallocated." << endl;
    } else {
        throw std::runtime_error("mem1 deallocation failed.");
    }
    cout << endl;

    cout << heap->dump() << endl;
    cout << endl;

    if (heap->dealloc_mem(mem2)) {
        cout << "mem2 deallocated." << endl;
    } else {
        throw std::runtime_error("mem2 deallocation failed.");
    }
    cout << endl;

    auto *obj1 = new TestClass(1);
    delete obj1;
    cout << endl;
    TestClass obj2(2);
}


#endif //CUSTOM_HEAP_TEST_H
