#include <iostream>
#include "parser.tab.hh"
#include "semantic_analysis.h"
#include "symbol_table.h"
#include "ir.h"
#include "interpreter.h"
#include <chrono>

extern Node *root;
extern FILE *yyin;
extern int yylineno;
extern int lexical_errors;
extern bool semantic_errors = false;
extern yy::parser::symbol_type yylex();

enum errCodes
{
	SUCCESS = 0,
	LEXICAL_ERROR = 1,
	SYNTAX_ERROR = 2,
	AST_ERROR = 3,
	SEMANTIC_ERROR = 4,
	SEGMENTATION_FAULT = 139
};

int errCode = errCodes::SUCCESS;

// Handling Syntax Errors
void yy::parser::error(std::string const &err)
{
	if (!lexical_errors)
	{
		std::cerr << "Syntax errors found! See the logs below:" << std::endl;
		std::cerr << "\t@error at line " << yylineno << ". Cannot generate a syntax for this input:" << err.c_str() << std::endl;
		std::cerr << "End of syntax errors!" << std::endl;
		errCode = errCodes::SYNTAX_ERROR;
	}
}

int main(int argc, char **argv)
{
	// Reads from file if a file name is passed as an argument. Otherwise, reads from stdin.
	if (argc > 1)
	{
		if (!(yyin = fopen(argv[1], "r")))
		{
			perror(argv[1]);
			return 1;
		}
	}
	//
	if (USE_LEX_ONLY)
		yylex();
	else
	{
		yy::parser parser;

		bool parseSuccess = !parser.parse();

		if (lexical_errors)
			errCode = errCodes::LEXICAL_ERROR;

		if (parseSuccess && !lexical_errors)
		{
			semantic_analysis * sem_anl = new semantic_analysis();
			

			printf("\nThe compiler successfuly generated a syntax tree for the given input! \n");

			printf("\nPrint Tree:  \n");
			try
			{
				root->print_tree();
				root->generate_tree();
			}
			catch (...)
			{
				errCode = errCodes::AST_ERROR;
			}

			printf("\nDoing Semantic analysis:  \n");
			try
			{
				sem_anl->doSemanticAnalysis();
			}
			catch (...)
			{
				errCode = errCodes::SEMANTIC_ERROR;
			}
			if(semantic_errors){
				printf("\nSemantic analysis found errors. Aborting further steps.\n");
				errCode = errCodes::SEMANTIC_ERROR;
			} else {
				printf("\nSemantic analysis completed successfully! No semantic errors found! \n");
				ir * ir_gen = new ir();
				ir_gen->generate(sem_anl->Symbol_table);
				ir_gen->generateByteCode();
				ir_gen->emitbytecode("bytecode.txt");
			}

		}
	}

	return errCode;
}