%{
open Ast
%}

%token <bool> BOOL
%token <int> INT
%token <string> IDENT
%token IF
%token THEN
%token ELSE
%token LET
%token IN
%token PLUS
%token MINUS
%token TIMES
%token DIV
%token AND
%token OR
%token EQ
%token LEQ
%token LPAREN
%token RPAREN
%token EOF
%token COMMA
%token UNIT
%token FST
%token SND
%token MATCH
%token WITH
%token ARR
%token PAIRCH
%token BOOLEANCH
%token NUMBERCH
%token UNITCH
%token LSQUARE
%token RSQUARE
%token SEMICOLON
%token FOLD
%token FAND

%start <Ast.expr> main

%left AND OR
%nonassoc EQ LEQ
%left PLUS MINUS
%left TIMES DIV
%left PAIRCH BOOLEANCH NUMBERCH UNITCH

%%

main:
    | e = mexpr; EOF { e }
    ;

mexpr:
    | IF; e1 = mexpr; THEN; e2 = mexpr; ELSE; e3 = mexpr
        { If(e1, e2, e3) }
    | LET; x = IDENT; EQ; e1 = mexpr; IN; e2 = mexpr
        { Let(x, e1, e2) }
    | MATCH; e1 = mexpr; WITH; LPAREN; x = IDENT; COMMA; y = IDENT; RPAREN; ARR; e2 = mexpr
        { Match(e1, x, y, e2) }
    | e = expr
        { e }
    ;

list:
    | e1 = mexpr; SEMICOLON; l1 = list { Pair(e1,l1) }
    | e1 = mexpr { Pair(e1,Unit) }

   ;
   

expr:
    | i = INT { Int i }
    | b = BOOL { Bool b }
    | x = IDENT { Var x }
    | e1 = expr; PLUS; e2 = expr { Binop(Add, e1, e2) }
    | e1 = expr; MINUS; e2 = expr { Binop(Sub, e1, e2) }
    | e1 = expr; DIV; e2 = expr { Binop(Div, e1, e2) }
    | e1 = expr; TIMES; e2 = expr { Binop(Mult, e1, e2) }
    | e1 = expr; AND; e2 = expr { Binop(And, e1, e2) }
    | e1 = expr; OR; e2 = expr { Binop(Or, e1, e2) }
    | e1 = expr; EQ; e2 = expr { Binop(Eq, e1, e2) }
    | e1 = expr; LEQ; e2 = expr { Binop(Leq, e1, e2) }
    | LPAREN; e1 = mexpr; COMMA; e2 = mexpr; RPAREN { Pair (e1,e2) }
    | UNIT { Unit }
    | FST; e = expr { Fst e }
    | SND; e = expr { Snd e }
    | PAIRCH; e = expr { Check(Pai, e) }
    | BOOLEANCH; e = expr { Check(Boo, e) }
    | NUMBERCH; e = expr { Check(Num, e) }
    | UNITCH; e = expr { Check(Uni, e) }
    | LPAREN; e = mexpr; RPAREN { e }
    | LSQUARE; RSQUARE { Unit }
    | LSQUARE; e = list; RSQUARE { e }
    | FOLD; e1 = expr; WITH; LPAREN; x = IDENT; COMMA; acc = IDENT; RPAREN; ARR; e2 = expr; FAND; e3 = expr { Fold(e1,x,acc,e2,e3) } 
    ;


