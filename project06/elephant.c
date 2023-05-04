/* Name: Landon Badstibner
 * Date: 03/15/2023
 * Terpconnect: landonb
 * UID: 119011416
 * Section: 0203
 *
 * Project 06 - Practice with dynamic memory location and string
 * library functions
 *
 * I pledge on my honor that I have not given or received
 * any unauthorized assistance on this assignment
 */

#include "elephant.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

Elephant *new_elephant(const char name[], enum type which_type,
                       unsigned int id, unsigned short weight,
                       float trunk_length)
{

    if (name != NULL)
    {
        Elephant *el = malloc(sizeof(Elephant));

        char *el_name = malloc(strlen(name) + 1);
        strcpy(el_name, name);

        el->elephant_type = which_type;
        el->id = id;
        el->weight = weight;
        el->trunk_length = trunk_length;
        el->name = el_name;

        return el;
    }
    return NULL;
}

unsigned short get_type(const Elephant *const el_ptr,
                        enum type *const type_ptr)
{
    if (el_ptr == NULL || type_ptr == NULL)
        return 0;

    *type_ptr = el_ptr->elephant_type;
    return 1;
}

const char *get_name(const Elephant *const el_ptr)
{
    char *name;

    if (el_ptr == NULL || el_ptr->name == NULL)
        return NULL;

    name = malloc(strlen(el_ptr->name) + 1);
    strcpy(name, el_ptr->name);

    return name;
}

void print_elephant(const Elephant *const el_ptr)
{
    if (el_ptr != NULL && el_ptr->name != NULL)
    {
        printf("%s ", el_ptr->name);
        if (el_ptr->elephant_type == 0)
            printf("AFRICAN ");
        else if (el_ptr->elephant_type == 1)
            printf("ASIAN ");

        printf("%d %d %g\n", el_ptr->id, el_ptr->weight, el_ptr->trunk_length);
    }
}

short compare(const Elephant *const el_ptr1, const Elephant *const el_ptr2)
{
    if (el_ptr1 == NULL || el_ptr2 == NULL || el_ptr1->name == NULL ||
        el_ptr2->name == NULL)
        return -1;

    if (strcmp(el_ptr1->name, el_ptr2->name) == 0 &&
        el_ptr1->id == el_ptr2->id &&
        el_ptr1->trunk_length == el_ptr2->trunk_length &&
        el_ptr1->weight == el_ptr2->weight &&
        el_ptr1->elephant_type == el_ptr2->elephant_type)
        return 1;
    else
        return 0;
}

unsigned short change_name(Elephant *const el_ptr, const char new_name[])
{
    if (el_ptr != NULL && new_name != NULL)
    {
        char *new_name1;
        new_name1 = malloc(strlen(new_name) + 1);
        strcpy(new_name1, new_name);

        free(el_ptr->name);
        el_ptr->name = new_name1;
        return 1;
    }

    return 0;
}

unsigned short copy(Elephant *const el_ptr1, const Elephant *const el_ptr2)
{
    if (el_ptr1 != NULL && el_ptr2 != NULL &&
        el_ptr1->name != NULL && el_ptr2->name != NULL)
    {
        char *new_name;
        new_name = malloc(strlen(el_ptr2->name) + 1);
        strcpy(new_name, el_ptr2->name);

        free(el_ptr1->name);
        el_ptr1->name = new_name;
        el_ptr1->elephant_type = el_ptr2->elephant_type;
        el_ptr1->id = el_ptr2->id;
        el_ptr1->weight = el_ptr2->weight;
        el_ptr1->trunk_length = el_ptr2->trunk_length;

        return 1;
    }
    return 0;
}