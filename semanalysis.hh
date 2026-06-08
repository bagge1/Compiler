#ifndef SEMANALYSIS_H
#define SEMANALYSIS_H

#include "Node.h"
#include <bits/stdc++.h>
#include "symboltable.hh"

using namespace std;


class SemAnalysis{
private:
	SymbolTable st = SymbolTable();
	vector<string> numerical_operators {"Multiplication", "Addition", "Subtraction", "Division", "PowerOf"};
	vector<string> boolean_operators {"And", "Or", "NotEqualTo", "EqualTo", "Not"};
	vector<string> comparison_operators {"GreaterThan", "LessThan", "GreaterOrEqual", "LessOrEqual"};
	vector<string> base_types {"int", "float", "boolean", "int[]", "float[]", "boolean[]"};
	string check_type(Node* node, bool child = false);
	string get_node_name(Node* node);
	bool has_return(Node* node);
	string cur_ret_type;
public:
	SemAnalysis();
	~SemAnalysis();
	void traversal(Node* node);
	void analyze();
};


#endif