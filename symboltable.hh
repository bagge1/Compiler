#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Node.h"

using namespace std;

struct SymbolTableEntry{
public:
	string name;		// id
	string type;		// "int", "float", ...
	string category;	// "variable", "method", "class", ...
	bool isVolatile;	// volatile or not
	int lineno;			// line number where declared
	vector<string> paramTypes; // list of parameter types
};

class Scope{
public:
	string scopeName;
	Scope* parentScope;
	unordered_map<string, SymbolTableEntry> symbols;
	unordered_map<string, Scope*> children;

	Scope(Scope* parent, string name);
	~Scope();
};


class SymbolTable
{
private:
	Scope* rootScope;
	Scope* currentScope;
	void createScope(const string& name);
	bool insertSymbol(const SymbolTableEntry& entry);
	void printScope(Scope* scope, int indent);
	void traversal(Node*);

public:
	int blockCounter;
	SymbolTable();
	~SymbolTable();
	const SymbolTableEntry* lookup(const string& name) const;
	const SymbolTableEntry* lookup_method(const string& className, const string& methodName) const;
	void build_st();
	void printST();
	void enterScope(const string& name);
	void exitScope();
	void resetTable();
};

#endif