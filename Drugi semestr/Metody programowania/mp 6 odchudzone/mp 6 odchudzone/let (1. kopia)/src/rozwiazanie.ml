let closed (e : expr) : bool =
let member xs y = List.fold_left (fun acc x -> acc || x = y ) false xs in
let rec closed2 e xs = 
match e with
| Binop (op, e1, e2) -> (closed2 e1 xs) && (closed2 e2 xs)
| If (b,t,e) -> (closed2 b xs) && (closed2 t xs) && (closed2 e xs)
| Var y -> member xs y
| Let (y, e1, e2) -> (closed2 e1 xs) && (closed2 e2 (y::xs))
| (Int _|Bool _) -> true
in closed2 e [];;
