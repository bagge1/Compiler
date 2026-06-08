#ifndef IR_H
#define IR_H

#include "Node.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <stack>
#include <utility>
#include <set>

using namespace std;


struct TACinstructions{
	string op;
	string arg1;
	string arg2;
	string result;
};

struct BasicBlock{
	string label;
	vector<TACinstructions> instructions;
	vector<BasicBlock*> successors;
	vector<BasicBlock*> predecessors;
};

struct MethodIR{
	string name;
	vector<BasicBlock*> basicBlocks;
};


class IntermediateRepresentation{
	private:
		int tempCounter = 0;
		int labelCounter = 0;
		int blockCounter = 0;

		// all methods
		vector<MethodIR*> methods;

		// current context
		BasicBlock* currentBlock = nullptr;
		MethodIR* currentMethod = nullptr;
		string currentClass;
		stack<pair<BasicBlock*, BasicBlock*>> loopBlocks;
		set<string> classNames;
		unordered_map<string, string> varTypes;
		unordered_map<string, set<string>> classFields;

		// helper functions
		string newTemp();		// returns t0, t1, t2, ...
		string newLabel();		// returns L0, L1, L2, ...

		// functions
		void emit(string op, string arg1, string arg2, string result);

		string generateExpression(Node* node);

		void generateStatement(Node* node);

		void generateMethod(Node* node);

		void addEdge(BasicBlock* from, BasicBlock* to);

		void setCurrentBlock(BasicBlock* block);

		void generateDot(std::ofstream& out);

		BasicBlock* newBlock();

	public:
		IntermediateRepresentation();
		~IntermediateRepresentation();
		void generate_ir(Node* node);
		void printTAC();
		void writeCFG(string& filename);
};


#endif