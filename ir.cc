#include "ir.hh"


extern Node* root;


IntermediateRepresentation::IntermediateRepresentation()
{

}

IntermediateRepresentation::~IntermediateRepresentation()
{
	for (MethodIR* method : methods){
		for (BasicBlock* block : method->basicBlocks){
			delete block;
		}
		delete method;
	}
}

string IntermediateRepresentation::newTemp()
{
	return "t" + to_string(tempCounter++);
}

string IntermediateRepresentation::newLabel()
{
	return to_string(labelCounter++);
}

BasicBlock *IntermediateRepresentation::newBlock()
{
	BasicBlock* b = new BasicBlock{"BB" + newLabel()};
	currentMethod->basicBlocks.push_back(b);
	return b;
}

bool IntermediateRepresentation::isTerminated(BasicBlock* block)
{
	if (block->instructions.empty()) return false;
	const string& op = block->instructions.back().op;
	return op == "GOTO" || op == "RETURN";			// already jumps, dont append another GOTO
}

void IntermediateRepresentation::emit(string op, string arg1, string arg2, string result)
{
	currentBlock->instructions.push_back({op, arg1, arg2, result});
}

string IntermediateRepresentation::generateExpression(Node* node)
{
	if (node == nullptr) return "";

	static unordered_map<string, string> TAC_ops {
		{"Addition", "ADD"}, {"Subtraction", "SUB"}, {"Multiplication", "MUL"},
		{"Division", "DIV"}, {"PowerOf", "POW"}, {"And", "AND"}, {"Or", "OR"},
		{"LessThan", "LT"}, {"GreaterThan", "GT"}, {"LessOrEqual", "LEQ"},
		{"GreaterOrEqual", "GEQ"}, {"EqualTo", "EQ"}, {"NotEqualTo", "NE"}
	};

	string type = node->type;

	if (type == "int" || type == "float"){
		return node->value;
	}

	if (type == "ID"){
		// Is the variable not declared locally / a parameter? | currently inside a class method? | is the variable a field of the current class?
		if (!varTypes.count(node->value) && !currentClass.empty() && classFields[currentClass].count(node->value)){
			string t = newTemp();
			emit("GET_FIELD", "this", node->value, t);
			return t;
		}
		return node->value;
	}

	if (type == "true"){
		return "true";
	}

	if (type == "false"){
		return "false";
	}

	auto it = TAC_ops.find(type);
	if (it != TAC_ops.end()){
		string lhs = generateExpression(node->children.front());
		string rhs = generateExpression(node->children.back());
		string t = newTemp();
		emit(it->second, lhs, rhs, t);
		return t;
	}

	if (type == "Not"){
		string expr = generateExpression(node->children.front());
		string t = newTemp();
		emit("NOT", expr, "", t);
		return t;
	}

	if (type == "ArrayAccess"){
		string arr = generateExpression(node->children.front());
		string idx = generateExpression(node->children.back());
		string t = newTemp();
		emit("ARRAY_LOAD", arr, idx, t);
		return t;
	}

	if (type == "Array"){
		Node* argsNode = node->children.back();
		int size = argsNode->children.size();
		string t = newTemp();
		emit("NEW_ARRAY", to_string(size), "", t);
		int idx = 0;
		for (Node* element : argsNode->children){
			string value = generateExpression(element);
			emit("ARRAY_STORE", t, to_string(idx), value);
			idx++;
		}
		return t;
	}

	if (type == "CallMethod" && node->children.size() == 1){
		int argc = 0;
		for (Node* arg : node->children.front()->children){
			emit("PARAM", generateExpression(arg), "", "");
			argc++;
		}
		string t = newTemp();
		if (classNames.count(node->value)){
			 emit("NEW_OBJECT", node->value, "", t);
			} else if (!currentClass.empty()){
				emit("PARAM", "this", "", "");
				emit("CALL", node->value, to_string(argc + 1), t);
			} else {
				emit("CALL", node->value, to_string(argc), t);
			}
		return t;
	}

	if (type == "CallMethod" && node->children.size() == 2){
		int argc = 0;
		for (Node* arg : node->children.back()->children){
			emit("PARAM", generateExpression(arg), "", "");
			argc++;
		}
		emit("PARAM", generateExpression(node->children.front()), "", "");
		string t = newTemp();
		emit("CALL", node->value, to_string(argc + 1), t);
		return t;
	}

	if (type == "LengthOf"){
		string t = newTemp();
		emit("ARRAY_LEN", node->value, "", t);
		return t;
	}

	return "";
}

void IntermediateRepresentation::generateStatement(Node* node)
{
	if (node == nullptr) return;

	string type = node->type;

	if (type == "Variable" || type == "VolatileVariable") return;

	if (type == "AssignVariable" || type == "AssignVolatileVariable"){
		varTypes[node->value] = node->children.front()->value;
		string expr = generateExpression(node->children.back());
		emit("ASSIGN", expr, "", node->value);
		return;
	}

	if (type == "Assign"){
		Node* lhs = node->children.front();
		string rhs = generateExpression(node->children.back());
		if (lhs->type == "ArrayAccess"){
			string arr = generateExpression(lhs->children.front());
			string idx = generateExpression(lhs->children.back());
			emit("ARRAY_STORE", arr, idx, rhs);
		} else {
			string name = lhs->value;
			if (!varTypes.count(name) && !currentClass.empty() && classFields[currentClass].count(name)){
				emit("SET_FIELD", "this", name, rhs);
			} else {
				emit("ASSIGN", rhs, "", name);
			}
		}
		return;
	}

	if (type == "Read"){
		string name = node->children.front()->value;
		string vType = varTypes.count(name) ? varTypes[name] : "int";
		emit("READ", name, vType, "");
		return;
	}

	if (type == "Print"){
		emit("PRINT", generateExpression(node->children.front()), "", "");
		return;
	}

	if (type == "Return"){
		emit("RETURN", generateExpression(node->children.front()), "", "");
		return;
	}

	if (type == "StatementBlock" || type == "StatementList"){
		for (Node* s : node->children) generateStatement(s);
		return;
	}

	if (type == "IfStatement"){
		string cond = generateExpression(node->children.front()->children.front());
		BasicBlock* thenBlock = newBlock();
		BasicBlock* joinBlock = newBlock();

		emit("IF_FALSE", cond, "", joinBlock->label);
		emit("GOTO", "", "", thenBlock->label);
		addEdge(currentBlock, thenBlock);
		addEdge(currentBlock, joinBlock);

		setCurrentBlock(thenBlock);
		generateStatement(node->children.back());
		if (!isTerminated(currentBlock)){
			emit("GOTO", "", "", joinBlock->label);
			addEdge(currentBlock, joinBlock);
		}
		

		setCurrentBlock(joinBlock);
		return;
	}

	if (type == "IfElseStatement"){
		auto it = node->children.begin();
		Node* condNode = *it++;
		Node* thenNode = *it++;
		Node* elseNode = *it++;
		
		string cond = generateExpression(condNode->children.front());

		BasicBlock* thenBlock = newBlock();
		BasicBlock* elseBlock = newBlock();
		BasicBlock* joinBlock = newBlock();

		emit("IF_FALSE", cond, "", elseBlock->label);
		emit("GOTO", "", "", thenBlock->label);
		addEdge(currentBlock, thenBlock);
		addEdge(currentBlock, elseBlock);

		setCurrentBlock(thenBlock);
		for (Node* stmt : thenNode->children){
			generateStatement(stmt);
		}
		if (!isTerminated(currentBlock)){
			emit("GOTO", "", "", joinBlock->label);
			addEdge(currentBlock, joinBlock);
		}
		

		setCurrentBlock(elseBlock);
		generateStatement(elseNode->children.front());
		if (!isTerminated(currentBlock)){
			emit("GOTO", "", "", joinBlock->label);
			addEdge(currentBlock, joinBlock);
		}
		

		setCurrentBlock(joinBlock);
		return;
	}

	if (type == "ForStatement"){
		Node *init=nullptr, *cond=nullptr, *update=nullptr, *body=nullptr;
		for (Node* child : node->children){
			if (child->type == "Initialization") init = child->children.front();
			else if (child->type == "Condition") cond = child->children.front();
			else if (child->type == "Update") update = child->children.front();
			else if (child->type == "LoopBody") body = child;
		}
		if (init) generateStatement(init);

		BasicBlock* condBlock = newBlock();
		BasicBlock* bodyBlock = newBlock();
		BasicBlock* afterBlock = newBlock();

		emit("GOTO", "", "", condBlock->label);
		addEdge(currentBlock, condBlock);

		setCurrentBlock(condBlock);
		if (cond) emit("IF_FALSE", generateExpression(cond), "", afterBlock->label);
		emit("GOTO", "", "", bodyBlock->label);
		addEdge(condBlock, bodyBlock);
		addEdge(condBlock, afterBlock);

		loopBlocks.push({afterBlock, condBlock});
		setCurrentBlock(bodyBlock);
		if (body){
			for (Node* stmt : body->children){
				generateStatement(stmt);
			}
		}
		if (update) generateStatement(update);
		if (!isTerminated(currentBlock)){
			emit("GOTO", "", "", condBlock->label);
			addEdge(currentBlock, condBlock);
		}
		
		loopBlocks.pop();

		setCurrentBlock(afterBlock);
		return;
	}

	if (type == "Break"){
		BasicBlock* block = loopBlocks.top().first;
		emit("GOTO", "", "", block->label);
		addEdge(currentBlock, block);
		return;
	}

	if (type == "Continue"){
		BasicBlock* block = loopBlocks.top().second;
		emit("GOTO", "", "", block->label);
		addEdge(currentBlock, block);
		return;
	}

	generateExpression(node);
}

void IntermediateRepresentation::generateMethod(Node* node)
{
	if (node == nullptr) return;
	varTypes.clear();

	string name;
	if (node->type == "Main method" || node->type == "StatementBlock") name = "main";
	else if (currentClass.empty()) name = node->value;
	else name = currentClass + "::" + node->value;

	MethodIR* method = new MethodIR{name};
	currentMethod = method;
	methods.push_back(method);
	setCurrentBlock(newBlock());

	for (Node* child : node->children){
		if (child->type == "Parameters"){
			for (Node* param : child->children){
				varTypes[param->value] = param->children.front()->value;
				method->params.push_back(param->value);
			}
		}
	}
	if (!currentClass.empty()){
		varTypes["this"] = currentClass;
		method->params.push_back("this");
	}

	Node* body = (node->type == "StatementBlock") ? node : nullptr;
	if (!body){
		for (Node* child : node->children){
			if (child->type == "StatementBlock") body = child;
		}
	}
	if (body){
		for (Node* stmt : body->children) generateStatement(stmt);
	}
}

void IntermediateRepresentation::generate_ir(Node* node)
{
	for (Node* child : node->children){
		if (child->type == "Class"){
			classNames.insert(child->value);
			for (Node* classChild : child->children){
				if (classChild->type == "Variable" || classChild->type == "VolatileVariable"){
					classFields[child->value].insert(classChild->value);
				}
			}
		}
	}

	for (Node* child : node->children){
		if (child->type == "Main method"){
			currentClass = "";
			generateMethod(child);
		} else if (child->type == "Class"){
			for (Node* classChild : child->children){
				if (classChild->type == "Method"){
					currentClass = child->value;
					generateMethod(classChild);
				}
			}
		} else if (child->type == "StatementBlock"){
			currentClass = "";
			generateMethod(child);
		}
	}
}

void IntermediateRepresentation::addEdge(BasicBlock* from, BasicBlock* to)
{
	from->successors.push_back(to);
	to->predecessors.push_back(from);
}

void IntermediateRepresentation::setCurrentBlock(BasicBlock* block)
{
	currentBlock = block;
}

void IntermediateRepresentation::writeCFG(string filename)
{
	std::ofstream out(filename);
	out << "digraph CFG {\n node [shape=box]; \n";
	generateDot(out);
	out << "}\n";
}

void IntermediateRepresentation::generateDot(std::ofstream& out)
{
	for (MethodIR* m : methods)
		for (BasicBlock* b : m->basicBlocks){
			out << " " << b->label << " [label=\"" << b->label << ":\\n";
			for (auto& in : b->instructions){
				out << in.op << " " << in.arg1 << " " << in.arg2;
				if (!in.result.empty()) out << " -> " << in.result;
				out << "\\n";
			}
			out << "\"];\n";
			for (BasicBlock* s : b->successors)
				out << " " << b->label << "->" << s->label << ";\n";
		}
}

void IntermediateRepresentation::printTAC()
{
	for (MethodIR* m : methods){
		cout << m->name << ":\n";
		for (BasicBlock* b : m->basicBlocks){
			cout << b->label << ":\n";
			for (auto& in : b->instructions){
				cout << " " << in.op << " " << in.arg1 << " " << in.arg2;
				if (!in.result.empty()) cout << " -> " << in.result;
				cout << "\n";
			}
		}
	}
}

static bool isInt(const string& s)
{
	return !s.empty() && s.find_first_not_of("-0123456789")==string::npos;
}

static bool isFloat(const string& s)
{
	return s.find('.') != string::npos && isInt(s.substr(0, s.find('.')));
}

void emitLoad(std::ofstream& out, const string& s)
{
	// determine if literal and what kind
	if (s.empty()) return;
	if (isInt(s)) out << "PUSH_INT " << s << "\n";
	else if (isFloat(s)) out << "PUSH_FLOAT " << s << "\n";
	else if (s=="true" || s=="false") out << "PUSH_BOOL " << s << "\n";
	// or variable
	else out << "LOAD " << s << "\n";
}

void IntermediateRepresentation::generateByteCode(string filename)
{
	std::ofstream out(filename);
	out << "Generated ByteCode\n";
	for (MethodIR* m : methods){
		out << "method " << m->name << " " << m->params.size() << "\n";
		out << "params";
		for (auto& p : m->params) out << " " << p;
		out << "\n";
		for (BasicBlock* b : m->basicBlocks){
			out << b->label << ":\n";
			for (auto& in : b->instructions) emitByteCode(out, in);
		}
		out << (m->name == "main" ? "HALT" : "RETURN") << "\n";
		out << "end\n";
	}
}

void IntermediateRepresentation::emitByteCode(std::ofstream& out, TACinstructions& in)
{
	const string& op = in.op;
	if (op == "GOTO") out << "JMP " << in.result << "\n";
	else if (op == "IF_FALSE") {emitLoad(out, in.arg1); out << "JMP_FALSE " << in.result << "\n";}
	else if (op == "ASSIGN") {emitLoad(out, in.arg1); out << "STORE " << in.result << "\n";}
	else if (op == "PRINT") {emitLoad(out, in.arg1); out << "PRINT\n";}
	else if (op == "READ") {out << "READ " << in.arg2 << "\nSTORE " << in.arg1 << "\n";}
	else if (op == "RETURN") {emitLoad(out, in.arg1); out << "RETURN\n";}
	else if (op == "NOT") {emitLoad(out, in.arg1); out << "NOT\nSTORE " << in.result << "\n";}
	// calls/arrays/object branches
	else if (op == "PARAM") {emitLoad(out, in.arg1); out << "PARAM\n";}
	else if (op == "CALL") {out << "CALL " << in.arg1 << " " << in.arg2 << "\nSTORE " << in.result << "\n";}
	else if (op == "NEW_OBJECT") {out << "NEW_OBJECT " << in.arg1 << "\nSTORE " << in.result << "\n";}
	else if (op == "NEW_ARRAY") {emitLoad(out, in.arg1); out << "NEW_ARRAY\nSTORE " << in.result << "\n";}
	else if (op == "ARRAY_LOAD") {emitLoad(out, in.arg1); emitLoad(out, in.arg2); out << "ARRAY_LOAD\nSTORE " << in.result << "\n";}
	else if (op == "ARRAY_STORE") {emitLoad(out, in.arg1); emitLoad(out, in.arg2); emitLoad(out, in.result); out << "ARRAY_STORE\n";}
	else if (op == "ARRAY_LEN") {emitLoad(out, in.arg1); out << "ARRAY_LEN\nSTORE " << in.result << "\n";}
	else if (op == "GET_FIELD") {emitLoad(out, in.arg1); out << "GET_FIELD " << in.arg2 << "\nSTORE " << in.result << "\n";}
	else if (op == "SET_FIELD") {emitLoad(out, in.arg1); emitLoad(out, in.result); out << "SET_FIELD " << in.arg2 << "\n";}
	else {emitLoad(out, in.arg1); emitLoad(out, in.arg2); out << op << "\nSTORE " << in.result << "\n";}
}