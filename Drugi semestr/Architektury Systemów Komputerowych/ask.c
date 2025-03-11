#include <stdio.h>
#include <stdint.h>

int main()
{
   

  /*
    printf("int:  %d\n", x); 
    printf("uint: %u\n", x);  
    printf("hex:  %X\n", x);  
    printf("oct:  %o\n", x);  
    printf("bin:  %032b\n", x);  
    printf("size: %d\n", sizeof(char*));  
    printf("addr: %p\n", c);
    printf("%02x ", c[i]);
    printf("\n");
    */
    int32_t x = 0x80000000;
    int32_t y;
	printf("%d\n",(x > 0) || (x - 1 < 0));
	x = 0x0000FFFF;
	printf("%d\n",(x * x) >= 0 );
	x = 0x80000000;
	printf("%d\n", x > 0 || -x >= 0);
	x = 0x7FFFFFFF;
	y = 0x00000000;
	printf("%d\n",x + y == (uint32_t)y + (uint32_t)x);
	//i byc moze ostatnie tez :)
	 


    
    
       
    return 0;
}
int32_t three_fourths(int32_t x){
    return x-(x>>2)-(((x&2)>>1)|(x&1));
}
