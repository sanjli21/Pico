// value.h
#pragma once
#include <string>

enum class ValueType {
    Undefined,
    Number,
    String
};

class Value {
private:
    ValueType type_;
    double number_value_;
    std::string string_value_;

public:
    Value();
    explicit Value(double number);
    explicit Value(const std::string& string);

    ValueType type() const;
    bool is_number() const;
    bool is_string() const;
    bool is_defined() const;

    double get_number() const;
    const std::string& get_string() const;

    std::string to_string() const;

    Value operator+(const Value& other) const;
    Value operator-(const Value& other) const;
    Value operator*(const Value& other) const;
    Value operator/(const Value& other) const;
    Value operator%(const Value& other) const;
};
