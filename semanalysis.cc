#include "semanalysis.hh"

extern Node* root;


SemAnalysis::SemAnalysis()
{

}

SemAnalysis::~SemAnalysis()
{

}

void SemAnalysis::traversal(Node* node)
{
	if (node == nullptr) return;
	string type = node->type;
	
	bool isMethod = (type == "Method" || type == "Main method");
	bool isBlock = (type == "StatementBlock" || (type.find("Body") != string::npos && type != "ClassBody" && type != "ElseBody"));
	bool isClass = (type == "Class");

	if (isMethod){
		cur_ret_type = "void";
		if (type == "Main method"){
			cur_ret_type = "int";
			st.enterScope("main");
		} else {
			auto methodEntry = st.lookup(node->value);
			if (methodEntry != nullptr){
				cur_ret_type = methodEntry->type;
			}
			st.enterScope(node->value);
		}

		if (cur_ret_type != "void"){
			if (!has_return(node)){
				cerr << "Semantic Error at line " << node->lineno << ": missing return statement in non-void function" << endl;
			}
		}
	}

	if (isBlock){
		string blocknr = "block" + to_string(st.blockCounter);
		st.blockCounter++;
		st.enterScope(blocknr);
	}

	if (isClass){
		st.enterScope(node->value);
	}

	if (type.find("Assign") != string::npos){
		Node* leftchild = node->children.front();
		Node* rightchild = node->children.back();
		if (leftchild->type == "ID"){
			auto entry = st.lookup(leftchild->value);
			if (entry != nullptr){
				if (entry->category == "Parameter"){
					cerr << "Semantic Error at line " << node->lineno - 1 << ": assignment to immutable parameter '" << leftchild->value << "'" << endl;
				} else if (entry->category == "Variable" && !entry->isVolatile){
					cerr << "Semantic Error at line " << node->lineno - 1 << ": assignment to immutable variable '" << leftchild->value << "'" << endl;
				}
			}
		}
		string lefttype = check_type(leftchild, true);
		string righttype = check_type(rightchild, true);
		if (lefttype != righttype){
			if (lefttype != "Mismatch" && righttype != "Mismatch" &&
				lefttype != "Undeclared" && righttype != "Undeclared" &&
				lefttype != "Unknown" && righttype != "Unknown") {
				cerr << "Semantic Error at line " << node->lineno - 1 << ": '" << leftchild->value << "' : '" << lefttype << "' and expression '" << rightchild->value
				<< "' : '" << righttype << "' are of different types. " << endl;
		}}
	}

	if (type.find("Variable") != string::npos || type == "Parameter"){
		auto entry = st.lookup(node->value);
		if (entry != nullptr){
			string varType = entry->type;
			if (find(base_types.begin(), base_types.end(), varType) == base_types.end()){
				auto classEntry = st.lookup(varType);
				if (classEntry == nullptr || classEntry->category != "Class"){
					cerr << "Semantic Error at line " << node->lineno << ": '" << varType << "' is undefined" << endl;
				}
			}
		}
	}

	if (type == "Condition"){
		string condType = check_type(node->children.front(), true);
		if (condType != "boolean" && condType != "Mismatch" && condType != "Undeclared"){
			cerr << "Semantic Error at line " << node->lineno << ": if/for condition must be boolean, got '" << condType << "'" << endl;
		}
	}

	if (type == "Return"){
		string returnType = "void";
		if (!node->children.empty()){
			returnType = check_type(node->children.front(), true);
		} 

		if (returnType != cur_ret_type){
			if (returnType != "Mismatch" && returnType != "Unknown"){
				cerr << "Semantic Error at line " << node->lineno - 1 << ": invalid return type: expected " << cur_ret_type << ", got " << returnType << endl;
			}
		}

	}

	bool is_operator = (find(numerical_operators.begin(), numerical_operators.end(), type) != numerical_operators.end()) ||
						(find(boolean_operators.begin(), boolean_operators.end(), type) != boolean_operators.end()) || 
						(find(comparison_operators.begin(), comparison_operators.end(), type) != comparison_operators.end());
	if (is_operator){
		check_type(node);
	}

	bool seenReturn = false;
	for (auto child : node->children){
		if (isMethod && child->type == "StatementBlock"){
			for (auto grandchild : child->children){
				if (seenReturn) cerr << "Semantic Error at line " << grandchild->lineno - 1 << ": Unreachable statement after return" << endl;
				traversal(grandchild);
				if (grandchild->type == "Return") seenReturn = true;
			}
		} else {
			if (seenReturn) cerr << "Semantic Error at line " << child->lineno - 1 << ": Unreachable statement after return" << endl;
			traversal(child);
			if (child->type == "Return") seenReturn = true; 
		}
		
	}
	if (isMethod){
		st.exitScope();
		st.blockCounter = 1;
	}
	if (isBlock || isClass){
		st.exitScope();
	}
}


string SemAnalysis::check_type(Node* node, bool child)
{
	if (node->type == "ID"){
		auto entry = st.lookup(node->value);
		if (entry != nullptr){
			if (node->lineno < entry->lineno){
				cerr << "Semantic Error at line " << node->lineno << ": '" << node->value << "' is used before it is defined." << endl;
				return "Undeclared";
			}
			return entry->type;
		} else {
			cerr << "Semantic Error at line " << node->lineno << ": Identifier undeclared: '" << node->value << "'" << endl;
			return "Undeclared";
		}}

	if (node->type == "ArrayAccess"){
		auto arrayExpr = node->children.front();
		string arrType = check_type(arrayExpr, true);
		if (arrType.find("[]") != string::npos){
			arrType = arrType.substr(0, arrType.length() - 2);
			string indexType = check_type(node->children.back(), true);
			if (indexType != "int"){
				cerr << "Semantic Error at line " << node->lineno << ": Invalid type of Array Index, expected int got '" << indexType << "'" << endl;
				return "Mismatch";
			} else {
				return arrType;
			}
		} else {
			cerr << "Semantic Error at line " << node->lineno << ": Expression '"
			<< arrayExpr->value << "' is not an array." << endl;
			return "Mismatch";
		}
	}

	if (node->type == "CallMethod"){
		const SymbolTableEntry* entry = nullptr;
		Node* argsNode = nullptr;
		if (node->children.size() == 2){
			Node* objExpr = node->children.front();
			argsNode = node->children.back();
			string objType = check_type(objExpr, true);
			if (objType == "Mismatch" || objType == "Undeclared" || objType == "Unknown"){
				return "Mismatch";
			}
			entry = st.lookup_method(objType, node->value);
			if (entry == nullptr || entry->category != "Method"){
				cerr << "Semantic Error at line " << node->lineno << ": Function '" << node->value 
				<< "' does not exist in class '" << objType << "'" << endl;
				return "Undeclared";
			}
		} else {
			argsNode = node->children.front();
			entry = st.lookup(node->value);
			if (entry == nullptr || entry->category != "Method"){
				cerr << "Semantic Error at line " << node->lineno << ": Function '" << node->value << "' does not exist in current scope" << endl;
				return "Undeclared";
			}
		}

		if (entry != nullptr){
			vector<string> providedArgs;

			if (argsNode != nullptr && argsNode->type == "Arguments"){
				for (Node* argExpr : argsNode->children){
					providedArgs.push_back(check_type(argExpr, true));
				}
			}

			if (providedArgs.size() != entry->paramTypes.size()){
				cerr << "Semantic Error at line " << node->lineno << ": Invalid number of parameters for '" << node->value
				<< "'. Expected " << entry->paramTypes.size() << ", got " << providedArgs.size() << endl;
				return "Mismatch";
			}

			bool argError = false;
			for (size_t i = 0; i < providedArgs.size(); i++){
				if (providedArgs[i] != entry->paramTypes[i] && providedArgs[i] != "Mismatch" && providedArgs[i] != "Unknown"){
					cerr << "Semantic Error at line " << node->lineno << ": Invalid Argument type for '" << node->value
					<< "' at position " << i + 1 << ". Expected '" << entry->paramTypes[i] << "', got '" << providedArgs[i] << "'" << endl;
					argError = true;
				}
			}
			if (argError){
				return "Mismatch";
			}
			return entry->type;
		}
	}

	if (node->type == "LengthOf"){
		auto entry = st.lookup(node->value);
		if (entry != nullptr){
			if (entry->type.find("[]") == string::npos){
				cerr << "Semantic Error at line " << node->lineno << ": .length function expects arrays, got " << entry->type << endl;
			} else {
				return "int";
			}
		}
	}

	auto numex = find(numerical_operators.begin(), numerical_operators.end(), node->type);
	if (numex != numerical_operators.end()){
		auto left = node->children.front();
		auto right = node->children.back();
		string lefttype = check_type(left, true);
		string righttype = check_type(right, true);
		bool isfloat = false;
		if (lefttype == "float" || righttype == "float"){
			isfloat = true;
		}
		if ((lefttype == "int" || lefttype == "float") && (righttype == "int" || righttype == "float")){
			if (isfloat){
				return "float";
			} else {
				return "int";
			}
		} else {
			if (!child){
				cerr << "Semantic Error at line " << node->lineno - 1 << ": '" << node->type << "' operation between '" 
				<< get_node_name(left) << "' : '" << lefttype << "' and '" 
				<< get_node_name(right) << "' : '" << righttype << "' is not possible. " 
				<< "Expected: float / int" << endl;
			}
			return "Mismatch";
		}
	}

	auto boolex = find(boolean_operators.begin(), boolean_operators.end(), node->type);
	if (boolex != boolean_operators.end()){
		if (node->type == "Not"){
			auto notchild = node->children.front();
			string childtype = check_type(notchild, true);
			if (childtype == "boolean"){
				return "boolean";
			} else {
				if (!child){
					cerr << "Semantic Error at line " << node->lineno - 1 << ": '" << node->type << "' operation invalid for "
					<< childtype << ". Expected: boolean" << endl;
				}
				return "Mismatch";
			}
		}
		auto left = node->children.front();
		auto right = node->children.back();
		string lefttype = check_type(left, true);
		string righttype = check_type(right, true);
		if (lefttype == "boolean" && righttype == "boolean"){
			return "boolean";
		} else if ((lefttype == "int" || lefttype == "float") && (righttype == "int" || righttype == "float")){
			return "boolean";
		} else {
			if (!child){
				cerr << "Semantic Error at line " << node->lineno - 1 << ": '" << node->type << "' operation between '" 
				<< get_node_name(left) << "' : '" << lefttype << "' and '" 
				<< get_node_name(right) << "' : '" << righttype << "' is not possible. " 
				<< "Expected: boolean" << endl;
			}
			return "Mismatch";
		}
	}

	auto compex = find(comparison_operators.begin(), comparison_operators.end(), node->type);
	if (compex != comparison_operators.end()){
		auto left = node->children.front();
		auto right = node->children.back();
		string lefttype = check_type(left, true);
		string righttype = check_type(right, true);
		if ((lefttype == "int" || lefttype == "float") && (righttype == "int" || righttype == "float")){
			return "boolean";
		} else {
			if (!child){
				cerr << "Semantic Error at line " << node->lineno - 1 << ": '" << node->type << "' operation between '" 
				<< get_node_name(left) << "' : '" << lefttype << "' and '" 
				<< get_node_name(right) << "' : '" << righttype << "' is not possible. " 
				<< "Expected: numerical" << endl;
			}
			return "Mismatch";
		}
	}

	if (node->type == "int" || node->type == "float"){
		return node->type;
	}

	if (node->type == "true" || node->type == "false"){
		return "boolean";
	}

	return "Unknown";
}


string SemAnalysis::get_node_name(Node* node){
	if (node == nullptr) return "Unknown";
	
	if (!node->value.empty()){
		return node->value;
	}

	if (node->type == "ArrayAccess"){
		return get_node_name(node->children.front()) + "[]";
	}

	if (node->type == "CallMethod"){
		return node->value + "()";
	}

	return node->type;
}


bool SemAnalysis::has_return(Node* node){
	if (node == nullptr) return false;

	if (node->type == "Return"){
		return true;
	}

	for (Node* child : node->children){
		if (has_return(child)){
			return true;
		}
	}

	return false;
}


void SemAnalysis::analyze()
{
	st.build_st();
	// st.printST();
	st.resetTable();
	traversal(root);
}