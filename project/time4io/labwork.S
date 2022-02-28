  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm
.global delay
.global time2string
.global hexasc

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #


.text

	
delay: 
	move  $t5, $a0     # int ms, men hur ger jag den inget värde?? a0 = 100 // ms
	li    $t7, 0 	   # int i		s0 = 0; //i 
	li   $t6, 4000	   # random värde       s1 = 5; //j 
	
     loop1:
     	slt $t1, $zero, $t5 # kontrollera om ms > 0   if (0 < a0) // a<ms  
     	beq $t1, $zero, exit # är den < 0 avsluta     if (t1 == 0 ) // gå to done 
     	nop
     	add $t5, $t5, -1 # minska ms med 1 	      a0 = a0 -1 // ms - 1 
     	addi $t7, $zero, 0 # reseta s0 så du kan loopa igen  s0  = 0; // i  
     loop2:
    	slt $t2, $t7, $t6 # kontrollera om i < random värde	s0 < s1 // i  < j;  
     	beq $t2, $zero, loop1 # är den < fortsätt loop annars hoppa till loop1 // t2 = 0 // gå to loop1 
     	nop
    	add $t7, $t7, 1 # plussa i med 1
    	j loop2
    	nop
    	
     exit:
	jr $ra
	nop
	
time2string:
	PUSH   $s0
	PUSH   $s1
	move   $s0, $a0
	move   $s1, $a1
	
	srl    $t1,  $a1, 12     # t1 = a1 >>12
	move   $a0, $t1 	 # a2 = t1
	PUSH	$ra 		#save the adress that is in ra
	jal	hexasc		# call hexasc'
	nop  
	sb      $v0, 0($s0)	#store whre a0 is pointing to 
	
	srl    $t1, $a1, 8	# t1 = a1 >>8
	move    $a0, $t1	 # a2 = t1
	jal	hexasc		# call hexasc'
	nop 
	sb      $v0, 1($s0) 
	
	li     $t1, 0x3A	# for semicolon 
	sb     $t1, 2($s0) 
	
	srl    $t1, $a1, 4	# t1 = a1 >>4
	move   $a0, $t1
	jal	hexasc		# call hexasc'
	nop 			# syscall with v0 = 11 will print out
	sb      $v0, 3($s0)
	 
	add    $t1, $a1, $zero	# t1 = a1 + 0 
	move   $a0, $t1
	jal	hexasc		# call hexasc'
	nop 
	POP	$ra
	sb      $v0, 4($s0) 
	
	addi	$t4, $0, 0x00	#nullbyte
	sb	$t4, 5($s0)
	move   $a0, $s0
	move   $a1, $s1
	POP     $s0
	POP     $s1 
	 
	
	jr     $ra
	nop 
	stop:	j	stop		# loop forever here
	nop	
	


hexasc:
	andi    $t1, $a0, 0xf      # a0 & 0xf
	slti    $t2, $t1, 10       # t1 < 10 då får t2 1 annars 0
	beq     $t2, $zero, AtoF   # if (t2 = 0) go to function AtoF
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
