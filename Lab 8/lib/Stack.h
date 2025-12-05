#pragma once

#include <iostream>
#include <cstddef>

namespace Custom {

    template <typename T>
    class Stack {
    private:
        T* m_data;
        size_t m_size;
        size_t m_capacity;

        void reserve(size_t new_capacity);

    public:
        // --- Constructors ---
        Stack();
        Stack(const Stack<T>& other);
        Stack<T>& operator=(const Stack<T>& other);
        ~Stack();

        // --- Operations ---
        void push(const T& value);
        T& top();
        void pop();
        void clear();


        // --- Capacity ---
        bool isEmpty() const;
        size_t size() const;
        size_t capacity() const;

        // --- Operator Overloading ---
        bool operator==(const Stack<T>& other) const;
        bool operator!=(const Stack<T>& other) const;
        Stack<T> operator+(const Stack<T>& other) const;
        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const Stack<U>& stack);
    };

}

#include "Stack.cpp"
