#include <stdio.h>
#include <assert.h>
#include "elephant.h"
#include "check-elephant.h"

int main(void)
{
    Elephant *elephant = new_elephant("Ellie", ASIAN, 11144, 9742, 6.5f);

    assert(elephant != NULL);
    /* check all the elephant's data using our check_elephant() function */
    assert(check_elephant(elephant, "Ellie", ASIAN, 11144, 9742, 6.5f) == 1);

    printf("All assertions passed!\n");

    return 0;
}