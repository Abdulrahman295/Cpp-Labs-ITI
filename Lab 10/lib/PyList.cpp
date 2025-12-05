#include "PyList.h"

PyList::PyList() {
    capacity = 10;
    count = 0;
    data = new Any[capacity];
}

PyList::~PyList() {
    delete[] data;
}

PyList::PyList(const PyList& other) {
    capacity = other.capacity;
    count = other.count;
    data = new Any[capacity];

    for (int i = 0; i < count; i++) {
        data[i] = other.data[i];
    }
}

PyList& PyList::operator=(const PyList& other) {
    if (this == &other) return *this;

    delete[] data;

    capacity = other.capacity;
    count = other.count;
    data = new Any[capacity];

    for (int i = 0; i < count; i++) {
        data[i] = other.data[i];
    }
    return *this;
}

void PyList::expand() {
    int newCapacity = capacity * 2;

    Any* newData = new Any[newCapacity];

    for (int i = 0; i < count; i++) {
        newData[i] = data[i];
    }

    delete[] data;

    data = newData;
    capacity = newCapacity;
}

void PyList::append(const Any& item) {
    if (count >= capacity) {
        expand();
    }
    data[count] = item;
    count++;
}

void PyList::insert(int index, const Any& item) {
    if (index < 0 || index > count) {
        throw "Index out of bounds";
    }

    if (count >= capacity) {
        expand();
    }

    for (int i = count; i > index; i--) {
        data[i] = data[i - 1];
    }

    data[index] = item;
    count++;
}

Any PyList::pop(int index) {
    if (index < 0 || index >= count) {
        throw "Index out of bounds";
    }

    Any savedItem = data[index];


    for (int i = index; i < count - 1; i++) {
        data[i] = data[i + 1];
    }

    count--;
    return savedItem;
}

int PyList::len() const {
    return count;
}

Any& PyList::operator[](int index) {
    if (index < 0 || index >= count) {
        throw "Index out of range";
    }

    return data[index];
}

const Any& PyList::operator[](int index) const {
    if (index < 0 || index >= count) {
        throw "Index out of range";
    }

    return data[index];
}

std::ostream& operator<<(std::ostream& os, const PyList& list) {
    os << "[";
    for (int i = 0; i < list.count; i++) {
        os << list.data[i];
        if (i < list.count - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}