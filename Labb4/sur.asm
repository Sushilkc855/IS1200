.text
addi $a0, $0, 4 # n
addi $a1, $0, 0 # current statues of loop, i
addi $v0, $a0, 0 # result 
add $a2, $0, $a0 # a2 = 4
add $a3, $a0, $0 # a3 = 4
addi $at, $0, 1

beq $a0, $at, final
add  $0, $0, $0	


main:
beq  $a0, $a1, final # if a0 == a1
add  $0, $0, $0

addi  $a1, $a1, 1 # 			         a1 = 4
addi  $a3, $v0, 0 # save the result              a3 = 24
addi  $v0, $0, 0  # result for the next number   v0 = 0
add $a2, $0, $a0  # a2 = n                       a2 = 4


loop:
beq  $a2, $a1, main # if a2 == a1                4==4   
add  $0, $0, $0	# NOP
add $v0, $a3, $v0    # v0 += a0 		v0 = 24

addi $a2, $a2, -1   # n-1 			a2 = 3
beq  $0, $0, loop
add  $0, $0, $0	# NOP

final:
addi $v0, $a3, 0
beq  $0,$0, done
add  $0, $0, $0			# NOP

done:
beq $0, $0, done	# NOP
add  $0, $0, $0			# NOP