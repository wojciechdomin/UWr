//void (*tab[100])(int u);
void fun( void (*tab[100])(),long x   ){

 (tab[x])(); 
}



/*  skompilowane z -O1!
fun(void (**)(), long):
        subq    $8, %rsp
        call    *(%rdi,%rsi,8)
        addq    $8, %rsp
        ret

*/