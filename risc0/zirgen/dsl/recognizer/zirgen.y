// Copyright 2024 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

%token ANGLE_L
%token ANGLE_R
%token BACK
%token BIT_AND
%token COLON
%token COMMA
%token COMPONENT
%token FUNCTION
%token CURLY_L
%token CURLY_R
%token DEFINE
%token DIV
%token DOT
%token ELSE
%token EQUALS
%token FOR
%token GUESS
%token IDENT
%token IF
%token INIT
%token LITERAL
%token MINUS
%token MUX
%token ORDER
%token PAREN_L
%token PAREN_R
%token PLUS
%token RANGE
%token REDUCE
%token SEMICOLON
%token SQUARE_L
%token SQUARE_R
%token TIMES
%token WITH

%nonassoc RANGE MUX BACK
%right REDUCE
%left BIT_AND
%left PLUS MINUS
%left TIMES DIV
%left UMINUS  /*supplies precedence for unary minus */
%left PAREN_L DOT ANGLE_L SQUARE_L

%code top {
  #include <stdio.h>

  int yylex (void);
  void yyerror (char const *);
}

%start module

%%

module
  : /* nothing */
  | module component_def ;

component_def
  : component_kind IDENT opt_type_params PAREN_L opt_params PAREN_R block
  ;

component_kind
  : COMPONENT
  | FUNCTION
  ;

block
   : CURLY_L stmts opt_expr CURLY_R

stmts
   : /* nothing */
   | stmts stmt
   ;

opt_type_params
  : /* nothing */
  | ANGLE_L params ANGLE_R
  ;

opt_params
  : /* nothing */
  | params
  ;

params
  : param
  | params COMMA param
  ;

param
  : IDENT COLON expr
  ;

opt_exprs
   : /* nothing */
   | exprs
   ;

opt_expr
   : /* nothing */
   | expr
   ;

exprs
   : expr
   | exprs COMMA expr
   ;

stmt
  : IDENT DEFINE expr SEMICOLON  // Define a member
  | IDENT COLON expr SEMICOLON // Declare a member (type, no value)
  | expr EQUALS expr SEMICOLON  // Add a constraint
  | expr SEMICOLON  // Ignore expression (often construct a component for constraints)
  ;

expr
  : LITERAL
  | IDENT
  | expr DOT IDENT  // Get element of component
  | expr ANGLE_L exprs ANGLE_R  // Specialize a generic
  | expr SQUARE_L expr SQUARE_R  // Get element of array or construct array type
  | PAREN_L expr PAREN_R
  | SQUARE_L opt_exprs SQUARE_R  // Array constructor
  | expr PAREN_L opt_exprs PAREN_R  // Component constructor
  | block  // Anonymous component
  | FOR IDENT COLON expr block  // For / map
  | REDUCE expr INIT expr WITH reduce_expr %prec REDUCE  // Reduction
  | expr MUX PAREN_L exprs PAREN_R  // Mux / Switch
  | GUESS block
  | IF PAREN_L expr PAREN_R block  // Sugar for if
  | IF PAREN_L expr PAREN_R block ELSE block  // Sugar for if/else
  | expr PLUS expr  // Sugar for 'Add(expr, expr)'
  | expr MINUS expr  // Sugar for 'Sub(expr, expr)'
  | MINUS expr %prec UMINUS  // Sugar for 'Neg(expr)'
  | expr TIMES expr  // Sugar for 'Mul(expr)'
  | expr DIV expr  // Sugar for 'Div(expr)'
  | expr BIT_AND expr  // Sugar for 'And(expr, expr)'
  | expr RANGE expr  // Sugar for 'Range(expr, expr)
  | expr BACK expr  // Back reference
  ;

reduce_expr
  : LITERAL
  | IDENT
  | reduce_expr DOT IDENT
  | reduce_expr ANGLE_L opt_exprs ANGLE_R
  ;
%%

void yyerror (char const *s) {
  fprintf(stderr, "%s\n", s);
}

int main() {
  return yyparse();
}
