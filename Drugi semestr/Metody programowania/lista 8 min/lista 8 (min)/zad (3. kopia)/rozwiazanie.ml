let rec deBru e xs c = let rec find x xs = match xs with | y :: ys -> if x = fst y then "#"^string_of_int (snd y) else find x ys | [] -> x in match e with 
| Binop(op, e1, e2) -> let (u1, c1) = deBru e1 xs c in let (u2, c2) = deBru e2 xs c1 in (Binop(op, u1, u2),c2)
| If(b,t,e) -> let (u1, c1) = deBru b xs c in let (u2, c2) = deBru t xs c1 in let (u3, c3) = deBru t xs c2 in (If(u1,u2,u3),c3)
| Var x -> (Var (find x xs),c)
| Let(x,e1,e2) ->  let nxs = (x,c) :: xs in let (u1,c1) = deBru e1 xs (c+1) in let (u2,c2) = deBru e2 nxs c1 in (Let("#"^string_of_int c,u1,u2),c2)
| (Int _ | Bool _) -> (e,c);;

let rename_expr (e:expr) : expr = deBru e [] 0 |> fst;;
