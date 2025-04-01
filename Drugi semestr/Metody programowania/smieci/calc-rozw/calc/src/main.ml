open Ast

let parse (s : string) : expr =
    Parser.main Lexer.read (Lexing.from_string s)

let eval_bop (op : bop) (v1 : float) (v2 : float) : float =
    match op with
    | Add -> v1 +. v2
    | Sub -> v1 -. v2
    | Mult -> v1 *. v2
    | Div -> v1 /. v2
    | Pow -> Float.pow v1 v2 (*zmiana *)



let eval_uop (op : uop) (v1 : float) : float = (*zmiana *)
    match op with (*zmiana *)
    | Log -> Float.log v1 (*zmiana *)
    

let rec eval (e : expr) : float =
    match e with
    | Int i -> i
    | Binop (op, e1, e2) -> eval_bop op (eval e1) (eval e2)
    | Unop (op, e1) -> eval_uop op (eval e1) (*zmiana *)

let interp (s : string) : float =
    eval (parse s)

