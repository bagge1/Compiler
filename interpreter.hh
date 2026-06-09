#include <memory>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <iostream>
#include <cmath>

using namespace std;

struct Value;

struct Obj{
	string cls;
	map<string, Value> fields;
};

struct Value{
	enum {
		INT,
		FLOAT,
		BOOL,
		ARRAY,
		OBJ
	} tag;
	long i = 0;
	double f = 0;
	bool b = false;
	std::shared_ptr<vector<Value>> arr;
	std::shared_ptr<Obj> obj;
};

struct Instr{
	string op;
	vector<string> args;
};

struct Method{
	string name;
	int argc;
	vector<string> params;
	vector<Instr> code;
	map<string,int> labels;
};

struct Frame{
	Method* m;
	int pc;
	map<string, Value> locals;
};
