        .globl  puzzle1
        
        .text
puzzle1:
	puzzle: testl %esi, %esi
	je .L4
	xorl %edx, %edx
	xorl %eax, %eax
	.L3: movl %edi, %ecx
	andl $1, %ecx
	addl %ecx, %eax
	sarq %rdi
	incl %edx
	cmpl %edx, %esi
	jne .L3
	ret
	.L4: movl %esi, %eax
	ret
