#include "MyString.h"
#include <stdexcept>

namespace Custom {

    size_t stringLength(const char* str) {
        if (!str) return 0;
        size_t len = 0;
        while (str[len] != '\0') {
            len++;
        }
        return len;
    }

    void stringCopy(char* dest, const char* src, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            dest[i] = src[i];
        }
    }

    void stringMove(char* dest, const char* src, size_t count) {
        if (count == 0 || dest == src) return;

        char* temp = new char[count];

        for (size_t i = 0; i < count; i++) {
            temp[i] = src[i];
        }

        for (size_t i = 0; i < count; i++) {
            dest[i] = temp[i];
        }

        delete[] temp;
    }

    int stringCompare(const char* str1, const char* str2) {
        while (*str1 && (*str1 == *str2)) {
            str1++;
            str2++;
        }

        return *str1 - *str2;
    }

    void String::reserve(size_t new_capacity) {
        if (m_data && new_capacity <= m_capacity) return;

        char* new_data = new char[new_capacity + 1];

        if (m_data) {
            stringCopy(new_data, m_data, m_size);
            delete[] m_data;
        }

        m_data = new_data;
        if (m_size == 0) m_data[0] = '\0';
        m_capacity = new_capacity;
    }

    String::String() {
        m_size = 0;
        m_capacity = 0;
        m_data = new char[1];
        m_data[0] = '\0';
    }

    String::String(const char* str) {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;

        if (str) {
            size_t len = stringLength(str);
            m_capacity = len;
            m_data = new char[m_capacity + 1];
            stringCopy(m_data, str, len);
            m_size = len;
            m_data[m_size] = '\0';
        } else {
            m_data = new char[1];
            m_data[0] = '\0';
        }
    }

    String::String(const std::string& str) : m_data(nullptr), m_size(0), m_capacity(0) {
        size_t len = str.length();
        m_capacity = len;
        m_data = new char[m_capacity + 1];
        stringCopy(m_data, str.c_str(), len);
        m_size = len;
        m_data[m_size] = '\0';
    }

    String::~String() {
        delete[] m_data;
    }

    String::String(const String& other) {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
        reserve(other.m_capacity);
        stringCopy(m_data, other.m_data, other.m_size);
        m_size = other.m_size;
        m_data[m_size] = '\0';
    }

    String& String::operator=(const String& other) {
        if (this == &other) {
            return *this;
        }

        char* new_data = new char[other.m_capacity + 1];
        stringCopy(new_data, other.m_data, other.m_size);
        new_data[other.m_size] = '\0';

        delete[] m_data;
        m_data = new_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        return *this;
    }

    size_t String::length() const {
        return m_size;
    }

    size_t String::capacity() const {
        return m_capacity;
    }

    bool String::empty() const {
        return m_size == 0;
    }

    char& String::operator[](size_t index) {
        return m_data[index];
    }

    const char& String::operator[](size_t index) const {
        return m_data[index];
    }

    char& String::at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("String index out of range");
        }
        return m_data[index];
    }

    char& String::front() {
        if (empty()) {
            throw std::out_of_range("String is empty");
        }
        return m_data[0];
    }

    char& String::back() {
        if (empty()) {
            throw std::out_of_range("String is empty");
        }
        return m_data[m_size - 1];
    }

    String::iterator String::begin() {
        return m_data;
    }

    String::iterator String::end() {
        return m_data + m_size;
    }

    String::const_iterator String::begin() const {
        return m_data;
    }

    String::const_iterator String::end() const {
        return m_data + m_size;
    }

    void String::clear() {
        m_size = 0;
        if (m_data) m_data[0] = '\0';
    }

    String& String::append(const String& str) {
        if (str.empty()) return *this;

        size_t needed = m_size + str.m_size;
        if (needed > m_capacity) {
            size_t double_cap = m_capacity * 2;
            size_t next_capacity = (double_cap > needed) ? double_cap : needed;
            reserve(next_capacity);
        }

        stringCopy(m_data + m_size, str.m_data, str.m_size);
        m_size += str.m_size;
        m_data[m_size] = '\0';
        return *this;
    }

    String& String::append(size_t count, char c) {
        if (count == 0) {
            return *this;
        }

        if (m_size + count > m_capacity) {
            size_t next = m_capacity * 2;
            if (next < m_size + count) next = m_size + count;
            reserve(next);
        }

        for (size_t i = 0; i < count; ++i) {
            m_data[m_size + i] = c;
        }

        m_size += count;
        m_data[m_size] = '\0';
        return *this;
    }

    String& String::insert(size_t pos, const String& str) {
        if (pos > m_size) {
            throw std::out_of_range("Index out of range");
        }

        if (str.empty()) {
            return *this;
        }

        size_t needed = m_size + str.m_size;
        if (needed > m_capacity) {
            size_t double_cap = m_capacity * 2;
            size_t next_capacity = (double_cap > needed) ? double_cap : needed;
            reserve(next_capacity);
        }

        stringMove(m_data + pos + str.m_size, m_data + pos, m_size - pos);
        stringCopy(m_data + pos, str.m_data, str.m_size);

        m_size += str.m_size;
        m_data[m_size] = '\0';
        return *this;
    }

    String& String::insert(size_t pos, size_t count, char c) {
        if (pos > m_size) {
            throw std::out_of_range("Index out of range");
        }

        if (count == 0) {
            return *this;
        }

        if (m_size + count > m_capacity) {
            size_t next = m_capacity * 2;
            if (next < m_size + count) next = m_size + count;
            reserve(next);
        }

        stringMove(m_data + pos + count, m_data + pos, m_size - pos);

        for (size_t i = 0; i < count; ++i) {
            m_data[pos + i] = c;
        }

        m_size += count;
        m_data[m_size] = '\0';
        return *this;
    }

    String& String::erase(size_t pos, size_t len) {
        if (pos > m_size) {
            throw std::out_of_range("Index out of range");
        }

        if (len == 0) {
            return *this;
        }

        if (len == npos || pos + len > m_size) {
            len = m_size - pos;
        }

        stringMove(m_data + pos, m_data + pos + len, m_size - pos - len);

        m_size -= len;
        m_data[m_size] = '\0';
        return *this;
    }

    String& String::replace(size_t pos, size_t len, const String& str) {
        erase(pos, len);
        insert(pos, str);
        return *this;
    }

    String& String::toUpper() {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_data[i] >= 'a' && m_data[i] <= 'z') {
                m_data[i] -= 32;
            }
        }
        return *this;
    }

    String& String::toLower() {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_data[i] >= 'A' && m_data[i] <= 'Z') {
                m_data[i] += 32;
            }
        }
        return *this;
    }

    String String::substr(size_t pos, size_t len) const {
        if (pos > m_size) {
            throw std::out_of_range("Index out of range");
        }

        if (len == npos || pos + len > m_size) {
            len = m_size - pos;
        }

        String result;
        result.reserve(len);
        stringCopy(result.m_data, m_data + pos, len);
        result.m_size = len;
        result.m_data[len] = '\0';
        return result;
    }

    size_t String::find(const String& str, size_t pos) const {
        if (pos > m_size) {
            return npos;
        }

        if (str.m_size == 0) {
            return pos;
        }

        for (size_t i = pos; i <= m_size - str.m_size; ++i) {
            size_t j = 0;
            while (j < str.m_size && m_data[i + j] == str.m_data[j]) {
                j++;
            }
            if (j == str.m_size) {
                return i;
            }
        }

        return npos;
    }

    const char* String::c_str() const {
        return m_data ? m_data : "";
    }

    String& String::operator+=(const String& other) {
        return append(other);
    }

    String& String::operator+=(char c) {
        char temp[2] = {c, '\0'};
        return append(String(temp));
    }

    String operator+(const String& lhs, const String& rhs) {
        String result(lhs);
        result += rhs;
        return result;
    }

    bool operator==(const String& lhs, const String& rhs) {
        if (lhs.m_size != rhs.m_size) return false;
        return stringCompare(lhs.m_data, rhs.m_data) == 0;
    }

    bool operator!=(const String& lhs, const String& rhs) {
        return !(lhs == rhs);
    }

    bool operator<(const String& lhs, const String& rhs) {
        return stringCompare(lhs.m_data, rhs.m_data) < 0;
    }

    bool operator>(const String& lhs, const String& rhs) {
       return  stringCompare(lhs.m_data, rhs.m_data) > 0;
    }

    bool operator<=(const String& lhs, const String& rhs) {
        return !(lhs > rhs);
    }

    bool operator>=(const String& lhs, const String& rhs) {
        return !(lhs < rhs);
    }

    std::ostream& operator<<(std::ostream& os, const String& str) {
        if (str.m_data) {
            os << str.m_data;
        }
        return os;
    }

    std::istream& operator>>(std::istream& is, String& str) {
        char buffer[1024];
        if (is >> buffer) {
            str = String(buffer);
        }
        return is;
    }

}