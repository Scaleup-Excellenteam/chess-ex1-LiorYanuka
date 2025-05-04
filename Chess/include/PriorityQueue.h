#pragma once

#include <list>
#include <stdexcept>

template<typename T>
struct MyComparator {
    int operator()(const T& a, const T& b) const {
        return a - b;
    }
};

template<typename T>
class PriorityQueue {
private:
    std::list<T> _elements;
    MyComparator<T> _comparator;
    size_t _maxSize;

public:
    PriorityQueue(size_t maxSize = 5) : _maxSize(maxSize) {}

    void push(const T& value) {
        if (_elements.empty()) {
            _elements.push_back(value);
            return;
        }

        // Insert at the correct position - O(n)
        auto it = _elements.begin();
        while (it != _elements.end() && _comparator(value, *it) <= 0) {
            ++it;
        }
        
        _elements.insert(it, value);
        
        if (_maxSize > 0 && _elements.size() > _maxSize) {
            _elements.pop_back();
        }
    }

    T poll() {
        if (_elements.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        
        // Get the first element - O(1)
        T value = _elements.front();
        _elements.pop_front();
        return value;
    }

    bool isEmpty() const {
        return _elements.empty();
    }
    
    size_t size() const {
        return _elements.size();
    }
    
    const T& peek() const {
        if (_elements.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        return _elements.front();
    }
    
    typename std::list<T>::const_iterator begin() const {
        return _elements.begin();
    }
    
    typename std::list<T>::const_iterator end() const {
        return _elements.end();
    }
}; 