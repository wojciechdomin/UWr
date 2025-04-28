let rec deBru e xs = let rec find x xs = match xs with | y :: ys -> if x = fst y then string_of_int (snd y) else find x ys | [] -> x in match e with 
| Binop(op, e1, e2) -> Binop(op, deBru e1 xs, deBru e2 xs)
| If(b,t,e) -> If(deBru b xs, deBru t xs, deBru e xs)
| Var x -> Var (find x xs)
| Let(x,e1,e2) -> let l = List.length xs in let nxs = (x,l) :: xs in Let(string_of_int l,deBru e1 xs, deBru e2 nxs)
| (Int _ | Bool _) -> e;; 

let alpha_equiv e1 e2 = 
(deBru e1 []) = (deBru e2 []);;