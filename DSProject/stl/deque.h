#ifndef __DEQUE_H__
#define __DEQUE_H__
#include <cstddef>
#include <stdexcept>

namespace MyStl {
    template<class T>
    class deque {
    public:
        deque() { initialize_map(); }
        
        template<class Container>
        deque(const Container& other) {
            initialize_map(); 
            copy(*this, other.begin(), other.end()); 
        }
        
        template<class Iterator>
        deque(const Iterator bg, const Iterator ed) {
            initialize_map(); 
            copy(*this, bg, ed);
        }

        ~deque() { delete[] _map; }

    private:
        T**         _map;
        size_t      _map_capacity;
        size_t      _size;

        size_t      _start_block;
        size_t      _start_offset;
        size_t      _end_block;
        size_t      _end_offset;

        const size_t BLOCK_SIZE = 512;
    
    // iterators
    public:
        class iterator {
        public:
            using value_type        = T;
            using difference_type   = std::ptrdiff_t;
            using pointer           = T*;
            using reference         = T&;

            iterator(size_t idx, deque<T>* container)
                : _idx(idx), _self(container) {}

            iterator() : _idx(0), _self(nullptr) {}

            ~iterator() = default;

            reference operator*() const {
                return (*_self)[_idx];
            }

            pointer operator->() const {
                return &((*_self)[_idx]);
            }

            iterator& operator++() {
                ++_idx;
                return *this;
            }

            iterator operator++(int) {
                iterator temp = *this;
                ++_idx;
                return temp;
            }

            iterator& operator--() {
                --_idx;
                return *this;
            }

            iterator operator--(int) {
                iterator temp = *this;
                --_idx;
                return temp;
            }

            iterator& operator+=(difference_type n) {
                _idx += n;
                return *this;
            }

            iterator& operator-=(difference_type n) {
                _idx -= n;
                return *this;
            }

            difference_type operator-(const iterator& rhs) const {
                return static_cast<difference_type>(this->_idx) -
                       static_cast<difference_type>(rhs._idx);
            }

            bool operator==(const iterator& rhs) const {
                return _idx == rhs._idx && _self == rhs._self;
            }

            bool operator!=(const iterator& rhs) const {
                return !(*this == rhs);
            }

            bool operator<(const iterator& rhs) const {
                return _idx < rhs._idx;
            }

        private:
            size_t      _idx;  
            deque<T>*   _self;        
        };

        iterator begin() {
            return iterator(0, this);     
        }

        iterator end() {
            return iterator(_size, this);  
        }

    // functions
    public:
        void clear() {
            for (int i = 0; i <= _map_capacity; i++) {
                if (_map[i] != nullptr) delete[] _map[i];
            }
            delete[] _map;
            initialize_map();
        }

        bool empty() { return (_size == 0); }
        size_t size() { return _size; }

        T& operator[](const int idx) {
            if (idx >= _size) {
                throw std::out_of_range("Index out of range!");
            }
            size_t cur_block = _start_block + ((_start_offset + idx) / BLOCK_SIZE);
            size_t cur_offset = (_start_offset + idx) % BLOCK_SIZE;
            return _map[cur_block][cur_offset];
        }

        deque<T> operator=(const deque& other) {
            clear();
            copy(*this, other.begin(), other.end());
        }

        T& front() {
            if (_size == 0) {
                throw std::runtime_error("deque is empty, no front()");
            }
            return _map[_start_block][_start_offset];
        }

        T& back() {
            if (_size == 0) {
                throw std::runtime_error("deque is empty, no back()");
            }
            return _map[_end_block][_end_offset];
        }

        void push_front(const T& v) {
            if (_start_block == 0 && _start_offset == 0) {
                extend();
            }

            if (_start_offset > 0) {
                _start_offset--;
                _map[_start_block][_start_offset] = v;
            }
            else {
                _start_block--;
                if (_map[_start_block] == nullptr) {
                    _map[_start_block] = allocate_block();
                }
                _start_offset = BLOCK_SIZE - 1;
                _map[_start_block][_start_offset] = v;
            }

            _size++;
        }

        void push_back(const T& v) {
            if (_end_block == _map_capacity - 1 && _end_offset == BLOCK_SIZE - 1) {
                extend();
            }

            if (_end_offset < BLOCK_SIZE - 1) {
                _end_offset++;
                _map[_end_block][_end_offset] = v;
            } 
            else {
                _end_block++;
                _end_offset = 0;
                if (_map[_end_block] == nullptr) {
                    _map[_end_block] = allocate_block();
                }
                _map[_end_block][_end_offset] = v;
            }

            _size++;
        }

        void pop_front() {
            if (_size == 0) {
                throw std::runtime_error("deque is empty, no pop_front()");
            }
            if (_start_offset == BLOCK_SIZE - 1) {
                _start_block++;
                _start_offset = 0;
            } else {
                _start_offset++;
            }
            _size--;
        }

        void pop_back() {
            if (_size == 0) {
                throw std::runtime_error("deque is empty, no pop_back()");
            }
            if (_end_offset == 0) {
                if (_end_block != 0) {
                    _end_block--;
                    _end_offset = BLOCK_SIZE - 1;
                }
            } else {
                _end_offset--;
            }
            _size--;
        }

    private:
        void initialize_map() {
            _map_capacity   = 8;
            _map            = new T*[_map_capacity];
            for (int i = 0; i < _map_capacity; i++) {
                _map[i] = nullptr;
            }

            _map[0]         = allocate_block();
            _start_block    = 0;
            _start_offset   = 0;
            _end_block      = 0;
            _end_offset     = 0;
            _size           = 0;
        }

        T* allocate_block() {
            return new T[BLOCK_SIZE];
        }

        void extend() {
            size_t new_capacity = _map_capacity * 2;
            T** new_map = new T*[new_capacity];
            for (size_t i = 0; i < new_capacity; i++) {
                new_map[i] = nullptr;
            }

            size_t mid = (new_capacity - (_end_block - _start_block + 1)) / 2;

            for (size_t i = _start_block; i <= _end_block; i++) {
                new_map[mid + (i - _start_block)] = _map[i];
            }

            size_t old_start_block = _start_block;
            _start_block = mid;
            _end_block   = mid + (_end_block - old_start_block);

            delete[] _map;
            _map = new_map;
            _map_capacity = new_capacity;
        }

        template<class Iterator>
        static bool copy(MyStl::deque<T>& self, const Iterator first, const Iterator last) {
            for (; first != last; ++first) {
                self.push_back(*first);
            }
            return true;
        }
    };
}
#endif