.data
    msg_maior_nivel: .asciiz "Maior nivel: "
    msg_velocidade1: .asciiz "velocidade 1"
    msg_velocidade2: .asciiz "velocidade 2"
    msg_velocidade3: .asciiz "velocidade 3"
    msg_error: .asciiz ": valor invalido."
    msg_error_velocidade: .asciiz ": velocidade invalida\n"
.text

.globl main

main:
    li $s0, 1                               #$s0 = 1 (limite inferior L e Vi)
    li $s1, 30                              #$s1 = 30 (limite superior L)
    li $s2, 50                              #$s2 = 50 (limite superior Vi)
    li $s4, 10                              #$s4 = 10 (velocidade 1)
    li $s5, 20                              #$s5 = 20 (velocidade 2)
    li $s6, 30                              #$s6 = 30 (velocidade 3)
    
    li, $v0, 5                              #le o L numero de lesmas
    syscall
    move $s3, $v0
    
    bge $s3, $s0, maiorque1
    
    li $v0, 1
    move $a0, $s3                           #print int ($s2)
    syscall
    li $v0, 4
    la $a0, msg_error                       #print msg_error
    syscall
    
    li $v0, 10                              #exit
    syscall
    
main_continue:                              #TUDO CERTO COM O NUMERO DE LESMAS
    
    li $t0, 0                               # usaremos pra sair do loop
    li $t1, 0                               #guardara a maior velocidade

loop:
    li, $v0, 5                              #le o L numero de velocidades das lesmas
    syscall
    move $t2, $v0
    
    bge $t2, $s0, maiorque1_velocidade      #verifica se a velocidade eh maior que 1
    
    li $v0, 1
    move $a0, $t2                           #print int ($s3)
    syscall
    li $v0, 4
    la $a0, msg_error_velocidade            #print msg
    syscall
    
    j loop_continue
    
a:
    add $t0, $t0, 1
    bge $t0, $s3, exitfor
    j loop
    

loop_continue:                              #TUDO CERTO COM A VELOCIDADE LIDA
    
    bgt $t2, $t1, atualiza_maior
    
    j a
    
atualiza_maior:
    move $t1, $t2
    j a
    
maiorque1_velocidade:
    ble $t2, $s2, loop_continue            #verifica se a velocidade eh menor que 50
    
    li $v0, 1
    move $a0, $t2                           #print int ($s3)
    syscall
    li $v0, 4
    la $a0, msg_error_velocidade            #print msg
    syscall
    
    j loop_continue

exitfor:                                    #AQUI TEMOS A LESMA MAIS VELOZ
    
    
    blt $t1, $s4, velocidade1
    
    blt $t1, $s5, velocidade2
    
    li $v0, 4
    la $a0, msg_maior_nivel
    syscall
    li $v0, 4
    la $a0, msg_velocidade3
    syscall
    
    li $v0, 10                              #exit
    syscall
    
velocidade1:
    li $v0, 4
    la $a0, msg_maior_nivel
    syscall
    li $v0, 4
    la $a0, msg_velocidade1
    syscall
    
    li $v0, 10                              #exit
    syscall

velocidade2:
    li $v0, 4
    la $a0, msg_maior_nivel
    syscall
    li $v0, 4
    la $a0, msg_velocidade2
    syscall
    
    li $v0, 10                              #exit
    syscall 
    
maiorque1:
    ble $s3, $s1, main_continue
    
    li $v0, 1
    move $a0, $s3                           #print int ($s2)
    syscall
    li $v0, 4
    la $a0, msg_error                       #print msg_error
    syscall
    
    li $v0, 10                              #exit
    syscall
    