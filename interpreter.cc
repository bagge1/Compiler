#include "interpreter.hh"


Value makeInt(long v){
	Value x;
	x.tag=Value::INT;
	x.i=v;
	return x;
}

Value makeBool(bool v){
	Value x;
	x.tag=Value::BOOL;
	x.b=v;
	return x;
}

static double asDouble(const Value& v)
{
	return v.tag==Value::FLOAT ? v.f : double(v.i);
}

static Value numOp(const Value& a, const Value& b, char op)
{
	bool isFloat = (a.tag == Value::FLOAT || b.tag == Value::FLOAT);
	if (isFloat){
		double x=asDouble(a), y=asDouble(b), r=0;
		switch(op){
			case '+' : r = x+y; break;
			case '-' : r = x-y; break;
			case '*' : r = x*y; break;
			case '/' : r = x/y; break;
			case '^' : r = pow(x,y); break;
		}
		Value v;
		v.tag=Value::FLOAT;
		v.f = r;
		return v;
	}
	long x=a.i, y=b.i, r=0;
	switch(op){
			case '+' : r = x+y; break;
			case '-' : r = x-y; break;
			case '*' : r = x*y; break;
			case '/' : r = x/y; break;
			case '^' : r = pow(x,y); break;
		}
	return makeInt(r);
}

static Value cmpOp(const Value& a, const Value& b, const string& op)
{
	double x = asDouble(a), y = asDouble(b);
	bool r = false;
	if (op == "LT") r = x < y;
	else if (op == "GT") r = x > y;
	else if (op == "LEQ") r = x <= y;
	else if (op == "GEQ") r = x >= y;
	else if (op == "EQ") r = x ==y;
	else if (op == "NE") r = x != y;
	return makeBool(r);
}

static void printValue(const Value& v)
{
	if (v.tag==Value::FLOAT) cout << v.f << "\n";
	else if (v.tag==Value::BOOL) cout << (v.b ? "true" : "false") << "\n";
	else cout << v.i << "\n";
}

void load(const string& path, map<string, Method>& methods)
{
	ifstream in(path);
	string line;
	Method* cur = nullptr;
	while (getline(in, line)){
		if (line.empty()) continue;
		if (line.find("method") == 0) {
			// method (name) (argc)
			istringstream ss(line);
			string keyword, name;
			int argc;
			ss >> keyword >> name >> argc;
			cur = &methods[name];
			cur->name = name;
			cur->argc = argc;
			continue;
		}

		if (cur == nullptr) continue;

		if (line.find("params") == 0){
			istringstream ss(line);
			string word;
			ss >> word;
			while (ss >> word){
				cur->params.push_back(word);
			}
			continue;
		}

		if (line == "end") {
			cur = nullptr;
			continue;;
		}

		if (line.back() == ':') {
			string label = line.substr(0, line.size() - 1);
			cur->labels[label] = cur->code.size();
			continue;
		}

		istringstream ss(line);
		Instr in;
		ss >> in.op;
		string arg;
		while (ss >> arg){
			in.args.push_back(arg);
		}
		cur->code.push_back(in);
};
}

void run(map<string, Method>& methods)
{
	stack<Value> ds;
	Frame fr = {&methods["main"], 0, {}};
	auto pop = [&]() {Value v = ds.top(); ds.pop(); return v;};
	stack<Frame> callStack;
	vector<Value> args;
	
	while(true){
		Instr& in = fr.m->code[fr.pc];
		const string& op = in.op;

		if (op == "PUSH_INT"){
			ds.push(makeInt(stol(in.args[0]))); 
			fr.pc++;
		}
		else if (op == "PUSH_FLOAT"){
			Value v; 
			v.tag=Value::FLOAT; 
			v.f=stod(in.args[0]); 
			ds.push(v); 
			fr.pc++;
		}
		else if (op == "PUSH_BOOL"){
			ds.push(makeBool(in.args[0]=="true"));
			fr.pc++;
		}
		else if (op == "LOAD"){
			ds.push(fr.locals[in.args[0]]);
			fr.pc++;
		}
		else if ( op == "STORE"){
			fr.locals[in.args[0]] = pop();
			fr.pc++;
		}
		else if (op == "MUL"){
			Value a=pop(), b=pop();
			ds.push(numOp(b,a,'*'));
			fr.pc++;
		}
		else if (op == "DIV"){
			Value a=pop(), b=pop();
			ds.push(numOp(b,a,'/'));
			fr.pc++;
		}
		else if (op == "ADD"){
			Value a=pop(), b=pop();
			ds.push(numOp(b,a,'+'));
			fr.pc++;
		}
		else if (op == "SUB"){
			Value a=pop(), b=pop();
			ds.push(numOp(b,a,'-'));
			fr.pc++;
		}
		else if (op == "POW"){
			Value a=pop(), b=pop();
			ds.push(numOp(b,a,'^'));
			fr.pc++;
		}
		else if (op == "PRINT"){
			printValue(pop());
			fr.pc++;
		} 
		else if (op == "JMP"){
			fr.pc = fr.m->labels[in.args[0]];
		}
		else if (op == "JMP_FALSE"){
			Value cond = pop();
			if (!cond.b) fr.pc = fr.m->labels[in.args[0]];
			else fr.pc++;
		}
		else if (op == "LT" || op == "GT" || op == "LEQ" || op == "GEQ" || op == "EQ" || op == "NE"){
			Value a=pop(), b=pop();
			ds.push(cmpOp(b, a, op));
			fr.pc++;
		} 
		else if (op == "AND"){
			Value a=pop(), b=pop();
			ds.push(makeBool(b.b && a.b));
			fr.pc++;
		} 
		else if (op == "OR"){
			Value a=pop(), b=pop();
			ds.push(makeBool(b.b || a.b));
			fr.pc++;
		}
		else if (op == "NOT"){
			Value a=pop();
			ds.push(makeBool(!a.b));
			fr.pc++;
		}
		else if (op == "READ"){
			string tok;
			cin >> tok;
			string type = in.args.empty() ? "int" : in.args[0];
			if (type == "float") {
				Value v;
				v.tag=Value::FLOAT;
				v.f=stod(tok);
				ds.push(v);
			} else if (type == "boolean"){
				ds.push(makeBool(tok=="true"));
			} else {ds.push(makeInt(stol(tok)));}
			fr.pc++;
		}
		else if (op == "PARAM"){
			args.push_back(pop());
			fr.pc++;
		}
		else if (op == "CALL"){
			int argc = stoi(in.args[1]);
			Value& self = args.back();
			Method* callee = &methods[self.obj->cls + "::" + in.args[0]];
			Frame f{callee, 0, {}};
			for (int k = 0; k < argc; ++k){
				f.locals[callee->params[k]] = args[args.size() - argc+k];
			}
			args.clear();
			callStack.push(fr);
			fr = f;
		}
		else if(op == "NEW_OBJECT"){
			Value v;
			v.tag = Value::OBJ;
			v.obj = make_shared<Obj>();
			v.obj->cls = in.args[0];
			ds.push(v);
			fr.pc++;
		}
		else if(op == "GET_FIELD"){
			Value o=pop();
			ds.push(o.obj->fields[in.args[0]]);
			fr.pc++;
		}
		else if (op == "SET_FIELD"){
			Value val=pop();
			Value o=pop();
			o.obj->fields[in.args[0]] = val;
			fr.pc++;
		}
		else if(op == "NEW_ARRAY"){
			Value size=pop();
			Value v;
			v.tag=Value::ARRAY;
			v.arr=make_shared<vector<Value>>(size.i);
			ds.push(v);
			fr.pc++;
		}
		else if (op == "ARRAY_LOAD"){
			Value idx=pop(), arr=pop();
			ds.push((*arr.arr)[idx.i]);
			fr.pc++;
		}
		else if (op == "ARRAY_STORE"){
			Value val=pop(), idx=pop(), arr=pop();
			(*arr.arr)[idx.i] = val;
			fr.pc++;
		}
		else if (op == "ARRAY_LEN"){
			Value arr=pop();
			ds.push(makeInt(arr.arr->size()));
			fr.pc++;
		}
		else if (op == "RETURN"){
			Value rv = ds.empty() ? Value{} : pop();
			if (callStack.empty()){
				break;
			}
			fr = callStack.top();
			callStack.pop();
			ds.push(rv);
			fr.pc++;
		}
		else if (op == "HALT"){break;}
		else { cerr << "unknown opcode: " << op << "\n"; exit(1);}

	}
}

int main(int argc, char** argv){
	if (argc < 2) { cerr << "usage: " << argv[0] << " <bytecode.txt\n"; return 1;}
	map<string, Method> methods;
	load(argv[1], methods);
	run(methods);
	return 0;
}
