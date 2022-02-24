delay:
# less bad delay
	

	li $t6, 180000	# constant
	move $t5, $a0	# called with argument $a0, move that to $t5 so we dare do stuff with it
	li $t4, 0	# i

	while_loop:
		ble $t5, 0, exit_delay	# if called with X < 0 go to exit
		nop
		sub $t5, $t5, 1	#ms -= 1	# for each iteration remove 1 from argument

	for_loop:
		bge $t4, $t6, while_loop	# if i <= argument break to while_loop
		nop
		addi $t4, $t4, 1	# i++
		j for_loop		# jump back to the top of the loop
		nop

	j while_loop
	nop

	exit_delay:
		j exit_delay
		nop