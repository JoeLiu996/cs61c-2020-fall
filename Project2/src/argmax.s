.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:
    li t0, 1
    ble t0, a1, normal
    li a1, 77
    j exit2

normal:
    #prologue
    addi sp, sp, -8
    sw s0, 0(sp)
    sw s1, 4(sp)

    add s0, x0, x0 #res
    lw s1, 0(a0) #s1 = a[i]
    add t0, x0, x0 #pointer

loop_start:
    lw t1, 0(a0)
    ble t1, s1, loop_continue
    mv s0, t0
    mv s1, t1

loop_continue:
    addi a0, a0, 4
    addi t0, t0, 1
    beq t0 a1 loop_end
    j loop_start

loop_end:
    # Epilogue
    mv a0, s0
    lw s0, 0(sp)
    lw s1, 4(sp)
    addi sp, sp, 8

    ret
