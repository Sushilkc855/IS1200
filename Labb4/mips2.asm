.text
addi $a0, $0, 7 # n
addi $a1, $a0, -1 # n-1
addi $v0, $a0, 0  # 4
addi $a2, $0, 1 # i 
addi $at, $0, 1  

beq $a0, $at, final
add  $0, $0, $0	

beq $a0, $0, final
add  $0, $0, $0

loop:
beq  $a0, $a2, done # if a2 == a1                4==3   
add  $0, $0, $0	

mul  $v0, $v0, $a1   # v0 * a1			 24
addi $a1, $a1, -1   # 0 			a2 = 3
addi $a2, $a2, 1   # i++ 4
beq  $0, $0, loop
add  $0, $0, $0	# NOP

final:
addi $v0, $a0, 0
add  $0, $0, $0

done:
beq $0, $0, done	# NOP
add  $0, $0, $0			# NOP