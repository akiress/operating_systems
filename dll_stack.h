#include <stdio.h>

int count = 0;

struct node
{
    struct node *prev;
    int n;
    struct node *next;
} *stack, *temp, *temp1, *temp2;

void create(int x)
{
    temp = (struct node *)malloc(1 * sizeof(struct node));
    temp->prev = NULL;
    temp->next = NULL;
    temp->n = x;
    count++;
}

void push_left(int x)
{
    if (stack == NULL)
    {
        create(x);
        stack = temp;
        temp1 = stack;
    }
    else
    {
        create(x);
        temp->next = stack;
        stack->prev = temp;
        stack = temp;
    }
}

void push_right(int x)
{
    if (stack == NULL)
    {
        create(x);
        stack = temp;
        temp1 = stack;
    }
    else
    {
        create(x);
        temp1->next = temp;
        temp->prev = temp1;
        temp1 = temp;
    }
}

void pop(int x)
{
    int i = 1;
    int pos = x;
    temp1 = stack;

    if ((pos < 1) || (pos >= count + 1))
    {
        return;
    }
    if (stack == NULL)
    {
        return;
    }
    else
    {
        while (i < pos)
        {
            temp1 = temp1->next;
            i++;
        }
        if (i == 1)
        {
            if (temp1->next == NULL)
            {
                free(temp1);
                temp1 = stack = NULL;
                return;
            }
        }
        if (temp1->next == NULL)
        {
            temp1->prev->next = NULL;
            free(temp1);
            return;
        }
        temp1->next->prev = temp1->prev;
        if (i != 1)
            temp1->prev->next = temp1->next;
        if (i == 1)
            stack = temp1->next;
        free(temp1);
    }
    count--;
}

void print_stack()
{
    temp2 = stack;

    if (temp2 == NULL)
    {
        return;
    }
    printf("STACK:\t\t");

    while (temp2->next != NULL)
    {
        printf(" %d ", temp2->n);
        temp2 = temp2->next;
    }
    printf(" %d ", temp2->n);
    printf("\n");
}

int search(int x)
{
    int counter = 0;
    temp2 = stack;

    if (temp2 == NULL)
    {
        return;
    }

    while (temp2 != NULL)
    {
        if (temp2->n == x)
        {
            return counter + 1;
        }
        else
            temp2 = temp2->next;
        counter++;
    }

    return -1;
}

void update(int x, int y)
{
    temp2 = stack;
    if (temp1 == NULL)
    {
        printf("\n Error : List empty no node to update");
        return;
    }
    while (temp2 != NULL)
    {
        if (temp2->n == x)
        {

            temp2->n = y;
            return;
        }
        else temp2 = temp2->next;
    }

    printf("\n Error : %d not found in list to update", x);
}

int value(int x)
{
    int counter = 0;
    temp1 = stack;

    if (temp1 == NULL)
    {
        return;
    }

    while (counter != x)
    {
        if (counter < x - 1)
        {
            temp1 = temp1->next;
        }
        counter++;
    }

    return temp1->n;
}