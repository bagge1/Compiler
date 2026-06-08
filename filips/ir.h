#include "parser.tab.hh"
#include <bits/stdc++.h>
#include "value.h"
#include "symbol_table.h"
#pragma once;

extern Node* root;

class opcode{
public:

    enum class ByteCodeOpcode
    {
        // constants
        CONST_INT,
        CONST_FLOAT,
        CONST_BOOL,

        // locals
        LOAD_LOCAL,
        STORE_LOCAL,

        // arithmetic
        ADD,
        SUB,
        MUL,
        DIV,
        POW,
        NEG,

        // boolean logic
        AND,
        OR,
        NOT,

        // comparisons
        CMP_EQ,
        CMP_NEQ,
        CMP_LT,
        CMP_GT,
        CMP_LTE,
        CMP_GTE,

        // control flow
        JUMP,
        JUMP_IF_FALSE,

        // function calls
        CALL_METHOD,
        RETURN,
        RETURN_VOID,

        // objects / classes
        NEW_OBJECT,
        LOAD_FIELD,
        STORE_FIELD,

        // arrays
        NEW_ARRAY,
        ARRAY_LOAD,
        ARRAY_STORE,
        ARRAY_LENGTH,

        // IO
        PRINT,
        READ,

        // program control
        HALT
    };

    ByteCodeOpcode Opcode;

    opcode(ByteCodeOpcode op) : Opcode(op) {}

    string to_string(){
        switch(Opcode){
            case ByteCodeOpcode::CONST_INT: return "CONST_INT";
            case ByteCodeOpcode::CONST_FLOAT: return "CONST_FLOAT";
            case ByteCodeOpcode::CONST_BOOL: return "CONST_BOOL";

            case ByteCodeOpcode::LOAD_LOCAL: return "LOAD_LOCAL";
            case ByteCodeOpcode::STORE_LOCAL: return "STORE_LOCAL";

            case ByteCodeOpcode::ADD: return "ADD";
            case ByteCodeOpcode::SUB: return "SUB";
            case ByteCodeOpcode::MUL: return "MUL";
            case ByteCodeOpcode::DIV: return "DIV";
            case ByteCodeOpcode::POW: return "POW";

            case ByteCodeOpcode::AND: return "AND";
            case ByteCodeOpcode::OR: return "OR";
            case ByteCodeOpcode::NOT: return "NOT";

            case ByteCodeOpcode::CMP_EQ: return "CMP_EQ";
            case ByteCodeOpcode::CMP_NEQ: return "CMP_NEQ";
            case ByteCodeOpcode::CMP_LT: return "CMP_LT";
            case ByteCodeOpcode::CMP_GT: return "CMP_GT";
            case ByteCodeOpcode::CMP_LTE: return "CMP_LTE";
            case ByteCodeOpcode::CMP_GTE: return "CMP_GTE";

            case ByteCodeOpcode::JUMP: return "JUMP";
            case ByteCodeOpcode::JUMP_IF_FALSE: return "JUMP_IF_FALSE";

            case ByteCodeOpcode::CALL_METHOD: return "CALL_METHOD";
            case ByteCodeOpcode::RETURN: return "RETURN";
            case ByteCodeOpcode::RETURN_VOID: return "RETURN_VOID";

            case ByteCodeOpcode::NEW_OBJECT: return "NEW_OBJECT";
            case ByteCodeOpcode::LOAD_FIELD: return "LOAD_FIELD";
            case ByteCodeOpcode::STORE_FIELD: return "STORE_FIELD";

            case ByteCodeOpcode::NEW_ARRAY: return "NEW_ARRAY";
            case ByteCodeOpcode::ARRAY_LOAD: return "ARRAY_LOAD";
            case ByteCodeOpcode::ARRAY_STORE: return "ARRAY_STORE";
            case ByteCodeOpcode::ARRAY_LENGTH: return "ARRAY_LENGTH";

            case ByteCodeOpcode::PRINT: return "PRINT";
            case ByteCodeOpcode::READ: return "READ";

            case ByteCodeOpcode::HALT: return "HALT";
        }

        return "UNKNOWN";
    }
};

class ByteCode{
    public:
    opcode op;
    int arg1;
    int arg2;
    string arg1_str;
    string arg2_str;
    ByteCode(opcode op, int arg1 = 0, int arg2 = 0, string arg1_str = "", string arg2_str = ""): op(op), arg1(arg1), arg2(arg2), arg1_str(arg1_str), arg2_str(arg2_str) {};
    string to_string(){
        return op.to_string() + " " + arg1_str + " " + arg2_str;
    }
};

class Expression{
    public:
    Value val_result;
    string result;
    virtual string get_string(){
        return result;
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        // This does nothing since there is no basic expression.
    }
    // "load" or "store"
    virtual void generate_BC_for_value(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map,Value * value, string LoadOrStore = "load"){
        ByteCode * BC;
        switch(value->type){
            case ValueType::CONSTANT_INT:{
                BC = new ByteCode(opcode(opcode::ByteCodeOpcode::CONST_INT),stoi(value->constant_str),0,value->constant_str);
                bytecode.push_back(BC);
                break;
            } 
            case ValueType::CONSTANT_BOOL:{
                BC = new ByteCode(opcode(opcode::ByteCodeOpcode::CONST_BOOL), value->constant_str == "true" ? 1 : 0,0,value->constant_str);
                bytecode.push_back(BC);
                break;
            }
            case ValueType::CONSTANT_FLOAT:{
                int bits;
                float f = stof(value->constant_str);
                memcpy(&bits, &f, sizeof(float));
                BC = new ByteCode(opcode(opcode::ByteCodeOpcode::CONST_FLOAT),bits,0,value->constant_str);
                bytecode.push_back(BC);
                break;
            }
            case ValueType::VARIABLE: {
                if(local_map.find(value->name) != local_map.end()){
                    BC = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::LOAD_LOCAL : opcode::ByteCodeOpcode::STORE_LOCAL),local_map[value->name],0,value->name);
                    bytecode.push_back(BC);
                    break;
                }
                else if(field_map.find(value->name) != field_map.end()){
                    ByteCode * load_field = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_LOCAL),0,0,"this");
                    BC = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::LOAD_FIELD : opcode::ByteCodeOpcode::STORE_FIELD),field_map[value->name],0,value->name);
                    bytecode.push_back(load_field);
                    bytecode.push_back(BC);
                    break;
                }
                else{
                    cout << "Something is very wrong! Variable " << value->name << " was not found in bytegen" << endl;
                }
            }
            case ValueType::ClassField: {
                if(local_map.find(value->name) != local_map.end()){
                    BC = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::LOAD_LOCAL : opcode::ByteCodeOpcode::STORE_LOCAL),local_map[value->name],0,value->name);
                    bytecode.push_back(BC);
                    break;
                }
                else if(field_map.find(value->name) != field_map.end()){
                    ByteCode * load_field = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_LOCAL), 0, 0 , "this");
                    BC = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::LOAD_FIELD : opcode::ByteCodeOpcode::STORE_FIELD),field_map[value->name],0,value->name);
                    bytecode.push_back(load_field);
                    bytecode.push_back(BC);
                    break;
                }
                else{
                    cout << "Something is very wrong! Variable " << value->name << " was not found in bytegen" << endl;
                }
            }
            case ValueType::TEMPORARY: {
                if(local_map.find(value->name) != local_map.end()){
                    BC = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::LOAD_LOCAL : opcode::ByteCodeOpcode::STORE_LOCAL),local_map[value->name],0,value->name);
                    bytecode.push_back(BC);
                    break;
                }
                else{
                    cout << "Something is very wrong! Temp " << value->name << " was not found in bytegen" << endl;
                }
            }
            case ValueType::ARRAY_ELEMENT: {
                if(local_map.find(value->array_name) != local_map.end()){
                    BC = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_LOCAL),local_map[value->array_name],0,value->array_name);
                    switch(value->index_val->type){
                        case ValueType::CONSTANT_INT:{
                            
                            ByteCode * index = new ByteCode(opcode(opcode::ByteCodeOpcode::CONST_INT),stoi(value->index_val->constant_str),0,value->index_val->constant_str);
                            bytecode.push_back(BC);
                            bytecode.push_back(index);
                            ByteCode * load_element = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::ARRAY_LOAD : opcode::ByteCodeOpcode::ARRAY_STORE));
                            bytecode.push_back(load_element);
                            break;
                        }
                        case ValueType::VARIABLE:{
                            if(local_map.find(value->index_val->name) != local_map.end()){
                                ByteCode * index = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_LOCAL),local_map[value->index_val->name],0,value->index_val->name);
                                bytecode.push_back(BC);
                                bytecode.push_back(index);
                                ByteCode * load_element = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::ARRAY_LOAD : opcode::ByteCodeOpcode::ARRAY_STORE));
                                bytecode.push_back(load_element);
                                break;
                            }
                            else if(field_map.find(value->index_val->name) != field_map.end()){
                                ByteCode * index_load_field = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_LOCAL), 0, 0, "this");
                                ByteCode * index = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_FIELD),field_map[value->index_val->name],0,value->index_val->name);
                                bytecode.push_back(BC);
                                bytecode.push_back(index_load_field);
                                bytecode.push_back(index);
                                ByteCode * load_element = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::ARRAY_LOAD : opcode::ByteCodeOpcode::ARRAY_STORE));
                                bytecode.push_back(load_element);
                                break;
                            }
                        }
                        case ValueType::TEMPORARY:{
                            if(local_map.find(value->index_val->name) != local_map.end()){
                                ByteCode * index = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_LOCAL),local_map[value->index_val->name],0,value->index_val->name);
                                bytecode.push_back(BC);
                                bytecode.push_back(index);
                                ByteCode * load_element = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::ARRAY_LOAD : opcode::ByteCodeOpcode::ARRAY_STORE));
                                bytecode.push_back(load_element);
                                break;
                            }
                            else if(field_map.find(value->index_val->name) != field_map.end()){
                                ByteCode * index_load_field = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_LOCAL), 0, 0, "this");
                                ByteCode * index = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_FIELD),field_map[value->index_val->name],0,value->index_val->name);
                                bytecode.push_back(BC);
                                bytecode.push_back(index_load_field);
                                bytecode.push_back(index);
                                ByteCode * load_element = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::ARRAY_LOAD : opcode::ByteCodeOpcode::ARRAY_STORE));
                                bytecode.push_back(load_element);
                                break;
                            }
                        }
                    }
                }
                else if(field_map.find(value->array_name) != field_map.end()){
                    ByteCode * load_field = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_LOCAL), 0, 0, "this");
                    BC = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_FIELD),field_map[value->array_name],0, value->array_name);
                    switch(value->index_val->type){
                        case ValueType::CONSTANT_INT:{
                            ByteCode * index = new ByteCode(opcode(opcode::ByteCodeOpcode::CONST_INT),stoi(value->index_val->constant_str),0,value->index_val->constant_str);
                            bytecode.push_back(load_field);
                            bytecode.push_back(BC);
                            bytecode.push_back(index);
                            ByteCode * load_element = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::ARRAY_LOAD : opcode::ByteCodeOpcode::ARRAY_STORE));
                            bytecode.push_back(load_element);
                            break;
                        }
                        case ValueType::VARIABLE:{
                            if(local_map.find(value->index_val->name) != local_map.end()){
                                ByteCode * index = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_LOCAL),local_map[value->index_val->name],0,value->index_val->name);
                                bytecode.push_back(load_field);
                                bytecode.push_back(BC);
                                bytecode.push_back(index);
                                ByteCode * load_element = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::ARRAY_LOAD : opcode::ByteCodeOpcode::ARRAY_STORE));
                                bytecode.push_back(load_element);
                                break;
                            }
                            else if(field_map.find(value->index_val->name) != field_map.end()){
                                ByteCode * index_load_field = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_LOCAL), 0, 0, "this");
                                ByteCode * index = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_FIELD),field_map[value->index_val->name],0,value->index_val->name);
                                bytecode.push_back(load_field);
                                bytecode.push_back(BC);
                                bytecode.push_back(index_load_field);
                                bytecode.push_back(index);
                                ByteCode * load_element = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::ARRAY_LOAD : opcode::ByteCodeOpcode::ARRAY_STORE));
                                bytecode.push_back(load_element);
                                break;
                            }
                        }
                        case ValueType::TEMPORARY:{
                            if(local_map.find(value->index_val->name) != local_map.end()){
                                ByteCode * index = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_LOCAL),local_map[value->index_val->name],0,value->index_val->name);
                                bytecode.push_back(load_field);
                                bytecode.push_back(BC);
                                bytecode.push_back(index);
                                ByteCode * load_element = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::ARRAY_LOAD : opcode::ByteCodeOpcode::ARRAY_STORE));
                                bytecode.push_back(load_element);
                                break;
                            }
                            else if(field_map.find(value->index_val->name) != field_map.end()){
                                ByteCode * index_load_field = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_LOCAL), 0 , 0, "this");
                                ByteCode * index = new ByteCode(opcode(opcode::ByteCodeOpcode::LOAD_FIELD),field_map[value->index_val->name],0,value->index_val->name);
                                bytecode.push_back(load_field);
                                bytecode.push_back(BC);
                                bytecode.push_back(index_load_field);
                                bytecode.push_back(index);
                                ByteCode * load_element = new ByteCode(opcode(LoadOrStore == "load" ? opcode::ByteCodeOpcode::ARRAY_LOAD : opcode::ByteCodeOpcode::ARRAY_STORE));
                                bytecode.push_back(load_element);
                                break;
                            }
                        }
                    }
                }
                else{
                    cout << "Something is very wrong! Variable " << value->name << " was not found in bytegen" << endl;
                }
            }
        }
    }
};

class Factor : public Expression{
    public:
    virtual string get_string(){
        return result;
    }
    
};

class OpExpression : public Expression{
    public:
    Value val_left, val_right;
    string left, op, right;
    virtual string get_string(){
        return result + " := " + left + " " + op + " " + right;
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        generate_BC_for_value(bytecode,local_map,field_map, &val_left, "load");
        generate_BC_for_value(bytecode,local_map,field_map, &val_right, "load");
        if(op == "+")      bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::ADD));
        else if(op == "-") bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::SUB));
        else if(op == "*") bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::MUL));
        else if(op == "/") bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::DIV));
        else if(op == "^") bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::POW));
        else if(op == "&") bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::AND));
        else if(op == "|") bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::OR));
        else if(op == "=")  bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::CMP_EQ));
        else if(op == "!=") bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::CMP_NEQ));
        else if(op == "<")  bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::CMP_LT));
        else if(op == ">")  bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::CMP_GT));
        else if(op == "<=") bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::CMP_LTE));
        else if(op == ">=") bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::CMP_GTE));
        else cout << "Unrecognised operator " << op << endl;
        if(val_result.type != ValueType::ARRAY_ELEMENT) generate_BC_for_value(bytecode,local_map,field_map, &val_result, "store");
        else{
            cout << "Array indexing result in OP Expression THIS IS WRONG!" << endl;
        }

    }
};

class Unary: public Expression{
    public:
    string op;
    virtual string get_string(){
        return op + " " + result;
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        
        if(op == "param") generate_BC_for_value(bytecode,local_map,field_map, &val_result, "load"); // I just load the var in the stack this does nothing else
        else if(op == "print"){
            generate_BC_for_value(bytecode,local_map,field_map, &val_result, "load");
            bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::PRINT));
        }
        else if(op == "read"){
            bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::READ));
            generate_BC_for_value(bytecode,local_map,field_map, &val_result, "store");
        }
        else if(op == "return"){
            generate_BC_for_value(bytecode,local_map,field_map, &val_result, "load");
            bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::RETURN));
        }
        else{
            cout << "Unary not asssigned in IR " << op << endl;
        }
    }
};

class AssignUnary: public Unary{
public:
    Value val_right;
    string right;
    virtual string get_string(){
        return result + " := " + op + " " + right;
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        generate_BC_for_value(bytecode,local_map,field_map, &val_right, "load");
        if(op == "length") bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::ARRAY_LENGTH));
        else if(op == "!") bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::NOT));
        else{
            cout << "Unary not asssigned in IR " << op << endl;
        }
        generate_BC_for_value(bytecode,local_map,field_map, &val_result, "store");
    }
};

class ArrayIndexExpression: public Expression{
    public:
    Value val_array;
    string array;
    Value val_index;
    string index;
    virtual string get_string(){
        return array + "[" + index + "]";
    }
};

class VarDecStatement : public Expression{
    public:
    string type;
    virtual string get_string(){
        return result + " := New " + type;
    }
};

class ArrayCreationExpression : public Expression{
    public:
    int amount;
    string type;
    virtual string get_string(){
        return result + " := New " + type + "," + to_string(amount);   
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::CONST_INT, amount,0,to_string(amount)));
        bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::NEW_ARRAY));
        generate_BC_for_value(bytecode,local_map,field_map, &val_result, "store");
    }
};

class AssignStatement : public Expression{
    public:
    Value val_right;
    string right;
    virtual string get_string(){
        return result + " := " + right;   
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        generate_BC_for_value(bytecode,local_map,field_map, &val_right, "load");
        generate_BC_for_value(bytecode,local_map,field_map, &val_result, "store");
    }
};




class Block{
    private:
    static int next_id;
    int local_id;
    public:
    string name;
    list<Expression*> expressions;
    vector<ByteCode*> code;
    Block *true_end, *false_end;

    // print with cycle detection so we don't revisit the same block twice
    void print_block(std::unordered_set<Block*>& visited){
        if(visited.count(this))
            return;
        visited.insert(this);

        cout << name << ":" << endl;
        for(auto expression = expressions.begin(); expression != expressions.end(); expression++){
            cout << (*expression)->get_string() << endl;
        }
        cout << "True end: " << (true_end ? true_end->name : "null") << endl;
        cout << "False end: " << (false_end ? false_end->name : "null") << endl << endl;

        if(true_end) true_end->print_block(visited);
        if(false_end) false_end->print_block(visited);
    }

    void print_ByteCode(std::unordered_set<Block*>& visited){
        if(visited.count(this))
            return;
        visited.insert(this);

        cout << name << ":" << endl;
        for(auto bytecode = code.begin(); bytecode != code.end(); bytecode++){
            cout << (*bytecode)->to_string() << endl;
        }
        cout << "True end: " << (true_end ? true_end->name : "null") << endl;
        cout << "False end: " << (false_end ? false_end->name : "null") << endl << endl;

        if(true_end) true_end->print_ByteCode(visited);
        if(false_end) false_end->print_ByteCode(visited);
    }

    void generate_tree(list<Block*> blocks) {
        std::ofstream outStream;
        const char* filename = "IR_tree.dot";
        outStream.open(filename);

        int count = 0;
        std::unordered_set<Block*> visited;
        outStream << "digraph {" << std::endl;
        for(auto block = blocks.begin();block != blocks.end(); block++){
            (*block)->generate_tree_content(count, &outStream, visited);
        }
        outStream << "}" << std::endl;
        outStream.close();

        printf("\nBuilt a parse-tree at %s. Use 'make IR_tree' to generate the pdf version.\n", filename);
    }

    void generate_tree_content(int &count, ofstream *outStream, std::unordered_set<Block*>& visited){
        static std::unordered_map<Block*, int> ids;
        if(!ids.count(this)) {
            ids[this] = count++;
        }
        int myid = ids[this];
        if(visited.count(this))
            return;
        visited.insert(this);
        string label = name;
        for (auto expression = expressions.begin(); expression != expressions.end(); expression++){
            label += "\\n" + (*expression)->get_string();
        }
        *outStream << "n" << myid << " [shape=box,label=\"" << label << "\"];" << endl;
        if(true_end){
            if (!ids.count(true_end))
                ids[true_end] = count++;

            int child_id = ids[true_end];
            *outStream << "n" << myid << " -> n" << child_id << " [label=\"true\"];" << endl;

            true_end->generate_tree_content(count, outStream, visited);
        }

        if(false_end) {
            if (!ids.count(false_end))
                ids[false_end] = count++;

            int child_id = ids[false_end];
            *outStream << "n" << myid << " -> n" << child_id << " [label=\"false\"];" << endl;

            false_end->generate_tree_content(count, outStream, visited);
        }
    }

    void generateByteCoderec(unordered_set<Block*>& visited, unordered_map<string,int>& method_local_map, unordered_map<string,int>& class_field_map){
        if(visited.count(this))
            return;
        visited.insert(this);
        for(auto instruction = expressions.begin(); instruction != expressions.end(); instruction++){
           (*instruction)->generateByteCode(code, method_local_map, class_field_map);
        }
        if(true_end != nullptr) code.push_back(new ByteCode(opcode::ByteCodeOpcode::JUMP,0,0,true_end->name));
        else if(false_end != nullptr) code.push_back(new ByteCode(opcode::ByteCodeOpcode::JUMP,0,0,false_end->name));
        else{
            bool foundmain = false;
            for(auto block = visited.begin(); block != visited.end(); block++){
                if((*block)->name == "main"){
                    foundmain = true;
                    break;
                }
            }
            if(foundmain) code.push_back(new ByteCode(opcode::ByteCodeOpcode::HALT));
            else code.push_back(new ByteCode(opcode::ByteCodeOpcode::RETURN_VOID));
        
        }

        if(true_end) true_end->generateByteCoderec(visited,method_local_map,class_field_map);
        if(false_end) false_end->generateByteCoderec(visited,method_local_map,class_field_map);
    }

    Block(){
        local_id = ++next_id;
        name = "Block_" + to_string(local_id);
        true_end = false_end = nullptr;
    }
    // used in interpreter since we already have names then.
    Block(bool){
        true_end = false_end = nullptr;
    }
};

class MethodInfo{
    public:
    int scope_id;
    string name;
    list<string> args;
};

class ClassInfo{
    public:
    int scope_id;
    string name;
    unordered_map<string, Value> classvars;
    list<MethodInfo*> methods_info;
    list<Block*> methods;
};

class MethodCallExpression: public Expression{
    public:
    Block * method_block;
    string str_block;
    Value * classfield;
    int arg_amount;
    virtual string get_string(){
        return "Call " + str_block + to_string(arg_amount); 
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        generate_BC_for_value(bytecode,local_map,field_map, classfield, "load");
        bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::CALL_METHOD,0,arg_amount,str_block,to_string(arg_amount)));
    }
    
};

class FunctionCallExpression: public Expression{
    public:
    Block * method_block;
    string str_block;
    Value * classfield;
    int arg_amount;
    virtual string get_string(){
        return "Call " + str_block + to_string(arg_amount); 
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::LOAD_LOCAL,0,0,"this"));
        bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::CALL_METHOD,0,arg_amount,str_block,to_string(arg_amount)));

    }
    
};

class AssignMethodCallExpression: public Expression{
    public:
    Block * method_block;
    string str_block;
    Value * classfield;
    int arg_amount;
    virtual string get_string(){
        return result + " := Call " + str_block  + ", " + to_string(arg_amount); 
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        generate_BC_for_value(bytecode,local_map,field_map, classfield, "load");
        bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::CALL_METHOD,0,arg_amount,str_block,to_string(arg_amount)));
        generate_BC_for_value(bytecode,local_map,field_map, &val_result, "store");
    }
};

class AssignFunctionCallExpression: public Expression{
    public:
    Block * method_block;
    string str_block;
    Value * classfield;
    int arg_amount;
    virtual string get_string(){
        return result + " := Call " + str_block  + ", " + to_string(arg_amount); 
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::LOAD_LOCAL,0,0,"this"));
        bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::CALL_METHOD,0,arg_amount,str_block,to_string(arg_amount)));
        generate_BC_for_value(bytecode,local_map,field_map, &val_result, "store");
    }
};

class ClassfieldCreationExpression: public Expression{
    public:
    ClassInfo * classinfo;
    virtual string get_string(){
        return result + " := New " + classinfo->name;   
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::NEW_OBJECT,0,0,classinfo->name));
        generate_BC_for_value(bytecode,local_map,field_map, &val_result, "store");
    }
};

class GoTo : public Expression{
    public:
    Block * block;
    string str_block;
    virtual string get_string(){
        return "GoTo " + str_block; 
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::JUMP,0,0,str_block));
    }
};

class IfStatement : public Expression{
    public:
    string cond;
    Value val_cond;
    string str_block;
    Block* block;
    virtual string get_string(){
        return "Iffalse " + cond + " Goto " + str_block;   
    }
    virtual void generateByteCode(vector<ByteCode*>& bytecode, unordered_map<string, int> local_map, unordered_map<string, int> field_map){
        generate_BC_for_value(bytecode,local_map,field_map, &val_cond, "load");
        bytecode.push_back(new ByteCode(opcode::ByteCodeOpcode::JUMP_IF_FALSE,0,0,str_block));
    }
};

// reprecentation of classes and methods for the interpreter.


class Method;

class Class{
    public:
    string name;
    list<Method*> methods;
    unordered_map<string, int> field_var_map;
    Class(string name, unordered_map<string, int> field_var_map){
        this->name = name;
        this->field_var_map = field_var_map;
    }
};

class Method{
    public:
    int args_amount;
    string name;
    Block * start;
    Class * owner;
    MethodInfo * info;
    unordered_map<string, int> local_var_map;
    unordered_map<string, int> class_field_map;
    Method(string name, Block* start, Class* owner, MethodInfo* info = nullptr){
        this->name = name;
        this->start = start;
        this->owner = owner;
        this->info = info;
        if(owner != nullptr) this->class_field_map = owner->field_var_map;
        if(info) args_amount = info->args.size();
        else args_amount = 0;

        if(owner != nullptr) local_var_map["this"] = 0;

        unordered_set<Block*> visited;
        build_locals(start, visited);
        unordered_set<Block*> visited2;
        start->generateByteCoderec(visited2, local_var_map, class_field_map);
    }
    Method(){
    }
    private:
    void build_locals(Block* block, unordered_set<Block*>& visited){
        if(visited.count(block))
            return;
        visited.insert(block);
        if(info){
            for(auto args = info->args.begin(); args != info->args.end(); args++){
                if(!local_var_map.count(*args)){
                    local_var_map[*args] = local_var_map.size();
                }
            }
        }
        for(auto expression = block->expressions.begin(); expression != block->expressions.end(); expression++){
            string name = (*expression)->result;
            size_t pos = name.find('[');
            if(pos != string::npos)
                name = name.substr(0, pos);
            if(name != "" && name[0] != '$' && !local_var_map.count(name)){
                if(owner != nullptr){
                    if(!owner->field_var_map.count(name)) local_var_map[name] = local_var_map.size();
                }
                else{
                    local_var_map[name] = local_var_map.size();
                }
            }
        }
        if(block->true_end) build_locals(block->true_end, visited);
        if(block->false_end) build_locals(block->false_end, visited);
    }
};

class Program{
    public:
    list<Class*> classes;
    Method * main;
};



class ir
{
private:
    /* data */
    int variable = 1;
    int next_scope_id = 0;
    symbol_table st;
    Block * main;
    list<ClassInfo*> classes;
    stack<Block*> break_stack;
    stack<Block*> continue_stack;
    //For recursive methods
    list<Block*> found_methods;
    void generate_rec(Node* parent, Block * block, int scopeid);
    void emitbytecode_blocks(ofstream&, Block*,unordered_set<Block*>&);
    void emitbytecode_varmap(ofstream&, unordered_map<string, int>);
    void emitbytecode_class(ofstream & ,Class *);
    Expression * expressions(Node* parent, Block * current_block, int scopeid);
    Block * block_statement(Node* parent, Block * current_block, int scopeid);
    void simple_statement(Node* parent, Block * block, int scopeid);
    string new_temp_var(){
        return("t" + to_string(variable++));
    }
    int find_break_amount_for(Node * parent){
        int break_amount = 0;
        for(auto children = parent->children.begin(); children != parent->children.end(); children++){
            if((*children)->type == "BreakStatement") break_amount++;
            if((*children)->type != "ForStatement") break_amount += find_break_amount_for((*children));
        }
        return break_amount;
    }
    int find_continue_amount_for(Node * parent){
        int continue_amount = 0;
        for(auto children = parent->children.begin(); children != parent->children.end(); children++){
            if((*children)->type == "ContinueStatement") continue_amount++;
            if((*children)->type != "ForStatement") continue_amount += find_continue_amount_for((*children));
        }
        return continue_amount;
    }
    void make_classes(Node* parent){
        for(auto children = parent->children.begin(); children != parent->children.end(); children++){
            found_methods.clear();
            next_scope_id++;
            ClassInfo * klass = new ClassInfo();
            klass->scope_id = next_scope_id;
            klass->name = (*children)->value;
            Node * classargs = *(*children)->children.begin();
            for(auto arg = classargs->children.begin(); arg != classargs->children.end(); arg++){
                if((*arg)->type == "Variable"){
                    Value v;
                    v.type = ValueType::VARIABLE;
                    v.name = (*arg)->value;
                    klass->classvars[(*arg)->value] = v;
                }
                else if((*arg)->type == "Method"){
                    next_scope_id++;
                    Block * method_block = new Block();
                    MethodInfo * method_info = new MethodInfo();
                    method_info->scope_id = next_scope_id;
                    method_info->name = (*arg)->value;
                    Node * methodargs = *++(*arg)->children.begin();
                    if(methodargs->type == "methodArgs"){
                        for(auto methodarg = methodargs->children.begin(); methodarg != methodargs->children.end(); methodarg++){
                            method_info->args.push_back((*methodarg)->value);
                        }
                    }
                    klass->methods_info.push_back(method_info);
                    method_block->name = (*arg)->value;
                    found_methods.push_back(method_block);
                    generate_rec((*++++(*arg)->children.begin()), method_block, next_scope_id);
                    klass->methods.push_back(method_block);
                }
            }
            classes.push_back(klass);
        }
    }
    // These are the basic expressions that look like (result = left op right). 
    vector<string> standard_expressions = {
        "AddExpression","SubExpression","MultExpression","DivExpression","PowExpression",
        "OrExpression","AndExpression","EqExpression","NeqExpression","LessExpression",
        "GreaterExpression","GreaterOrEqExpression","LessOrEqExpression"   
    };
    vector<string> length_expression = {
        "lengthExpression"
    };
    vector<string> array_index_expression = {
        "ArrayIndexExpression"
    };
    vector<string> method_call_expression = {
        "MethodCallExpression"
    };
    vector<string> function_call_expression = {
        "FunctionCallExpression"
    };
    vector<string> array_creation_expression = {
        "ArrayCreationExpression"
    };
    vector<string> not_expression = {
        "NotExpression"
    };
    // statements that form or terminate basic blocks (control flow)
    vector<string> block_statements = {
        "IfStatement","ElseStatement","ForStatement",
        "ReturnStatement","BreakStatement","ContinueStatement","Method","Class"
    };

    // simple/straightline statements that emit TAC but do not split blocks
    vector<string> simple_statements = {
        "Variable","AssignStatement","PrintStatement","ReadStatement","ExpressionStatement"
    };
public:
    Program program = Program();
    void generate(symbol_table);
    void generateByteCode();
    void emitbytecode(string);
    ir(/* args */);
    ~ir();
};

