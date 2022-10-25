.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
# - If malloc returns an error,
#   this function terminates the program with error code 88.
# - If you receive an fopen error or eof, 
#   this function terminates the program with error code 90.
# - If you receive an fread error or eof,
#   this function terminates the program with error code 91.
# - If you receive an fclose error or eof,
#   this function terminates the program with error code 92.
# ==============================================================================
read_matrix:

    # Prologue
	addi sp, sp, -44
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)
    sw s5, 24(sp)
    sw s6, 28(sp)
    sw s7, 32(sp)
    sw s8, 36(sp)
    sw s9, 40(sp)

    mv s0, a0
    mv s1, a1
    mv s2, a2

    #open file
    mv a1, s0
    li a2, 0
    jal fopen
    li t0, -1
    beq a0, t0, exit_90
    mv s3, a0 #file descriptor

    #read dimision of matrix
    #row
    mv a1, s3
    mv a2, s1
    li a3, 4
    jal fread
    li t0, 4
    bne a0, t0, exit_91

    #col
    mv a1, s3
    mv a2, s2
    li a3, 4
    jal fread
    li t0, 4
    bne a0, t0, exit_91

    #restore the value of s1, s2
    lw s1, 0(s1)
    lw s2, 0(s2)

    #allocate memory for matrix
    mul a0, s1, s2
    li t0, 4
    mul a0, a0,t0
    jal malloc
    beq x0, a0, exit_88
    mv s6, a0 #pointer to the matrix

    #read elements in matrix

    mul s7, s1, s2 #total elements in the  matrix
    li s8, 0 # i = 0
    mv s9, s6 #pointer + offset

loop_start:
    mv a1, s3
    mv a2, s9
    li a3, 4
    jal fread
    li t0, 4
    bne t0, a0, exit_91
    addi s8, s8, 1 # i++
    beq s8, s7, loop_end
    addi s9, s9, 4 #move to next element
    j loop_start

loop_end:
    #close the file
    mv a1, s3
    jal fclose
    bne x0, a0, exit_92

    #return results
    mv a0, s6

    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    lw s5, 24(sp)
    lw s6, 28(sp)
    lw s7, 32(sp)
    lw s8, 36(sp)
    lw s9, 40(sp)
    addi, sp, sp, 44

    ret

exit_88:
    li a1, 88
    jal exit2

exit_90:
    li a1, 90
    jal exit2

exit_91:
    li a1, 91
    jal exit2

exit_92:
    li a1, 92
    jal exit2