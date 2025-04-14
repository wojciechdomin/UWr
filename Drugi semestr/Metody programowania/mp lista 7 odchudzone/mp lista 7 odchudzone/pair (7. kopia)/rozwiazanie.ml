interp "let y = x in let x = 2 in y*x";;
(*powinien być wielbłąd "Unbound value x", ale program zwraca VInt 4*)
(*po zmianie w funkcji subst program działa poprawnie
np.  interp "let y = x in let x = 2 in y";;
kończy się Exception: Failure "unbound variable!!! x".
a dla interp "let x = 2 in let y = x in let x = 2 in y";;
program zwraca VInt 2
*)