#pragma once
#include "Any.h"
#include <iostream>

class PyList {
private:
    Any* data;
    int capacity;
    int count;

    void expand();

public:
    PyList();
    ~PyList();
    PyList(const PyList& other);
    PyList& operator=(const PyList& other);

    void append(const Any& item);
    void insert(int index, const Any& item);
    Any pop(int index);
    int len() const;

    Any& operator[](int index);

    const Any& operator[](int index) const;

    friend std::ostream& operator<<(std::ostream& os, const PyList& list);
};