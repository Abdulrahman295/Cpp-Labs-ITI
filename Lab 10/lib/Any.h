#pragma once

#include <iostream>
#include <typeinfo>

class Any {
private:
    struct placeholder {
        virtual ~placeholder() = default;
        virtual placeholder* clone() const = 0;
        virtual const std::type_info& getType() const = 0;
        virtual void print(std::ostream& os) const = 0;
    };

    template <typename T>
    struct concrete : placeholder {
        T value;

        concrete(T x) {
            value = x;
        }

        placeholder* clone() const override {
            return new concrete<T>(value);
        }

        const std::type_info& getType() const override {
            return typeid(T);
        }

        void print(std::ostream& os) const override {
            os << value;
        }
    };

    placeholder* ptr;

public:
    Any();
    Any(const Any& other);
    Any& operator=(const Any& other);
    ~Any();

    template <typename T>
    Any(T x) {
        ptr = new concrete<T>(x);
    }

    bool has_value() const;

    std::string type() const;

    template <typename T>
    T& cast() const {
        concrete<T>* p = dynamic_cast<concrete<T>*>(ptr);

        if (p == nullptr) {
            throw "Type Mismatch Error";
        }

        return p->value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Any& a);

    friend std::istream& operator>>(std::istream& is, Any& a);
};