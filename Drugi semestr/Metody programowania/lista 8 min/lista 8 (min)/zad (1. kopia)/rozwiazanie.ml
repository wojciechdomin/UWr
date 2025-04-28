module M  = Map.Make(String);;
type env = expr M.t;;

let cp (e:expr) : expr = 
let rec cp2 (e:expr) (env:env) : expr =
match e with
| Binop(Add, e1, e2) -> (let u1 = cp2 e1 env and u2 = cp2 e2 env in match (u1,u2) 
	with | Int a, Int b -> Int (a+b) | _,_ -> Binop(Add,u1,u2) )
| Binop(Sub, e1, e2) -> (let u1 = cp2 e1 env and u2 = cp2 e2 env in match (u1,u2) 
	with | Int a, Int b -> Int (a-b) | _,_ -> Binop(Sub,u1,u2) )
| Binop(Mult, e1, e2) -> (let u1 = cp2 e1 env and u2 = cp2 e2 env in match (u1,u2) 
	with | Int a, Int b -> Int (a*b) | _,_ -> Binop(Mult,u1,u2) )
| Binop(Div, e1, e2) -> (let u1 = cp2 e1 env and u2 = cp2 e2 env in match (u1,u2) 
	with | Int a, Int b -> Int (a/b) | _,_ -> Binop(Div,u1,u2) )
| Binop(And, e1, e2) -> (let u1 = cp2 e1 env and u2 = cp2 e2 env in match (u1,u2) 
	with | Bool a, Bool b -> Bool (a&&b) | _,_ -> Binop(And,u1,u2) )
| Binop(Or, e1, e2) -> (let u1 = cp2 e1 env and u2 = cp2 e2 env in match (u1,u2) 
	with | Bool a, Bool b -> Bool (a||b) | _,_ -> Binop(Or,u1,u2) )
| Binop(Eq, e1, e2) -> (let u1 = cp2 e1 env and u2 = cp2 e2 env in match (u1,u2) with | 
Int a, Int b -> Bool (a = b) | Int a, Bool b -> Bool false | Bool a, Bool b -> Bool (a = b)| Bool a ,Int b -> Bool false |
_, _ -> Binop(Eq, u1, u2))
| Binop(Leq, e1, e2) -> (let u1 = cp2 e1 env and u2 = cp2 e2 env in match (u1,u2) 
	with | Int a, Int b -> Bool (a<=b) | _,_ -> Binop(Leq,u1,u2) )
| Int a  -> e | Bool a -> e
| If(b,t,e1) ->  (let u1 = cp2 b env in match u1 with | Bool true -> cp2 t env | Bool false -> cp2 e1 env | _ -> If(u1, cp2 t env, cp2 e1 env))
| Let(x,e1,e2) -> (let u1 = cp2 e1 env in match u1 with | Int a -> cp2 e2 (M.add x u1 env) | Bool a -> cp2 e2 (M.add x u1 env) | _ -> Let(x,u1,cp2 e2 env) ) 
| Var x -> match M.find_opt x env with | None -> e | Some c -> c
in cp2 e M.empty;;