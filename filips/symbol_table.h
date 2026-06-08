#include <iostream>
#include "parser.tab.hh"
#pragma once

static int nextid = 0;

class symbol{
public:
    string name, type, id_type;
	int scope, lineno;
	bool vol;
    //Purely used if the symbol is a method.
    list<symbol*> methodargs;
    symbol(string n, string t, string id_t, int id, int lno, bool vol): name(n), type(t), id_type(id_t), scope(id), lineno(lno), vol(vol){}

	string get_string(){
		return ("name: " + name + ", type: " + type +", id_type:" + id_type +", scope: " + std::to_string(scope)+ ", volatile: " + to_string(vol) +", Declared at line: " +std::to_string(lineno));
	}
};

class Scope {
public:
	int treeid;
	int id;
	string type, value;
	Scope* above;
	list<Scope*> children;
    list<symbol*> symbols;
	Scope(Scope* parent = nullptr,string t ="", string v=""): type(t), value(v){
		id = nextid;nextid++;
		if(t=="ElseStatement"){
			above = parent->above;
		} else{
			above = parent;
		}
		
	}
        
	void print_tree(int depth=0) {
		for(int i=0; i<depth; i++)
		cout << "  |";

		cout << "Scope " << type << ":" << value <<" Symbols: ";
		for(auto i = symbols.begin(); i!= symbols.end(); i++)
		cout << " Symbol(" << (*i)->get_string() << ")";

		cout << endl;
		for(auto i=children.begin(); i!=children.end(); i++)
		(*i)->print_tree(depth+1);

	}
  
	void generate_tree() {
		std::ofstream outStream;
		char* filename = "st_tree.dot";
	  	outStream.open(filename);

		int count = 0;
		outStream << "digraph {" << std::endl;
		generate_tree_content(count, &outStream);
		outStream << "}" << std::endl;
		outStream.close();

		printf("\nBuilt a parse-tree at %s. Use 'make st_tree' to generate the pdf version.\n", filename);
  	}

  	void generate_tree_content(int &count, ofstream *outStream) {
		treeid = count++;
		int scopesid= count++;
		int identifierid= count++;
		*outStream << "n" << treeid << " [label=\"" << id << ":" << type << ":" << value << "\"];" << endl;
		*outStream << "n" << scopesid << " [label=\"" << "Scopes" <<"\"];" << endl;
		*outStream << "n" << identifierid << " [label=\"" << "Identifiers" << "\"];" << endl;
		*outStream << "n" << treeid << " -> n" << scopesid << endl;
		*outStream << "n" << treeid << " -> n" << identifierid << endl;
		for (auto i = symbols.begin(); i != symbols.end(); i++){
			count++;
			*outStream << "n" << count << " [label=\"" << (*i)->id_type << ":" << (*i)->type << ":" << (*i)->name << ":" << ((*i)->vol ? "volatile" : "const") << ":Linenumber="<<(*i)->lineno <<"\"];" << endl;
		  	*outStream << "n" << identifierid << " -> n" << count << endl;
	  	}
		count++;
		for (auto i = children.begin(); i != children.end(); i++)
		{
			(*i)->generate_tree_content(count, outStream);
		  	*outStream << "n" << scopesid << " -> n" << (*i)->treeid << endl;
	  	}
  	}

};

class symbol_table
{
private:
    bool errors;
    void create_symbol_table_rec(Node*, Scope*);
public:
    Scope* program_scope;
    vector<string> scope_creation_types = {
        "MainEntry","IfStatement","ElseStatement","ForStatement","Class","Method"
    };
    symbol_table(/* args */);
    ~symbol_table();
    void create_symbol_table();
    void print_tree();
    void generate_tree();
    symbol* find_symbol_in_scope(int,string);
    symbol * find_method_in_class(string class_name,string method_name);
    Node * get_child_at_index(Node*,int);
    
    
};




