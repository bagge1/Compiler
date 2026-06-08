#include "symbol_table.h"
#include "parser.tab.hh"
#pragma once

class semantic_analysis
{
private:
    /* data */
    void doSemanticAnalysis_rec(int scopeid, Node* current_node);
    void variables(int scopeid,Node* current_node);
    void assign_statement(int scopeid, Node* current_node);
    void methods(int scopeid, Node* current_node);
    void ifs(int scopeid,Node* current_node);
    void fors(int scopeid,Node* current_node);
    bool checkReturnType(int scopeid,Node* current_node,string type);
    string expresions(int scopeid,Node* current_node);

    bool volatilecheck(int scopeid,Node* current_node){

        if(current_node->type == "Id"){
            return Symbol_table.find_symbol_in_scope(scopeid, current_node->value) == nullptr ? true : Symbol_table.find_symbol_in_scope(scopeid, current_node->value)->vol;
        } else if(current_node->type == "ArrayIndexExpression"){
            return Symbol_table.find_symbol_in_scope(scopeid, (*(current_node->children.begin()))->value) == nullptr ? true : Symbol_table.find_symbol_in_scope(scopeid, (*(current_node->children.begin()))->value)->vol;
        } else if(current_node->type == "Variable"){
            return Symbol_table.find_symbol_in_scope(scopeid, current_node->value) == nullptr ? true : Symbol_table.find_symbol_in_scope(scopeid, current_node->value)->vol;
        } else return true;
    }

public:
    vector<string> numeric_operation_expression = {
        "AddExpression","SubExpression","MultExpression","DivExpression","PowExpression"
    };
    vector<string> boolean_operation_expression = {
        "OrExpression","AndExpression"
    };
    vector<string> compare_operation_expression = {
        "EqExpression","NeqExpression","LessExpression","GreaterExpression","GreaterOrEqExpression","LessOrEqExpression"
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
    semantic_analysis();
    ~semantic_analysis();
    void doSemanticAnalysis();
    symbol_table Symbol_table;
    
};


