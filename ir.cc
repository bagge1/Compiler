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

void IntermediateRepresentation::emit(string op, string arg1, string arg2, string result)
{
	currentBlock->instructions.push_back({op, arg1, arg2, result});
}

string IntermediateRepresentation::generateExpression(Node* node)
{
	if (node == nullptr) return "";

	string type = node->type;

	if (type == "int" || type == "float"){

	}

	if (type == "true"){

	}

	if (type == "false"){

	}

	if (type == "ID"){

	}

	static unordered_map<string, string> TAC_ops {
		{"Addition", "ADD"}, {"Subtraction", "SUB"}, {"Multiplication", "MUL"},
		{"Division", "DIV"}, {"PowerOf", "POW"}, {"And", "AND"}, {"Or", "OR"},
		{"LessThan", "LT"}, {"GreaterThan", "GT"}, {"LessOrEqual", "LEQ"},
		{"GreaterOrEqual", "GEQ"}, {"EqualTo", "EQ"}, {"NotEqualTo", "NE"}
	};

	auto it = TAC_ops.find(type);
	if (it != TAC_ops.end()){

	}

	if (type == "Not"){

	}

	if (type == "ArrayAccess"){

	}

	if (type == "Array"){

	}

	if (type == "CallMethod"){

	}

	if (type == "LengthOf"){

	}

	return "";
}

void IntermediateRepresentation::generateStatement(Node* node)
{
	if (node == nullptr) return;

	string type = node->type;

	if (type == "Variable" || type == "VolatileVariable"){

	}

	if (type == "AssignVariable" || type == "AssignVolatileVariable"){

	}

	if (type == "Assign"){

	}

	if (type == "IfStatement"){

	}

	if (type == "IfElseStatement"){

	}

	if (type == "ForStatement"){

	}

	if (type == "Print"){

	}

	if (type == "Read"){

	}

	if (type == "Return"){

	}

	if (type == "StatementBlock" || type == "StatementList"){

	}

	if (type == "Break"){

	}

	if (type == "Continue"){

	}
}

void IntermediateRepresentation::generateMethod(Node* node)
{
	if (node == nullptr) return;

	MethodIR* method = new MethodIR{node->value};

	currentMethod = method;

	methods.push_back(method);

	string label = "BB" + newLabel();
	BasicBlock* block = new BasicBlock{label};

	currentMethod->basicBlocks.push_back(block);

	setCurrentBlock(block);

	for (Node* child : node->children){
		if (child->type == "Parameters"){
			// handle parameters
			for (auto param : child->children){

			}
		} else if (child->type == "StatementBlock"){
			for (auto stmt : child->children){
				generateStatement(stmt);
			}
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

void IntermediateRepresentation::generate_ir(Node* node)
{
	for (Node* child : node->children){
		if (child->type == "Main method"){
			generateMethod(child);
		} else if (child->type == "Class"){
			for (Node* classChild : child->children){
				if (classChild->type == "Method"){
					generateMethod(classChild);
				}
			}
		}
	}
}

void IntermediateRepresentation::generateDot(std::ofstream& out)
{

}

void IntermediateRepresentation::printTAC()
{

}

void IntermediateRepresentation::writeCFG(string& filename)
{

}