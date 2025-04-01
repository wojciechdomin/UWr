{
open Parser
}

let white = [' ' '\t']+
let digit = ['0'-'9']
let number = ('-'? digit+ '.'? digit*) | 'e' (*zmiana *)

rule read =
    parse
    | white { read lexbuf }
    | "*" { TIMES }
    | "+" { PLUS }
    | "-" { MINUS }
    | "/" { DIV }
    | "(" { LPAREN }
    | ")" { RPAREN }
    | "**" { POWER } (*zmiana *)
    | "log" { LOG } (*zmiana *)
    | number { INT ( let s = Lexing.lexeme lexbuf in if s = "e" then 2.71828182846 else float_of_string (s)) } (*zmiana *)
    | eof { EOF }
