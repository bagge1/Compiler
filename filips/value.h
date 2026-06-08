#pragma once
#include <string>

using namespace std;

enum class ValueType {
    CONSTANT_INT,
    CONSTANT_FLOAT,
    CONSTANT_BOOL,
    VARIABLE,
    TEMPORARY,
    ARRAY_ELEMENT,
    ClassField,
};

struct Value {
    ValueType type;
    string constant_str;
    string name;
    string array_name;
    string index_expr;
    Value * index_val;
    
    string to_string() const {
        switch(type) {
            case ValueType::CONSTANT_INT: return "$" + constant_str;
            case ValueType::CONSTANT_FLOAT: return "$" + constant_str;
            case ValueType::CONSTANT_BOOL: return "$" + constant_str;
            case ValueType::VARIABLE: return name;
            case ValueType::TEMPORARY: return name;
            case ValueType::ClassField: return name;
            case ValueType::ARRAY_ELEMENT: return array_name + "[" + index_expr + "]";
        }
        return "Error";
    }

    static Value make_int(int val) {
        Value v;
        v.type = ValueType::CONSTANT_INT;
        v.constant_str = std::to_string(val);
        return v;
    }

    static Value make_float(float val) {
        Value v;
        v.type = ValueType::CONSTANT_FLOAT;
        v.constant_str = std::to_string(val);
        return v;
    }

    static Value make_bool(bool val) {
        Value v;
        v.type = ValueType::CONSTANT_BOOL;
        v.constant_str = val ? "true" : "false";
        return v;
    }

    static Value make_variable(string var_name) {
        Value v;
        v.type = ValueType::VARIABLE;
        v.name = var_name;
        return v;
    }

    static Value make_classfield(string field_name) {
        Value v;
        v.type = ValueType::ClassField;
        v.name = field_name;
        return v;
    }

    static Value make_temporary(string temp_name) {
        Value v;
        v.type = ValueType::TEMPORARY;
        v.name = temp_name;
        return v;
    }

    static Value make_array_element(string arr_name, string idx_expr, Value * idx_var) {
        Value v;
        v.type = ValueType::ARRAY_ELEMENT;
        v.array_name = arr_name;
        v.index_expr = idx_expr;
        v.index_val = idx_var;
        return v;
    }
};