#include "parser.tab.hh"
#include <bits/stdc++.h>
#include "ir.h"
#pragma once;



enum class ValType {
    INT,
    FLOAT,
    BOOL,
    ARRAY,
    OBJECT,
};
class ArrayObject;
class Object;

class Val{
    public:
    ValType type;
    union{
        int int_val;
        float float_val;
        bool bool_val;
        ArrayObject* arr_ref;
        Object* obj_ref; 
    };

    static Val make_int(int val){
        Val v;
        v.type = ValType::INT;
        v.int_val = val;
        return v;
    }
    static Val make_float(float val){
        Val v;
        v.type = ValType::FLOAT;
        v.float_val = val;
        return v;
    }
    static Val make_bool(bool val){
        Val v;
        v.type = ValType::BOOL;
        v.bool_val = val;
        return v;
    }
    static Val make_array(ArrayObject* ref){
        Val v;
        v.type = ValType::ARRAY;
        v.arr_ref = ref;
        return v;
    }
    static Val make_object(Object* ref){
        Val v;
        v.type = ValType::OBJECT;
        v.obj_ref = ref;
        return v;
    }
};

class ArrayObject{
    public:
    int length;
    vector<Val> elements;
    ArrayObject(int size){
        length = size;
        elements.resize(size);
    }
};

class Object{
    public:
    Class * klass;
    vector<Val> fields;

    Object(Class * c){
        klass = c;
        fields.resize(c->field_var_map.size());
    }
};

class Frame {
public:
    vector<Val> locals;
    Block * current_block;
    int pc; // basically index of code in current block
};

class interpreter{
    private:
    void run(Frame*, Program);
    stack<Val> valstack;
    stack<Frame*> framestack;
    Method * parse_method(ifstream&,bool main = false, Class * klass = nullptr);
    Block * parse_blocks(ifstream&,unordered_set<Block *>&);
    void parse_classes(ifstream& , Program*);
    unordered_map<string,int> parse_varmap(ifstream&);
    public:
    Program parse(ifstream&);
    void interpret(Program);
    interpreter(/* args */);
    ~interpreter();

    vector<string> split(string line) {
        vector<string> parts;
        stringstream ss(line);
        string part;

        while (getline(ss, part, ':')) {
            parts.push_back(part);
        }

        if (line.back() == ':') {
            parts.push_back("");
        }
        return parts;
    }

    #include <string>

    bool isInt(const string s) {
        try {
            size_t pos;
            stoi(s, &pos);
            return pos == s.size(); // ensure entire string was consumed
        } catch (...) {
            return false;
        }
    }

    bool isFloat(const string s) {
        try {
            size_t pos;
            stof(s, &pos);
            return pos == s.size();
        } catch (...) {
            return false;
        }
    }

    opcode::ByteCodeOpcode string_to_opcode(const std::string& op) {
        if (op == "CONST_INT") return opcode::ByteCodeOpcode::CONST_INT;
        else if (op == "CONST_FLOAT") return opcode::ByteCodeOpcode::CONST_FLOAT;
        else if (op == "CONST_BOOL") return opcode::ByteCodeOpcode::CONST_BOOL;

        else if (op == "LOAD_LOCAL") return opcode::ByteCodeOpcode::LOAD_LOCAL;
        else if (op == "STORE_LOCAL") return opcode::ByteCodeOpcode::STORE_LOCAL;

        else if (op == "ADD") return opcode::ByteCodeOpcode::ADD;
        else if (op == "SUB") return opcode::ByteCodeOpcode::SUB;
        else if (op == "MUL") return opcode::ByteCodeOpcode::MUL;
        else if (op == "DIV") return opcode::ByteCodeOpcode::DIV;
        else if (op == "POW") return opcode::ByteCodeOpcode::POW;

        else if (op == "AND") return opcode::ByteCodeOpcode::AND;
        else if (op == "OR") return opcode::ByteCodeOpcode::OR;
        else if (op == "NOT") return opcode::ByteCodeOpcode::NOT;

        else if (op == "CMP_EQ") return opcode::ByteCodeOpcode::CMP_EQ;
        else if (op == "CMP_NEQ") return opcode::ByteCodeOpcode::CMP_NEQ;
        else if (op == "CMP_LT") return opcode::ByteCodeOpcode::CMP_LT;
        else if (op == "CMP_GT") return opcode::ByteCodeOpcode::CMP_GT;
        else if (op == "CMP_LTE") return opcode::ByteCodeOpcode::CMP_LTE;
        else if (op == "CMP_GTE") return opcode::ByteCodeOpcode::CMP_GTE;

        else if (op == "JUMP") return opcode::ByteCodeOpcode::JUMP;
        else if (op == "JUMP_IF_FALSE") return opcode::ByteCodeOpcode::JUMP_IF_FALSE;

        else if (op == "CALL_METHOD") return opcode::ByteCodeOpcode::CALL_METHOD;
        else if (op == "RETURN") return opcode::ByteCodeOpcode::RETURN;
        else if (op == "RETURN_VOID") return opcode::ByteCodeOpcode::RETURN_VOID;

        else if (op == "NEW_OBJECT") return opcode::ByteCodeOpcode::NEW_OBJECT;
        else if (op == "LOAD_FIELD") return opcode::ByteCodeOpcode::LOAD_FIELD;
        else if (op == "STORE_FIELD") return opcode::ByteCodeOpcode::STORE_FIELD;

        else if (op == "NEW_ARRAY") return opcode::ByteCodeOpcode::NEW_ARRAY;
        else if (op == "ARRAY_LOAD") return opcode::ByteCodeOpcode::ARRAY_LOAD;
        else if (op == "ARRAY_STORE") return opcode::ByteCodeOpcode::ARRAY_STORE;
        else if (op == "ARRAY_LENGTH") return opcode::ByteCodeOpcode::ARRAY_LENGTH;

        else if (op == "PRINT") return opcode::ByteCodeOpcode::PRINT;
        else if (op == "READ") return opcode::ByteCodeOpcode::READ;

        else if (op == "HALT") return opcode::ByteCodeOpcode::HALT;
    }
    
};