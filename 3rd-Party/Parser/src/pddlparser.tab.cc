// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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


// First part of user declarations.

#line 37 "src/pddlparser.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "pddlparser.tab.hh"

// User implementation prologue.

#line 51 "src/pddlparser.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 58 "src/pddlparser.yy" // lalr1.cc:413

#include "pddldriver.hh"

#line 57 "src/pddlparser.tab.cc" // lalr1.cc:413


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

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
      *yycdebug_ << std::endl;                  \
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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 143 "src/pddlparser.tab.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  PDDLParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              // Fall through.
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


  /// Build a parser object.
  PDDLParser::PDDLParser (PDDLDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  PDDLParser::~PDDLParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  PDDLParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  PDDLParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  PDDLParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  PDDLParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  PDDLParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  PDDLParser::symbol_number_type
  PDDLParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  PDDLParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  PDDLParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 34: // "action-def"
      case 68: // action-def
        value.move< Action* > (that.value);
        break;

      case 35: // "action-def-body"
      case 71: // action-def-body
        value.move< ActionDefBody* > (that.value);
        break;

      case 33: // "actions"
      case 67: // actions
        value.move< ActionList* > (that.value);
        break;

      case 27: // "domain-def"
      case 60: // domain-def
        value.move< Domain* > (that.value);
        break;

      case 29: // "domain-body"
      case 62: // domain-body
        value.move< DomainBody* > (that.value);
        break;

      case 41: // "literal"
      case 43: // "grounded-literal"
      case 91: // literal
      case 92: // grounded-literal
        value.move< Literal* > (that.value);
        break;

      case 36: // "preconditions-list"
      case 37: // "effects-list"
      case 38: // "atomic-formula"
      case 42: // "literal-list"
      case 44: // "grounded-literal-list"
      case 45: // "grounded-atomic-formula"
      case 56: // "init-def"
      case 57: // "goal-def"
      case 72: // preconditions-list
      case 73: // effects-list
      case 78: // init-def
      case 79: // goal-def
      case 85: // literal-list
      case 86: // grounded-literal-list
      case 87: // atomic-formula
      case 88: // grounded-atomic-formula
        value.move< LiteralList* > (that.value);
        break;

      case 50: // "parameters-list"
      case 70: // parameters-list
        value.move< ParameterList* > (that.value);
        break;

      case 39: // "predicate"
      case 40: // "grounded-predicate"
      case 89: // predicate
      case 90: // grounded-predicate
        value.move< Predicate* > (that.value);
        break;

      case 48: // "predicates-def"
      case 49: // "predicates-list"
      case 66: // predicates-def
      case 69: // predicates-list
        value.move< PredicateList* > (that.value);
        break;

      case 30: // "problem-def"
      case 74: // problem-def
        value.move< Problem* > (that.value);
        break;

      case 46: // "requirements-def"
      case 47: // "requirekeys-list"
      case 52: // "variables-list"
      case 53: // "names-list"
      case 55: // "objects-def"
      case 63: // requirements-def
      case 77: // objects-def
      case 80: // requirekeys-list
      case 81: // names-list
      case 83: // variables-list
        value.move< StringList* > (that.value);
        break;

      case 51: // "typed-variables-list"
      case 54: // "typed-names-list"
      case 82: // typed-names-list
      case 84: // typed-variables-list
        value.move< TypeDict* > (that.value);
        break;

      case 24: // "number"
        value.move< int > (that.value);
        break;

      case 23: // "name"
      case 25: // "variable"
      case 26: // "requirekey"
      case 28: // "domain-name"
      case 31: // "problem-name"
      case 32: // "domain-reference"
      case 61: // domain-name
      case 75: // problem-name
      case 76: // domain-reference
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  PDDLParser::stack_symbol_type&
  PDDLParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 34: // "action-def"
      case 68: // action-def
        value.copy< Action* > (that.value);
        break;

      case 35: // "action-def-body"
      case 71: // action-def-body
        value.copy< ActionDefBody* > (that.value);
        break;

      case 33: // "actions"
      case 67: // actions
        value.copy< ActionList* > (that.value);
        break;

      case 27: // "domain-def"
      case 60: // domain-def
        value.copy< Domain* > (that.value);
        break;

      case 29: // "domain-body"
      case 62: // domain-body
        value.copy< DomainBody* > (that.value);
        break;

      case 41: // "literal"
      case 43: // "grounded-literal"
      case 91: // literal
      case 92: // grounded-literal
        value.copy< Literal* > (that.value);
        break;

      case 36: // "preconditions-list"
      case 37: // "effects-list"
      case 38: // "atomic-formula"
      case 42: // "literal-list"
      case 44: // "grounded-literal-list"
      case 45: // "grounded-atomic-formula"
      case 56: // "init-def"
      case 57: // "goal-def"
      case 72: // preconditions-list
      case 73: // effects-list
      case 78: // init-def
      case 79: // goal-def
      case 85: // literal-list
      case 86: // grounded-literal-list
      case 87: // atomic-formula
      case 88: // grounded-atomic-formula
        value.copy< LiteralList* > (that.value);
        break;

      case 50: // "parameters-list"
      case 70: // parameters-list
        value.copy< ParameterList* > (that.value);
        break;

      case 39: // "predicate"
      case 40: // "grounded-predicate"
      case 89: // predicate
      case 90: // grounded-predicate
        value.copy< Predicate* > (that.value);
        break;

      case 48: // "predicates-def"
      case 49: // "predicates-list"
      case 66: // predicates-def
      case 69: // predicates-list
        value.copy< PredicateList* > (that.value);
        break;

      case 30: // "problem-def"
      case 74: // problem-def
        value.copy< Problem* > (that.value);
        break;

      case 46: // "requirements-def"
      case 47: // "requirekeys-list"
      case 52: // "variables-list"
      case 53: // "names-list"
      case 55: // "objects-def"
      case 63: // requirements-def
      case 77: // objects-def
      case 80: // requirekeys-list
      case 81: // names-list
      case 83: // variables-list
        value.copy< StringList* > (that.value);
        break;

      case 51: // "typed-variables-list"
      case 54: // "typed-names-list"
      case 82: // typed-names-list
      case 84: // typed-variables-list
        value.copy< TypeDict* > (that.value);
        break;

      case 24: // "number"
        value.copy< int > (that.value);
        break;

      case 23: // "name"
      case 25: // "variable"
      case 26: // "requirekey"
      case 28: // "domain-name"
      case 31: // "problem-name"
      case 32: // "domain-reference"
      case 61: // domain-name
      case 75: // problem-name
      case 76: // domain-reference
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  PDDLParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  PDDLParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 23: // "name"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 532 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 24: // "number"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int > (); }
#line 539 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 25: // "variable"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 546 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 26: // "requirekey"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 553 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 27: // "domain-def"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Domain* > (); }
#line 560 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 28: // "domain-name"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 567 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 29: // "domain-body"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< DomainBody* > (); }
#line 574 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 30: // "problem-def"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Problem* > (); }
#line 581 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 31: // "problem-name"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 588 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 32: // "domain-reference"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 595 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 33: // "actions"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ActionList* > (); }
#line 602 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 34: // "action-def"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Action* > (); }
#line 609 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 35: // "action-def-body"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ActionDefBody* > (); }
#line 616 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 36: // "preconditions-list"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 623 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 37: // "effects-list"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 630 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 38: // "atomic-formula"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 637 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 39: // "predicate"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Predicate* > (); }
#line 644 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 40: // "grounded-predicate"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Predicate* > (); }
#line 651 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 41: // "literal"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Literal* > (); }
#line 658 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 42: // "literal-list"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 665 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 43: // "grounded-literal"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Literal* > (); }
#line 672 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 44: // "grounded-literal-list"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 679 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 45: // "grounded-atomic-formula"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 686 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 46: // "requirements-def"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< StringList* > (); }
#line 693 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 47: // "requirekeys-list"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< StringList* > (); }
#line 700 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 48: // "predicates-def"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< PredicateList* > (); }
#line 707 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 49: // "predicates-list"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< PredicateList* > (); }
#line 714 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 50: // "parameters-list"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ParameterList* > (); }
#line 721 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 51: // "typed-variables-list"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TypeDict* > (); }
#line 728 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 52: // "variables-list"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< StringList* > (); }
#line 735 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 53: // "names-list"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< StringList* > (); }
#line 742 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 54: // "typed-names-list"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TypeDict* > (); }
#line 749 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 55: // "objects-def"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< StringList* > (); }
#line 756 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 56: // "init-def"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 763 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 57: // "goal-def"

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 770 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 60: // domain-def

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Domain* > (); }
#line 777 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 61: // domain-name

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 784 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 62: // domain-body

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< DomainBody* > (); }
#line 791 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 63: // requirements-def

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< StringList* > (); }
#line 798 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 66: // predicates-def

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< PredicateList* > (); }
#line 805 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 67: // actions

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ActionList* > (); }
#line 812 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 68: // action-def

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Action* > (); }
#line 819 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 69: // predicates-list

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< PredicateList* > (); }
#line 826 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 70: // parameters-list

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ParameterList* > (); }
#line 833 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 71: // action-def-body

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< ActionDefBody* > (); }
#line 840 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 72: // preconditions-list

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 847 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 73: // effects-list

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 854 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 74: // problem-def

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Problem* > (); }
#line 861 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 75: // problem-name

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 868 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 76: // domain-reference

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 875 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 77: // objects-def

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< StringList* > (); }
#line 882 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 78: // init-def

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 889 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 79: // goal-def

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 896 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 80: // requirekeys-list

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< StringList* > (); }
#line 903 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 81: // names-list

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< StringList* > (); }
#line 910 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 82: // typed-names-list

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TypeDict* > (); }
#line 917 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 83: // variables-list

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< StringList* > (); }
#line 924 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 84: // typed-variables-list

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< TypeDict* > (); }
#line 931 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 85: // literal-list

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 938 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 86: // grounded-literal-list

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 945 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 87: // atomic-formula

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 952 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 88: // grounded-atomic-formula

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< LiteralList* > (); }
#line 959 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 89: // predicate

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Predicate* > (); }
#line 966 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 90: // grounded-predicate

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Predicate* > (); }
#line 973 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 91: // literal

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Literal* > (); }
#line 980 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;

      case 92: // grounded-literal

#line 136 "src/pddlparser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< Literal* > (); }
#line 987 "src/pddlparser.tab.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  PDDLParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  PDDLParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  PDDLParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  PDDLParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  PDDLParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  PDDLParser::debug_level_type
  PDDLParser::debug_level () const
  {
    return yydebug_;
  }

  void
  PDDLParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline PDDLParser::state_type
  PDDLParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  PDDLParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  PDDLParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  PDDLParser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 49 "src/pddlparser.yy" // lalr1.cc:741
{
// Initialize the initial location.
yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 1106 "src/pddlparser.tab.cc" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

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
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 34: // "action-def"
      case 68: // action-def
        yylhs.value.build< Action* > ();
        break;

      case 35: // "action-def-body"
      case 71: // action-def-body
        yylhs.value.build< ActionDefBody* > ();
        break;

      case 33: // "actions"
      case 67: // actions
        yylhs.value.build< ActionList* > ();
        break;

      case 27: // "domain-def"
      case 60: // domain-def
        yylhs.value.build< Domain* > ();
        break;

      case 29: // "domain-body"
      case 62: // domain-body
        yylhs.value.build< DomainBody* > ();
        break;

      case 41: // "literal"
      case 43: // "grounded-literal"
      case 91: // literal
      case 92: // grounded-literal
        yylhs.value.build< Literal* > ();
        break;

      case 36: // "preconditions-list"
      case 37: // "effects-list"
      case 38: // "atomic-formula"
      case 42: // "literal-list"
      case 44: // "grounded-literal-list"
      case 45: // "grounded-atomic-formula"
      case 56: // "init-def"
      case 57: // "goal-def"
      case 72: // preconditions-list
      case 73: // effects-list
      case 78: // init-def
      case 79: // goal-def
      case 85: // literal-list
      case 86: // grounded-literal-list
      case 87: // atomic-formula
      case 88: // grounded-atomic-formula
        yylhs.value.build< LiteralList* > ();
        break;

      case 50: // "parameters-list"
      case 70: // parameters-list
        yylhs.value.build< ParameterList* > ();
        break;

      case 39: // "predicate"
      case 40: // "grounded-predicate"
      case 89: // predicate
      case 90: // grounded-predicate
        yylhs.value.build< Predicate* > ();
        break;

      case 48: // "predicates-def"
      case 49: // "predicates-list"
      case 66: // predicates-def
      case 69: // predicates-list
        yylhs.value.build< PredicateList* > ();
        break;

      case 30: // "problem-def"
      case 74: // problem-def
        yylhs.value.build< Problem* > ();
        break;

      case 46: // "requirements-def"
      case 47: // "requirekeys-list"
      case 52: // "variables-list"
      case 53: // "names-list"
      case 55: // "objects-def"
      case 63: // requirements-def
      case 77: // objects-def
      case 80: // requirekeys-list
      case 81: // names-list
      case 83: // variables-list
        yylhs.value.build< StringList* > ();
        break;

      case 51: // "typed-variables-list"
      case 54: // "typed-names-list"
      case 82: // typed-names-list
      case 84: // typed-variables-list
        yylhs.value.build< TypeDict* > ();
        break;

      case 24: // "number"
        yylhs.value.build< int > ();
        break;

      case 23: // "name"
      case 25: // "variable"
      case 26: // "requirekey"
      case 28: // "domain-name"
      case 31: // "problem-name"
      case 32: // "domain-reference"
      case 61: // domain-name
      case 75: // problem-name
      case 76: // domain-reference
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 145 "src/pddlparser.yy" // lalr1.cc:859
    { driver.domain  = yystack_[0].value.as< Domain* > (); }
#line 1327 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 146 "src/pddlparser.yy" // lalr1.cc:859
    { driver.problem = yystack_[0].value.as< Problem* > (); }
#line 1333 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 150 "src/pddlparser.yy" // lalr1.cc:859
    {
        yylhs.value.as< Domain* > () = new Domain(yystack_[2].value.as< std::string > ());
        yylhs.value.as< Domain* > ()->set_requirements(yystack_[1].value.as< DomainBody* > ()->requirements);
        yylhs.value.as< Domain* > ()->set_predicates(yystack_[1].value.as< DomainBody* > ()->predicates);
        yylhs.value.as< Domain* > ()->set_actions(yystack_[1].value.as< DomainBody* > ()->actions);
        delete yystack_[1].value.as< DomainBody* > ();
    }
#line 1345 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 158 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[1].value.as< std::string > (); }
#line 1351 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 161 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< DomainBody* > () = new DomainBody{yystack_[2].value.as< StringList* > (), yystack_[1].value.as< PredicateList* > (), yystack_[0].value.as< ActionList* > ()}; }
#line 1357 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 162 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< DomainBody* > () = new DomainBody{yystack_[3].value.as< StringList* > (), yystack_[1].value.as< PredicateList* > (), yystack_[0].value.as< ActionList* > ()}; }
#line 1363 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 163 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< DomainBody* > () = new DomainBody{yystack_[3].value.as< StringList* > (), yystack_[1].value.as< PredicateList* > (), yystack_[0].value.as< ActionList* > ()}; }
#line 1369 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 164 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< DomainBody* > () = new DomainBody{yystack_[4].value.as< StringList* > (), yystack_[1].value.as< PredicateList* > (), yystack_[0].value.as< ActionList* > ()}; }
#line 1375 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 167 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< StringList* > () = yystack_[1].value.as< StringList* > (); }
#line 1381 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 170 "src/pddlparser.yy" // lalr1.cc:859
    {}
#line 1387 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 171 "src/pddlparser.yy" // lalr1.cc:859
    {}
#line 1393 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 175 "src/pddlparser.yy" // lalr1.cc:859
    {}
#line 1399 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 176 "src/pddlparser.yy" // lalr1.cc:859
    {}
#line 1405 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 179 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< PredicateList* > () = yystack_[1].value.as< PredicateList* > (); }
#line 1411 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 182 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< ActionList* > () = new ActionList; yylhs.value.as< ActionList* > ()->push_back(yystack_[0].value.as< Action* > ()); }
#line 1417 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 183 "src/pddlparser.yy" // lalr1.cc:859
    { yystack_[1].value.as< ActionList* > ()->push_back(yystack_[0].value.as< Action* > ()); yylhs.value.as< ActionList* > () = yystack_[1].value.as< ActionList* > (); }
#line 1423 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 187 "src/pddlparser.yy" // lalr1.cc:859
    {
        yylhs.value.as< Action* > () = new Action(yystack_[3].value.as< std::string > (), yystack_[2].value.as< ParameterList* > (), yystack_[1].value.as< ActionDefBody* > ()->first, yystack_[1].value.as< ActionDefBody* > ()->second);
        delete yystack_[1].value.as< ActionDefBody* > ();
    }
#line 1432 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 193 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< PredicateList* > () = new PredicateList; yylhs.value.as< PredicateList* > ()->push_back(yystack_[0].value.as< Predicate* > ()); }
#line 1438 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 194 "src/pddlparser.yy" // lalr1.cc:859
    { yystack_[1].value.as< PredicateList* > ()->push_back(yystack_[0].value.as< Predicate* > ()); yylhs.value.as< PredicateList* > () = yystack_[1].value.as< PredicateList* > ();}
#line 1444 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 199 "src/pddlparser.yy" // lalr1.cc:859
    {
            StringList *parameters = new StringList();
            for (const auto& param : *yystack_[1].value.as< TypeDict* > ()) {
                parameters->push_back(param.first);
            }
            yylhs.value.as< ParameterList* > () = new ParameterList(parameters, yystack_[1].value.as< TypeDict* > ());
        }
#line 1456 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 207 "src/pddlparser.yy" // lalr1.cc:859
    {
            yylhs.value.as< ParameterList* > () = new ParameterList(yystack_[1].value.as< StringList* > (), nullptr);
        }
#line 1464 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 211 "src/pddlparser.yy" // lalr1.cc:859
    {
            yylhs.value.as< ParameterList* > () = new ParameterList(nullptr, nullptr);
        }
#line 1472 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 217 "src/pddlparser.yy" // lalr1.cc:859
    {
        yylhs.value.as< ActionDefBody* > () = new ActionDefBody(yystack_[1].value.as< LiteralList* > (), yystack_[0].value.as< LiteralList* > ());
    }
#line 1480 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 221 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< LiteralList* > () = yystack_[0].value.as< LiteralList* > (); }
#line 1486 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 223 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< LiteralList* > () = yystack_[0].value.as< LiteralList* > (); }
#line 1492 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 226 "src/pddlparser.yy" // lalr1.cc:859
    {
        yylhs.value.as< Problem* > () = new Problem(yystack_[5].value.as< std::string > (), yystack_[4].value.as< std::string > ());
        yylhs.value.as< Problem* > ()->set_objects(yystack_[3].value.as< StringList* > ());
        yylhs.value.as< Problem* > ()->set_init_state(yystack_[2].value.as< LiteralList* > ());
        yylhs.value.as< Problem* > ()->set_goal_state(yystack_[1].value.as< LiteralList* > ());
    }
#line 1503 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 233 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[1].value.as< std::string > (); }
#line 1509 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 235 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[1].value.as< std::string > (); }
#line 1515 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 237 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< StringList* > () = yystack_[1].value.as< StringList* > (); }
#line 1521 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 239 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< LiteralList* > () = yystack_[1].value.as< LiteralList* > (); }
#line 1527 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 241 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< LiteralList* > () = yystack_[1].value.as< LiteralList* > (); }
#line 1533 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 244 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< StringList* > () = new StringList; yylhs.value.as< StringList* > ()->push_back(yystack_[0].value.as< std::string > ()); }
#line 1539 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 245 "src/pddlparser.yy" // lalr1.cc:859
    { yystack_[1].value.as< StringList* > ()->push_back(yystack_[0].value.as< std::string > ()); yylhs.value.as< StringList* > () = yystack_[1].value.as< StringList* > (); }
#line 1545 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 249 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< StringList* > () = new StringList; yylhs.value.as< StringList* > ()->push_back(yystack_[0].value.as< std::string > ()); }
#line 1551 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 250 "src/pddlparser.yy" // lalr1.cc:859
    { yystack_[1].value.as< StringList* > ()->push_back(yystack_[0].value.as< std::string > ()); yylhs.value.as< StringList* > () = yystack_[1].value.as< StringList* > (); }
#line 1557 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 37:
#line 254 "src/pddlparser.yy" // lalr1.cc:859
    {}
#line 1563 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 38:
#line 255 "src/pddlparser.yy" // lalr1.cc:859
    {}
#line 1569 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 39:
#line 259 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< StringList* > () = new StringList; yylhs.value.as< StringList* > ()->push_back(yystack_[0].value.as< std::string > ()); }
#line 1575 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 260 "src/pddlparser.yy" // lalr1.cc:859
    { yystack_[1].value.as< StringList* > ()->push_back(yystack_[0].value.as< std::string > ()); yylhs.value.as< StringList* > () = yystack_[1].value.as< StringList* > (); }
#line 1581 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 265 "src/pddlparser.yy" // lalr1.cc:859
    {
            std::string type(yystack_[0].value.as< std::string > ());
            yylhs.value.as< TypeDict* > () = new TypeDict;
            for (const auto& var : *yystack_[2].value.as< StringList* > ()) {
                (*yylhs.value.as< TypeDict* > ())[var] = type;
            }
        }
#line 1593 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 273 "src/pddlparser.yy" // lalr1.cc:859
    {
            std::string type(yystack_[0].value.as< std::string > ());
            for (const auto& var : *yystack_[2].value.as< StringList* > ()) {
                (*yystack_[3].value.as< TypeDict* > ())[var] = type;
            }
            yylhs.value.as< TypeDict* > () = yystack_[3].value.as< TypeDict* > ();
        }
#line 1605 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 283 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< LiteralList* > () = new LiteralList; yylhs.value.as< LiteralList* > ()->push_back(yystack_[0].value.as< Literal* > ()); }
#line 1611 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 284 "src/pddlparser.yy" // lalr1.cc:859
    { yystack_[1].value.as< LiteralList* > ()->push_back(yystack_[0].value.as< Literal* > ()); yylhs.value.as< LiteralList* > () = yystack_[1].value.as< LiteralList* > (); }
#line 1617 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 288 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< LiteralList* > () = new LiteralList; yylhs.value.as< LiteralList* > ()->push_back(yystack_[0].value.as< Literal* > ()); }
#line 1623 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 289 "src/pddlparser.yy" // lalr1.cc:859
    { yystack_[1].value.as< LiteralList* > ()->push_back(yystack_[0].value.as< Literal* > ()); yylhs.value.as< LiteralList* > () = yystack_[1].value.as< LiteralList* > (); }
#line 1629 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 293 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< LiteralList* > () = new LiteralList; yylhs.value.as< LiteralList* > ()->push_back(yystack_[0].value.as< Literal* > ()); }
#line 1635 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 294 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< LiteralList* > () = yystack_[1].value.as< LiteralList* > (); }
#line 1641 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 298 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< LiteralList* > () = new LiteralList; yylhs.value.as< LiteralList* > ()->push_back(yystack_[0].value.as< Literal* > ()); }
#line 1647 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 299 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< LiteralList* > () = yystack_[1].value.as< LiteralList* > (); }
#line 1653 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 304 "src/pddlparser.yy" // lalr1.cc:859
    {
            StringList *vars = new StringList;
            for (const auto& var : *yystack_[1].value.as< TypeDict* > ()) {
                vars->push_back(var.first);
            }
            auto args = new ArgumentList(vars, yystack_[1].value.as< TypeDict* > ());
            yylhs.value.as< Predicate* > () = new Predicate(yystack_[2].value.as< std::string > (), args);
        }
#line 1666 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 313 "src/pddlparser.yy" // lalr1.cc:859
    {
            auto args = new ArgumentList(yystack_[1].value.as< StringList* > (), nullptr);
            yylhs.value.as< Predicate* > () = new Predicate(yystack_[2].value.as< std::string > (), args);
        }
#line 1675 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 318 "src/pddlparser.yy" // lalr1.cc:859
    {
            StringList *vars = new StringList(2);
            (*vars)[0] = yystack_[2].value.as< std::string > ();
            (*vars)[1] = yystack_[1].value.as< std::string > ();
            auto args = new ArgumentList(vars, nullptr);
            yylhs.value.as< Predicate* > () = new Predicate("=", args);
        }
#line 1687 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 329 "src/pddlparser.yy" // lalr1.cc:859
    {
            auto args = new ArgumentList(yystack_[1].value.as< StringList* > (), nullptr);
            yylhs.value.as< Predicate* > () = new Predicate(yystack_[2].value.as< std::string > (), args);
        }
#line 1696 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 334 "src/pddlparser.yy" // lalr1.cc:859
    {
            StringList *vars = new StringList(2);
            (*vars)[0] = yystack_[2].value.as< std::string > ();
            (*vars)[1] = yystack_[1].value.as< std::string > ();
            auto args = new ArgumentList(vars, nullptr);
            yylhs.value.as< Predicate* > () = new Predicate("=", args);
        }
#line 1708 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 344 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< Literal* > () = new Literal(yystack_[0].value.as< Predicate* > (), true); }
#line 1714 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 345 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< Literal* > () = new Literal(yystack_[1].value.as< Predicate* > (), false); }
#line 1720 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 349 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< Literal* > () = new Literal(yystack_[0].value.as< Predicate* > (), true); }
#line 1726 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 350 "src/pddlparser.yy" // lalr1.cc:859
    { yylhs.value.as< Literal* > () = new Literal(yystack_[1].value.as< Predicate* > (), false); }
#line 1732 "src/pddlparser.tab.cc" // lalr1.cc:859
    break;


#line 1736 "src/pddlparser.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  PDDLParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  PDDLParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

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
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char PDDLParser::yypact_ninf_ = -127;

  const signed char PDDLParser::yytable_ninf_ = -1;

  const short int
  PDDLParser::yypact_[] =
  {
      21,    55,    76,  -127,  -127,    64,  -127,    74,    73,    75,
      51,    77,    88,    78,    81,    92,    82,    83,    84,    80,
    -127,    53,    89,    90,    91,    85,    86,    93,  -127,  -127,
    -127,     5,    94,    94,    95,    72,    90,    91,   103,    91,
      87,    91,  -127,    97,    94,    96,    99,  -127,  -127,  -127,
      42,    31,    46,    49,    -8,    62,  -127,    91,    91,    91,
      98,  -127,  -127,    50,   100,    79,   101,  -127,   102,  -127,
    -127,    63,  -127,  -127,   104,   105,  -127,  -127,    91,   112,
    -127,    17,    67,  -127,  -127,   106,  -127,  -127,   108,   107,
    -127,    23,    13,   113,   115,   114,   116,    94,  -127,  -127,
       2,   117,  -127,  -127,   119,  -127,   118,  -127,  -127,    34,
      28,   122,   123,   111,    -4,   124,   120,    54,   100,  -127,
    -127,  -127,   125,  -127,    25,    30,    14,  -127,  -127,  -127,
    -127,   122,  -127,  -127,   126,  -127,    69,  -127,  -127,  -127,
     129,    95,  -127,  -127,  -127,    20,    71,  -127,   130,  -127,
    -127,  -127
  };

  const unsigned char
  PDDLParser::yydefact_[] =
  {
       0,     0,     0,     2,     3,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       4,     0,     0,     0,     0,     0,     0,     0,     5,    28,
      33,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,    16,     0,     0,     0,     0,    10,    34,    35,
       0,     0,     0,     0,     0,     0,    19,     0,     8,     7,
       0,    17,    29,     0,     0,     0,     0,    11,     0,    36,
      12,     0,    13,    14,     0,     0,    15,    20,     9,     0,
      30,     0,     0,    58,    45,     0,    27,    37,     0,     0,
      39,     0,     0,     0,     0,     0,     0,     0,    31,    46,
       0,     0,    49,    38,     0,    52,     0,    40,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
      53,    41,     0,    23,     0,     0,     0,    25,    56,    47,
      18,     0,    24,    59,     0,    54,     0,    42,    22,    21,
       0,     0,    26,    55,    50,     0,     0,    43,     0,    48,
      44,    57
  };

  const short int
  PDDLParser::yypgoto_[] =
  {
    -127,  -127,  -127,  -127,  -127,  -127,  -127,   128,   -12,   -30,
     -36,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,   -31,   121,   -71,     6,  -127,    10,     4,
    -127,   -34,    41,  -126,   -79
  };

  const short int
  PDDLParser::yydefgoto_[] =
  {
      -1,     2,     3,     8,    13,    14,    22,    23,    24,    41,
      42,    55,    94,   112,   113,   132,     4,     9,    16,    27,
      46,    66,    31,    71,    51,   109,    92,   146,    82,   127,
     101,   128,    83,   129,    84
  };

  const unsigned char
  PDDLParser::yytable_[] =
  {
      56,    50,    52,    99,    91,    61,   102,    58,    74,    59,
      37,    39,    96,    63,   147,    75,   118,    95,    96,    97,
     150,    77,    61,    61,    57,    97,    47,    78,   140,   141,
      74,    48,    95,    96,   108,   141,    74,    75,    90,   124,
      97,     1,    61,    75,   105,   106,   138,   106,   107,   123,
     107,   139,    70,    90,    49,    90,   122,    99,     5,   107,
      32,    33,    34,    67,    68,    69,   117,    72,    68,    69,
      73,    80,    49,    69,    17,   135,     6,    69,    10,    11,
      33,    34,    54,    76,     7,    88,    69,    81,    98,    81,
     144,   145,   149,    12,    19,    15,    25,    60,    85,    20,
      18,    21,    26,    44,    28,    29,    30,   148,    43,    35,
      38,    40,    34,    45,    64,    54,   125,    49,    62,    65,
      81,    79,    86,    93,   131,    87,   100,   111,   136,    89,
      90,   103,   104,   110,   114,   142,   115,     0,   119,   116,
     120,   121,   126,   134,   130,   133,     0,   143,   137,   145,
      36,   151,     0,     0,    53
  };

  const short int
  PDDLParser::yycheck_[] =
  {
      34,    32,    33,    82,    75,    41,    85,    37,    16,    39,
      22,    23,    16,    44,   140,    23,    14,    15,    16,    23,
     146,    55,    58,    59,    36,    23,    21,    57,    14,    15,
      16,    26,    15,    16,    21,    15,    16,    23,    25,   110,
      23,    20,    78,    23,    21,    22,    21,    22,    25,    21,
      25,    21,    21,    25,    23,    25,    22,   136,     3,    25,
       7,     8,     9,    21,    22,    23,    97,    21,    22,    23,
      21,    21,    23,    23,    23,    21,     0,    23,     4,     5,
       8,     9,    20,    21,    20,    22,    23,    20,    21,    20,
      21,    20,    21,    20,     6,    20,     4,    10,    19,    21,
      23,    20,    20,    17,    21,    21,    26,   141,    23,    20,
      20,    20,     9,    20,    18,    20,   110,    23,    21,    20,
      20,    23,    21,    11,    13,    23,    20,    12,   118,    25,
      25,    23,    25,    20,    20,   131,    95,    -1,    21,    23,
      21,    23,    20,    23,    21,    21,    -1,    21,    23,    20,
      22,    21,    -1,    -1,    33
  };

  const unsigned char
  PDDLParser::yystos_[] =
  {
       0,    20,    59,    60,    74,     3,     0,    20,    61,    75,
       4,     5,    20,    62,    63,    20,    76,    23,    23,     6,
      21,    20,    64,    65,    66,     4,    20,    77,    21,    21,
      26,    80,     7,     8,     9,    20,    65,    66,    20,    66,
      20,    67,    68,    23,    17,    20,    78,    21,    26,    23,
      81,    82,    81,    82,    20,    69,    89,    66,    67,    67,
      10,    68,    21,    81,    18,    20,    79,    21,    22,    23,
      21,    81,    21,    21,    16,    23,    21,    89,    67,    23,
      21,    20,    86,    90,    92,    19,    21,    23,    22,    25,
      25,    83,    84,    11,    70,    15,    16,    23,    21,    92,
      20,    88,    92,    23,    25,    21,    22,    25,    21,    83,
      20,    12,    71,    72,    20,    90,    23,    81,    14,    21,
      21,    23,    22,    21,    83,    84,    20,    87,    89,    91,
      21,    13,    73,    21,    23,    21,    86,    23,    21,    21,
      14,    15,    87,    21,    21,    20,    85,    91,    89,    21,
      91,    21
  };

  const unsigned char
  PDDLParser::yyr1_[] =
  {
       0,    58,    59,    59,    60,    61,    62,    62,    62,    62,
      63,    64,    64,    65,    65,    66,    67,    67,    68,    69,
      69,    70,    70,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    80,    81,    81,    82,    82,    83,
      83,    84,    84,    85,    85,    86,    86,    87,    87,    88,
      88,    89,    89,    89,    90,    90,    91,    91,    92,    92
  };

  const unsigned char
  PDDLParser::yyr2_[] =
  {
       0,     2,     1,     1,     5,     4,     3,     4,     4,     5,
       4,     4,     4,     4,     4,     4,     1,     2,     6,     1,
       2,     4,     4,     3,     2,     2,     2,     8,     4,     4,
       4,     4,     4,     1,     2,     1,     2,     3,     4,     1,
       2,     3,     4,     1,     2,     1,     2,     1,     4,     1,
       4,     4,     4,     5,     4,     5,     1,     4,     1,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const PDDLParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"define\"", "\"domain\"",
  "\"problem\"", "\"requirements\"", "\"types\"", "\"constants\"",
  "\"predicates\"", "\"action\"", "\"parameters\"", "\"preconditions\"",
  "\"effects\"", "\"and\"", "\"not\"", "\"=\"", "\"objects\"", "\"init\"",
  "\"goal\"", "\"(\"", "\")\"", "\"-\"", "\"name\"", "\"number\"",
  "\"variable\"", "\"requirekey\"", "\"domain-def\"", "\"domain-name\"",
  "\"domain-body\"", "\"problem-def\"", "\"problem-name\"",
  "\"domain-reference\"", "\"actions\"", "\"action-def\"",
  "\"action-def-body\"", "\"preconditions-list\"", "\"effects-list\"",
  "\"atomic-formula\"", "\"predicate\"", "\"grounded-predicate\"",
  "\"literal\"", "\"literal-list\"", "\"grounded-literal\"",
  "\"grounded-literal-list\"", "\"grounded-atomic-formula\"",
  "\"requirements-def\"", "\"requirekeys-list\"", "\"predicates-def\"",
  "\"predicates-list\"", "\"parameters-list\"", "\"typed-variables-list\"",
  "\"variables-list\"", "\"names-list\"", "\"typed-names-list\"",
  "\"objects-def\"", "\"init-def\"", "\"goal-def\"", "$accept", "pddl",
  "domain-def", "domain-name", "domain-body", "requirements-def", "types",
  "constants", "predicates-def", "actions", "action-def",
  "predicates-list", "parameters-list", "action-def-body",
  "preconditions-list", "effects-list", "problem-def", "problem-name",
  "domain-reference", "objects-def", "init-def", "goal-def",
  "requirekeys-list", "names-list", "typed-names-list", "variables-list",
  "typed-variables-list", "literal-list", "grounded-literal-list",
  "atomic-formula", "grounded-atomic-formula", "predicate",
  "grounded-predicate", "literal", "grounded-literal", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  PDDLParser::yyrline_[] =
  {
       0,   145,   145,   146,   149,   158,   161,   162,   163,   164,
     167,   170,   171,   175,   176,   179,   182,   183,   186,   193,
     194,   198,   206,   210,   216,   221,   223,   225,   233,   235,
     237,   239,   241,   244,   245,   249,   250,   254,   255,   259,
     260,   264,   272,   283,   284,   288,   289,   293,   294,   298,
     299,   303,   312,   317,   328,   333,   344,   345,   349,   350
  };

  // Print the state stack on the debug stream.
  void
  PDDLParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  PDDLParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 2218 "src/pddlparser.tab.cc" // lalr1.cc:1167
#line 354 "src/pddlparser.yy" // lalr1.cc:1168



void
yy::PDDLParser::error (const location_type& l, const std::string& m)
{
    driver.error (l, m);
}
