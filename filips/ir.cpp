#include "ir.h"
#include "parser.tab.hh"
#include <bits/stdc++.h>
#include "value.h"
#include "symbol_table.h"

extern Node* root;

ir::ir(/* args */)
{
}

ir::~ir()
{
}
Expression * ir::expressions(Node*parent, Block* current_block, int scopeid){
    auto found = find(standard_expressions.begin(),standard_expressions.end(),parent->type);
    if(found != standard_expressions.end()){
        OpExpression * op = new OpExpression();
        op->op = parent->value;
        auto children = parent->children.begin();
        Expression * left = expressions(*children, current_block, scopeid);
        Expression * right = expressions(*(++children), current_block, scopeid);
        op->left = left->result;
        op->val_left = left->val_result;
        op->right = right->result;
        op->val_right = right->val_result;
        op->result = new_temp_var();
        op->val_result = Value::make_temporary(op->result);
        current_block->expressions.push_back(op);
        return op;
    }
    found = find(length_expression.begin(),length_expression.end(),parent->type);
    if(found != length_expression.end()){
        AssignUnary * length = new AssignUnary();
        length->op = "length";
        Expression * expression = expressions(*(parent->children.begin()),current_block, scopeid);
        length->right = expression->result;
        length->val_right = expression->val_result;
        length->result = new_temp_var();
        length->val_result = Value::make_temporary(length->result);
        current_block->expressions.push_back(length);
        return length;
    }
    found = find(array_index_expression.begin(),array_index_expression.end(),parent->type);
    if(found != array_index_expression.end()){
        auto children = parent->children.begin();
        ArrayIndexExpression * arrindex = new ArrayIndexExpression();
        Expression * left = expressions(*children, current_block, scopeid);
        Expression * right = expressions(*(++children), current_block, scopeid);
        arrindex->array = left->result;
        arrindex->val_array = left->val_result;
        arrindex->index = right->result;
        arrindex->val_index = right->val_result;
        arrindex->result = arrindex->array + "[" + arrindex->index + "]";
        arrindex->val_result = Value::make_array_element(arrindex->val_array.to_string(), arrindex->val_index.to_string(),&arrindex->val_index);
        return arrindex;
    }
    found = find(method_call_expression.begin(),method_call_expression.end(),parent->type);
    if(found != method_call_expression.end()){
        auto children = parent->children.begin();
        symbol * sym = st.find_symbol_in_scope(scopeid, (*children)->value);
        symbol * method = st.find_method_in_class(sym->type,parent->value);
        
        if(method->type == "void"){
            MethodCallExpression * methodcall = new MethodCallExpression();
            for(auto klass = classes.begin(); klass != classes.end(); klass++){
                if((*klass)->name == sym->type){
                    for(auto method = (*klass)->methods.begin(); method != (*klass)->methods.end(); method++){
                        if((*method)->name == parent->value){
                            methodcall->method_block = *method;
                            break;
                        }
                    }
                    break;
                }
            }
            methodcall->str_block = methodcall->method_block->name;
            methodcall->classfield = new Value();
            methodcall->classfield->type = ValueType::ClassField;
            methodcall->classfield->name = (*children)->value;
            methodcall->arg_amount = (*++parent->children.begin())->children.size();
            for(auto args = (*++parent->children.begin())->children.begin(); args != (*++parent->children.begin())->children.end();args++){
                Unary * argexp = new Unary();
                argexp->op = "param";
                Expression * arg = expressions(*args,current_block, scopeid);
                argexp->result = arg->result;
                argexp->val_result = arg->val_result;
                current_block->expressions.push_back(argexp);
            }
            current_block->expressions.push_back(methodcall);
            return methodcall;
        }else{
            AssignMethodCallExpression * methodcall = new AssignMethodCallExpression();
            for(auto klass = classes.begin(); klass != classes.end(); klass++){
                if((*klass)->name == sym->type){
                    for(auto method = (*klass)->methods.begin(); method != (*klass)->methods.end(); method++){
                        if((*method)->name == parent->value){
                            methodcall->method_block = *method;
                            break;
                        }
                    }
                    break;
                }
            }
            methodcall->str_block = methodcall->method_block->name;
            methodcall->classfield = new Value();
            methodcall->classfield->type = ValueType::ClassField;
            methodcall->classfield->name = (*children)->value;
            methodcall->arg_amount = (*++parent->children.begin())->children.size();
            for(auto args = (*++parent->children.begin())->children.begin(); args != (*++parent->children.begin())->children.end();args++){
                Unary * argexp = new Unary();
                argexp->op = "param";
                Expression * arg = expressions(*args,current_block, scopeid);
                argexp->result = arg->result;
                argexp->val_result = arg->val_result;
                current_block->expressions.push_back(argexp);
            }
            methodcall->result = new_temp_var();
            methodcall->val_result = Value::make_temporary(methodcall->result);
            current_block->expressions.push_back(methodcall);
            return methodcall;
        }
    }
    found = find(function_call_expression.begin(),function_call_expression.end(),parent->type);
    if(found != function_call_expression.end()){
        symbol * sym =  st.find_symbol_in_scope(scopeid,parent->value);
        if(sym->id_type == "Method"){
            // It is a method call in the same class
            auto children = parent->children.begin();
            if(sym->id_type == "void"){
                FunctionCallExpression * methodcall = new FunctionCallExpression();
                for(auto method = found_methods.begin();method != found_methods.end();method++){
                    if((*method)->name == parent->value){
                        methodcall->method_block = *method;
                        break;
                    }
                }
                if(methodcall == nullptr){
                    cout << "shout!" << endl;
                    exit(-1);
                }

                methodcall->str_block = methodcall->method_block->name;
                methodcall->classfield = nullptr;
                methodcall->arg_amount = (*parent->children.begin())->children.size();
                for(auto args = (*parent->children.begin())->children.begin(); args != (*parent->children.begin())->children.end();args++){
                    Unary * argexp = new Unary();
                    argexp->op = "param";
                    Expression * arg = expressions(*args,current_block, scopeid);
                    argexp->result = arg->result;
                    argexp->val_result = arg->val_result;
                    current_block->expressions.push_back(argexp);
                }
                
                current_block->expressions.push_back(methodcall);
                return methodcall;
            } else{
                AssignFunctionCallExpression * methodcall = new AssignFunctionCallExpression();
                for(auto method = found_methods.begin();method != found_methods.end();method++){
                    if((*method)->name == parent->value){
                        methodcall->method_block = *method;
                        break;
                    }
                }
                if(methodcall == nullptr){
                    cout << "shout!" << endl;
                    exit(-1);
                }

                methodcall->str_block = methodcall->method_block->name; // this is line 161
                methodcall->classfield = nullptr;
                methodcall->arg_amount = (*parent->children.begin())->children.size();
                for(auto args = (*parent->children.begin())->children.begin(); args != (*parent->children.begin())->children.end();args++){
                    Unary * argexp = new Unary();
                    argexp->op = "param";
                    Expression * arg = expressions(*args,current_block, scopeid);
                    argexp->result = arg->result;
                    argexp->val_result = arg->val_result;
                    current_block->expressions.push_back(argexp);
                }
                methodcall->result = new_temp_var();
                methodcall->val_result = Value::make_temporary(methodcall->result);
                current_block->expressions.push_back(methodcall);
                return methodcall;
            }
            
        }
        else{
            // It is a new classfield
            ClassfieldCreationExpression * classfield = new ClassfieldCreationExpression();
            classfield->result = new_temp_var();
            classfield->val_result = Value::make_temporary(classfield->result);
            for(auto klass = classes.begin(); klass != classes.end(); klass++){
                if(parent->value == (*klass)->name){
                    classfield->classinfo = (*klass);
                    break;
                }
            }
            current_block->expressions.push_back(classfield);
            return classfield;
        }
        
    }
    found = find(array_creation_expression.begin(),array_creation_expression.end(),parent->type);
    if(found != array_creation_expression.end()){
        auto children = parent->children.begin();
        ArrayCreationExpression * newarr = new ArrayCreationExpression();
        newarr->type = (*children)->value + "[]";
        Node * commaargs = (*++children);
        int amount = commaargs->children.size();
        newarr->amount = amount;
        newarr->result = new_temp_var();
        newarr->val_result = Value::make_temporary(newarr->result);
        current_block->expressions.push_back(newarr);
        int index = 0;
        for(auto args = commaargs->children.begin(); args != commaargs->children.end(); args++){
            AssignStatement * assign = new AssignStatement();
            ArrayIndexExpression * arrindex = new ArrayIndexExpression();
            arrindex->array = newarr->result;
            arrindex->val_array = newarr->val_result;
            arrindex->index = "$" + to_string(index);
            arrindex->val_index = Value::make_int(index);
            assign->result = arrindex->get_string();
            assign->val_result = Value::make_array_element(newarr->val_result.to_string(), to_string(index),&arrindex->val_index);
            Expression * right = expressions(*args,current_block, scopeid);
            assign->right = right->result;
            assign->val_right = right->val_result;
            current_block->expressions.push_back(assign);
            ++index;
        }
        return newarr;
    }
    found = find(not_expression.begin(),not_expression.end(),parent->type);
    if(found != not_expression.end()){
        auto children = parent->children.begin();
        AssignUnary * notexp = new AssignUnary();
        notexp->op = "!";
        Expression * right = expressions(*children,current_block, scopeid);
        notexp->result = new_temp_var();
        notexp->val_result = Value::make_temporary(notexp->result);
        notexp->right = right->result;
        notexp->val_right = right->val_result;
        current_block->expressions.push_back(notexp);
        return(notexp);
    }
    // like in the semantic analysis, If we have not found any expression we are a factor OR a complete failure
    Factor * factor = new Factor();
    factor->result = (parent->type == "Id") ? parent->value : "$" + parent->value;
    if(parent->type == "Id"){
        factor->val_result = Value::make_variable(parent->value);
    }else if(parent->type == "Int"){
        factor->val_result = Value::make_int(stoi(parent->value));
    }else if(parent->type == "Float"){
        factor->val_result = Value::make_float(stof(parent->value));
    }else if(parent->type == "Boolean"){
        factor->val_result = Value::make_bool(parent->value == "true");
    }else{
        cout << "IR Error: Unrecognized factor type: \"" << parent->type << "\"! line:" << parent->lineno << endl;
    }
    return factor;
}
Block * ir::block_statement(Node* parent, Block * current_block, int scopeid){
    // statements that form or terminate blocks
    if(parent->type == "IfStatement"){
        scopeid = ++next_scope_id;
        Block * trueBlock = new Block();
        Block * falseBlock = new Block();
        IfStatement * ifstmt = new IfStatement();
        Expression * cond = expressions(*(parent->children.begin()), current_block, scopeid);

        ifstmt->cond = cond->result;
        ifstmt->val_cond = cond->val_result;
        ifstmt->str_block = falseBlock->name;
        ifstmt->block = falseBlock;

        if((*++++(parent->children.begin()))->type == "ElseStatement"){
            Block * elseBlock = new Block();
            elseBlock->true_end = falseBlock;
            falseBlock->true_end = current_block->true_end;

            ifstmt->str_block = elseBlock->name;
            ifstmt->block = elseBlock;

            current_block->true_end = trueBlock;
            current_block->false_end = elseBlock;

            generate_rec((*++++(parent->children.begin())), elseBlock, ++next_scope_id);
        }else{
            
            falseBlock->true_end = current_block->true_end;
            current_block->true_end = trueBlock;
            current_block->false_end = falseBlock;
        }
        trueBlock->true_end = falseBlock;
        current_block->expressions.push_back(ifstmt);
        Node * statement_block = (*++(parent->children.begin()));
        cout << statement_block->type << endl;
        generate_rec(statement_block, trueBlock, scopeid);
        
        return falseBlock;
    }
    else if(parent->type == "ForStatement"){
        scopeid = ++next_scope_id;
        auto children = parent->children.begin();
        if((*children)->type == "newVar"){
            simple_statement(*(*children)->children.begin(), current_block, scopeid);
        } else if((*children)->type == "AssignStatement"){
            simple_statement(*children, current_block, scopeid);
        }
        IfStatement * ifstmt = new IfStatement();
        Block * loopBlock = new Block();
        Block * afterLoopBlock = new Block();
        Block * conditionBlock = new Block();

        Expression * cond = expressions(*++children, conditionBlock, scopeid);
        ifstmt->cond = cond->result;
        ifstmt->val_cond = cond->val_result;
        ifstmt->str_block = afterLoopBlock->name;
        ifstmt->block = afterLoopBlock;

        conditionBlock->expressions.push_back(ifstmt);
        conditionBlock->true_end = loopBlock;
        conditionBlock->false_end = afterLoopBlock;

        loopBlock->true_end = conditionBlock;

        afterLoopBlock->true_end = current_block->true_end;
        current_block->true_end = conditionBlock;
        current_block->false_end = afterLoopBlock;

        Node * statement_block = (*++++children);

        int break_amount = find_break_amount_for(statement_block);
        for(;break_amount != 0; break_amount--) break_stack.push(afterLoopBlock);

        int continue_amount = find_continue_amount_for(statement_block);

        if(continue_amount){
            Block * increment_block = new Block();
            simple_statement((*++++parent->children.begin()),increment_block, scopeid);
            increment_block->true_end = conditionBlock;
            for(;continue_amount != 0; continue_amount--) continue_stack.push(increment_block);
        }

        if(statement_block->type == "StatementBlock") generate_rec(statement_block, loopBlock, scopeid);
        else simple_statement(statement_block, loopBlock, scopeid);
        
        // We go to the lowest block in the forloop by following the false path and fiding the block before
        // Going back to the condition block and place the increment there
        Block * block = loopBlock;
        for(; block->true_end != conditionBlock; block = block->false_end);
        simple_statement(*--children, block, scopeid);

        return afterLoopBlock;
    }
    else if(parent->type == "ReturnStatement"){
        Unary * returnexp = new Unary();
        returnexp->op = "return";
        Expression * expression = expressions(*(parent->children.begin()),current_block, scopeid);
        returnexp->result = expression->result;
        returnexp->val_result = expression->val_result;
        current_block->expressions.push_back(returnexp);
        return current_block;
    }
    else if(parent->type == "BreakStatement"){
        GoTo * breakexp = new GoTo();
        Block * outblock = break_stack.top();
        break_stack.pop();
        breakexp->block = outblock;
        breakexp->str_block = outblock->name;
        current_block->expressions.push_back(breakexp);
        // This is for the traversal of for loops
        Block * afterbreak = new Block();
        afterbreak->false_end = current_block->false_end;
        afterbreak->true_end = current_block->true_end;
        current_block->false_end = afterbreak;
        current_block->true_end = outblock;
        return afterbreak;
    }
    else if(parent->type == "ContinueStatement"){
        GoTo * continueexp = new GoTo();
        Block * outblock = continue_stack.top();
        continue_stack.pop();
        continueexp->block = outblock;
        continueexp->str_block = outblock->name;
        current_block->expressions.push_back(continueexp);
        // This is for the traversal of for loops
        Block * aftercontinue = new Block();
        aftercontinue->false_end = current_block->false_end;
        aftercontinue->true_end = current_block->true_end;
        current_block->false_end = aftercontinue;
        current_block->true_end = outblock;
        return aftercontinue;
    }
    return nullptr;
}

void ir::simple_statement(Node* parent, Block * block , int scopeid){
    // simple/straightline statements that make TAC
    if(parent->type == "Variable"){
        auto children = parent->children.begin();
        VarDecStatement * newvar = new VarDecStatement();
        if((*(parent->children.begin()))->type != "TypeExpression"){
            newvar->result = parent->value;
            newvar->val_result = Value::make_variable(parent->value);
            newvar->type = (*children)->type == "ArrayExpression" ? (*children)->value + "[]" : (*children)->value;
            block->expressions.push_back(newvar);
            if((*++(children))->type != "NoExpression"){
                Expression * right = expressions(*children, block, scopeid);
                AssignStatement * assign = new AssignStatement();
                assign->result = newvar->result;
                assign->val_result = newvar->val_result;
                assign->right = right->result;
                assign->val_right = right->val_result;
                block->expressions.push_back(assign);
            }
        }else{
            newvar->result = parent->value;
            newvar->val_result = Value::make_classfield(parent->value);
            newvar->type = (*children)->value;
            block->expressions.push_back(newvar);
            if((*++(children))->type != "NoExpression"){
                Expression * right = expressions(*children, block, scopeid);
                AssignStatement * assign = new AssignStatement();
                assign->result = newvar->result;
                assign->val_result = newvar->val_result;
                assign->right = right->result;
                assign->val_right = right->val_result;
                block->expressions.push_back(assign);
            }
        }
        
    }
    else if(parent->type == "AssignStatement"){
        auto children = parent->children.begin();
        AssignStatement * assign = new AssignStatement();
        Expression * left = expressions(*children, block, scopeid);
        Expression * right = expressions(*++children, block, scopeid);
        assign->result = left->result;
        assign->val_result = left->val_result;
        assign->right = right->result;
        assign->val_right = right->val_result;
        block->expressions.push_back(assign);
    }
    else if(parent->type == "PrintStatement"){
        Unary * print = new Unary();
        print->op = "print";
        Expression * expression = expressions(*(parent->children.begin()),block, scopeid);
        print->result = expression->result;
        print->val_result = expression->val_result;
        block->expressions.push_back(print);
    }
    else if(parent->type == "ReadStatement"){
        Unary * read = new Unary();
        read->op = "read";
        Expression * expression = expressions(*(parent->children.begin()),block, scopeid);
        read->result = expression->result;
        read->val_result = expression->val_result;
        block->expressions.push_back(read);
    }
    else if(parent->type == "ExpressionStatement"){
        expressions(*(parent->children.begin()), block, scopeid);
    }
}
void ir::generate_rec(Node* parent, Block * block, int scopeid){
    for(auto children = parent->children.begin(); children != parent->children.end(); children++){
        auto found_block_statement = find(block_statements.begin(),block_statements.end(),(*children)->type);
        auto found_simple_statement = find(simple_statements.begin(),simple_statements.end(),(*children)->type);
        auto found_scope_creation = find(st.scope_creation_types.begin(), st.scope_creation_types.end(), (*children)->type);
        if(found_block_statement != block_statements.end()){
            Block * new_block = block_statement(*children, block, next_scope_id);
            block = new_block;
        }else if(found_simple_statement != simple_statements.end()){
            simple_statement(*children, block, next_scope_id);
            generate_rec(*children, block, next_scope_id);
        }else{
            generate_rec(*children, block, next_scope_id);
        }
    }
}



// initialize the static id counter for blocks
int Block::next_id = 0;

void ir::generate(symbol_table complete_symbol_table){
    st = complete_symbol_table;

    make_classes(*root->children.begin());

    Block * mainBlock = new Block();
    mainBlock->name = "main";
    main = mainBlock;
    generate_rec((*++root->children.begin()), mainBlock, ++next_scope_id);

    std::unordered_set<Block*> visited;
    list<Block*> blocks;
    blocks.push_back(main);
    for(auto klass = classes.begin(); klass != classes.end(); klass++){
        for(auto method = (*klass)->methods.begin(); method != (*klass)->methods.end(); method++){
            blocks.push_back(*method);
        }
    }
    Block Dummy;
    Dummy.generate_tree(blocks);
    // print the IR blocks
    for(auto block = blocks.begin();block != blocks.end(); block++){
        (*block)->print_block(visited);
    }
}



void ir::generateByteCode(){
    Method * mainMethod = new Method(main->name, main, nullptr);
    program.main = mainMethod;
    unordered_set<Block*> visited;
    for(auto klass = classes.begin(); klass != classes.end(); klass++){
        
        unordered_map<string, int> field_var_map;
        for(auto field = (*klass)->classvars.begin(); field != (*klass)->classvars.end(); field++){
            field_var_map[field->first] = field_var_map.size();
        }
        
        Class * newclass = new Class((*klass)->name, field_var_map);

        list<Method*> methods;
        for(auto method = (*klass)->methods.begin(); method != (*klass)->methods.end(); method++){
            MethodInfo * info = nullptr;
            for(auto method_info = (*klass)->methods_info.begin(); method_info != (*klass)->methods_info.end(); method_info++){
                if((*method_info)->name == (*method)->name){
                    info = *method_info;
                    break;
                }
            }
            methods.push_back(new Method((*method)->name, *method, newclass, info));
        }
        newclass->methods = methods;
        program.classes.push_back(newclass);
    }


    // For printing the local variables and fields with their indexes

    for(auto mainlocal = mainMethod->local_var_map.begin(); mainlocal != mainMethod->local_var_map.end(); mainlocal++){
        cout << "main local var: " << mainlocal->first << " with index: " << mainlocal->second << endl;
    }
    for(auto klass = program.classes.begin(); klass != program.classes.end(); klass++){
        cout << "class: " << (*klass)->name << endl;
        for(auto field = (*klass)->field_var_map.begin(); field != (*klass)->field_var_map.end(); field++){
            cout << "\tfield: " << field->first << " with index: " << field->second << endl;
        }
        for(auto method = (*klass)->methods.begin(); method != (*klass)->methods.end(); method++){
            cout << "\tmethod: " << (*method)->name << endl;
            for(auto local = (*method)->local_var_map.begin(); local != (*method)->local_var_map.end(); local++){
                cout << "\t\tlocal var: " << local->first << " with index: " << local->second << endl;
            }
        }
    }
    unordered_set<Block*> visited2;
    cout << "main method bytecode:" << endl;
    program.main->start->print_ByteCode(visited2);
    cout << "classes bytecode:" << endl;
    for(auto klass = program.classes.begin(); klass != program.classes.end(); klass++){
        for(auto method = (*klass)->methods.begin(); method != (*klass)->methods.end(); method++){
            unordered_set<Block*> visited3;
            (*method)->start->print_ByteCode(visited3);
        }
    }
}

void ir::emitbytecode_varmap(ofstream & outfile,unordered_map<string, int> var_map){
    outfile << "VMSTART" << endl;
    for(auto v = var_map.begin(); v != var_map.end();v++){
        outfile << (*v).first + ":" + to_string((*v).second) << endl;
    }
    outfile << "VMEND" << endl;
}
void ir::emitbytecode_blocks(ofstream & outfile,Block * block,unordered_set<Block*>& visited){
    if(visited.count(block))
            return;
    visited.insert(block);

    outfile << "-"+block->name << endl;
    outfile << (block->true_end ? block->true_end->name : "null") << endl; 
    outfile << (block->false_end ? block->false_end->name : "null") << endl; 
    for(auto bc = block->code.begin(); bc != block->code.end(); bc++){
        outfile << (*bc)->op.to_string() + ":" << to_string((*bc)->arg1) + ":" << to_string((*bc)->arg2) + ":" << (*bc)->arg1_str + ":" << (*bc)->arg2_str << endl;
    }
    if(block->true_end) emitbytecode_blocks(outfile,block->true_end,visited);
    if(block->false_end) emitbytecode_blocks(outfile,block->false_end,visited);
}

void ir::emitbytecode_class(ofstream & outfile,Class * klass){
    outfile << "." + klass->name << endl;
    emitbytecode_varmap(outfile,klass->field_var_map);
    for(auto method = klass->methods.begin(); method != klass->methods.end();method++){
        outfile << "#" + (*method)->name << endl;
        emitbytecode_varmap(outfile,(*method)->local_var_map);
        unordered_set<Block*> visited;
        outfile << "START" << endl;
        emitbytecode_blocks(outfile,(*method)->start,visited);
        outfile << "END" << endl;
    }
}


void ir::emitbytecode(string name){
    ofstream outfile(name);
    outfile << "CPMBC" << endl;
    outfile << "#" + program.main->name << endl;
    emitbytecode_varmap(outfile, program.main->local_var_map);
    outfile << "START" << endl;
    unordered_set<Block*> visited;
    emitbytecode_blocks(outfile,program.main->start,visited);
    outfile << "END" << endl;
    outfile << "MAINEND" << endl;
    for(auto klass = program.classes.begin(); klass != program.classes.end();klass++){
        emitbytecode_class(outfile, (*klass));
    }

}



