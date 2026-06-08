#include "symboltable.hh"
#include <iomanip>
#include <algorithm>

extern Node* root;


Scope::Scope(Scope* parent, string name) : parentScope(parent), scopeName(name)
{
	
}

Scope::~Scope()
{
	for (auto it = children.begin(); it != children.end(); ++it) {
		delete it->second;
	}
}


SymbolTable::SymbolTable()
{
	rootScope = new Scope(nullptr, "global");
	currentScope = rootScope;
	blockCounter = 1;
}

SymbolTable::~SymbolTable()
{
	delete rootScope;
}

void SymbolTable::enterScope(const string& name)
{
	if (currentScope->children.find(name) != currentScope->children.end()){
		currentScope = currentScope->children[name];
	} else {
	// 	cout << endl;
	// 	cerr << "COULD NOT FIND SCOPE: '" << name << "'" << endl;
	// 	cout << "Current Scope: '" << currentScope->scopeName << "' children:" << endl;
	// 	for (auto child : currentScope->children){
	// 		cout << child.second->scopeName << endl;
	// 	}
	// 	cout << endl;
	}
}

void SymbolTable::resetTable()
{
	blockCounter = 1;
	currentScope = rootScope;
}

void SymbolTable::createScope(const string &name)
{
	Scope* newScope = new Scope(currentScope, name);
	currentScope->children[name] = newScope;
	currentScope = newScope;
}

void SymbolTable::exitScope()
{
	if (currentScope->parentScope != nullptr) {
		currentScope = currentScope->parentScope;
	}
}

bool SymbolTable::insertSymbol(const SymbolTableEntry& entry)
{
	auto it = currentScope->symbols.find(entry.name);

	if (it != currentScope->symbols.end()){	
		cerr << "Semantic Error at line " << entry.lineno << ": Already declared " << entry.category << ": " << entry.name << endl;
		return false;
	}
	currentScope->symbols[entry.name] = entry;
	return true;
}

const SymbolTableEntry* SymbolTable::lookup(const string& name) const
{
	Scope* scope = currentScope;
	while (scope != nullptr){
		if (scope->symbols.find(name) != scope->symbols.end()){
			return &(scope->symbols.at(name));
		}
		scope = scope->parentScope;
	}
	return nullptr;
}

const SymbolTableEntry* SymbolTable::lookup_method(const string& className, const string& methodName) const
{
	if (rootScope->children.find(className) != rootScope->children.end()){
		Scope* classScope = rootScope->children.at(className);
		if (classScope->symbols.find(methodName) != classScope->symbols.end()){
			return &(classScope->symbols.at(methodName));
		}
	}
	return nullptr;
}

void SymbolTable::traversal(Node* node)
{
	if (node == nullptr)
		return;

	string type = node->type;

	if (type.find("Variable") != string::npos){
		SymbolTableEntry entry;
		entry.name = node->value;
		entry.category = "Variable";
		entry.lineno = node->lineno;

		entry.isVolatile = (type.find("Volatile") != string::npos);

		if (!node->children.empty()){
			Node* typeNode = node->children.front();
			if (typeNode->value == "array" && !typeNode->children.empty()){
				entry.type = typeNode->children.front()->value + "[]";
			} else {
				entry.type = typeNode->value;
			}
		} else {
			entry.type = "unknown";
		}
		insertSymbol(entry);
	}

	else if (type == "Main method"){
		createScope("main");
		for (Node* child : node->children){
			if (child->type == "StatementBlock"){
				for (Node* grandChild : child->children){
					traversal(grandChild);
				}
			} else {
				traversal(child);
			}
		}
		exitScope();
	}

	else if (type == "Method"){
		SymbolTableEntry entry;
		entry.name = node->value;
		entry.category = "Method";
		entry.lineno = node->lineno;

		string retType = "void";
		vector<string> pTypes;
		for (Node* child : node->children){
			if (child->type == "ReturnType" && !child->children.empty()){
				if (child->children.front()->value == "array"){
					retType = child->children.front()->children.front()->value + "[]";
				} else {
					retType = child->children.front()->value;
				}
			} else if (child->type == "Parameters" && child->value != "None"){
				for (Node* paramNode : child->children){
					if (!paramNode->children.empty()){
						string pType = paramNode->children.front()->value;
						if (pType == "array" && !paramNode->children.front()->children.empty()){
							pType = paramNode->children.front()->children.front()->value + "[]";
						}
						pTypes.push_back(pType);
					}
				}
			}
		}
		entry.type = retType;
		entry.paramTypes = pTypes;

		insertSymbol(entry);

		createScope(node->value);

		for (Node* child : node->children){
			if (child->type == "StatementBlock"){
				for (Node* grandChild : child->children){
					traversal(grandChild);
				}
			} else {
				traversal(child);
			}
		}
		blockCounter = 1;
		exitScope();
	}

	else if (type == "Parameter"){
		SymbolTableEntry entry;
		entry.name = node->value;
		entry.category = "Parameter";
		entry.lineno = node->lineno;
		entry.isVolatile = false;

		if (!node->children.empty()){
			Node* typeNode = node->children.front();
			if (typeNode->value == "array" && !typeNode->children.empty()){
				entry.type = typeNode->children.front()->value + "[]";
			} else {
				entry.type = typeNode->value;
			}
		} else {
			entry.type = "unknown";
		}
		insertSymbol(entry);
	}

	else if (type == "Class"){
		SymbolTableEntry entry;
		entry.name = node->value;
		entry.category = "Class";
		entry.lineno = node->lineno;
		entry.type = "class";

		insertSymbol(entry);

		createScope(node->value);

		for (Node* child : node->children){
			traversal(child);
		}
		exitScope();
	}

	else if (type == "StatementBlock" || (type.find("Body") != string::npos && type != "ClassBody")){
		if (type == "ElseBody"){
			traversal(node->children.front());
		} else {
			string blocknr = "block" + to_string(blockCounter++);
			createScope(blocknr);
			for (Node* child : node->children){
				traversal(child);
			}
			exitScope();
		}
	} 

	else {
		for (Node* child : node->children){
			traversal(child);
		}
	}
}

void SymbolTable::build_st()
{
	if (root != nullptr){
		traversal(root);
	}
}

void SymbolTable::printST()
{
	cout << "\n========== SYMBOL TABLE ==========\n";
	printScope(rootScope, 0);
	cout << endl;
}

void SymbolTable::printScope(Scope* scope, int indent)
{
	if (!scope) return;

	string ind(indent * 4, ' ');

	cout << endl << ind << "SCOPE: " << scope->scopeName << endl;
	cout << ind << " ----------------------------------------" << endl;

	cout << ind << left
		<< "| " << setw(12) << "Name"
		<< "| " << setw(10) << "Type" 
		<< "| " << setw(10) << "Category"
		<< "| " << setw(4) << "Line" << "|" << endl;
	cout << ind << " ----------------------------------------" << endl;

	vector<SymbolTableEntry> sortedEntries;
	for (const auto& pair : scope->symbols){
		sortedEntries.push_back(pair.second);
	}

	sort(sortedEntries.begin(), sortedEntries.end(), [](const SymbolTableEntry& a, const SymbolTableEntry& b) {return a.lineno < b.lineno;});

	for (const auto& entry : sortedEntries){
		cout << ind << left
			<< "| " << setw(12) << entry.name
			<< "| " << setw(10) << entry.type
			<< "| " << setw(10) << entry.category
			<< "| " << setw(4) << entry.lineno << "|" << endl;
	}

	for (const auto& pair : scope->children){
		printScope(pair.second, indent + 1);
	}

}
