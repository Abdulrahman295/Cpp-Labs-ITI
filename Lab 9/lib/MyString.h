# pragma once

#include <iostream>
#include <cstddef>

namespace Custom {

    class String {
    private:
        char* m_data;
        size_t m_size;
        size_t m_capacity;
        void reserve(size_t new_capacity);

    public:
        // Static constant for "not found"
        static const size_t npos = -1;

        // --- Constructors ---
        String();
        String(const char* str);
        String(const String& other);
        String& operator=(const String& other);
        ~String();

        // --- Size Accessors ---
        size_t length() const;
        size_t capacity() const;
        bool empty() const;;

        // --- Element Access ---
        char& operator[](size_t index);
        char& at(size_t index);
        char& front();
        char& back();

        // --- Modifiers ---
        void clear();
        String& append(const String& str);
        String& insert(size_t pos, const String& str);
        String& erase(size_t pos, size_t len);
        String& replace(size_t pos, size_t len, const String& str);
        String& toUpper();
        String& toLower();

        // --- Operations ---
        String substr(size_t pos = 0, size_t len = npos) const;
        size_t find(const String& str, size_t pos = 0) const;

        // --- Operator Overloads ---
        String& operator+=(const String& other);
        String& operator+=(char c);
        friend String operator+(const String& lhs, const String& rhs);
        friend bool operator==(const String& lhs, const String& rhs);
        friend bool operator!=(const String& lhs, const String& rhs);
        friend bool operator<(const String& lhs, const String& rhs);
        friend bool operator>(const String& lhs, const String& rhs);
        friend bool operator<=(const String& lhs, const String& rhs);
        friend bool operator>=(const String& lhs, const String& rhs);
        friend std::ostream& operator<<(std::ostream& os, const String& str);
        friend std::istream& operator>>(std::istream& is, String& str);
    };
}
