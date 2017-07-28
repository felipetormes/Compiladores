# DATA SECTION

	.LC0:
		.string "%s"
	.LC1:
		.string "%x"
	.LC2:
		.string "%c"
	.LC3:
		.string "\n"

	.globl ___temp6___
	.data
	.align 4
	.type ___temp6___, @object
	.size ___temp6___, 4
	___temp6___:
		.long 161698560

	.globl a
	.data
	.align 4
	.type a, @object
	.size a, 4
	a:
		.long 161684784

	.globl c
	.data
	.align 4
	.type c, @object
	.size c, 4
	c:
		.long 161686840

	.globl d
	.data
	.align 4
	.type d, @object
	.size d, 4
	d:
		.long 161687560

	.globl i
	.data
	.align 4
	.type i, @object
	.size i, 4
	i:
		.long 161685488

	.globl ___temp12___
	.data
	.align 4
	.type ___temp12___, @object
	.size ___temp12___, 4
	___temp12___:
		.long 161699608

	.globl ___temp7___
	.data
	.align 4
	.type ___temp7___, @object
	.size ___temp7___, 4
	___temp7___:
		.long 161698728

	.globl ___temp10___
	.data
	.align 4
	.type ___temp10___, @object
	.size ___temp10___, 4
	___temp10___:
		.long 161699240

	.comm	mat,40
	.globl ___temp9___
	.data
	.align 4
	.type ___temp9___, @object
	.size ___temp9___, 4
	___temp9___:
		.long 161699064

	.comm	vfloat,16
	.globl ___temp11___
	.data
	.align 4
	.type ___temp11___, @object
	.size ___temp11___, 4
	___temp11___:
		.long 161699424

	.globl ___temp8___
	.data
	.align 4
	.type ___temp8___, @object
	.size ___temp8___, 4
	___temp8___:
		.long 161698896


# CODE SECTION:

		# STARTING MOVE
			movl $0, %edx
			movl %edx, a(%rip)
		# ENDING MOVE

		# STARTING MOVE
			movl $0, %edx
			movl %edx, i(%rip)
		# ENDING MOVE

		# STARTING MOVE
			movl $120, %edx
			movl %edx, c(%rip)
		# ENDING MOVE

		# STARTING MOVE
			movl $101, %edx
			movl %edx, d(%rip)
		# ENDING MOVE

			___main_start___:
	.globl	main
	.type	main, @function
	main:
	.LFB0:
		.cfi_startproc
		pushq	%rbp
		.cfi_def_cfa_offset 16
		.cfi_offset 6, -16
		movq	%rsp, %rbp
		.cfi_def_cfa_register 6

		# STARTING ADD
			movl	$3, %edx
			movl	$5, %eax
			addl %edx, %eax
			movl %eax, ___temp6___(%rip)
		# ENDING ADD

		# STARTING MUL
			movl	___temp6___(%rip), %edx
			movl	___temp6___(%rip), %eax
			imul	%edx, %eax
			movl	%eax, ___temp7___(%rip)
		# ENDING MUL

		# STARTING MUL
			movl	___temp7___(%rip), %edx
			movl	___temp6___(%rip), %eax
			imul	%edx, %eax
			movl	%eax, ___temp8___(%rip)
		# ENDING MUL

		# STARTING MUL
			movl	___temp8___(%rip), %edx
			movl	___temp6___(%rip), %eax
			imul	%edx, %eax
			movl	%eax, ___temp9___(%rip)
		# ENDING MUL

		# STARTING MUL
			movl	___temp9___(%rip), %edx
			movl	___temp6___(%rip), %eax
			imul	%edx, %eax
			movl	%eax, ___temp10___(%rip)
		# ENDING MUL

		# STARTING MUL
			movl	___temp10___(%rip), %edx
			movl	___temp6___(%rip), %eax
			imul	%edx, %eax
			movl	%eax, ___temp11___(%rip)
		# ENDING MUL

		# STARTING MUL
			movl	___temp11___(%rip), %edx
			movl	___temp6___(%rip), %eax
			imul	%edx, %eax
			movl	%eax, ___temp12___(%rip)
		# ENDING MUL

		# STARTING MOVE
			movl ___temp12___(%rip), %edx
			movl %edx, a(%rip)
		# ENDING MOVE

		# STARTING PRINT LIST
			movl	a(%rip), %esi
			movl	$.LC1, %edi
			movl	$0, %eax
			call	printf
		# ENDING PRINT LIST

		# STARTING RET
			movl	$0, %eax
			popq	%rbp
			.cfi_def_cfa 7, 8
			ret
			.cfi_endproc
		# ENDING RET

	.LFE0:
		.size	main, .-main

			___main_end___:
