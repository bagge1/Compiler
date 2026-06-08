// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file parser.tab.hh
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_PARSER_TAB_HH_INCLUDED
# define YY_YY_PARSER_TAB_HH_INCLUDED
// "%code requires" blocks.
#line 9 "parser.yy"

  #include <string>
  #include "Node.h"
  #define USE_LEX_ONLY false //change this macro to true if you want to isolate the lexer from the parser.

#line 55 "parser.tab.hh"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif



#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

namespace yy {
#line 190 "parser.tab.hh"




  /// A Bison parser.
  class parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // root
      // program
      // entry
      // param
      // param_list
      // params
      // var_list
      // classes
      // class_list
      // class_body
      // class_decl
      // class
      // method_decl
      // method
      // expression
      // factor
      // arglist
      // args
      // baseType
      // variable
      // for_init
      // for_cond
      // for_upd
      // stmts
      // stmtBl
      // stmtEnd
      // statement
      // type
      char dummy1[sizeof (Node *)];

      // PLUSOP
      // SUBOP
      // MULTOP
      // DIVOP
      // POWOP
      // LP
      // RP
      // LCB
      // RCB
      // LB
      // RB
      // MAIN
      // BREAK
      // CONTINUE
      // NEWLINE
      // ASSIGN
      // EQUAL_TO
      // GREATER_THAN
      // LESS_THAN
      // LESS_OR_EQUAL_TO
      // GREATER_OR_EQUAL_TO
      // NOT_EQUAL_TO
      // IS_OF
      // AND
      // OR
      // DELIMITER
      // DOT
      // IF
      // ELSE
      // NOT
      // FOR
      // VOLATILE_TYPE
      // INT
      // FLOAT
      // ID
      // BOOLEAN_TYPE
      // TRUE
      // FALSE
      // INT_TYPE
      // FLOAT_TYPE
      // VOID_TYPE
      // RETURN
      // PRINT
      // READ
      // CLASS
      // LEN
      char dummy2[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;


    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    END = 0,                       // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    PLUSOP = 258,                  // PLUSOP
    SUBOP = 259,                   // SUBOP
    MULTOP = 260,                  // MULTOP
    DIVOP = 261,                   // DIVOP
    POWOP = 262,                   // POWOP
    LP = 263,                      // LP
    RP = 264,                      // RP
    LCB = 265,                     // LCB
    RCB = 266,                     // RCB
    LB = 267,                      // LB
    RB = 268,                      // RB
    MAIN = 269,                    // MAIN
    BREAK = 270,                   // BREAK
    CONTINUE = 271,                // CONTINUE
    NEWLINE = 272,                 // NEWLINE
    ASSIGN = 273,                  // ASSIGN
    EQUAL_TO = 274,                // EQUAL_TO
    GREATER_THAN = 275,            // GREATER_THAN
    LESS_THAN = 276,               // LESS_THAN
    LESS_OR_EQUAL_TO = 277,        // LESS_OR_EQUAL_TO
    GREATER_OR_EQUAL_TO = 278,     // GREATER_OR_EQUAL_TO
    NOT_EQUAL_TO = 279,            // NOT_EQUAL_TO
    IS_OF = 280,                   // IS_OF
    AND = 281,                     // AND
    OR = 282,                      // OR
    DELIMITER = 283,               // DELIMITER
    DOT = 284,                     // DOT
    IF = 285,                      // IF
    ELSE = 286,                    // ELSE
    NOT = 287,                     // NOT
    FOR = 288,                     // FOR
    VOLATILE_TYPE = 289,           // VOLATILE_TYPE
    INT = 290,                     // INT
    FLOAT = 291,                   // FLOAT
    ID = 292,                      // ID
    BOOLEAN_TYPE = 293,            // BOOLEAN_TYPE
    TRUE = 294,                    // TRUE
    FALSE = 295,                   // FALSE
    INT_TYPE = 296,                // INT_TYPE
    FLOAT_TYPE = 297,              // FLOAT_TYPE
    VOID_TYPE = 298,               // VOID_TYPE
    RETURN = 299,                  // RETURN
    PRINT = 300,                   // PRINT
    READ = 301,                    // READ
    CLASS = 302,                   // CLASS
    LEN = 303,                     // LEN
    IFELSE = 304                   // IFELSE
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 50, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_PLUSOP = 3,                            // PLUSOP
        S_SUBOP = 4,                             // SUBOP
        S_MULTOP = 5,                            // MULTOP
        S_DIVOP = 6,                             // DIVOP
        S_POWOP = 7,                             // POWOP
        S_LP = 8,                                // LP
        S_RP = 9,                                // RP
        S_LCB = 10,                              // LCB
        S_RCB = 11,                              // RCB
        S_LB = 12,                               // LB
        S_RB = 13,                               // RB
        S_MAIN = 14,                             // MAIN
        S_BREAK = 15,                            // BREAK
        S_CONTINUE = 16,                         // CONTINUE
        S_NEWLINE = 17,                          // NEWLINE
        S_ASSIGN = 18,                           // ASSIGN
        S_EQUAL_TO = 19,                         // EQUAL_TO
        S_GREATER_THAN = 20,                     // GREATER_THAN
        S_LESS_THAN = 21,                        // LESS_THAN
        S_LESS_OR_EQUAL_TO = 22,                 // LESS_OR_EQUAL_TO
        S_GREATER_OR_EQUAL_TO = 23,              // GREATER_OR_EQUAL_TO
        S_NOT_EQUAL_TO = 24,                     // NOT_EQUAL_TO
        S_IS_OF = 25,                            // IS_OF
        S_AND = 26,                              // AND
        S_OR = 27,                               // OR
        S_DELIMITER = 28,                        // DELIMITER
        S_DOT = 29,                              // DOT
        S_IF = 30,                               // IF
        S_ELSE = 31,                             // ELSE
        S_NOT = 32,                              // NOT
        S_FOR = 33,                              // FOR
        S_VOLATILE_TYPE = 34,                    // VOLATILE_TYPE
        S_INT = 35,                              // INT
        S_FLOAT = 36,                            // FLOAT
        S_ID = 37,                               // ID
        S_BOOLEAN_TYPE = 38,                     // BOOLEAN_TYPE
        S_TRUE = 39,                             // TRUE
        S_FALSE = 40,                            // FALSE
        S_INT_TYPE = 41,                         // INT_TYPE
        S_FLOAT_TYPE = 42,                       // FLOAT_TYPE
        S_VOID_TYPE = 43,                        // VOID_TYPE
        S_RETURN = 44,                           // RETURN
        S_PRINT = 45,                            // PRINT
        S_READ = 46,                             // READ
        S_CLASS = 47,                            // CLASS
        S_LEN = 48,                              // LEN
        S_IFELSE = 49,                           // IFELSE
        S_YYACCEPT = 50,                         // $accept
        S_root = 51,                             // root
        S_program = 52,                          // program
        S_entry = 53,                            // entry
        S_param = 54,                            // param
        S_param_list = 55,                       // param_list
        S_params = 56,                           // params
        S_var_list = 57,                         // var_list
        S_classes = 58,                          // classes
        S_class_list = 59,                       // class_list
        S_class_body = 60,                       // class_body
        S_class_decl = 61,                       // class_decl
        S_class = 62,                            // class
        S_method_decl = 63,                      // method_decl
        S_method = 64,                           // method
        S_expression = 65,                       // expression
        S_factor = 66,                           // factor
        S_arglist = 67,                          // arglist
        S_args = 68,                             // args
        S_baseType = 69,                         // baseType
        S_variable = 70,                         // variable
        S_for_init = 71,                         // for_init
        S_for_cond = 72,                         // for_cond
        S_for_upd = 73,                          // for_upd
        S_stmts = 74,                            // stmts
        S_stmtBl = 75,                           // stmtBl
        S_stmtEnd = 76,                          // stmtEnd
        S_statement = 77,                        // statement
        S_type = 78                              // type
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
      {
        switch (this->kind ())
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
        value.move< Node * > (std::move (that.value));
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
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Node *&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Node *& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
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
        value.template destroy< Node * > ();
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
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#else
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const std::string& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
    };

    /// Build a parser object.
    parser ();
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END ()
      {
        return symbol_type (token::END);
      }
#else
      static
      symbol_type
      make_END ()
      {
        return symbol_type (token::END);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#else
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#else
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUSOP (std::string v)
      {
        return symbol_type (token::PLUSOP, std::move (v));
      }
#else
      static
      symbol_type
      make_PLUSOP (const std::string& v)
      {
        return symbol_type (token::PLUSOP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUBOP (std::string v)
      {
        return symbol_type (token::SUBOP, std::move (v));
      }
#else
      static
      symbol_type
      make_SUBOP (const std::string& v)
      {
        return symbol_type (token::SUBOP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MULTOP (std::string v)
      {
        return symbol_type (token::MULTOP, std::move (v));
      }
#else
      static
      symbol_type
      make_MULTOP (const std::string& v)
      {
        return symbol_type (token::MULTOP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIVOP (std::string v)
      {
        return symbol_type (token::DIVOP, std::move (v));
      }
#else
      static
      symbol_type
      make_DIVOP (const std::string& v)
      {
        return symbol_type (token::DIVOP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POWOP (std::string v)
      {
        return symbol_type (token::POWOP, std::move (v));
      }
#else
      static
      symbol_type
      make_POWOP (const std::string& v)
      {
        return symbol_type (token::POWOP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LP (std::string v)
      {
        return symbol_type (token::LP, std::move (v));
      }
#else
      static
      symbol_type
      make_LP (const std::string& v)
      {
        return symbol_type (token::LP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RP (std::string v)
      {
        return symbol_type (token::RP, std::move (v));
      }
#else
      static
      symbol_type
      make_RP (const std::string& v)
      {
        return symbol_type (token::RP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LCB (std::string v)
      {
        return symbol_type (token::LCB, std::move (v));
      }
#else
      static
      symbol_type
      make_LCB (const std::string& v)
      {
        return symbol_type (token::LCB, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RCB (std::string v)
      {
        return symbol_type (token::RCB, std::move (v));
      }
#else
      static
      symbol_type
      make_RCB (const std::string& v)
      {
        return symbol_type (token::RCB, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LB (std::string v)
      {
        return symbol_type (token::LB, std::move (v));
      }
#else
      static
      symbol_type
      make_LB (const std::string& v)
      {
        return symbol_type (token::LB, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RB (std::string v)
      {
        return symbol_type (token::RB, std::move (v));
      }
#else
      static
      symbol_type
      make_RB (const std::string& v)
      {
        return symbol_type (token::RB, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAIN (std::string v)
      {
        return symbol_type (token::MAIN, std::move (v));
      }
#else
      static
      symbol_type
      make_MAIN (const std::string& v)
      {
        return symbol_type (token::MAIN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BREAK (std::string v)
      {
        return symbol_type (token::BREAK, std::move (v));
      }
#else
      static
      symbol_type
      make_BREAK (const std::string& v)
      {
        return symbol_type (token::BREAK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTINUE (std::string v)
      {
        return symbol_type (token::CONTINUE, std::move (v));
      }
#else
      static
      symbol_type
      make_CONTINUE (const std::string& v)
      {
        return symbol_type (token::CONTINUE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEWLINE (std::string v)
      {
        return symbol_type (token::NEWLINE, std::move (v));
      }
#else
      static
      symbol_type
      make_NEWLINE (const std::string& v)
      {
        return symbol_type (token::NEWLINE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN (std::string v)
      {
        return symbol_type (token::ASSIGN, std::move (v));
      }
#else
      static
      symbol_type
      make_ASSIGN (const std::string& v)
      {
        return symbol_type (token::ASSIGN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUAL_TO (std::string v)
      {
        return symbol_type (token::EQUAL_TO, std::move (v));
      }
#else
      static
      symbol_type
      make_EQUAL_TO (const std::string& v)
      {
        return symbol_type (token::EQUAL_TO, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATER_THAN (std::string v)
      {
        return symbol_type (token::GREATER_THAN, std::move (v));
      }
#else
      static
      symbol_type
      make_GREATER_THAN (const std::string& v)
      {
        return symbol_type (token::GREATER_THAN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESS_THAN (std::string v)
      {
        return symbol_type (token::LESS_THAN, std::move (v));
      }
#else
      static
      symbol_type
      make_LESS_THAN (const std::string& v)
      {
        return symbol_type (token::LESS_THAN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESS_OR_EQUAL_TO (std::string v)
      {
        return symbol_type (token::LESS_OR_EQUAL_TO, std::move (v));
      }
#else
      static
      symbol_type
      make_LESS_OR_EQUAL_TO (const std::string& v)
      {
        return symbol_type (token::LESS_OR_EQUAL_TO, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATER_OR_EQUAL_TO (std::string v)
      {
        return symbol_type (token::GREATER_OR_EQUAL_TO, std::move (v));
      }
#else
      static
      symbol_type
      make_GREATER_OR_EQUAL_TO (const std::string& v)
      {
        return symbol_type (token::GREATER_OR_EQUAL_TO, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT_EQUAL_TO (std::string v)
      {
        return symbol_type (token::NOT_EQUAL_TO, std::move (v));
      }
#else
      static
      symbol_type
      make_NOT_EQUAL_TO (const std::string& v)
      {
        return symbol_type (token::NOT_EQUAL_TO, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IS_OF (std::string v)
      {
        return symbol_type (token::IS_OF, std::move (v));
      }
#else
      static
      symbol_type
      make_IS_OF (const std::string& v)
      {
        return symbol_type (token::IS_OF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND (std::string v)
      {
        return symbol_type (token::AND, std::move (v));
      }
#else
      static
      symbol_type
      make_AND (const std::string& v)
      {
        return symbol_type (token::AND, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR (std::string v)
      {
        return symbol_type (token::OR, std::move (v));
      }
#else
      static
      symbol_type
      make_OR (const std::string& v)
      {
        return symbol_type (token::OR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DELIMITER (std::string v)
      {
        return symbol_type (token::DELIMITER, std::move (v));
      }
#else
      static
      symbol_type
      make_DELIMITER (const std::string& v)
      {
        return symbol_type (token::DELIMITER, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT (std::string v)
      {
        return symbol_type (token::DOT, std::move (v));
      }
#else
      static
      symbol_type
      make_DOT (const std::string& v)
      {
        return symbol_type (token::DOT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (std::string v)
      {
        return symbol_type (token::IF, std::move (v));
      }
#else
      static
      symbol_type
      make_IF (const std::string& v)
      {
        return symbol_type (token::IF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (std::string v)
      {
        return symbol_type (token::ELSE, std::move (v));
      }
#else
      static
      symbol_type
      make_ELSE (const std::string& v)
      {
        return symbol_type (token::ELSE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT (std::string v)
      {
        return symbol_type (token::NOT, std::move (v));
      }
#else
      static
      symbol_type
      make_NOT (const std::string& v)
      {
        return symbol_type (token::NOT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FOR (std::string v)
      {
        return symbol_type (token::FOR, std::move (v));
      }
#else
      static
      symbol_type
      make_FOR (const std::string& v)
      {
        return symbol_type (token::FOR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VOLATILE_TYPE (std::string v)
      {
        return symbol_type (token::VOLATILE_TYPE, std::move (v));
      }
#else
      static
      symbol_type
      make_VOLATILE_TYPE (const std::string& v)
      {
        return symbol_type (token::VOLATILE_TYPE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT (std::string v)
      {
        return symbol_type (token::INT, std::move (v));
      }
#else
      static
      symbol_type
      make_INT (const std::string& v)
      {
        return symbol_type (token::INT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (std::string v)
      {
        return symbol_type (token::FLOAT, std::move (v));
      }
#else
      static
      symbol_type
      make_FLOAT (const std::string& v)
      {
        return symbol_type (token::FLOAT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ID (std::string v)
      {
        return symbol_type (token::ID, std::move (v));
      }
#else
      static
      symbol_type
      make_ID (const std::string& v)
      {
        return symbol_type (token::ID, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOLEAN_TYPE (std::string v)
      {
        return symbol_type (token::BOOLEAN_TYPE, std::move (v));
      }
#else
      static
      symbol_type
      make_BOOLEAN_TYPE (const std::string& v)
      {
        return symbol_type (token::BOOLEAN_TYPE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRUE (std::string v)
      {
        return symbol_type (token::TRUE, std::move (v));
      }
#else
      static
      symbol_type
      make_TRUE (const std::string& v)
      {
        return symbol_type (token::TRUE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FALSE (std::string v)
      {
        return symbol_type (token::FALSE, std::move (v));
      }
#else
      static
      symbol_type
      make_FALSE (const std::string& v)
      {
        return symbol_type (token::FALSE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT_TYPE (std::string v)
      {
        return symbol_type (token::INT_TYPE, std::move (v));
      }
#else
      static
      symbol_type
      make_INT_TYPE (const std::string& v)
      {
        return symbol_type (token::INT_TYPE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT_TYPE (std::string v)
      {
        return symbol_type (token::FLOAT_TYPE, std::move (v));
      }
#else
      static
      symbol_type
      make_FLOAT_TYPE (const std::string& v)
      {
        return symbol_type (token::FLOAT_TYPE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VOID_TYPE (std::string v)
      {
        return symbol_type (token::VOID_TYPE, std::move (v));
      }
#else
      static
      symbol_type
      make_VOID_TYPE (const std::string& v)
      {
        return symbol_type (token::VOID_TYPE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN (std::string v)
      {
        return symbol_type (token::RETURN, std::move (v));
      }
#else
      static
      symbol_type
      make_RETURN (const std::string& v)
      {
        return symbol_type (token::RETURN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PRINT (std::string v)
      {
        return symbol_type (token::PRINT, std::move (v));
      }
#else
      static
      symbol_type
      make_PRINT (const std::string& v)
      {
        return symbol_type (token::PRINT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_READ (std::string v)
      {
        return symbol_type (token::READ, std::move (v));
      }
#else
      static
      symbol_type
      make_READ (const std::string& v)
      {
        return symbol_type (token::READ, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLASS (std::string v)
      {
        return symbol_type (token::CLASS, std::move (v));
      }
#else
      static
      symbol_type
      make_CLASS (const std::string& v)
      {
        return symbol_type (token::CLASS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEN (std::string v)
      {
        return symbol_type (token::LEN, std::move (v));
      }
#else
      static
      symbol_type
      make_LEN (const std::string& v)
      {
        return symbol_type (token::LEN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IFELSE ()
      {
        return symbol_type (token::IFELSE);
      }
#else
      static
      symbol_type
      make_IFELSE ()
      {
        return symbol_type (token::IFELSE);
      }
#endif


    class context
    {
    public:
      context (const parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 650,     ///< Last index in yytable_.
      yynnts_ = 29,  ///< Number of nonterminal symbols.
      yyfinal_ = 34 ///< Termination state number.
    };



  };

  inline
  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
    };
    // Last valid token kind.
    const int code_max = 304;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
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
        value.copy< Node * > (YY_MOVE (that.value));
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
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
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
        value.move< Node * > (YY_MOVE (s.value));
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
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  inline
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


} // yy
#line 2465 "parser.tab.hh"




#endif // !YY_YY_PARSER_TAB_HH_INCLUDED
