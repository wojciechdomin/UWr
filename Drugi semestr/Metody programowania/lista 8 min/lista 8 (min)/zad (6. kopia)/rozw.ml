interp "let matrix_id = ((1,0),(0,1)) in let dot = fun x -> fun y -> fun z -> fun t -> (x * z + y * t) in let matrix_mult = fun x -> fun y -> let a = fst (fst x) in let b = fst (snd x) in let c = snd (fst x) in let d = snd (snd x) in let e = fst (fst y) in let f = fst (snd y) in let g = snd (fst y) in let h = snd (snd y) in (((dot a b e g),(dot a b f h)),((dot c d e g),(dot c d f h))) in let mef = funrec mef y -> fun x -> if x = 0 then matrix_id else if x = 1 then y else let u = mef y (x/2) in if (x/2)*2 = x then matrix_mult u u else matrix_mult y (matrix_mult u u) in let fib_fast = fun x -> fst(fst(mef ((1,1),(1,0)) x)) in fib_fast 14";;



interp "
let matrix_id = ((1,0),(0,1)) in 
let dot = fun x -> fun y -> fun z -> fun t -> (x * z + y * t) in
let matrix_mult = 
	fun x -> fun y -> let a = fst (fst x) in let b = fst (snd x) in let c = snd (fst x) in let d = snd (snd x) in let e = fst (fst y) in let f = fst (snd y) in let g = snd (fst y) in let h = snd (snd y) in
	(((dot a b e g),(dot a b f h)),((dot c d e g),(dot c d f h))) in
let mef = 
	funrec mef y -> fun x ->
	if x = 0 then matrix_id else
		if x = 1 then y 
		else let u = mef y (x/2) in if (x/2)*2 = x then
		matrix_mult u u else
		matrix_mult y (matrix_mult u u) in
let fib_fast = fun x -> fst(fst(mef ((1,1),(1,0)) x)) in
fib_fast 14
";;
