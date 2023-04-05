.data
    barran: .asciiz "\n"

    vet:
        .align 2
        .space 60                       #4 * 15 = 60 (vetor de 15 posicoes de 4 bytes)
    
    vet2:
        .align 2
        .space 60
.text

.globl main

#variaveis
#$t0 = i
#$t3 = j
#$t2 = contador
#$t4 = a[i]
#$t5 = a[j]


main:
    move $t0, $zero                     #registrador que guardara o indicie a ser utilizado
    li $t1, 60                          #tamanho do array (usaremos no loop para verificar se o array ja foi preenchido) 
   
#preenchendo o vetor    
for:
    
    beq $t0, $t1, saiDoFor              #verifica se o vetor esta totalmente preenchido
    
    li $v0, 5                           #lendo o inteiro a ser alocado
    syscall
    sw $v0, vet($t0)                    #carregando o valor lido no syscall diretamente no vetor
    
    addi $t0, $t0, 4                    #$t0 = $t0 + 4 (4 pois cada espaco no vetor possui 4 bytes)
    j for

saiDoFor:

#Rank_sort

    move $t0, $zero                     #resetamos o valor do $t0 para acessar novamente as posicoes corretas no vetor
    
loopRank_sort:
    beq $t0, $t1, saiDoLoopRank_sort    #percorrendo o vetor
    
    li $t2, 0                           #contador
    lw $t4, vet($t0)                    #a[i]
    
    li $t3, 0                           
loop2Rank_sort:

    beq $t3, $t1, saiDoLoop2Rank_sort
    
    lw $t5, vet($t3)                    #a[j]
    
    bgt $t4, $t5, incrementa
    j a
    
a:    
   
    addi $t3, $t3, 4
    j loop2Rank_sort

#t0 e $t3 indicies $t2 contador $t4 e $t5 valores dos vetores

saiDoLoop2Rank_sort:
    
    sw $t4, vet2($t2)
    
    addi $t0, $t0, 4
    j loopRank_sort
    
saiDoLoopRank_sort:
    move $t0, $zero
    j impressao
    
incrementa:
    addi $t2, $t2, 4
    j a






#imprimir o vetor
impressao:
    beq $t0, $t1, saiDaImpressao        #verifica se ja percorreu todo o vetor 
    
    li $v0, 1                           #imprime um inteiro
    lw $a0, vet2($t0)
    syscall
    
    li $v0, 4                           #imprime string
    la, $a0, barran
    syscall
    
    addi $t0, $t0, 4                    #incrementando $t0
    
    j impressao
    
saiDaImpressao:
    
    li $v0, 10
    syscall
    
    