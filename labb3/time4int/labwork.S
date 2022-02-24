  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

.global delay
.global time2string
.global hexasc
.global enable_interrupt

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm


.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

.data
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
	PUSH	$s0
	PUSH	$s1				          # Save contents of s1 to restore it after the function ends
	PUSH	$ra				          # Save the return adress on the stack
	move	$s1, $a1		     	  # Move contents of $a0 to $s1 so we can work with it
	move	$s0, $a0

	# First digit
	andi 	$t1, $s1, 0xf000		# Masking out bit from index 15 to 12
	srl 	$a0, $t1, 12		  	# Shifting the bits to lowest position and store it in $a0 for hexas
	jal	hexasc				        # Calling the hexasc that will transform the decimal into hexadecimal
	nop
	sb 	$v0, 0($s0)		 	      # Save the return value from hexasc in the first byte location $s1
						                # points to

	# Second digit
	andi 	$t1, $s1, 0x0f00		# Masking out bit from index 11 to 8
	srl 	$a0, $t1, 8	    		# Shifting the bits to lowest position and store it in $a0 for hexasc
	jal	hexasc			        	# Calling the hexasc that will transform the decimal into hexadecimal
	nop
	sb 	$v0, 1($s0)		 	      # Save the return value from hexasc in the second byte location $s1
						                # points to

	# Adding the colon
	li 	$t1, 0x3a			        # Loading the ASCII code for colon
	sb 	$t1, 2($s0)		 	      # Save the return value from hexasc in the third byte location $s1
						# points to

	# Third digit
	andi 	$t1, $s1, 0x00f0		# Masking out bit from index 7 to 4
	srl 	$a0, $t1, 4		     	# Shifting the bits to lowest position and store it in $a0 for hexasc
	jal	hexasc			        	# Calling the hexasc that will transform the decimal into hexadecimal
	nop
	sb 	$v0, 3($s0)		 	      # Save the return value from hexasc in the fourth byte location $s1
						                # points to

	# Forth digit
	andi 	$t1, $s1, 0x000f		# Masking out bit from index 3 to 0
	move 	$a0, $t1			      # No need for shifting, just move it to the argument.
	jal	hexasc				        # Calling the hexasc that will transform the decimal into hexadecimal
	nop
	sb 	$v0, 4($s0)		 	      # Save the return value from hexasc in the fifth byte location $s1
						                # points to

	# Adding the NUL byte
	li	$t1, 0x00			        # Loading the ASCII code for NUL
	sb 	$t1, 5($s0)		      	# Save the return value from hexasc in the sixth byte location $s1

	# End of subroutine. Restoring registers and jumping back to caller.
		POP	$ra
		POP	$s1
		POP	$s0
 		jr 	$ra
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
	


# Function that enables interrupts globally
enable_interrupt:
    ei
    jr  $ra
    nop