type bop = Add | Sub | Mult | Div | Pow (*zmiana *)
type uop =  Log (*zmiana *)

type expr = 
    | Int of float (*zmiana *)
    | Binop of bop * expr * expr
    | Unop of uop * expr (*zmiana *)
