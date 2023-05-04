# Landon Badstibner
# UID: 119011416
# Terpconnect: landonb
# Section: 0203
# Date: 05/02/23
# Program description: recursively implements program 2, which determines
# the number of digits of a number in any base > 0.


            .data

number:     .word 0
base:       .word 0
result:     .word 0


            .text

main:       li      $v0, 5            # scanf("%d", &number);
            syscall
            move    $t0, $v0
            sw      $t0, number

            li      $v0, 5            # scanf("%d", &base);
            syscall
            move    $t1, $v0
            sw      $t1, base

            li      $sp, 0x7ffffffc   # set up stack ptr

            sw      $t0, ($sp)        # push args onto stack
            sub     $sp, $sp, 4
            sw      $t1, ($sp)
            sub     $sp, $sp, 4

            jal     num_digits        # call num_digits

            add     $sp, $sp, 8       # pop args from stack

            sw      $v0, result       # result = num_digits(number, base);

            li      $v0, 1            # printf("%d\n", result);
            lw      $a0, result
            syscall
            li      $v0, 11
            li      $a0, 10
            syscall

            li      $v0, 10           # quit program
            syscall

                                      # prologue
num_digits: sub     $sp, $sp, 12      # set new stack ptr
            sw      $ra, 12($sp)      # save ret addr in stack
            sw      $fp, 8($sp)       # save old frame ptr in stack
            add     $fp, $sp, 12      # set new frame ptr

            li      $t0, 0            # ans = 0
            sw      $t0, 4($sp)      
            lw      $t2, 8($fp)       # load number in t2 register
            lw      $t3, 4($fp)       # load base in t3 register

            bgtz    $t3, else         # if base > 0 jump to else
            li      $t0, -1           # ans = -1
            sw      $t0, 4($sp)
            j       end               # jump to end    

else:       bltz    $t2, less         # if n < 0 jump to less
            j       ifbase            # if n >= 0, jump to ifbase

less:       neg     $t2, $t2          # n = -n
            sw      $t2, 8($fp)

ifbase:     li      $t4, 1            # load 1 into reg t4
            bne     $t3, $t4, elseif  # if base != 1 jump to elseif
            lw      $t0, 8($fp)       # ans = n
            sw      $t0, 4($sp)
            j       end               # jump to end

elseif:     bge     $t2, $t3, else2   # if n >= base jump to else2
            li      $t0, 1            # ans = 1
            sw      $t0, 4($sp)
            j       end               # jump to end

else2:      div     $t2, $t2, $t3     # divide n by base

            sw      $t2, ($sp)        # push args onto the stack
            sub     $sp, $sp, 4
            sw      $t3, ($sp)
            sub     $sp, $sp, 4

            jal     num_digits        # call num_digits recursively

            add     $t0, $v0, 1       # ans = 1 + num_digits(n / base, base);
            sw      $t0, 4($sp)

            add     $sp, $sp, 8       # pop args from stack


end:        move    $v0, $t0          # copy return value to $v0

                                      # epilogue
            lw      $ra, 12($sp)      # load ret addr from stack
            lw      $fp, 8($sp)       # restore old frame ptr from stack
            add     $sp, $sp, 12      # reset stack ptr
            jr      $ra               # return to caller using saved ret addr
            
