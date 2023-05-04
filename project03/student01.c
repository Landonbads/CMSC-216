#include <stdio.h>
#include "raisin.h"

#define NUM_INSTRUCTIONS 5

int main(void)
{
    unsigned int instructions[NUM_INSTRUCTIONS] = {0x48ffffff, 0x0fffffff,
                                                   0x140cffff, 0xa40c00ff,
                                                   0xa20c00ff};
    int i;

    for (i = 0; i < NUM_INSTRUCTIONS; i++)
        print_instruction(instructions[i]);

    return 0;
}
