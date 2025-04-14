interp "let y = x in let x = 2 in y*x";;
(*powinien być wielbłąd "Unbound value x", ale program zwraca VInt 4*)