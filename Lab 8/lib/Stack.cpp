#pragma once

#include "Stack.h"
#include <stdexcept>

namespace Custom {

    template <typename T>
    void Stack<T>::reserve(size_t new_capacity) {
        if (new_capacity <= m_capacity) {
            return;
        }

        T* new_data = new T[new_capacity];

        if (m_data) {
            for (size_t i = 0; i < m_size; ++i) {
                new_data[i] = m_data[i];
            }
            delete[] m_data;
        }

        m_data = new_data;
        m_capacity = new_capacity;
    }

    template <typename T>
    Stack<T>::Stack() {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
        reserve(2);
    }

    template <typename T>
    Stack<T>::~Stack() {
        delete[] m_data;
    }

    template <typename T>
    Stack<T>::Stack(const Stack<T>& other) {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
        
        reserve(other.m_capacity);

        for (size_t i = 0; i < other.m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
        m_size = other.m_size;
    }

    template <typename T>
    Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
        if (this == &other) {
            return *this;
        }

        delete[] m_data;

        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = new T[m_capacity];

        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }

        return *this;
    }

    template <typename T>
    void Stack<T>::push(const T& value) {
        if (m_size == m_capacity) {
            size_t next_cap = (m_capacity == 0) ? 2 : m_capacity * 2;
            reserve(next_cap);
        }

        m_data[m_size] = value;
        m_size++;
    }

    template <typename T>
    void Stack<T>::pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack underflow: Cannot pop from empty stack");
        }

        m_size--;
    }

    template <typename T>
    T& Stack<T>::top() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return m_data[m_size - 1];
    }

    template <typename T>
    bool Stack<T>::isEmpty() const {
        return m_size == 0;
    }

    template <typename T>
    size_t Stack<T>::size() const {
        return m_size;
    }

    template <typename T>
    size_t Stack<T>::capacity() const {
        return m_capacity;
    }

    template <typename T>
    void Stack<T>::clear() {
        m_size = 0;
    }

    template <typename T>
    bool Stack<T>::operator==(const Stack<T>& other) const {
        if (m_size != other.m_size) {
            return false;
        }
        
        for (size_t i = 0; i < m_size; ++i) {
            if (m_data[i] != other.m_data[i]) {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    bool Stack<T>::operator!=(const Stack<T>& other) const {
        return !(*this == other);
    }

    template <typename T>
    Stack<T> Stack<T>::operator+(const Stack<T>& other) const {
        Stack<T> result;
        result.reserve(m_size + other.m_size);

        for (size_t i = 0; i < m_size; ++i) {
            result.push(m_data[i]);
        }

        for (size_t i = 0; i < other.m_size; ++i) {
            result.push(other.m_data[i]);
        }

        return result;
    }

    template <typename U>
    std::ostream& operator<<(std::ostream& os, const Stack<U>& stack) {
        os << "[ ";
        for (size_t i = 0; i < stack.m_size; ++i) {
            os << stack.m_data[i];
            if (i < stack.m_size - 1) os << ", ";
        }
        os << " ]";
        return os;
    }

}