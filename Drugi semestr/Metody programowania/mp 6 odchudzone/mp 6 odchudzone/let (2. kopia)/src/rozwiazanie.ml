type expr = 
  | Int   of int
  | Binop of bop * expr * expr
  | Bool  of bool
  | If    of expr * expr * expr
  | Let   of ident * expr * expr
  | Var   of ident
  | For   of ident * int * int * expr
  | Integ of ident * int * int * expr 
(*w pliku ast.ml*)