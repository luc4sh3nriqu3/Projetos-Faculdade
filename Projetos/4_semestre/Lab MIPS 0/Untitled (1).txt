
.data
    msg1:   .asciiz "Enter the number and wait for the result... "
    msg2:   .asciiz "Invalid number."
.text

.globl main

main: 
        li	$v0,4		 #print msg1
	    la	$a0, msg1
	    syscall
	    
        li $v0, 5        #load int input
        syscall
        move $t0, $v0
        
        li $t1, 0        #$t1 = 0
        
        bgt $t0, $t1, a
        
        li	$v0,4		 #print msg2
	    la	$a0, msg2
	    syscall
	    
	    li	$v0,10       #exit
	    syscall
    
        
a:
        add $t0, $t0, $t0
        
        li $v0, 1        #print int
        move $a0, $t0
        syscall
    

