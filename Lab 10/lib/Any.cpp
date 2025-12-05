#include "Any.h"
#include <algorithm>
#include <climits>

Any::Any() {
    ptr = nullptr;
}

Any::Any(const Any& other) {
    ptr = nullptr;

    if (other.ptr) {
        ptr = other.ptr->clone();
    }
}

Any::~Any() {
    if (ptr) {
        delete ptr;
        ptr = nullptr;
    }
}

Any& Any::operator=(const Any& other) {
    if (this == &other) {
        return *this;
    }

    if (ptr) {
        delete ptr;
        ptr = nullptr;
    }

    if (other.ptr) {
        ptr = other.ptr->clone();
    }

    return *this;
}

std::string Any::type() const {
   if (ptr == nullptr) {
       return "null";
   }
    const std::type_info& ti = ptr->getType();

    if (ti == typeid(int)) {
        return "int";
    } else if (ti == typeid(long)) {
        return "long";
    } else if (ti == typeid(double)) {
        return "double";
    } else if (ti == typeid(bool)) {
        return "bool";
    } else if (ti == typeid(char)) {
        return "char";
    } else if (ti == typeid(std::string)) {
        return "string";
    } else {
        return  ti.name();
    }
}


bool Any::has_value() const {
    return ptr != nullptr;
}

std::ostream& operator<<(std::ostream& os, const Any& a) {
    if (a.ptr) {
        a.ptr->print(os);
    } else {
        os << "null";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Any& a) {
    std::string text;
    is >> text;

    if (text.empty()) {
        return is;
    }

    // Try Boolean
    std::string lower = text;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    if (lower == "true") {
        a = true;
        return is;
    }
    if (lower == "false") {
        a= false;
        return is;
    }

    char* end; // Pointer to where parsing stopped

    // Try Integer and Long (strtol)
    long lVal = std::strtol(text.c_str(), &end, 10);
    if (end != text.c_str() && *end == '\0') {  // Did we consume the ENTIRE string? (*end == 0 means yes)
        if (lVal >= INT_MIN && lVal <= INT_MAX) {
            a = (int)lVal;
        } else {
            a = lVal;
        }
        return is;
    }

    // Try Double (strtod)
    double dVal = std::strtod(text.c_str(), &end);
    if (end != text.c_str() && *end == '\0') {  // Did we consume the ENTIRE string? (*end == 0 means yes)
        a = dVal;
        return is;
    }

    // Try Char
    if (text.length() == 1) {
        a = (char)text[0];
        return is;
    }

    // Fallback to String
    a = text;
    return is;
}