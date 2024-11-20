/*
Copyright 2024 RISC Zero, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

%{
    #include <stdio.h>
    #include "zirgen.tab.h"
    extern int yylval;
%}

%x block_comment
%%

component               { return COMPONENT; }
function                { return FUNCTION; }
else                    { return ELSE; }
guess                   { return GUESS; }
for                     { return FOR; }
if                      { return IF; }
init                    { return INIT; }
order                   { return ORDER; }
reduce                  { return REDUCE; }
with                    { return WITH; }
[<]                     { return ANGLE_L; }
[>]                     { return ANGLE_R; }
[@]                     { return BACK; }
[&]                     { return BIT_AND; }
[:]                     { return COLON; }
[,]                     { return COMMA; }
\{                      { return CURLY_L; }
\}                      { return CURLY_R; }
:=                      { return DEFINE; }
\/                      { return DIV; }
\.                      { return DOT; }
=                       { return EQUALS; }
-                       { return MINUS; }
-\>                     { return MUX; }
\(                      { return PAREN_L; }
\)                      { return PAREN_R; }
\+                      { return PLUS; }
\.\.                    { return RANGE; }
\;                      { return SEMICOLON; }
\[                      { return SQUARE_L; }
\]                      { return SQUARE_R; }
\*                      { return TIMES; }
[0-9]+                  { printf("literal: %s\n", yytext); return LITERAL; }
[a-zA-Z][a-zA-Z0-9_]*   { printf("identifier: %s\n", yytext); return IDENT; }
\/\/.*$ ;
\/\*                    { printf("block comment\n"); BEGIN(block_comment); }
<block_comment>[^*]* ;
<block_comment>\*+[^*/]* ;
<block_comment>\*+\/     { printf("end block comment\n"); BEGIN(INITIAL); }
[ \t\n] ;

%%

int yywrap(void) { return 1; }
