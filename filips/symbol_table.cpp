#include <iostream>
#include <bits/stdc++.h>
#include "parser.tab.hh"
#include "symbol_table.h"

extern Node *root;
extern bool semantic_errors;


symbol_table::symbol_table(/* args */)
{
	program_scope = new Scope(nullptr,"Program","");
	errors = false;
}

symbol_table::~symbol_table()
{
}

void symbol_table::create_symbol_table_rec(Node* parent, Scope* current_scope){
    for(auto i= parent->children.begin();i!=parent->children.end();i++){
		auto found = find(scope_creation_types.begin(), scope_creation_types.end(),(*i)->type);
		if(found != scope_creation_types.end()){
			// cout << distance(scope_creation_types.begin(), found) << endl;
			if((*i)->type == "Class"){
				symbol * new_symbol = new symbol((*i)->value,(*i)->value,(*i)->type,current_scope->id,(*i)->lineno, true);
				current_scope->symbols.push_back(new_symbol);
			} 
			if((*i)->type == "Method"){
				symbol * new_symbol = new symbol((*i)->value,((get_child_at_index(get_child_at_index((*i),0),0)->type == "ArrayExpression") ? get_child_at_index(get_child_at_index((*i),0),0)->value + "Array" : get_child_at_index(get_child_at_index((*i),0),0)->value),(*i)->type,current_scope->id,(*i)->lineno, true);
				Node* method_args = *(++(*i)->children.begin());
				if(method_args->type != "NoArgs"){
					for(auto arg = method_args->children.begin(); arg != method_args->children.end(); arg++){
						Node * child = get_child_at_index((*arg),0);
						if(child->type == "ArrayExpression"){
							symbol* arg_symbol = new symbol((*arg)->value,child->value+"Array",(*arg)->type,current_scope->id,(*arg)->lineno, true);
							new_symbol->methodargs.push_back(arg_symbol);
						}
						else{
							symbol* arg_symbol = new symbol((*arg)->value,child->value,(*arg)->type,current_scope->id,(*arg)->lineno, true);
							new_symbol->methodargs.push_back(arg_symbol);
						}
					}
				}
				current_scope->symbols.push_back(new_symbol);
			} 
			if((*i)->type == "MainEntry"){
				symbol * new_symbol = new symbol((*i)->value,"int",(*i)->type,current_scope->id,(*i)->lineno,true);
				current_scope->symbols.push_back(new_symbol);
			} 
			Scope * new_scope = new Scope(current_scope,(*i)->type,(*i)->value);
			if((*i)->type == "ElseStatement"){
				current_scope->above->children.push_back(new_scope);
			}
			else{
				current_scope->children.push_back(new_scope);
			}
			
			create_symbol_table_rec(*i,new_scope);

		} else{
			if((*i)->type == "Variable"){
				// cout << get_child_at_index((*i),0).type << endl;
				Node * child = get_child_at_index((*i),0);
				Node * vol = get_child_at_index((*i),2);
				symbol * new_symbol;
				symbol * checksymbol;
				if(child->type == "ArrayExpression"){
					new_symbol = new symbol((*i)->value,child->value +"Array",child->type,current_scope->id,(*i)->lineno,vol == nullptr ? true : vol->type=="vol");
					checksymbol = find_symbol_in_scope(current_scope->id,new_symbol->name);
				}else{
					new_symbol = new symbol((*i)->value,child->value,(*i)->type,current_scope->id,(*i)->lineno, vol == nullptr ? true : vol->type=="vol");
					checksymbol = find_symbol_in_scope(current_scope->id,new_symbol->name);
				}
				if(checksymbol!=nullptr){
					cout << "ERROR: Variable(" <<new_symbol->get_string() << ") name already declared at Variable(" << checksymbol->get_string()<<")"<< endl;
					errors=true;
					semantic_errors = true;
				}
				current_scope->symbols.push_back(new_symbol);
			}
			create_symbol_table_rec(*i, current_scope);
		}
    }
}

void symbol_table::create_symbol_table(){
    create_symbol_table_rec(root, program_scope);
	// if(errors)exit(-1);
}

// Checks if the symbol has been declared in the current scope or any above scopes.
// Goes from program scope to current scope
// Returns a pointer to the found symbol or null
symbol * symbol_table::find_symbol_in_scope(int scope_id, string symbol_name){
	Scope * current_scope = program_scope;
	bool scope_found = false;
	while(!scope_found){
		if(current_scope->id == scope_id) scope_found = true;
		for(auto i = current_scope->symbols.begin(); i != current_scope->symbols.end();i++){
			// cout << (*i)->name << endl;
			if((*i)->name == symbol_name){
				return(*i);
			}
		}
		if(!scope_found){
			auto next_scope = current_scope->children.begin();
			for(auto i = current_scope->children.begin(); i != current_scope->children.end();i++){
				if((*i)->id > scope_id){
					break;
				}else{
					next_scope = i;
				}
			}
			current_scope = *next_scope;
		}	
	}
	
	return nullptr;
}

symbol * symbol_table::find_method_in_class(string class_name, string method_name){
	Scope * current_scope = program_scope;
	for(auto scope = current_scope->children.begin();scope != current_scope->children.end();scope++){
		if((*scope)->value == class_name){
			for(auto method = (*scope)->symbols.begin(); method != (*scope)->symbols.end(); method++){
				if((*method)->name == method_name) return (*method);
			}
		}
	}
	return nullptr;
}

void symbol_table::print_tree(){
	//program_scope->print_tree();
}

void symbol_table::generate_tree(){
	program_scope->generate_tree();
}

Node * symbol_table::get_child_at_index(Node *parent,int index){
	auto it = (parent->children).begin();
	if (distance(it, parent->children.end()) >= index) {
    	advance(it, index);
		return (*it);
	}else return nullptr;
	
}