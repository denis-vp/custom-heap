#include <iostream>
#include "test.h"

using namespace std;

int main() {
    try {
        test();
        cout << endl << "Test passed." << endl;
    } catch (const std::exception &e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
