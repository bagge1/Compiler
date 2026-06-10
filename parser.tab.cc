// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 16 "parser.yy"

  #define YY_DECL yy::parser::symbol_type yylex()
  YY_DECL;
  
  Node* root;
  extern int yylineno;

#line 54 "parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 127 "parser.tab.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_program: // program
      case symbol_kind::S_entry: // entry
      case symbol_kind::S_param: // param
      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_params: // params
      case symbol_kind::S_var_list: // var_list
      case symbol_kind::S_classes: // classes
      case symbol_kind::S_class_list: // class_list
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_class_decl: // class_decl
      case symbol_kind::S_class: // class
      case symbol_kind::S_method_decl: // method_decl
      case symbol_kind::S_method: // method
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_arglist: // arglist
      case symbol_kind::S_args: // args
      case symbol_kind::S_baseType: // baseType
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_for_upd: // for_upd
      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmtBl: // stmtBl
      case symbol_kind::S_stmtEnd: // stmtEnd
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< Node * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_SUBOP: // SUBOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_DIVOP: // DIVOP
      case symbol_kind::S_POWOP: // POWOP
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LCB: // LCB
      case symbol_kind::S_RCB: // RCB
      case symbol_kind::S_LB: // LB
      case symbol_kind::S_RB: // RB
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_NEWLINE: // NEWLINE
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL_TO: // EQUAL_TO
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_LESS_OR_EQUAL_TO: // LESS_OR_EQUAL_TO
      case symbol_kind::S_GREATER_OR_EQUAL_TO: // GREATER_OR_EQUAL_TO
      case symbol_kind::S_NOT_EQUAL_TO: // NOT_EQUAL_TO
      case symbol_kind::S_IS_OF: // IS_OF
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_DELIMITER: // DELIMITER
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_VOLATILE_TYPE: // VOLATILE_TYPE
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_ID: // ID
      case symbol_kind::S_BOOLEAN_TYPE: // BOOLEAN_TYPE
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_INT_TYPE: // INT_TYPE
      case symbol_kind::S_FLOAT_TYPE: // FLOAT_TYPE
      case symbol_kind::S_VOID_TYPE: // VOID_TYPE
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_LEN: // LEN
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_program: // program
      case symbol_kind::S_entry: // entry
      case symbol_kind::S_param: // param
      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_params: // params
      case symbol_kind::S_var_list: // var_list
      case symbol_kind::S_classes: // classes
      case symbol_kind::S_class_list: // class_list
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_class_decl: // class_decl
      case symbol_kind::S_class: // class
      case symbol_kind::S_method_decl: // method_decl
      case symbol_kind::S_method: // method
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_arglist: // arglist
      case symbol_kind::S_args: // args
      case symbol_kind::S_baseType: // baseType
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_for_upd: // for_upd
      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmtBl: // stmtBl
      case symbol_kind::S_stmtEnd: // stmtEnd
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_type: // type
        value.move< Node * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_SUBOP: // SUBOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_DIVOP: // DIVOP
      case symbol_kind::S_POWOP: // POWOP
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LCB: // LCB
      case symbol_kind::S_RCB: // RCB
      case symbol_kind::S_LB: // LB
      case symbol_kind::S_RB: // RB
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_NEWLINE: // NEWLINE
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL_TO: // EQUAL_TO
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_LESS_OR_EQUAL_TO: // LESS_OR_EQUAL_TO
      case symbol_kind::S_GREATER_OR_EQUAL_TO: // GREATER_OR_EQUAL_TO
      case symbol_kind::S_NOT_EQUAL_TO: // NOT_EQUAL_TO
      case symbol_kind::S_IS_OF: // IS_OF
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_DELIMITER: // DELIMITER
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_VOLATILE_TYPE: // VOLATILE_TYPE
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_ID: // ID
      case symbol_kind::S_BOOLEAN_TYPE: // BOOLEAN_TYPE
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_INT_TYPE: // INT_TYPE
      case symbol_kind::S_FLOAT_TYPE: // FLOAT_TYPE
      case symbol_kind::S_VOID_TYPE: // VOID_TYPE
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_LEN: // LEN
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_program: // program
      case symbol_kind::S_entry: // entry
      case symbol_kind::S_param: // param
      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_params: // params
      case symbol_kind::S_var_list: // var_list
      case symbol_kind::S_classes: // classes
      case symbol_kind::S_class_list: // class_list
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_class_decl: // class_decl
      case symbol_kind::S_class: // class
      case symbol_kind::S_method_decl: // method_decl
      case symbol_kind::S_method: // method
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_arglist: // arglist
      case symbol_kind::S_args: // args
      case symbol_kind::S_baseType: // baseType
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_for_upd: // for_upd
      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmtBl: // stmtBl
      case symbol_kind::S_stmtEnd: // stmtEnd
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_type: // type
        value.copy< Node * > (that.value);
        break;

      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_SUBOP: // SUBOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_DIVOP: // DIVOP
      case symbol_kind::S_POWOP: // POWOP
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LCB: // LCB
      case symbol_kind::S_RCB: // RCB
      case symbol_kind::S_LB: // LB
      case symbol_kind::S_RB: // RB
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_NEWLINE: // NEWLINE
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL_TO: // EQUAL_TO
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_LESS_OR_EQUAL_TO: // LESS_OR_EQUAL_TO
      case symbol_kind::S_GREATER_OR_EQUAL_TO: // GREATER_OR_EQUAL_TO
      case symbol_kind::S_NOT_EQUAL_TO: // NOT_EQUAL_TO
      case symbol_kind::S_IS_OF: // IS_OF
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_DELIMITER: // DELIMITER
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_VOLATILE_TYPE: // VOLATILE_TYPE
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_ID: // ID
      case symbol_kind::S_BOOLEAN_TYPE: // BOOLEAN_TYPE
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_INT_TYPE: // INT_TYPE
      case symbol_kind::S_FLOAT_TYPE: // FLOAT_TYPE
      case symbol_kind::S_VOID_TYPE: // VOID_TYPE
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_LEN: // LEN
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_program: // program
      case symbol_kind::S_entry: // entry
      case symbol_kind::S_param: // param
      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_params: // params
      case symbol_kind::S_var_list: // var_list
      case symbol_kind::S_classes: // classes
      case symbol_kind::S_class_list: // class_list
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_class_decl: // class_decl
      case symbol_kind::S_class: // class
      case symbol_kind::S_method_decl: // method_decl
      case symbol_kind::S_method: // method
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_arglist: // arglist
      case symbol_kind::S_args: // args
      case symbol_kind::S_baseType: // baseType
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_for_upd: // for_upd
      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmtBl: // stmtBl
      case symbol_kind::S_stmtEnd: // stmtEnd
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_type: // type
        value.move< Node * > (that.value);
        break;

      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_SUBOP: // SUBOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_DIVOP: // DIVOP
      case symbol_kind::S_POWOP: // POWOP
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LCB: // LCB
      case symbol_kind::S_RCB: // RCB
      case symbol_kind::S_LB: // LB
      case symbol_kind::S_RB: // RB
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_NEWLINE: // NEWLINE
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL_TO: // EQUAL_TO
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_LESS_OR_EQUAL_TO: // LESS_OR_EQUAL_TO
      case symbol_kind::S_GREATER_OR_EQUAL_TO: // GREATER_OR_EQUAL_TO
      case symbol_kind::S_NOT_EQUAL_TO: // NOT_EQUAL_TO
      case symbol_kind::S_IS_OF: // IS_OF
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_DELIMITER: // DELIMITER
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_VOLATILE_TYPE: // VOLATILE_TYPE
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_ID: // ID
      case symbol_kind::S_BOOLEAN_TYPE: // BOOLEAN_TYPE
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_INT_TYPE: // INT_TYPE
      case symbol_kind::S_FLOAT_TYPE: // FLOAT_TYPE
      case symbol_kind::S_VOID_TYPE: // VOID_TYPE
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_LEN: // LEN
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_root: // root
      case symbol_kind::S_program: // program
      case symbol_kind::S_entry: // entry
      case symbol_kind::S_param: // param
      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_params: // params
      case symbol_kind::S_var_list: // var_list
      case symbol_kind::S_classes: // classes
      case symbol_kind::S_class_list: // class_list
      case symbol_kind::S_class_body: // class_body
      case symbol_kind::S_class_decl: // class_decl
      case symbol_kind::S_class: // class
      case symbol_kind::S_method_decl: // method_decl
      case symbol_kind::S_method: // method
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_factor: // factor
      case symbol_kind::S_arglist: // arglist
      case symbol_kind::S_args: // args
      case symbol_kind::S_baseType: // baseType
      case symbol_kind::S_variable: // variable
      case symbol_kind::S_for_init: // for_init
      case symbol_kind::S_for_cond: // for_cond
      case symbol_kind::S_for_upd: // for_upd
      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmtBl: // stmtBl
      case symbol_kind::S_stmtEnd: // stmtEnd
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_type: // type
        yylhs.value.emplace< Node * > ();
        break;

      case symbol_kind::S_PLUSOP: // PLUSOP
      case symbol_kind::S_SUBOP: // SUBOP
      case symbol_kind::S_MULTOP: // MULTOP
      case symbol_kind::S_DIVOP: // DIVOP
      case symbol_kind::S_POWOP: // POWOP
      case symbol_kind::S_LP: // LP
      case symbol_kind::S_RP: // RP
      case symbol_kind::S_LCB: // LCB
      case symbol_kind::S_RCB: // RCB
      case symbol_kind::S_LB: // LB
      case symbol_kind::S_RB: // RB
      case symbol_kind::S_MAIN: // MAIN
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_NEWLINE: // NEWLINE
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL_TO: // EQUAL_TO
      case symbol_kind::S_GREATER_THAN: // GREATER_THAN
      case symbol_kind::S_LESS_THAN: // LESS_THAN
      case symbol_kind::S_LESS_OR_EQUAL_TO: // LESS_OR_EQUAL_TO
      case symbol_kind::S_GREATER_OR_EQUAL_TO: // GREATER_OR_EQUAL_TO
      case symbol_kind::S_NOT_EQUAL_TO: // NOT_EQUAL_TO
      case symbol_kind::S_IS_OF: // IS_OF
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_DELIMITER: // DELIMITER
      case symbol_kind::S_DOT: // DOT
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_FOR: // FOR
      case symbol_kind::S_VOLATILE_TYPE: // VOLATILE_TYPE
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_ID: // ID
      case symbol_kind::S_BOOLEAN_TYPE: // BOOLEAN_TYPE
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_INT_TYPE: // INT_TYPE
      case symbol_kind::S_FLOAT_TYPE: // FLOAT_TYPE
      case symbol_kind::S_VOID_TYPE: // VOID_TYPE
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_PRINT: // PRINT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_CLASS: // CLASS
      case symbol_kind::S_LEN: // LEN
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // root: program "end of file"
#line 51 "parser.yy"
                     {root = yystack_[1].value.as < Node * > ();}
#line 908 "parser.tab.cc"
    break;

  case 3: // program: var_list class_list entry
#line 53 "parser.yy"
                                   {
              yylhs.value.as < Node * > () = new Node("Program", "", yylineno);
              if (yystack_[2].value.as < Node * > () != nullptr){
                for (Node* child : yystack_[2].value.as < Node * > ()->children){ 
                  yylhs.value.as < Node * > ()->children.push_back(child);
                }
              }
              if (yystack_[1].value.as < Node * > () != nullptr){
                for (Node* child : yystack_[1].value.as < Node * > ()->children){ 
                  yylhs.value.as < Node * > ()->children.push_back(child);
                }
              }
              yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 927 "parser.tab.cc"
    break;

  case 4: // program: stmtBl
#line 67 "parser.yy"
                     {
              yylhs.value.as < Node * > () = new Node("Program", "", yylineno);
              yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 936 "parser.tab.cc"
    break;

  case 5: // entry: MAIN LP RP IS_OF INT_TYPE stmtBl
#line 74 "parser.yy"
                                        {
            yylhs.value.as < Node * > () = new Node("Main method", "", yylineno);
            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 945 "parser.tab.cc"
    break;

  case 6: // param: ID IS_OF type
#line 80 "parser.yy"
                     {
            yylhs.value.as < Node * > () = new Node("Parameter", yystack_[2].value.as < std::string > (), yylineno);
            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 954 "parser.tab.cc"
    break;

  case 7: // param_list: param
#line 86 "parser.yy"
                  {
            yylhs.value.as < Node * > () = new Node("Parameters", "", yylineno);
            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 963 "parser.tab.cc"
    break;

  case 8: // param_list: param_list DELIMITER param
#line 90 "parser.yy"
                                         {
            yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > ();
            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 972 "parser.tab.cc"
    break;

  case 9: // params: param_list
#line 96 "parser.yy"
                   {
            yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > ();
            }
#line 980 "parser.tab.cc"
    break;

  case 10: // params: %empty
#line 99 "parser.yy"
                     {
            yylhs.value.as < Node * > () = nullptr;
            }
#line 988 "parser.tab.cc"
    break;

  case 11: // var_list: var_list variable stmtEnd
#line 104 "parser.yy"
                                    {
              yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > ();
              yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
            }
#line 997 "parser.tab.cc"
    break;

  case 12: // var_list: var_list stmtEnd
#line 108 "parser.yy"
                               {
              yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
            }
#line 1005 "parser.tab.cc"
    break;

  case 13: // var_list: %empty
#line 111 "parser.yy"
                     {
              yylhs.value.as < Node * > () = new Node("VarList", "", yylineno);
            }
#line 1013 "parser.tab.cc"
    break;

  case 14: // classes: class stmtEnd
#line 116 "parser.yy"
                       {
              yylhs.value.as < Node * > () = new Node("ClassList", "", yylineno);
              yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
            }
#line 1022 "parser.tab.cc"
    break;

  case 15: // classes: classes class stmtEnd
#line 120 "parser.yy"
                                    {
              yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > ();
              yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
            }
#line 1031 "parser.tab.cc"
    break;

  case 16: // classes: classes stmtEnd
#line 124 "parser.yy"
                              {
              yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
            }
#line 1039 "parser.tab.cc"
    break;

  case 17: // class_list: classes
#line 129 "parser.yy"
                    {
            yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > ();
          }
#line 1047 "parser.tab.cc"
    break;

  case 18: // class_list: %empty
#line 132 "parser.yy"
                   {
            yylhs.value.as < Node * > () = new Node("ClassList", "", yylineno);
          }
#line 1055 "parser.tab.cc"
    break;

  case 19: // class_body: class_body variable stmtEnd
#line 136 "parser.yy"
                                        {
              yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > ();
              yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
            }
#line 1064 "parser.tab.cc"
    break;

  case 20: // class_body: class_body method stmtEnd
#line 140 "parser.yy"
                                        {
              yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > ();
              yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
            }
#line 1073 "parser.tab.cc"
    break;

  case 21: // class_body: class_body stmtEnd
#line 144 "parser.yy"
                                 {
              yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
            }
#line 1081 "parser.tab.cc"
    break;

  case 22: // class_body: %empty
#line 147 "parser.yy"
                     {
              yylhs.value.as < Node * > () = new Node("ClassBody", "", yylineno);
            }
#line 1089 "parser.tab.cc"
    break;

  case 23: // class_decl: CLASS ID LCB
#line 152 "parser.yy"
                         {
            yylhs.value.as < Node * > () = new Node("Class", yystack_[1].value.as < std::string > (), yylineno);
          }
#line 1097 "parser.tab.cc"
    break;

  case 24: // class: class_decl class_body RCB
#line 156 "parser.yy"
                                 {
            yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > ();
            if  (yystack_[1].value.as < Node * > () != nullptr){
              for(Node* child : yystack_[1].value.as < Node * > ()->children){
                yylhs.value.as < Node * > ()->children.push_back(child);
              }
            }
            
          }
#line 1111 "parser.tab.cc"
    break;

  case 25: // method_decl: ID LP params RP IS_OF type
#line 167 "parser.yy"
                                        {
             yylhs.value.as < Node * > () = new Node("Method", yystack_[5].value.as < std::string > (), yylineno);
             if (yystack_[3].value.as < Node * > () != nullptr){
              yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
             } else {
              yylhs.value.as < Node * > ()->children.push_back(new Node("Parameters", "None", yylineno));
             }
             Node* ret = new Node("ReturnType", "", yylineno);
             ret->children.push_back(yystack_[0].value.as < Node * > ());
             yylhs.value.as < Node * > ()->children.push_back(ret);
            }
#line 1127 "parser.tab.cc"
    break;

  case 26: // method: method_decl stmtBl
#line 180 "parser.yy"
                          {
              yylhs.value.as < Node * > ()= yystack_[1].value.as < Node * > ();
              yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1136 "parser.tab.cc"
    break;

  case 27: // expression: expression PLUSOP expression
#line 185 "parser.yy"
                                         {  
                            yylhs.value.as < Node * > () = new Node("Addition", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            /* printf("r1 "); */
                          }
#line 1147 "parser.tab.cc"
    break;

  case 28: // expression: expression SUBOP expression
#line 191 "parser.yy"
                                          {
                            yylhs.value.as < Node * > () = new Node("Subtraction", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            /* printf("r2 "); */
                          }
#line 1158 "parser.tab.cc"
    break;

  case 29: // expression: expression MULTOP expression
#line 197 "parser.yy"
                                           {
                            yylhs.value.as < Node * > () = new Node("Multiplication", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
                            /* printf("r3 "); */
                          }
#line 1169 "parser.tab.cc"
    break;

  case 30: // expression: expression DIVOP expression
#line 203 "parser.yy"
                                          {
                            yylhs.value.as < Node * > () = new Node("Division", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1179 "parser.tab.cc"
    break;

  case 31: // expression: expression POWOP expression
#line 208 "parser.yy"
                                          {
                            yylhs.value.as < Node * > () = new Node("PowerOf", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1189 "parser.tab.cc"
    break;

  case 32: // expression: expression AND expression
#line 213 "parser.yy"
                                        {
                            yylhs.value.as < Node * > () = new Node("And", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1199 "parser.tab.cc"
    break;

  case 33: // expression: expression OR expression
#line 218 "parser.yy"
                                       {
                            yylhs.value.as < Node * > () = new Node("Or", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1209 "parser.tab.cc"
    break;

  case 34: // expression: expression LESS_THAN expression
#line 223 "parser.yy"
                                              {
                            yylhs.value.as < Node * > () = new Node("LessThan", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1219 "parser.tab.cc"
    break;

  case 35: // expression: expression GREATER_THAN expression
#line 228 "parser.yy"
                                                 {
                            yylhs.value.as < Node * > () = new Node("GreaterThan", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1229 "parser.tab.cc"
    break;

  case 36: // expression: expression LESS_OR_EQUAL_TO expression
#line 233 "parser.yy"
                                                     {
                            yylhs.value.as < Node * > () = new Node("LessOrEqual", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1239 "parser.tab.cc"
    break;

  case 37: // expression: expression GREATER_OR_EQUAL_TO expression
#line 238 "parser.yy"
                                                        {
                            yylhs.value.as < Node * > () = new Node("GreaterOrEqual", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1249 "parser.tab.cc"
    break;

  case 38: // expression: expression EQUAL_TO expression
#line 243 "parser.yy"
                                             {
                            yylhs.value.as < Node * > () = new Node("EqualTo", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1259 "parser.tab.cc"
    break;

  case 39: // expression: expression NOT_EQUAL_TO expression
#line 248 "parser.yy"
                                                 {
                            yylhs.value.as < Node * > () = new Node("NotEqualTo", yystack_[1].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1269 "parser.tab.cc"
    break;

  case 40: // expression: expression LB expression RB
#line 253 "parser.yy"
                                          {
                            yylhs.value.as < Node * > () = new Node("ArrayAccess", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
                            
            }
#line 1280 "parser.tab.cc"
    break;

  case 41: // expression: expression DOT LEN
#line 259 "parser.yy"
                                 {
                            yylhs.value.as < Node * > () = new Node("LengthOf", yystack_[2].value.as < Node * > ()->value, yylineno);
                            
            }
#line 1289 "parser.tab.cc"
    break;

  case 42: // expression: expression DOT ID LP args RP
#line 263 "parser.yy"
                                           {
                            yylhs.value.as < Node * > () = new Node("CallMethod", yystack_[3].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[5].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
            }
#line 1299 "parser.tab.cc"
    break;

  case 43: // expression: ID LP args RP
#line 268 "parser.yy"
                            {
                            yylhs.value.as < Node * > () = new Node("CallMethod", yystack_[3].value.as < std::string > (), yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
            }
#line 1308 "parser.tab.cc"
    break;

  case 44: // expression: NOT expression
#line 272 "parser.yy"
                             {
                            yylhs.value.as < Node * > () = new Node("Not", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1317 "parser.tab.cc"
    break;

  case 45: // expression: baseType LB args RB
#line 276 "parser.yy"
                                  {
                            yylhs.value.as < Node * > () = new Node("Array", "", yylineno);
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
                            yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
            }
#line 1327 "parser.tab.cc"
    break;

  case 46: // expression: factor
#line 281 "parser.yy"
                          {yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > (); /* printf("r4 ");*/}
#line 1333 "parser.tab.cc"
    break;

  case 47: // factor: INT
#line 284 "parser.yy"
                          {  yylhs.value.as < Node * > () = new Node("int", yystack_[0].value.as < std::string > (), yylineno); /* printf("r5 ");  Here we create a leaf node Int. The value of the leaf node is $1 */}
#line 1339 "parser.tab.cc"
    break;

  case 48: // factor: FLOAT
#line 285 "parser.yy"
                          {  yylhs.value.as < Node * > () = new Node("float", yystack_[0].value.as < std::string > (), yylineno);}
#line 1345 "parser.tab.cc"
    break;

  case 49: // factor: TRUE
#line 286 "parser.yy"
                          {  yylhs.value.as < Node * > () = new Node("true", "", yylineno);}
#line 1351 "parser.tab.cc"
    break;

  case 50: // factor: FALSE
#line 287 "parser.yy"
                          {  yylhs.value.as < Node * > () = new Node("false", "", yylineno);}
#line 1357 "parser.tab.cc"
    break;

  case 51: // factor: ID
#line 288 "parser.yy"
                          {  yylhs.value.as < Node * > () = new Node("ID", yystack_[0].value.as < std::string > (), yylineno);}
#line 1363 "parser.tab.cc"
    break;

  case 52: // factor: LP expression RP
#line 289 "parser.yy"
                               { yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > (); /* printf("r6 ");  simply return the expression */}
#line 1369 "parser.tab.cc"
    break;

  case 53: // arglist: expression
#line 292 "parser.yy"
                    {
                yylhs.value.as < Node * > () = new Node("Arguments", "", yylineno);
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1378 "parser.tab.cc"
    break;

  case 54: // arglist: arglist DELIMITER expression
#line 296 "parser.yy"
                                           {
              yylhs.value.as < Node * > () = yystack_[2].value.as < Node * > ();
              yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1387 "parser.tab.cc"
    break;

  case 55: // args: arglist
#line 302 "parser.yy"
               {
                yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > ();
          }
#line 1395 "parser.tab.cc"
    break;

  case 56: // args: %empty
#line 305 "parser.yy"
                   {
            yylhs.value.as < Node * > () = new Node("Arguments", "", yylineno);
          }
#line 1403 "parser.tab.cc"
    break;

  case 57: // baseType: INT_TYPE
#line 310 "parser.yy"
                   {
                yylhs.value.as < Node * > () = new Node("IntType", yystack_[0].value.as < std::string > (), yylineno);
            }
#line 1411 "parser.tab.cc"
    break;

  case 58: // baseType: FLOAT_TYPE
#line 313 "parser.yy"
                         {
                            yylhs.value.as < Node * > () = new Node("FloatType", yystack_[0].value.as < std::string > (), yylineno);
            }
#line 1419 "parser.tab.cc"
    break;

  case 59: // baseType: BOOLEAN_TYPE
#line 316 "parser.yy"
                           {
                            yylhs.value.as < Node * > () = new Node("BoolType", yystack_[0].value.as < std::string > (), yylineno);
            }
#line 1427 "parser.tab.cc"
    break;

  case 60: // variable: ID IS_OF type
#line 321 "parser.yy"
                        {
              yylhs.value.as < Node * > () = new Node("Variable", yystack_[2].value.as < std::string > (), yylineno - 1);
              yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1436 "parser.tab.cc"
    break;

  case 61: // variable: VOLATILE_TYPE ID IS_OF type
#line 325 "parser.yy"
                                          {
              yylhs.value.as < Node * > () = new Node("VolatileVariable", yystack_[2].value.as < std::string > (), yylineno - 1);
              yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1445 "parser.tab.cc"
    break;

  case 62: // variable: ID IS_OF type ASSIGN expression
#line 329 "parser.yy"
                                              {
              yylhs.value.as < Node * > () = new Node("AssignVariable", yystack_[4].value.as < std::string > (), yylineno - 1);
              yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
              yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1455 "parser.tab.cc"
    break;

  case 63: // variable: VOLATILE_TYPE ID IS_OF type ASSIGN expression
#line 334 "parser.yy"
                                                            {
              yylhs.value.as < Node * > () = new Node("AssignVolatileVariable", yystack_[4].value.as < std::string > (), yylineno - 1);
              yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
              yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1465 "parser.tab.cc"
    break;

  case 64: // for_init: variable
#line 341 "parser.yy"
                   {
              yylhs.value.as < Node * > () = new Node("Initialization", "", yylineno);
              yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1474 "parser.tab.cc"
    break;

  case 65: // for_init: expression ASSIGN expression
#line 345 "parser.yy"
                                           {
              yylhs.value.as < Node * > () = new Node("Initialization", "", yylineno);
              Node* assignNode = new Node("Assign", "", yylineno);
              assignNode->children.push_back(yystack_[2].value.as < Node * > ());
              assignNode->children.push_back(yystack_[0].value.as < Node * > ());
              yylhs.value.as < Node * > ()->children.push_back(assignNode);
            }
#line 1486 "parser.tab.cc"
    break;

  case 66: // for_init: %empty
#line 352 "parser.yy"
                     {
              yylhs.value.as < Node * > () = nullptr;
            }
#line 1494 "parser.tab.cc"
    break;

  case 67: // for_cond: expression
#line 357 "parser.yy"
                     {
              yylhs.value.as < Node * > () = new Node("Condition", "", yylineno);
              yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
            }
#line 1503 "parser.tab.cc"
    break;

  case 68: // for_cond: %empty
#line 361 "parser.yy"
                     {
              yylhs.value.as < Node * > () = nullptr;
            }
#line 1511 "parser.tab.cc"
    break;

  case 69: // for_upd: expression ASSIGN expression
#line 366 "parser.yy"
                                      {
              yylhs.value.as < Node * > () = new Node("Update", "", yylineno);
              Node* assignNode = new Node("Assign", "", yylineno);
              assignNode->children.push_back(yystack_[2].value.as < Node * > ());
              assignNode->children.push_back(yystack_[0].value.as < Node * > ());
              yylhs.value.as < Node * > ()->children.push_back(assignNode);
            }
#line 1523 "parser.tab.cc"
    break;

  case 70: // stmts: statement
#line 375 "parser.yy"
                 {
              yylhs.value.as < Node * > () = new Node("StatementList", "", yylineno);
              if (yystack_[0].value.as < Node * > () != nullptr){
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
              }
            }
#line 1534 "parser.tab.cc"
    break;

  case 71: // stmts: stmts statement
#line 381 "parser.yy"
                              {
              yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
              if (yystack_[0].value.as < Node * > () != nullptr){
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
              }
            }
#line 1545 "parser.tab.cc"
    break;

  case 72: // stmtBl: LCB stmts RCB
#line 388 "parser.yy"
                      {
              yylhs.value.as < Node * > () = new Node("StatementBlock", "", yylineno);
              if (yystack_[1].value.as < Node * > () != nullptr){
                for (Node* child : yystack_[1].value.as < Node * > ()->children){
                  yylhs.value.as < Node * > ()->children.push_back(child);
                }
              }
            }
#line 1558 "parser.tab.cc"
    break;

  case 73: // stmtBl: LCB RCB
#line 396 "parser.yy"
                      {
              yylhs.value.as < Node * > () = new Node("EmptyStatementBlock", "", yylineno);
            }
#line 1566 "parser.tab.cc"
    break;

  case 74: // stmtEnd: NEWLINE
#line 401 "parser.yy"
                 {
            yylhs.value.as < Node * > () = nullptr;
          }
#line 1574 "parser.tab.cc"
    break;

  case 75: // statement: stmtBl
#line 406 "parser.yy"
                  {
              yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > ();
            }
#line 1582 "parser.tab.cc"
    break;

  case 76: // statement: stmtEnd
#line 409 "parser.yy"
                      {
              yylhs.value.as < Node * > () = nullptr;
            }
#line 1590 "parser.tab.cc"
    break;

  case 77: // statement: variable stmtEnd
#line 412 "parser.yy"
                               {
              yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
            }
#line 1598 "parser.tab.cc"
    break;

  case 78: // statement: expression ASSIGN expression stmtEnd
#line 415 "parser.yy"
                                                   {
              yylhs.value.as < Node * > () = new Node("Assign", "", yylineno);
              yylhs.value.as < Node * > ()->children.push_back(yystack_[3].value.as < Node * > ());
              yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
            }
#line 1608 "parser.tab.cc"
    break;

  case 79: // statement: IF LP expression RP statement
#line 420 "parser.yy"
                                                        {
              yylhs.value.as < Node * > () = new Node("IfStatement", "", yylineno);
              Node* condNode = new Node("Condition", "", yylineno);
              condNode->children.push_back(yystack_[2].value.as < Node * > ());
              yylhs.value.as < Node * > ()->children.push_back(condNode);
              if (yystack_[0].value.as < Node * > () != nullptr){
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
              }
            }
#line 1622 "parser.tab.cc"
    break;

  case 80: // statement: IF LP expression RP statement ELSE statement
#line 429 "parser.yy"
                                                           {
              yylhs.value.as < Node * > () = new Node("IfElseStatement", "", yylineno);
              Node* condNode = new Node("Condition", "", yylineno);
              condNode->children.push_back(yystack_[4].value.as < Node * > ());
              yylhs.value.as < Node * > ()->children.push_back(condNode);

              if (yystack_[2].value.as < Node * > ()->type == "StatementBlock"){
                yystack_[2].value.as < Node * > ()->type = "ThenBody";
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
              } else {
                Node* thenNode = new Node("ThenBody", "", yylineno);
                thenNode->children.push_back(yystack_[2].value.as < Node * > ());
                yylhs.value.as < Node * > ()->children.push_back(thenNode);
              }

              Node* elseNode = new Node("ElseBody", "", yylineno);
              elseNode->children.push_back(yystack_[0].value.as < Node * > ());
              yylhs.value.as < Node * > ()->children.push_back(elseNode);
            }
#line 1646 "parser.tab.cc"
    break;

  case 81: // statement: FOR LP for_init DELIMITER for_cond DELIMITER for_upd RP statement
#line 448 "parser.yy"
                                                                                {
              yylhs.value.as < Node * > () = new Node("ForStatement", "", yylineno);
              if (yystack_[6].value.as < Node * > () != nullptr){
                yylhs.value.as < Node * > ()->children.push_back(yystack_[6].value.as < Node * > ());
              }
              if (yystack_[4].value.as < Node * > () != nullptr){
                yylhs.value.as < Node * > ()->children.push_back(yystack_[4].value.as < Node * > ());
              }
              if (yystack_[2].value.as < Node * > () != nullptr){
                yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
              }
              if (yystack_[0].value.as < Node * > ()->type == "StatementBlock"){
                yystack_[0].value.as < Node * > ()->type = "LoopBody";
                yylhs.value.as < Node * > ()->children.push_back(yystack_[0].value.as < Node * > ());
              } else {
                  Node* bodyNode = new Node("LoopBody", "", yylineno);
                  bodyNode->children.push_back(yystack_[0].value.as < Node * > ());
                  yylhs.value.as < Node * > ()->children.push_back(bodyNode);
              }
            }
#line 1671 "parser.tab.cc"
    break;

  case 82: // statement: PRINT LP expression RP stmtEnd
#line 468 "parser.yy"
                                             {
              yylhs.value.as < Node * > () = new Node("Print", "", yylineno);
              yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
            }
#line 1680 "parser.tab.cc"
    break;

  case 83: // statement: READ LP expression RP stmtEnd
#line 472 "parser.yy"
                                            {
              yylhs.value.as < Node * > () = new Node("Read", "", yylineno);
              yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
            }
#line 1689 "parser.tab.cc"
    break;

  case 84: // statement: RETURN expression stmtEnd
#line 476 "parser.yy"
                                        {
              yylhs.value.as < Node * > () = new Node("Return", "", yylineno);
              yylhs.value.as < Node * > ()->children.push_back(yystack_[1].value.as < Node * > ());
            }
#line 1698 "parser.tab.cc"
    break;

  case 85: // statement: BREAK stmtEnd
#line 480 "parser.yy"
                            {
              yylhs.value.as < Node * > () = new Node("Break", "", yylineno);
            }
#line 1706 "parser.tab.cc"
    break;

  case 86: // statement: CONTINUE stmtEnd
#line 483 "parser.yy"
                               {
              yylhs.value.as < Node * > () = new Node("Continue", "", yylineno);
            }
#line 1714 "parser.tab.cc"
    break;

  case 87: // statement: expression stmtEnd
#line 486 "parser.yy"
                                 {
              yylhs.value.as < Node * > () = yystack_[1].value.as < Node * > ();
            }
#line 1722 "parser.tab.cc"
    break;

  case 88: // type: baseType
#line 491 "parser.yy"
               {
            yylhs.value.as < Node * > () = yystack_[0].value.as < Node * > ();
            }
#line 1730 "parser.tab.cc"
    break;

  case 89: // type: baseType LB RB
#line 494 "parser.yy"
                             {
            yylhs.value.as < Node * > () = new Node("Type", "array", yylineno);
            yylhs.value.as < Node * > ()->children.push_back(yystack_[2].value.as < Node * > ());
            }
#line 1739 "parser.tab.cc"
    break;

  case 90: // type: ID
#line 498 "parser.yy"
                 {
            yylhs.value.as < Node * > () = new Node("Type", yystack_[0].value.as < std::string > (), yylineno);
            }
#line 1747 "parser.tab.cc"
    break;

  case 91: // type: VOID_TYPE
#line 501 "parser.yy"
                        {
            yylhs.value.as < Node * > () = new Node("Type", yystack_[0].value.as < std::string > (), yylineno);
            }
#line 1755 "parser.tab.cc"
    break;


#line 1759 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -87;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
       2,   175,    13,    16,    -8,   -87,    40,   -87,     4,     4,
     -87,    35,    40,    37,   -13,   -87,   -87,     0,   -87,   -87,
     -87,   -87,   -87,    40,    39,    76,   297,   -87,    15,     4,
     214,   -87,   -87,   -87,   -87,   -87,    60,    49,    -7,    73,
     -87,     4,     4,   -87,    87,   324,   -87,   -87,    40,    84,
      -4,    74,    40,   -23,   351,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,   -26,   -87,    40,   -87,   -87,   -87,    88,     4,
     -87,   101,   -87,    56,   -87,   -87,   -87,   378,   405,   -87,
      80,   -23,   540,    90,   106,   -87,   -87,    98,    99,   -87,
     432,   459,   100,   100,    82,    82,    82,   486,   351,   594,
     594,   594,   594,   594,   594,   621,   567,   112,   -87,   108,
     -87,   -87,   113,   -87,    89,     2,     4,     4,   -87,   253,
      40,    40,   105,    40,   -87,   118,    40,     4,     4,   -87,
     -87,    40,   -87,   107,    96,   -87,   -87,   -87,   103,   540,
     540,   109,    40,   540,   -87,   540,   -87,   -87,   129,   102,
     114,   -87,   116,   131,   253,    40,   540,   -87,     2,   -23,
      96,   117,   -87,   513,   138,   -87,   -87,   -87,   -23,    40,
     253,   -87,   540,   -87
  };

  const signed char
  parser::yydefact_[] =
  {
      13,     0,     0,     0,    18,     4,     0,    73,     0,     0,
      74,     0,     0,     0,     0,    47,    48,    51,    59,    49,
      50,    57,    58,     0,     0,     0,     0,    46,     0,     0,
       0,    75,    76,    70,     1,     2,     0,     0,    17,     0,
      22,     0,     0,    12,    51,     0,    85,    86,     0,    44,
      66,     0,    56,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,    56,    77,    72,    71,     0,     0,
      16,     0,     3,     0,    14,    11,    52,     0,     0,    64,
       0,     0,    53,    55,     0,    90,    91,    88,    60,    84,
       0,     0,    27,    28,    29,    30,    31,     0,     0,    38,
      35,    34,    36,    37,    39,    32,    33,     0,    41,     0,
      23,    15,     0,    24,     0,     0,     0,     0,    21,     0,
       0,    68,    61,     0,    43,     0,     0,     0,     0,    40,
      78,    56,    45,     0,    10,    26,    20,    19,    79,    65,
      67,     0,     0,    54,    89,    62,    82,    83,     0,     0,
       0,     7,     9,     0,     0,     0,    63,    42,     0,     0,
       0,     0,    80,     0,     0,     5,     6,     8,     0,     0,
       0,    25,    69,    81
  };

  const signed char
  parser::yypgoto_[] =
  {
     -87,   -87,   -87,   -87,   -22,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   111,   -87,   -87,    -6,   -87,   -87,   -67,   -50,
      19,   -87,   -87,   -87,   -87,     1,    62,   -28,   -86
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,     2,     3,    82,   161,   162,   163,     4,    38,    39,
      83,    40,    41,   125,   126,    26,    27,    93,    94,    28,
      29,    90,   151,   174,    30,    31,    32,    33,    98
  };

  const short
  parser::yytable_[] =
  {
      45,     5,    77,    97,     6,   132,    49,   119,    52,    10,
      10,   117,     1,    34,    95,    18,    35,    54,    21,    22,
      96,    10,   118,    42,    51,    53,    14,    74,    12,    36,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    37,
      37,    97,    87,    48,    88,    50,    92,    55,     6,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,    43,   123,    92,    89,
      46,    47,    12,    10,   158,    15,    16,    44,    18,    19,
      20,    21,    22,   176,    56,    53,    78,    81,    73,    61,
      14,    75,   181,   124,    62,    52,    62,   144,   120,    91,
      80,   148,   127,    84,    85,    59,    60,    61,   131,   122,
     135,    72,    62,    72,    53,   134,    99,   136,   133,    97,
     141,   142,   143,   152,   149,   150,   145,   153,    97,    72,
     155,   154,   159,   160,   164,    92,   172,   165,   167,   169,
     171,   121,   178,   168,   170,   128,   166,   180,   177,    79,
       0,     0,   183,     0,     0,     0,     0,     0,     0,   173,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   175,
     140,     0,     0,   182,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,     0,     1,     7,     0,   146,   147,
       8,     9,    10,     0,     0,     0,     0,     0,     0,   156,
     157,     0,     0,     0,     0,    11,     0,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,     0,    23,
      24,    25,     6,     0,     1,    76,     0,     0,     0,     8,
       9,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    11,     0,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,     0,    23,    24,
      25,     6,     0,     1,     0,     0,     0,     0,     8,     9,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,     0,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,     0,    23,    24,    25,
      57,    58,    59,    60,    61,     0,     0,     0,     0,    62,
       0,     0,     0,     0,    10,    63,    64,    65,    66,    67,
      68,    69,     0,    70,    71,     0,    72,    57,    58,    59,
      60,    61,     0,    86,     0,     0,    62,     0,     0,     0,
       0,     0,     0,    64,    65,    66,    67,    68,    69,     0,
      70,    71,     0,    72,    57,    58,    59,    60,    61,     0,
       0,     0,     0,    62,     0,     0,     0,     0,    10,     0,
      64,    65,    66,    67,    68,    69,     0,    70,    71,     0,
      72,    57,    58,    59,    60,    61,     0,   129,     0,     0,
      62,     0,     0,     0,     0,     0,     0,    64,    65,    66,
      67,    68,    69,     0,    70,    71,     0,    72,    57,    58,
      59,    60,    61,     0,     0,     0,     0,    62,     0,     0,
       0,     0,     0,   130,    64,    65,    66,    67,    68,    69,
       0,    70,    71,     0,    72,    57,    58,    59,    60,    61,
       0,   137,     0,     0,    62,     0,     0,     0,     0,     0,
       0,    64,    65,    66,    67,    68,    69,     0,    70,    71,
       0,    72,    57,    58,    59,    60,    61,     0,   138,     0,
       0,    62,     0,     0,     0,     0,     0,     0,    64,    65,
      66,    67,    68,    69,     0,    70,    71,     0,    72,    57,
      58,    59,    60,    61,     0,     0,     0,     0,    62,   139,
       0,     0,     0,     0,     0,    64,    65,    66,    67,    68,
      69,     0,    70,    71,     0,    72,    57,    58,    59,    60,
      61,     0,     0,     0,     0,    62,     0,     0,     0,     0,
       0,   179,    64,    65,    66,    67,    68,    69,     0,    70,
      71,     0,    72,    57,    58,    59,    60,    61,     0,     0,
       0,     0,    62,     0,     0,     0,     0,     0,     0,    64,
      65,    66,    67,    68,    69,     0,    70,    71,     0,    72,
      57,    58,    59,    60,    61,     0,     0,     0,     0,    62,
       0,     0,     0,     0,     0,     0,    64,    65,    66,    67,
      68,    69,     0,    70,     0,     0,    72,    57,    58,    59,
      60,    61,     0,     0,     0,     0,    62,     0,     0,     0,
       0,     0,     0,    -1,    -1,    -1,    -1,    -1,    -1,     0,
       0,     0,     0,    72,    57,    58,    59,    60,    61,     0,
       0,     0,     0,    62,     0,     0,     0,     0,     0,     0,
      64,    65,    66,    67,    68,    69,     0,     0,     0,     0,
      72
  };

  const short
  parser::yycheck_[] =
  {
       6,     0,    30,    53,     8,    91,    12,    74,     8,    17,
      17,    37,    10,     0,    37,    38,     0,    23,    41,    42,
      43,    17,    48,     4,    37,    25,    34,    12,    32,    37,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    47,
      47,    91,    48,     8,    50,     8,    52,     8,     8,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,     4,    11,    74,    50,
       8,     9,    32,    17,   141,    35,    36,    37,    38,    39,
      40,    41,    42,   169,     8,    25,    37,    14,    26,     7,
      34,    29,   178,    37,    12,     8,    12,     8,    10,    25,
      38,   129,    83,    41,    42,     5,     6,     7,    28,     8,
      12,    29,    12,    29,    25,     9,    54,    18,    28,   169,
       8,    13,     9,    18,   130,   131,   125,   133,   178,    29,
     136,    13,    25,    37,    31,   141,   164,    28,     9,    25,
       9,    79,    25,    41,    28,    83,   152,     9,   170,    38,
      -1,    -1,   180,    -1,    -1,    -1,    -1,    -1,    -1,   165,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   168,
     108,    -1,    -1,   179,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     8,    -1,    10,    11,    -1,   126,   127,
      15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,   137,
     138,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      45,    46,     8,    -1,    10,    11,    -1,    -1,    -1,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    45,
      46,     8,    -1,    10,    -1,    -1,    -1,    -1,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    45,    46,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    26,    27,    -1,    29,     3,     4,     5,
       6,     7,    -1,     9,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    -1,
      26,    27,    -1,    29,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    -1,
      19,    20,    21,    22,    23,    24,    -1,    26,    27,    -1,
      29,     3,     4,     5,     6,     7,    -1,     9,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    -1,    26,    27,    -1,    29,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    26,    27,    -1,    29,     3,     4,     5,     6,     7,
      -1,     9,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    -1,    26,    27,
      -1,    29,     3,     4,     5,     6,     7,    -1,     9,    -1,
      -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    -1,    26,    27,    -1,    29,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    12,    13,
      -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,
      24,    -1,    26,    27,    -1,    29,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    26,
      27,    -1,    29,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    -1,    26,    27,    -1,    29,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    -1,    26,    -1,    -1,    29,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    29,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      29
  };

  const signed char
  parser::yystos_[] =
  {
       0,    10,    51,    52,    57,    75,     8,    11,    15,    16,
      17,    30,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    44,    45,    46,    65,    66,    69,    70,
      74,    75,    76,    77,     0,     0,    37,    47,    58,    59,
      61,    62,    70,    76,    37,    65,    76,    76,     8,    65,
       8,    37,     8,    25,    65,     8,     8,     3,     4,     5,
       6,     7,    12,    18,    19,    20,    21,    22,    23,    24,
      26,    27,    29,    76,    12,    76,    11,    77,    37,    62,
      76,    14,    53,    60,    76,    76,     9,    65,    65,    70,
      71,    25,    65,    67,    68,    37,    43,    69,    78,    76,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    37,    48,    68,
      10,    76,     8,    11,    37,    63,    64,    70,    76,     9,
      18,    28,    78,    28,     9,    12,    18,     9,     9,    13,
      76,     8,    13,     9,     8,    75,    76,    76,    77,    65,
      65,    72,    18,    65,    13,    65,    76,    76,    68,    25,
      37,    54,    55,    56,    31,    28,    65,     9,    41,    25,
      28,     9,    77,    65,    73,    75,    78,    54,    25,    18,
       9,    78,    65,    77
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    50,    51,    52,    52,    53,    54,    55,    55,    56,
      56,    57,    57,    57,    58,    58,    58,    59,    59,    60,
      60,    60,    60,    61,    62,    63,    64,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    66,    66,    66,
      66,    66,    66,    67,    67,    68,    68,    69,    69,    69,
      70,    70,    70,    70,    71,    71,    71,    72,    72,    73,
      74,    74,    75,    75,    76,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    78,    78,
      78,    78
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     3,     1,     6,     3,     1,     3,     1,
       0,     3,     2,     0,     2,     3,     2,     1,     0,     3,
       3,     2,     0,     3,     3,     6,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     3,     6,     4,     2,     4,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     0,     1,     1,     1,
       3,     4,     5,     6,     1,     3,     0,     1,     0,     3,
       1,     2,     3,     2,     1,     1,     1,     2,     4,     5,
       7,     9,     5,     5,     3,     2,     2,     2,     1,     3,
       1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "PLUSOP", "SUBOP",
  "MULTOP", "DIVOP", "POWOP", "LP", "RP", "LCB", "RCB", "LB", "RB", "MAIN",
  "BREAK", "CONTINUE", "NEWLINE", "ASSIGN", "EQUAL_TO", "GREATER_THAN",
  "LESS_THAN", "LESS_OR_EQUAL_TO", "GREATER_OR_EQUAL_TO", "NOT_EQUAL_TO",
  "IS_OF", "AND", "OR", "DELIMITER", "DOT", "IF", "ELSE", "NOT", "FOR",
  "VOLATILE_TYPE", "INT", "FLOAT", "ID", "BOOLEAN_TYPE", "TRUE", "FALSE",
  "INT_TYPE", "FLOAT_TYPE", "VOID_TYPE", "RETURN", "PRINT", "READ",
  "CLASS", "LEN", "IFELSE", "$accept", "root", "program", "entry", "param",
  "param_list", "params", "var_list", "classes", "class_list",
  "class_body", "class_decl", "class", "method_decl", "method",
  "expression", "factor", "arglist", "args", "baseType", "variable",
  "for_init", "for_cond", "for_upd", "stmts", "stmtBl", "stmtEnd",
  "statement", "type", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    51,    51,    53,    67,    74,    80,    86,    90,    96,
      99,   104,   108,   111,   116,   120,   124,   129,   132,   136,
     140,   144,   147,   152,   156,   167,   180,   185,   191,   197,
     203,   208,   213,   218,   223,   228,   233,   238,   243,   248,
     253,   259,   263,   268,   272,   276,   281,   284,   285,   286,
     287,   288,   289,   292,   296,   302,   305,   310,   313,   316,
     321,   325,   329,   334,   341,   345,   352,   357,   361,   366,
     375,   381,   388,   396,   401,   406,   409,   412,   415,   420,
     429,   448,   468,   472,   476,   480,   483,   486,   491,   494,
     498,   501
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2440 "parser.tab.cc"

