#include <iostream>
#include <bits/stdc++.h>
#include "parser.tab.hh"
#include "semantic_analysis.h"
#include "symbol_table.h"


extern Node *root;
extern bool semantic_errors;

static int next_scope_id = 0;

// Expression handling
string semantic_analysis::expresions(int scopeid,Node* parent){
    auto found = find(numeric_operation_expression.begin(),numeric_operation_expression.end(),parent->type);
    if(found != numeric_operation_expression.end()){
        auto children = parent->children.begin();
        string left = expresions(scopeid,*children);
        string right = expresions(scopeid,*++children);
        if(right == "TypeError" || left == "TypeError") return("TypeError");
        if(left == "IntType" && right == "IntType") return("IntType");
        if((left == "IntType" && right == "FloatType") || (left == "FloatType" && right == "IntType") || (left == "FloatType" && right == "FloatType"))return("FloatType");
        cout << "Numeric operation between \"" << left <<"\" and \"" << right << "\" is not allowed! line:" <<(*prev(children))->lineno << endl;
        semantic_errors = true;
        return ("TypeError");
    }
    found = find(boolean_operation_expression.begin(),boolean_operation_expression.end(),parent->type);
    if(found != boolean_operation_expression.end()){
        auto children = parent->children.begin();
        string left = expresions(scopeid,*children);
        string right = expresions(scopeid,*++children);
        if(right == "TypeError" || left == "TypeError"){
            return"TypeError";
        }
        if(left != "BoolType" || right != "BoolType"){
            cout << "ERROR: Using \"" << parent->value <<"\" between "<< left <<" and " << right<< " is not allowed! line:" << (*--children)->lineno << endl;
            semantic_errors = true;
            return "TypeError";
        }
        return "BoolType";
    }
    found = find(compare_operation_expression.begin(),compare_operation_expression.end(),parent->type);
    if(found != compare_operation_expression.end()){
        auto children = parent->children.begin();
        string left = expresions(scopeid,*children);
        string right = expresions(scopeid,*++children);
        if(right == "TypeError" || left == "TypeError"){
            // cout << "ERROR: one of the expressions have an error. line:" << (*--children)->lineno << endl;
            return("TypeError");
        }
        if(!((right=="BoolType" && left=="BoolType")||((left == "FloatType" || left=="IntType")&&(right == "FloatType"|| right =="IntType")))){
            cout << "ERROR: Cannot compare numeric to a boolean type. line:" << (*--children)->lineno << endl;
            semantic_errors = true;
            return("TypeError");
        }
        return("BoolType");
    }
    found = find(length_expression.begin(),length_expression.end(),parent->type);
    if(found != length_expression.end()){
        auto child = parent->children.begin();
        if((*child)->type != "Id"){
            cout << "length can only be used on an identifier! line:" << (*child)->lineno << endl;
            semantic_errors = true;
            return("TypeError");
        }else{
            symbol * identifier = Symbol_table.find_symbol_in_scope(scopeid,(*child)->value);
            if(identifier == nullptr){
                cout << "ERROR: Identifier: \"" << (*child)->value << "\" Not defined in this scope! line:" << (*child)->lineno << endl;
                semantic_errors = true;
                return("TypeError");
            }
            if(identifier->id_type != "ArrayExpression"){
                cout << "ERROR: length can ONLY be used in arrays. identifier: \"" << (*child)->value << "\" Is not an array! line:" << (*child)->lineno << endl;
                semantic_errors = true;
                return("TypeError");
            }
            return("IntType");
        }
    }
    found = find(array_index_expression.begin(),array_index_expression.end(),parent->type);
    if(found != array_index_expression.end()){
        auto children = parent->children.begin();
        if((*children)->type != "Id"){
            cout << "Array indexing can only be used on an identifier! line:" << (*children)->lineno << endl;
            semantic_errors = true;
            return("TypeError");
        }else{
            symbol * identifier = Symbol_table.find_symbol_in_scope(scopeid,(*children)->value);
            if(identifier == nullptr){
                cout << "ERROR: Identifier: \"" << (*children)->value << "\" Not defined in this scope! line:" << (*children)->lineno << endl;
                semantic_errors = true;
                return("TypeError");
            }
            if(identifier->id_type != "ArrayExpression"){
                cout << "ERROR: Array indexing can ONLY be used on arrays. identifier: \"" << (*children)->value << "\" Is not an array! line:" << (*children)->lineno << endl;
                semantic_errors = true;
                return("TypeError");
            }
            string right = expresions(scopeid,(*++children));
            if(right != "IntType"){
                cout << "ERROR: Cannot use \"" << right <<"\" to index an array! line:" << (*prev(children))->lineno << endl;
                semantic_errors = true;
                return("TypeError");
            }
            if(identifier->type == "intArray") return("IntType");
            if(identifier->type == "floatArray") return("FloatType");
            if(identifier->type == "booleanArray") return("BoolType");
            
        }
    }
    found = find(method_call_expression.begin(),method_call_expression.end(),parent->type);
    if(found != method_call_expression.end()){
        auto children = parent->children.begin();
        symbol * classvar = Symbol_table.find_symbol_in_scope(scopeid,(*children)->value);
        if(classvar == nullptr){
            cout << "Cannot find \"" << (*children)->value << "\" in this scope! line:" << parent->lineno << endl;
            semantic_errors = true;
            return "TypeError";
        }
        symbol * function = Symbol_table.find_method_in_class(classvar->type,parent->value);
        if(function == nullptr){
            cout << "Could find Class \"" << classvar->type << "\"! or Could not find method \"" << parent->value <<"\" in Class \"" << classvar->type <<"\" ! line:" << parent->lineno << endl;
            semantic_errors = true;
            return "TypeError";
        }
        children++;
        if((*children)->type == "NoArgs"){
            if(function->methodargs.size() != 0){
                cout << "Function \"" << function->name << "\" Takes "<< function->methodargs.size() << " arguments line:" << parent->lineno << endl;
                semantic_errors = true;
                return "TypeError";
            }
            if(function->type == "int") return("IntType");
            if(function->type == "float") return("FloatType");
            if(function->type == "boolean") return("BoolType");
            if(function->type == "intArray") return("IntTypeArray");
            if(function->type == "floatArray") return("FloatTypeArray");
            if(function->type == "booleanArray") return("BoolTypeArray");
            if(function->type == "void") return ("VoidType");
        }
        else{
            if(function->methodargs.size() != (*children)->children.size()){
                    cout << "Function \"" << function->name << "\" expected " << function->methodargs.size() << " arguments but got " << (*children)->children.size() << " arguments! line:" << parent->lineno << endl;
                    semantic_errors = true;
                    return "TypeError";
            }
            else{
                auto method_args = function->methodargs.begin();
                for(auto grand_children = (*children)->children.begin(); grand_children != (*children)->children.end(); grand_children++){
                    
                    string gc_type = expresions(scopeid,(*grand_children));
                    if(gc_type != "TypeError"){
                        if((gc_type == "FloatTypeArray" || gc_type == "IntTypeArray" || gc_type == "BoolTypeArray") && !volatilecheck(scopeid,(*grand_children))){
                            cout << "Cannot send a constant array as an argument to a function. Make it volatile! line: " << parent->lineno << endl;
                            semantic_errors = true;
                        }
                        if(gc_type == "IntType" && (*method_args)->type != "int"){
                            cout << "Function expected \"" << (*method_args)->type << "\" but got \"" << gc_type << "\" line:" << parent->lineno << endl;
                            semantic_errors = true;
                            return "TypeError";
                        }
                        if(gc_type == "IntTypeArray" && (*method_args)->type != "intArray"){
                            cout << "Function expected \"" << (*method_args)->type << "\" but got \"" << gc_type << "\" line:" << parent->lineno << endl;
                            semantic_errors = true;
                            return "TypeError";
                        }
                        if(gc_type == "FloatType" && (*method_args)->type != "float"){
                            cout << "Function expected \"" << (*method_args)->type << "\" but got \"" << gc_type << "\" line:" << parent->lineno << endl;
                            semantic_errors = true;
                            return "TypeError";
                        }
                        if(gc_type == "FloatTypeArray" && (*method_args)->type != "floatArray"){ 
                            cout << "Function expected \"" << (*method_args)->type << "\" but got \"" << gc_type << "\" line:" << parent->lineno << endl;
                            semantic_errors = true;
                            return "TypeError";
                        }
                        if(gc_type == "BoolType" && (*method_args)->type != "boolean"){ 
                            cout << "Function expected \"" << (*method_args)->type << "\" but got \"" << gc_type << "\" line:" << parent->lineno << endl;
                            semantic_errors = true;
                            return "TypeError";
                        }
                        if(gc_type == "BoolTypeArray" && (*method_args)->type != "booleanArray"){
                            cout << "Function expected \"" << (*method_args)->type << "\" but got \"" << gc_type << "\" line:" << parent->lineno << endl;
                            semantic_errors = true;
                            return "TypeError";
                        }
                        
                    }
                    method_args++;
                }
                if(function->type == "int") return("IntType");
                if(function->type == "float") return("FloatType");
                if(function->type == "boolean") return("BoolType");
                if(function->type == "intArray") return("IntTypeArray");
                if(function->type == "floatArray") return("FloatTypeArray");
                if(function->type == "booleanArray") return("BoolTypeArray");
                if(function->type == "void") return ("VoidType");
            }
        }


    }
    found = find(function_call_expression.begin(),function_call_expression.end(),parent->type);
    if(found != function_call_expression.end()){
        auto children = parent->children.begin();
        symbol * function = Symbol_table.find_symbol_in_scope(scopeid,parent->value);
        if(function == nullptr){
            cout << "Cannot find \"" << parent->value << "\" in this scope! line:" << parent->lineno << endl;
            semantic_errors = true;
            return "TypeError";
        }
        if(function->id_type == "Method"){
            if((*children)->type == "NoArgs"){
                if(function->methodargs.size() != 0){
                    cout << "Function \"" << function->name << "\" Takes "<< function->methodargs.size() << " arguments line:" << parent->lineno << endl;
                    semantic_errors = true;
                    return "TypeError";
                }
                if(function->type == "int") return("IntType");
                if(function->type == "float") return("FloatType");
                if(function->type == "boolean") return("BoolType");
                if(function->type == "intArray") return("IntTypeArray");
                if(function->type == "floatArray") return("FloatTypeArray");
                if(function->type == "booleanArray") return("BoolTypeArray");
                if(function->type == "void") return ("VoidType");
            }
            else{
                if(function->methodargs.size() != (*children)->children.size()){
                    cout << "Function \"" << function->name << "\" expected " << function->methodargs.size() << " arguments but got " << (*children)->children.size() << " arguments! line:" << parent->lineno << endl;
                    semantic_errors = true;
                    return "TypeError";
                }
                else{
                    auto method_args = function->methodargs.begin();
                    for(auto grand_children = (*children)->children.begin(); grand_children != (*children)->children.end(); grand_children++){
                        
                        string gc_type = expresions(scopeid,(*grand_children));
                        if(gc_type != "TypeError"){
                            if((gc_type == "FloatTypeArray" || gc_type == "IntTypeArray" || gc_type == "BoolTypeArray") && !volatilecheck(scopeid,(*grand_children))){
                                cout << "Cannot send a constant array as an argument to a function. Make it volatile! line: " << parent->lineno << endl;
                                semantic_errors = true;
                            }
                            if(gc_type == "IntType" && (*method_args)->type != "int"){
                                cout << "Function expected \"" << (*method_args)->type << "\" but got \"" << gc_type << "\" line:" << parent->lineno << endl;
                                semantic_errors = true;
                                return "TypeError";
                            }
                            if(gc_type == "IntTypeArray" && (*method_args)->type != "intArray"){
                                cout << "Function expected \"" << (*method_args)->type << "\" but got \"" << gc_type << "\" line:" << parent->lineno << endl;
                                semantic_errors = true;
                                return "TypeError";
                            }
                            if(gc_type == "FloatType" && (*method_args)->type != "float"){
                                cout << "Function expected \"" << (*method_args)->type << "\" but got \"" << gc_type << "\" line:" << parent->lineno << endl;
                                semantic_errors = true;
                                return "TypeError";
                            }
                            if(gc_type == "FloatTypeArray" && (*method_args)->type != "floatArray"){ 
                                cout << "Function expected \"" << (*method_args)->type << "\" but got \"" << gc_type << "\" line:" << parent->lineno << endl;
                                semantic_errors = true;
                                return "TypeError";
                            }
                            if(gc_type == "BoolType" && (*method_args)->type != "boolean"){ 
                                cout << "Function expected \"" << (*method_args)->type << "\" but got \"" << gc_type << "\" line:" << parent->lineno << endl;
                                semantic_errors = true;
                                return "TypeError";
                            }
                            if(gc_type == "BoolTypeArray" && (*method_args)->type != "booleanArray"){
                                cout << "Function expected \"" << (*method_args)->type << "\" but got \"" << gc_type << "\" line:" << parent->lineno << endl;
                                semantic_errors = true;
                                return "TypeError";
                            }
                        }
                        method_args++;
                    }
                    if(function->type == "int") return("IntType");
                    if(function->type == "float") return("FloatType");
                    if(function->type == "boolean") return("BoolType");
                    if(function->type == "intArray") return("IntTypeArray");
                    if(function->type == "floatArray") return("FloatTypeArray");
                    if(function->type == "booleanArray") return("BoolTypeArray");
                    if(function->type == "void") return ("VoidType");
                }
            }
        }
        else if(function->id_type == "Class"){
            if((*children)->type != "NoArgs"){
                cout << "A class does not take arguments! line:" << parent->lineno;
                semantic_errors = true;
                return "TypeError";
            }
            return(parent->value);
        }
    }
    found = find(array_creation_expression.begin(),array_creation_expression.end(),parent->type);
    if(found != array_creation_expression.end()){
        auto children = parent->children.begin();
        string left = (*children)->type;
        Node*right = (*++children);
        if(right->type=="NoArgs"){
            return(left);
        }
        if(left =="IntType"){
            bool error = false;
            for(auto right_kids = right->children.begin(); right_kids != right->children.end();right_kids++){
                if((*right_kids)->type != "Int") {
                    cout << "ERROR: Adding a \"" << (*right_kids)->type << "\" To an Int array isn't possible! line:" << right->lineno << endl;
                    semantic_errors = true;
                    error = true;
                }
            }
            return(error ? "TypeError" : "IntTypeArray");
        }
        if(left =="FloatType"){
            bool error = false;
            for(auto right_kids = right->children.begin(); right_kids != right->children.end();right_kids++){
                if((*right_kids)->type != "Float" && (*right_kids)->type != "Int"){
                    cout << "ERROR: Adding a \"" << (*right_kids)->type << "\" To a Float array isn't possible! line:" << right->lineno << endl;
                    semantic_errors = true;
                    error = true;
                }
            }
            return(error ? "TypeError" : "FloatTypeArray");
        }
        if(left =="BoolType"){
            bool error = false;
            for(auto right_kids = right->children.begin(); right_kids != right->children.end();right_kids++){
                if((*right_kids)->type != "Boolean"){
                    cout << "ERROR: Adding a \"" << (*right_kids)->type << "\" To an Boolean array isn't possible! line:" << right->lineno << endl;
                    semantic_errors = true;
                    error = true;
                }
            }
            return(error ? "TypeError" : "BoolTypeArray");
        }
        return("Compiler Error!");
    }
    found = find(not_expression.begin(),not_expression.end(),parent->type);
    if(found != not_expression.end()){
        auto children = parent->children.begin();
        string child = expresions(scopeid,(*children));
        if(child != "TypeError"){
            if(child != "BoolType"){
                cout << "Cannot use a not operator on a \"" << child << "\". line:" << parent->lineno << endl;
                semantic_errors = true;
                return("TypeError");
            }
            return("BoolType");
        }
    }
    // if we have not found any we are a factor.
    if(parent->type == "Int") return("IntType");
    if(parent->type == "Float") return("FloatType");
    if(parent->type == "Boolean") return("BoolType");
    if(parent->type == "Id"){
        symbol* identifier = Symbol_table.find_symbol_in_scope(scopeid,parent->value);
        if(identifier == nullptr){
            cout << "ERROR: Identifier: \"" << parent->value << "\" Not defined in this scope! line:" << parent->lineno << endl;
            semantic_errors = true;
            return("TypeError");
        }
        if(identifier->id_type == "Variable"){
            if(identifier->type == "int") return("IntType");
            if(identifier->type == "float") return("FloatType");
            if(identifier->type == "boolean") return("BoolType");
            return(identifier->type);
        }
        else if(identifier->id_type == "ArrayExpression"){
            if(identifier->type == "intArray") return("IntTypeArray");
            if(identifier->type == "floatArray") return("FloatTypeArray");
            if(identifier->type == "booleanArray") return("BoolTypeArray");
        }
        
    }
    return "Compiler error";
}

// Variable declaration
void semantic_analysis::variables(int scopeid,Node* parent){
    symbol * new_symbol = Symbol_table.find_symbol_in_scope(scopeid,parent->value);
    auto children = parent->children.begin();
    string left = (*children)->type;
    if(left=="TypeExpression"){
        symbol * found_symbol = Symbol_table.find_symbol_in_scope(scopeid, (*children)->value);
        if(found_symbol == nullptr){
            cout << "Could not find Class \"" << (*children)->value << "\" in scope! line:" << parent->lineno << endl;
            semantic_errors = true;
        } else if(found_symbol->id_type != "Class"){
            cout << "\"" << (*children)->value << "\" is not a Class! line:" << parent->lineno << endl;
            semantic_errors = true;
        }
        children++;
        if((*children)->type !="NoExpression"){
            if(found_symbol != nullptr && ((*children)->value != found_symbol->type)){
                cout << "Cannot assign Class \"" << (*children)->value << "\" to Class \"" << found_symbol->type <<"\"! line:" << parent->lineno << endl;
                semantic_errors = true;
            }
        }
    }
    else{
        children++;
        if((*children)->type !="NoExpression"){
            string right = expresions(scopeid,*children);
            if(right != "TypeError"){
                if(left=="ArrayExpression"){
                    children--;
                    if((*children)->value == "int" && right != "IntTypeArray"){
                        cout << "Cannot assign\"" << right << "\" to an \"IntType\" array! line:" << (*children)->lineno << endl; 
                        semantic_errors = true;
                    }
                    if((*children)->value == "float" && right != "FloatTypeArray"){
                        cout << "Cannot assign\"" << right << "\" to an \"FloatType\" array! line:" << (*children)->lineno << endl; 
                        semantic_errors = true;
                    }
                    if((*children)->value == "boolean" && right != "BoolTypeArray"){
                        cout << "Cannot assign\"" << right << "\" to an \"BoolType\" array! line:" << (*children)->lineno << endl; 
                        semantic_errors = true;
                    }
                    if(volatilecheck(scopeid, parent) && !volatilecheck(scopeid,(*++children))){
                        cout << "Cannot make volatile array refrence a constant array! line: " << parent->lineno << endl;
                        semantic_errors = true;
                    }
                }else{
                    if(left == "FloatType"){
                        if(right == "BoolType") { cout << "symbol: " << (*new_symbol).get_string() << " types dont match! one is type \"" << left <<"\" and the other is type \"" << right << "\". line:" <<(*prev(children))->lineno << endl; semantic_errors = true; }
                    }else{
                        if(left != right) {
                            cout << "symbol: " << (*new_symbol).get_string() << " types dont match! one is type \"" << left <<"\" and the other is type \"" << right << "\". line:" <<(*prev(children))->lineno <<endl;
                            semantic_errors = true;
                        }
                    }
                }
            }
        }
    }
    
}

// Assigning to declared var
void semantic_analysis::assign_statement(int scopeid,Node* parent){
    auto children = parent->children.begin();
    if(!volatilecheck(scopeid,*children)){
        cout << "left side of assign can not be a constant! line:" << (*children)->lineno << endl;
        semantic_errors = true;
    }
    string left = expresions(scopeid,*children);
    string right = expresions(scopeid,*++children);
    if(right != "TypeError"){
        if(left == "IntTypeArray" && right != "IntTypeArray") { cout << "Cannot assign an \"IntType\" array to a \"" << right << "\"! line:" << (*prev(children))->lineno << endl; semantic_errors = true; }
        else if(left == "FloatTypeArray" && right != "FloatTypeArray") { cout << "Cannot assign a \"FloatType\" array to a \"" << right << "\"! line:" << (*prev(children))->lineno << endl; semantic_errors = true; }
        else if(left == "BoolTypeArray" && right != "BoolTypeArray") { cout << "Cannot assign a \"BoolType\" array to a \"" << right << "\"! line:" << (*prev(children))->lineno << endl; semantic_errors = true; }
        else if(left == "FloatType"){
            if(right == "BoolType") { cout << "types dont match! one is type \"" << left <<"\" and the other is type \"" << right << "\". line:" <<(*prev(children))->lineno << endl; semantic_errors = true; }
        }else{
            if(left != right) { cout << "types dont match! one is type \"" << left <<"\" and the other is type \"" << right << "\". line:" <<(*prev(children))->lineno <<endl; semantic_errors = true; }
        }
    }
}
    


void semantic_analysis::methods(int scopeid,Node* parent){
    symbol* method = Symbol_table.find_symbol_in_scope(scopeid, parent->value);
    // ++++ to skip method type and method args since i get that from the symbol* method
    // and the validity of args and method type is in symbol tree and parser.
    auto start = ++++parent->children.begin();
    int temp_next_scope_id = next_scope_id;
    if(!checkReturnType(scopeid,(*start),method->type) && method->type != "void"){
        cout << "Method needs a return! line:" << (*start)->lineno << endl;
        semantic_errors = true;
    }
    next_scope_id = temp_next_scope_id;
    doSemanticAnalysis_rec(scopeid,(*start));
}

void semantic_analysis::ifs(int scopeid,Node* parent){
    auto children = parent->children.begin();
    string cond = expresions(scopeid,*children);
    if(cond != "TypeError" && cond != "BoolType"){
        cout << "Condition in \"if\" needs to be of \"BoolType\", not \"" << cond <<"\"! line:" << parent->lineno << endl;
        semantic_errors = true;
    }
    doSemanticAnalysis_rec(scopeid,(*++children));
    if((*++children)->type == "ElseStatement") doSemanticAnalysis_rec(next_scope_id++,(*children));
}

void semantic_analysis::fors(int scopeid,Node* parent){
    auto children = parent->children.begin();
    doSemanticAnalysis_rec(scopeid,*children);
    children++;
    if((*children)->type != "noCondition"){
        string cond = expresions(scopeid,*children);
        if(cond != "TypeError" && cond != "BoolType"){
            cout << "Condition in \"for\" needs to be of \"BoolType\", not \"" << cond <<"\"! line:" << parent->lineno << endl;
            semantic_errors = true;
        }
    }
    children++;
    assign_statement(scopeid,*children);
    doSemanticAnalysis_rec(scopeid,*++children);
}

bool semantic_analysis::checkReturnType(int scopeid,Node* parent,string methodtype){
    bool found_return = false;
    for(auto children = parent->children.begin(); children != parent->children.end(); children++){
        if((*children)->type == "ReturnStatement"){
            string returnType = expresions(scopeid,(*(*children)->children.begin()));
            if(returnType != "TypeError"){
                if(methodtype =="int" && returnType != "IntType") { cout << "Method is of type \"" << methodtype << "\" but the return is of type \"" << returnType << "\" line:" << (*children)->lineno << endl; semantic_errors = true; }
                else if(methodtype =="float" && returnType != "FloatType") { cout << "Method is of type \"" << methodtype << "\" but the return is of type \"" << returnType << "\" line:" << (*children)->lineno << endl; semantic_errors = true; }
                else if(methodtype =="boolean" && returnType != "BoolType") { cout << "Method is of type \"" << methodtype << "\" but the return is of type \"" << returnType << "\" line:" << (*children)->lineno << endl; semantic_errors = true; }
                else if(methodtype =="intArray" && returnType != "IntTypeArray") { cout << "Method is of type \"" << methodtype << "\" but the return is of type \"" << returnType << "\" line:" << (*children)->lineno << endl; semantic_errors = true; }
                else if(methodtype =="floatArray" && returnType != "FloatTypeArray") { cout << "Method is of type \"" << methodtype << "\" but the return is of type \"" << returnType << "\" line:" << (*children)->lineno << endl; semantic_errors = true; }
                else if(methodtype =="booleanArray" && returnType != "BoolTypeArray") { cout << "Method is of type \"" << methodtype << "\" but the return is of type \"" << returnType << "\" line:" << (*children)->lineno << endl; semantic_errors = true; }
            }
            
            return true;
        }
        auto found = find(Symbol_table.scope_creation_types.begin(),Symbol_table.scope_creation_types.end(),(*children)->type);
        if(found != Symbol_table.scope_creation_types.end()){
            if(checkReturnType(scopeid + 1,(*children),methodtype)) found_return = true;
        }
        else{
            if(checkReturnType(scopeid,(*children),methodtype)) found_return = true;
        }
    }
    return found_return;
}

void semantic_analysis::doSemanticAnalysis_rec(int scopeid,Node* parent){
    if(parent->type == "MainEntry"){
        if(!checkReturnType(scopeid, parent,"int")) { cout << "Method needs a return! line:" << parent->lineno << endl; semantic_errors = true; };
    }
    for(auto i = parent->children.begin(); i !=parent->children.end();i++){
        //cout << scopeid << ":"<< next_scope_id << ":" << (*i)->type << endl;
        if((*i)->type == "Variable") variables(scopeid,(*i));
        else if((*i)->type == "AssignStatement") assign_statement(scopeid,(*i));
        else if((*i)->type == "Method") methods(++next_scope_id,(*i));
        else if((*i)->type == "ExpressionStatement") expresions(scopeid,(*(*i)->children.begin()));
        else if((*i)->type == "PrintStatement") expresions(scopeid,(*(*i)->children.begin()));
        else if((*i)->type == "ReadStatement") expresions(scopeid,(*(*i)->children.begin()));
        else if((*i)->type == "IfStatement") ifs(++next_scope_id, (*i));
        else if((*i)->type == "ForStatement") fors(++next_scope_id, (*i));
        else{
            auto found = find(Symbol_table.scope_creation_types.begin(),Symbol_table.scope_creation_types.end(),(*i)->type);
            if(found != Symbol_table.scope_creation_types.end()) doSemanticAnalysis_rec(++next_scope_id,(*i));
            else{
                doSemanticAnalysis_rec(scopeid,(*i));
            }
        }
    }
}

void semantic_analysis::doSemanticAnalysis(){
    doSemanticAnalysis_rec(next_scope_id,root);
}

semantic_analysis::semantic_analysis(/* args */){
        cout << "Printing tree" << endl;
        if(root == nullptr){
            cout << "WTF!" << endl;
            exit(-1);
        }
        Symbol_table.create_symbol_table();
        Symbol_table.print_tree();
        Symbol_table.generate_tree();
    }

semantic_analysis::~semantic_analysis(){
        
    }