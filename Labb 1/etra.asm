.text
main:
	li     $t1, 5
	jal    test
	nop 
	
	# move	$a0,$v0		# copy return value to argument register
	move    $a0, $t1
	li	$v0,1		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

test: 
	addi   $t1, $t1, 20
	jr    $ra
	nop 