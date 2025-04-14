let prog = "with (x,xs) -> (fold xs with (p,q) -> (p,q) and [x])  and []"

let prog_of_list ( xs : int list ) : string = List . fold_right
( fun x s -> " ( " ^ string_of_int x ^ " ," ^ s ^ " ) " )
xs " () "
let rec list_of_val ( v : value ) : int list =
match v with
| VPair ( VInt n , vs ) -> n :: list_of_val vs
| VUnit -> []
| _ -> failwith " error "
let reverse ( xs : int list ) : int list =
( " fold " ^ prog_of_list xs ^ prog ) |> interp |> list_of_val

