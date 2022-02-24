  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,9	# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #
hexasc:
	andi    $t1, $a0, 0xf      # a0 & 0xf
	slti    $t2, $t1, 10       # t1 < 10 då får t2 1 annars 0
	beq     $t2, $zero, AtoF   # if (t2 == 0) go to function AtoF
	nop
	addi    $t1, $t1, 0x30	   # t1 + 0x30 
	move    $v0, $t1           # v0 = t1
	jr      $ra			
	nop
AtoF:
	addi	$t1, $t1, 0x37    #t1 = t1 + 0x37
	move   	$v0, $t1	  # v0 = t1
	jr      $ra
	nop
