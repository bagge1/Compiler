#include "interpreter.h"
#include "parser.tab.hh"
#include <bits/stdc++.h>
#include <cmath>
#include "ir.h"

bool debug = false;

void interpreter::run(Frame * frame, Program program){
    while(true){
        ByteCode * code = frame->current_block->code[frame->pc++];
        if(debug){
            stack<Val> temp_stack = valstack;
            cout << "Locals: ";
            int index = 0;
            for(auto val = frame->locals.begin(); val != frame->locals.end();val++){
                Val values = (*val);
                cout << index << ":";
                switch(values.type){
                    case(ValType::INT):{
                        cout << values.int_val << ":INT : ";
                        break;
                    }
                    case(ValType::BOOL):{
                        cout << values.bool_val << ":BOOL : ";
                        break;
                    }
                    case(ValType::FLOAT):{
                        cout << values.float_val << ":FLOAT : ";
                        break;
                    }
                    case(ValType::ARRAY):{
                        cout << values.arr_ref << ":ARRAY : ";
                        break;
                    }
                    case(ValType::OBJECT):{
                        cout << values.obj_ref << ":OBJECT : ";
                        break;
                    }
                }
                index++;
            }
            cout << endl;
            cout << "Stack\n" << "--------------------" << endl;
            for(Val val; !temp_stack.empty();){
                val = temp_stack.top();
                temp_stack.pop();
                switch(val.type){
                    case(ValType::INT):{
                        cout << val.int_val << ":INT" << endl;
                        break;
                    }
                    case(ValType::BOOL):{
                        cout << val.bool_val << ":BOOL" << endl;
                        break;
                    }
                    case(ValType::FLOAT):{
                        cout << val.float_val << ":FLOAT" << endl;
                        break;
                    }
                    case(ValType::ARRAY):{
                        cout << val.arr_ref << ":ARRAY" << endl;
                        break;
                    }
                    case(ValType::OBJECT):{
                        cout << val.obj_ref << ":OBJECT" << endl;
                        break;
                    }

                }
                
            }
            cout << "--------------------" << endl;
            cout << frame->current_block->name << ":" << frame->pc << " Running: " << code->to_string() << endl;
        }
        switch(code->op.Opcode){
            case opcode::ByteCodeOpcode::CONST_INT:{
                valstack.push(Val().make_int(code->arg1));
                break;
            }
            case opcode::ByteCodeOpcode::CONST_FLOAT:{
                float f;
                memcpy(&f, &code->arg1,sizeof(float));
                valstack.push(Val().make_float(f));
                break;
            }
            case opcode::ByteCodeOpcode::CONST_BOOL:{
                valstack.push(Val().make_bool(code->arg1 == 1));
                break;
            }
            case opcode::ByteCodeOpcode::LOAD_LOCAL:{
                Val val = frame->locals[code->arg1];
                valstack.push(val);
                break;
            }
            case opcode::ByteCodeOpcode::STORE_LOCAL:{
                
                Val val = valstack.top();
                valstack.pop();
                frame->locals[code->arg1] = val;
                break;
            }
            case opcode::ByteCodeOpcode::ADD:{
                
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                if(val_right.type == ValType::FLOAT && val_left.type != ValType::FLOAT){
                    valstack.push(Val().make_float(val_left.int_val + val_right.float_val));
                }else if(val_right.type != ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_float(val_left.float_val + val_right.int_val));
                }else if(val_right.type == ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_float(val_left.float_val + val_right.float_val));
                }else{
                    valstack.push(Val().make_int(val_left.int_val + val_right.int_val));
                }
                break;
            }
            
            case opcode::ByteCodeOpcode::SUB:{
                
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                if(val_right.type == ValType::FLOAT && val_left.type != ValType::FLOAT){
                    valstack.push(Val().make_float(val_left.int_val - val_right.float_val));
                }else if(val_right.type != ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_float(val_left.float_val - val_right.int_val));
                }else if(val_right.type == ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_float(val_left.float_val - val_right.float_val));
                }else{
                    valstack.push(Val().make_int(val_left.int_val - val_right.int_val));
                }
                break;
            }
            case opcode::ByteCodeOpcode::MUL:{
                
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                if(val_right.type == ValType::FLOAT && val_left.type != ValType::FLOAT){
                    valstack.push(Val().make_float(val_left.int_val * val_right.float_val));
                }else if(val_right.type != ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_float(val_left.float_val * val_right.int_val));
                }else if(val_right.type == ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_float(val_left.float_val * val_right.float_val));
                }else{
                    valstack.push(Val().make_int(val_left.int_val * val_right.int_val));
                }
                break;
            }
            case opcode::ByteCodeOpcode::DIV:{
                
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                if(val_right.type == ValType::FLOAT && val_left.type != ValType::FLOAT){
                    valstack.push(Val().make_float((float)val_left.int_val / val_right.float_val));
                }else if(val_right.type != ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_float(val_left.float_val / (float)val_right.int_val));
                }else if(val_right.type == ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_float(val_left.float_val / val_right.float_val));
                }else{
                    valstack.push(Val().make_float((float)val_left.int_val / (float)val_right.int_val));
                }
                break;
            }
            case opcode::ByteCodeOpcode::POW:{
                
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                if(val_right.type == ValType::FLOAT && val_left.type != ValType::FLOAT){
                    valstack.push(Val().make_float(pow(val_left.int_val, val_right.float_val)));
                }else if(val_right.type != ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_float(pow(val_left.float_val, val_right.int_val)));
                }else if(val_right.type == ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_float(pow(val_left.float_val, val_right.float_val)));
                }else{
                    (val_right.int_val >= 0) ? valstack.push(Val().make_int(pow(val_left.int_val, val_right.int_val))):valstack.push(Val().make_float(pow(val_left.int_val, val_right.int_val)));
                }
                break;
            }
            case opcode::ByteCodeOpcode::AND:{
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                valstack.push(Val().make_bool(val_left.bool_val && val_right.bool_val));
                break;
            }
            case opcode::ByteCodeOpcode::OR:{
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                valstack.push(Val().make_bool(val_left.bool_val || val_right.bool_val));
                break;
            }
            case opcode::ByteCodeOpcode::NOT:{
                Val val = valstack.top();
                valstack.pop();
                valstack.push(Val().make_bool(!(val.bool_val)));
                break;
            }
            case opcode::ByteCodeOpcode::CMP_EQ:{
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                if(val_right.type == ValType::FLOAT && val_left.type != ValType::FLOAT){
                    valstack.push(Val().make_bool(fabs(val_left.int_val - val_right.float_val) < 1e-4));
                }else if(val_right.type != ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_bool(fabs(val_left.float_val - val_right.int_val) < 1e-4));
                }else if(val_right.type == ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_bool(fabs(val_left.float_val - val_right.float_val) < 1e-4));
                }else{
                    valstack.push(Val().make_bool(val_left.int_val == val_right.int_val));
                }
                break;
            }
            case opcode::ByteCodeOpcode::CMP_NEQ:{
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                if(val_right.type == ValType::FLOAT && val_left.type != ValType::FLOAT){
                    valstack.push(Val().make_bool(fabs(val_left.int_val - val_right.float_val) > 1e-4));
                }else if(val_right.type != ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_bool(fabs(val_left.float_val - val_right.int_val) > 1e-4));
                }else if(val_right.type == ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_bool(fabs(val_left.float_val - val_right.float_val) > 1e-4));
                }else{
                    valstack.push(Val().make_bool(val_left.int_val != val_right.int_val));
                }
                break;
            }
            case opcode::ByteCodeOpcode::CMP_LT:{
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                if(val_right.type == ValType::FLOAT && val_left.type != ValType::FLOAT){
                    valstack.push(Val().make_bool(val_left.int_val < val_right.float_val));
                }else if(val_right.type != ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_bool(val_left.float_val < val_right.int_val));
                }else if(val_right.type == ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_bool(val_left.float_val < val_right.float_val));
                }else{
                    valstack.push(Val().make_bool(val_left.int_val < val_right.int_val));
                }
                break;
            }
            case opcode::ByteCodeOpcode::CMP_LTE:{
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                if(val_right.type == ValType::FLOAT && val_left.type != ValType::FLOAT){
                    valstack.push(Val().make_bool(val_left.int_val <= val_right.float_val));
                }else if(val_right.type != ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_bool(val_left.float_val <= val_right.int_val));
                }else if(val_right.type == ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_bool(val_left.float_val <= val_right.float_val));
                }else{
                    valstack.push(Val().make_bool(val_left.int_val <= val_right.int_val));
                }
                break;
            }
            case opcode::ByteCodeOpcode::CMP_GT:{
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                if(val_right.type == ValType::FLOAT && val_left.type != ValType::FLOAT){
                    valstack.push(Val().make_bool(val_left.int_val > val_right.float_val));
                }else if(val_right.type != ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_bool(val_left.float_val > val_right.int_val));
                }else if(val_right.type == ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_bool(val_left.float_val > val_right.float_val));
                }else{
                    valstack.push(Val().make_bool(val_left.int_val > val_right.int_val));
                }
                break;
            }
            case opcode::ByteCodeOpcode::CMP_GTE:{
                Val val_right = valstack.top();
                valstack.pop();
                Val val_left = valstack.top();
                valstack.pop();
                if(val_right.type == ValType::FLOAT && val_left.type != ValType::FLOAT){
                    valstack.push(Val().make_bool(val_left.int_val >= val_right.float_val));
                }else if(val_right.type != ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_bool(val_left.float_val >= val_right.int_val));
                }else if(val_right.type == ValType::FLOAT && val_left.type == ValType::FLOAT){
                    valstack.push(Val().make_bool(val_left.float_val >= val_right.float_val));
                }else{
                    valstack.push(Val().make_bool(val_left.int_val >= val_right.int_val));
                }
                break;
            }
            case opcode::ByteCodeOpcode::JUMP:{
                if(code->arg1_str == frame->current_block->true_end->name){
                    frame->current_block = frame->current_block->true_end;
                    frame->pc = 0;
                }else{
                    frame->current_block = frame->current_block->false_end;
                    frame->pc = 0;
                }
                break;
            }
            case opcode::ByteCodeOpcode::JUMP_IF_FALSE:{
                Val val = valstack.top();
                valstack.pop();
                if(val.bool_val == false){
                    frame->current_block = frame->current_block->false_end;
                    frame->pc = 0;
                }
                break;
            }
            case opcode::ByteCodeOpcode::CALL_METHOD:{
                framestack.push(frame);
                Frame * new_frame = new Frame();
                Val obj = valstack.top();
                valstack.pop();
                Method* method;
                for(auto m = obj.obj_ref->klass->methods.begin(); m != obj.obj_ref->klass->methods.end(); m++){
                    if((*m)->name == code->arg1_str){
                        method = (*m);
                        break;
                    }
                }
                new_frame->locals.resize(method->local_var_map.size());
                new_frame->current_block = method->start;
                new_frame->locals[0] = obj;
                for(int i = code->arg2; i > 0; i--){
                    Val arg = valstack.top();
                    new_frame->locals[i] = arg;
                    valstack.pop();
                }
                new_frame->pc = 0;
                frame = new_frame;
                break;
            }
            case opcode::ByteCodeOpcode::RETURN:{
                Val return_val = valstack.top();
                if(framestack.size() == 0){
                    //We are ENDING!
                    if(return_val.int_val == 0) cout << "Program exited successfully!" << endl;
                    else cout << "Program exited unsuccessfully!" << endl;
                    exit(0);
                }

                Frame * old_frame = framestack.top();
                framestack.pop();
                frame = old_frame;
                break;
            }
            case opcode::ByteCodeOpcode::RETURN_VOID:{
                Frame * old_frame = framestack.top();
                framestack.pop();
                frame = old_frame;
                break;
            }
            case opcode::ByteCodeOpcode::NEW_OBJECT:{
                Class* origin_class;
                for(auto klass = program.classes.begin();klass != program.classes.end();klass++){
                    if((*klass)->name == code->arg1_str){
                        origin_class = (*klass);
                        break;
                    }
                }
                Object * obj = new Object(origin_class);
                valstack.push(Val().make_object(obj));
                break;
            }
            case opcode::ByteCodeOpcode::LOAD_FIELD:{
                Val obj = valstack.top();
                valstack.pop();
                valstack.push(obj.obj_ref->fields[code->arg1]);
                break;
            }
            case opcode::ByteCodeOpcode::STORE_FIELD:{
                Val obj = valstack.top();
                valstack.pop();
                Val val = valstack.top();
                valstack.pop();
                obj.obj_ref->fields[code->arg1] = val;
                break;
            }
            case opcode::ByteCodeOpcode::NEW_ARRAY:{
                Val size = valstack.top();
                valstack.pop();
                ArrayObject * arr = new ArrayObject(size.int_val);
                valstack.push(Val().make_array(arr));
                break;
            }
            case opcode::ByteCodeOpcode::ARRAY_LOAD:{
                
                Val index = valstack.top();
                valstack.pop();
                Val arr = valstack.top();
                valstack.pop();
                if(index.int_val > arr.arr_ref->length - 1){
                    cout << frame->current_block->name << " pc:" << frame->pc << endl;
                    cout << "array Out of index! Arrayhighestindex: " << arr.arr_ref->length-1 << " Trying to index: " << index.int_val << endl;
                    return;
                }
                valstack.push(arr.arr_ref->elements[index.int_val]);
                break;
            }
            case opcode::ByteCodeOpcode::ARRAY_STORE:{
                Val index = valstack.top();
                valstack.pop();
                Val arr = valstack.top();
                valstack.pop();
                Val val = valstack.top();
                valstack.pop();
                arr.arr_ref->elements[index.int_val] = val;
                break;
            }
            case opcode::ByteCodeOpcode::ARRAY_LENGTH:{
                Val arr = valstack.top();
                valstack.pop();
                valstack.push(Val().make_int(arr.arr_ref->length));
                break;
            }

            case opcode::ByteCodeOpcode::PRINT:{
                Val printval = valstack.top();
                valstack.pop();
                switch(printval.type){
                    case(ValType::INT): cout << printval.int_val << endl; break;
                    case(ValType::FLOAT): cout << printval.float_val << endl; break;
                    case(ValType::BOOL): cout << (printval.bool_val == 1 ? "true" : "false") << endl; break;
                    case(ValType::ARRAY):{
                        string printstring = "";
                        printstring += "[";
                        for(auto element = printval.arr_ref->elements.begin();element != printval.arr_ref->elements.end();element++){
                            switch((*element).type){
                                case(ValType::INT): printstring += to_string((*element).int_val); break;
                                case(ValType::FLOAT): printstring += to_string((*element).float_val); break;
                                case(ValType::BOOL): printstring += ((*element).bool_val == 1 ? "true" : "false"); break;
                            }
                            printstring+=", ";
                        }
                        if(printstring.length() > 2){
                            printstring.pop_back();
                            printstring.pop_back();
                        }
                        printstring += "]\n";
                        cout << printstring;
                        break;
                    }
                    default: cout << "non supported print of an object" << endl; break;
                }
                break;
            }
            case opcode::ByteCodeOpcode::READ:{
                
                string input;
                while(true){
                    cout << "Read: ";
                    cin >> input;
                    if(input == "true" || input == "false"){
                        valstack.push(Val().make_bool(input == "true"));
                        break;
                    }
                    else if(isInt(input)){
                        valstack.push(Val().make_int(stoi(input)));
                        break;
                    }
                    else if(isFloat(input)){
                        valstack.push(Val().make_float(stoi(input)));
                        break;
                    }
                    else{
                        cout << "Input should be written as one of the following:\n(1)\n(4.5)\n(true)" << endl;
                    }
                }
                break;
            }
            case opcode::ByteCodeOpcode::HALT:{
                exit(0);
                break;
            }
            default:{
                cout << code->to_string() << "Not Recognized" << endl;
            }
        }
    }
}

void interpreter::interpret(Program program){
    Frame main_frame;
    main_frame.current_block = program.main->start;
    main_frame.pc = 0;
    main_frame.locals.resize(program.main->local_var_map.size());
    run(&main_frame, program);
}

interpreter::interpreter(/* args */){

}
interpreter::~interpreter(){

}

unordered_map<string,int> interpreter::parse_varmap(ifstream& infile){
    string line;
    unordered_map<string,int> map;
    while (getline(infile, line)) {
        if(line == "VMEND") return map;
        else{
            auto maping = split(line);
            map[maping[0]] = stoi(maping[1]);
        }
    }
}

Method * interpreter::parse_method(ifstream& infile, bool main, Class * klass){
    Method * method = new Method();
    if(main){
        string line;
        while(getline(infile, line)){
            if(line == "MAINEND") return method;
            else if(line[0] == '#') method->name = line.substr(1);
            else if(line == "VMSTART"){
                method->local_var_map = parse_varmap(infile);
            }
            else if(line == "START"){
                unordered_set<Block *> visited;
                method->start = parse_blocks(infile, visited);
            }
        }
    }else{
        string line;
        getline(infile, line);
        method->name = line.substr(1);
        getline(infile, line);
        method->local_var_map = parse_varmap(infile);
        getline(infile, line);
        unordered_set<Block *> visited;
        method->start = parse_blocks(infile,visited);
        method->class_field_map = klass->field_var_map;
        method->owner = klass;
        klass->methods.push_back(method);
        if(infile.peek() == '#'){
            parse_method(infile,false,klass);
        }
        return method;
    }

}

Block * interpreter::parse_blocks(ifstream& infile, unordered_set<Block *>& visited){
    Block * block = new Block(true);
    visited.insert(block);
    string line;
    string true_end;
    string false_end;
    getline(infile, line);
    block->name = line.substr(1);
    getline(infile, line);
    true_end = line;
    getline(infile, line);
    false_end = line;
    while (getline(infile, line)){
        if(line == "END") break;
        auto bc = split(line);
        ByteCode * bytecode = new ByteCode(opcode(string_to_opcode(bc[0])),stoi(bc[1]),stoi(bc[2]),bc[3],bc[4]);
        block->code.push_back(bytecode);
        if(infile.peek() == '-'){
            parse_blocks(infile,visited);
            break;
        }
    }
    for(auto blk = visited.begin(); blk != visited.end(); blk++){
        if((*blk)->name == true_end) block->true_end = (*blk);
        if((*blk)->name == false_end) block->false_end = (*blk);
    }
    return block;

}

void interpreter::parse_classes(ifstream& infile, Program * program){
    string line;
    string name;
    getline(infile, line);
    name = line.substr(1);
    getline(infile, line);
    unordered_map<string,int> field_map;
    field_map = parse_varmap(infile);
    Class * klass = new Class(name,field_map);
    program->classes.push_back(klass);
    while(true){
        if(infile.peek() == '.'){
            parse_classes(infile,program);
            return;
        }else if(infile.peek() == EOF){
            return;
        } else{
            parse_method(infile,false,klass);
        }
    }   

}

Program interpreter::parse(ifstream& infile){
    Program new_program = Program();
    new_program.main = parse_method(infile,true);
    if(infile.peek() == '.') parse_classes(infile, &new_program);
    // for(auto klass = new_program.classes.begin();klass != new_program.classes.end();klass++){
    //     for(auto method = (*klass)->methods.begin();method != (*klass)->methods.end();method++){
    //         unordered_set<Block *> visited;
    //         (*method)->start->print_ByteCode(visited);
    //     }
    // }
    return(new_program);
}

int main(int argc, char** argv){
    if(argc < 2){
        cout << "Usage: ./interpreter <bytecode file>\n";
        return 1;
    }

    ifstream infile(argv[1]);
    if(!infile){
        cout << "Cannot open file " << argv[1] << endl;
        return 1;
    }

    interpreter interp;
    string header;
    getline(infile, header);
    if(header != "CPMBC"){
        cout << "File is not C+- ByteCode!" << endl;
        return 1;
    }

    Program program = interp.parse(infile);

    interp.interpret(program);
}