.data
    msg: .asciiz "Maior: "
.text

.globl main

main:
        li $t0, 0       #$t0 = 0
        
        li $v0, 5       #le o primeiro numero e armazena ele em $v0
        syscall
        move $t1, $v0   #passa o valor lido em $v0 para $t1

        li $v0, 5       #le o segundo numero e armazena ele em $v0
        syscall
        move $t2, $v0   #passa o valor lido em $v0 para $t2

        li $v0, 5       #le o terceiro numero e armazena ele em $v0
        syscall
        move $t3, $v0   #passa o valor lido em $v0 para $t3
        
        bgt $t1, $t2, a    #if($t1 > $t2)
        
        bgt $t3, $t2, c     #if($t3 > $t2)
        
        li $v0, 4       #print msg
        la $a0, msg
        syscall
        
        li $v0, 1       #print $t2
        move $a0, $t2
        syscall
        
        li $v0, 10      #exit
        syscall

a:      #primeiro numero eh maior que o segundo
        bgt $t3, $t1, c     #if($t3 > $t1)
        
        li $v0, 4       #print msg
        la $a0, msg
        syscall
        
        li $v0, 1       #print $t1
        move $a0, $t1
        syscall
        
        li $v0, 10      #exit
        syscall
        
c:      #terceiro numero eh maior
        li $v0, 4       #print msg
        la $a0, msg
        syscall
        
        li $v0, 1       #print $t3
        move $a0, $t3
        syscall
        
        li $v0, 10      #exit
        syscall