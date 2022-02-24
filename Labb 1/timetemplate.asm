# timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
  #

	
delay: 
	move  $t5, $a0     # int ms, men hur ger jag den inget värde?? a0 = 100 // ms
	li    $t7, 0 	   # int i		s0 = 0; //i 
	li   $t6, 50	   # random värde       s1 = 5; //j 
	
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
	PUSH   ($s0)
	PUSH   ($s1)
	move   $s0, $a0
	move   $s1, $a1
	
	srl    $t1,  $a1, 12     # t1 = a1 >>12
	move   $a0, $t1 	 # a2 = t1
	PUSH	($ra) 		#save the adress that is in ra
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
	POP	($ra)
	sb      $v0, 4($s0) 
	
	addi	$t4, $0, 0x00	#nullbyte
	sb	$t4, 5($s0)
	move   $a0, $s0
	move   $a1, $s1
	POP     ($s0)
	POP     ($s1) 
	 
	
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
