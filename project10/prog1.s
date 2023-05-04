# Landon Badstibner
# UID:119011416
# Terpconnect: landonb
# Section: 0203
# Date: 05/01/23
# Program description: Takes input for the length and width of two rectanges, 
# calculates the area of both and returns either -2, 1, -1, or 0 depending
# on the area of the rectanges and if the length/width are negative

        .data

l1:     .word 0
w1:     .word 0
l2:     .word 0
w2:     .word 0
rect1:  .word 0
rect2:  .word 0
result: .word 0

        .text

main:   sw   $0, result
        lw   $t0, l1
        lw   $t1, w1
        lw   $t2, l2
        lw   $t3, w2
        lw   $t4, rect1
        lw   $t5, rect2
        lw   $t6, result

        li   $v0, 5             # scanf read int 
        syscall
        move $t0, $v0           # move result of scanf into t0
        sw   $t0, l1            # store result from reg into mem

        li   $v0, 5             # same steps repeated with diff var
        syscall
        move $t1, $v0
        sw   $t1, w1

        li   $v0, 5
        syscall
        move $t2, $v0
        sw   $t2, l2

        li   $v0, 5
        syscall
        move $t3, $v0
        sw   $t3, w2            # scanf snippets end


        bltz $t0, neg2          # if l1 < 0, jump to neg2
        bltz $t1, neg2          # if w1 < 0, jump to neg2
        bltz $t2, neg2          # if l2 < 0, jump to neg2
        bltz $t3, neg2          # if w2 < 0, jump to neg2
        j    else               # if none of these are true, jump to else block

neg2:   li   $t6, -2            # loads -2 immediate into result reg
        sw   $t6, result        # stores value in result reg into result mem
        j    end                # skip over else block

else:   mul  $t0, $t0, $t1      # multiply l1 and w1 and store result in $t0
        move $t4, $t0           # move value at $t0 into $t4
        sw   $t4, rect1         # store value from reg $t4 into rect1 memory

        mul  $t2, $t2, $t3      # multiply l2 and w2 and store result in $t2
        move $t5, $t2           # move value at $t2 into $t5
        sw   $t5, rect2         # store value from reg $t5 into rect2 memory

        blt  $t4, $t5, less     # if rect1 less than rect2, jump to less

        bgt  $t4, $t5, greater  # if rect1 more than rect2, jump to greater
        j    end                # jump to end snippet

less:
        li   $t6, -1            # load -1 into result reg if rect1 < rect2
        sw   $t6, result        # store value in result reg into result mem
        j    end                # jump to end snippet

greater:
        li   $t6, 1             # load 1 into result reg if rect1 > rect2
        sw   $t6, result        # store value in result reg into result mem


end:    li   $v0, 1             # load 1 into $v0 to print an int to stdout
        lw   $a0, result        # load value in result into param reg $a0
        syscall

        li   $v0, 11            # load 11 into $v0 to print a char to stdout
        li   $a0, 10            # load 10 into param reg $a0 to represent "\n"
        syscall

        li   $v0, 10            # quit program
        syscall
     

