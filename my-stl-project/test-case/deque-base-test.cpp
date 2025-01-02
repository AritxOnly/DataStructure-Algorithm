#include <cassert>
#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <string>
#include "../deque.h"
#include "../vector.h"
#include "../string.h"

using std::string, std::cout, std::endl;

template <typename Func>
void benchmark(const string& operation, Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << operation << " took " << duration << " microseconds" << endl;
}

namespace MyStl {
    void testDequeFunctionality() {
        deque<int> t1;

        cout << "Running functionality tests with assertions...\n";

        benchmark("Push back 5000 elements", [&]() {
            for (int i = 5001; i <= 10000; i++) {
                t1.push_back(i);
            }
        });

        assert(t1.size() == 5000 && "Deque size should be 5000 after pushing back 5000 elements.");
        assert(t1[4900] == 9900 && "Element at index 4900 should be 9900.");

        benchmark("Push front 5000 elements", [&]() {
            for (int i = 1; i <= 5000; i++) {
                t1.push_front(i);
            }
        });

        assert(t1.size() == 10000 && "Deque size should be 10000 after pushing front 5000 elements.");
        assert(t1.front() == 1 && "Deque front should be 1.");

        benchmark("Pop back 1200 elements", [&]() {
            for (int i = 0; i < 1200; i++) {
                t1.pop_back();
            }
        });
        assert(t1.back() == 8800 && "Deque back should be 8800.");

        benchmark("Pop front 1000 elements", [&]() {
            for (int i = 0; i < 1000; i++) {
                t1.pop_front();
            }
        });
        assert(t1.front() == 1001 && "Deque front should be 1001.");

        deque<int> t2;
        benchmark("Deep copy with operator=", [&]() {
            t2 = t1;
        });
        assert(t2.size() == t1.size() && t2.front() == t1.front() && "Size and front should be the same after deep copying.");
    
        vector<int> v(10000, 114);
        benchmark("Copy constuctor with a vector containing 10000 elements", [&]() {
            deque<int> t3(v);
            assert(t3.size() == 10000 && "Deque size should be 10000 after copy constructed.");
        });

        string str("Hello World.");
        benchmark("Copy constructor with string iterators containing 5 elements", [&]() {
            deque<char> t4(str.begin(), str.begin() + 5);
            assert(t4[0] == 'H');
        });
    }
}

namespace std {
    void testDequeFunctionality() {
        deque<int> t1;

        cout << "Running functionality tests with assertions...\n";

        benchmark("Push back 5000 elements", [&]() {
            for (int i = 5001; i <= 10000; i++) {
                t1.push_back(i);
            }
        });

        assert(t1.size() == 5000 && "Deque size should be 5000 after pushing back 5000 elements.");
        assert(t1[4900] == 9900 && "Element at index 4900 should be 9900.");

        benchmark("Push front 5000 elements", [&]() {
            for (int i = 1; i <= 5000; i++) {
                t1.push_front(i);
            }
        });

        assert(t1.size() == 10000 && "Deque size should be 10000 after pushing front 5000 elements.");
        assert(t1.front() == 1 && "Deque front should be 1.");

        benchmark("Pop back 1200 elements", [&]() {
            for (int i = 0; i < 1200; i++) {
                t1.pop_back();
            }
        });
        assert(t1.back() == 8800 && "Deque back should be 8800.");

        benchmark("Pop front 1000 elements", [&]() {
            for (int i = 0; i < 1000; i++) {
                t1.pop_front();
            }
        });
        assert(t1.front() == 1001 && "Deque front should be 1001.");

        deque<int> t2;
        benchmark("Deep copy with operator=", [&]() {
            t2 = t1;
        });
        assert(t2.size() == t1.size() && t2.front() == t1.front() && "Size and front should be the same after deep copying.");
    
        vector<int> v(10000, 114);
        benchmark("Copy constuctor with a vector containing 10000 elements", [&]() {
            // deque<int> t3(v);
            // assert(t3.size() == 10000 && "Deque size should be 10000 after copy constructed.");
        });

        string str("Hello World.");
        benchmark("Copy constructor with string iterators containing 5 elements", [&]() {
            deque<char> t4(str.begin(), str.begin() + 5);
            assert(t4[0] == 'H');
        });
    }
}

int main() {
    cout << "MyStl::deque<int> benchmark:\n";
    MyStl::testDequeFunctionality();

    cout << "std::deque<int> benchmark\n";
    std::testDequeFunctionality();

    return 0;
}