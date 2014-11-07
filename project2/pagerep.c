#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#include <limits.h>
#include "flex_array.h"
#include "dll_stack.h"

#define STACK_MAX 28

typedef enum boolean { BFALSE, BTRUE } bool_t;

struct Frame_Data
{
    int fframe[STACK_MAX];
    int number_frames;
    int page_accesses;
    int page_hits;
    int page_misses;
};

static bool_t get_int ( int *ival )
{
    char buff[25];
    long lval;
    char *end;

    if ( fgets ( buff, sizeof buff, stdin ) == NULL )
        return BFALSE;

    lval = strtol ( buff, &end, 10 );

    if ( lval < INT_MIN || INT_MAX < lval || end == buff )
        return BFALSE;

    *ival = (int)lval;

    return BTRUE;
}

int find_index(int a[], int num, int x)
{
    int i;
    for (i = 0; i < num; i++)
    {
        if (a[i] == x)
        {
            return i;
        }
    }
    return -1;
}

void print_data(struct Frame_Data *f, Array evict)
{
    printf("Number of page accesses: %d\n", f->page_accesses);
    printf("Number of page hits: %d\n", f->page_hits);
    printf("Number of page misses: %d\n", f->page_misses);
    printf("Evicted pages: [");
    for (i = 1; i < evict.used; i++)
    {
        if (i != evict.used - 1)
        {
            printf("%d, ", evict.array[i]);
        }
        else
        {
            printf("%d]\n", evict.array[i]);
        }
    }

}

void lru(struct Frame_Data *f)
{
    int val = 0;

    printf("Enter number of frames: ");
    if ( get_int ( &val ) != BFALSE )
        f->number_frames = val;
    else
    {
        printf("Invalid input. Restarting process.\n");
    }
    printf("\nResults: \n");

    Array evict;
    initArray(&evict, 1);
    insertArray(&evict, -999);

    int page = 0;
    int size = 0;
    for (page = 0; page < STACK_MAX; page++)
    {
        ++f->page_accesses;
        if (size < f->number_frames && search(f->fframe[page]) < 1)
        {
            push_left(f->fframe[page]);
            ++f->page_misses;
            ++size;
        }
        else
        {
            int x = search(f->fframe[page]);
            if (x > -1)
            {
                pop(x);
                ++f->page_hits;
            }
            else
            {
                insertArray(&evict, value(f->number_frames));
                pop(f->number_frames);
                ++f->page_misses;
            }
            push_left(f->fframe[page]);
        }
    }
    printf("Number of page accesses: %d\n", f->page_accesses);
    printf("Number of page hits: %d\n", f->page_hits);
    printf("Number of page misses: %d\n", f->page_misses);
    printf("Evicted pages: [");
    int i;
    for (i = 1; i < evict.used; i++)
    {
        if (i != evict.used - 1)
        {
            printf("%d, ", evict.array[i]);
        }
        else
        {
            printf("%d]\n", evict.array[i]);
        }
    }
    freeArray(&evict);

    printf("\n\n");
}

void clock_replace(struct Frame_Data *f)
{
    int val = 0;

    printf("Enter number of frames: ");
    if ( get_int ( &val ) != BFALSE )
        f->number_frames = val;
    else
    {
        printf("Invalid input. Restarting process.\n");
    }
    printf("\nResults: \n");

    Array evict;
    initArray(&evict, 1);
    insertArray(&evict, -999);

    int page = 0;
    int size = 0;
    int clock_hand = 0;

    int clock_array[f->number_frames];
    int ref_array[f->number_frames];

    int i = 0;
    for (i = 0; i < f->number_frames; i++)
    {
        clock_array[i] = -1;
        ref_array[i] = 0;
    }

    int idx2 = 0;
    int idx = 0;

    for (page = 0; page < STACK_MAX; page++)
    {
        ++f->page_accesses;
        idx2 = find_index(clock_array, f->number_frames, f->fframe[page]);
        while (idx2 == -1)
        {
            if (clock_hand == f->number_frames) clock_hand = 0;
            if (ref_array[clock_hand] == 0)
            {
                ++size;
                if (size > f->number_frames) insertArray(&evict, clock_array[clock_hand]);
                ref_array[clock_hand] = 1;
                clock_array[clock_hand] = f->fframe[page];
                clock_hand++;
                ++f->page_misses;
                break;
            }
            else
            {
                ref_array[clock_hand] = 0;
            }
            if (clock_hand < f->number_frames) clock_hand++;
            else clock_hand = 0;
            if (clock_hand == f->number_frames) ref_array[clock_hand] = 1;

        }
        if (idx2 != -1)
        {
            ++f->page_hits;
            ref_array[idx2] = 1;
        }
    }

    print_data(f, evict);

    // printf("Number of page accesses: %d\n", f->page_accesses);
    // printf("Number of page hits: %d\n", f->page_hits);
    // printf("Number of page misses: %d\n", f->page_misses);
    // printf("Evicted pages: [");
    // for (i = 1; i < evict.used; i++)
    // {
    //     if (i != evict.used - 1)
    //     {
    //         printf("%d, ", evict.array[i]);
    //     }
    //     else
    //     {
    //         printf("%d]\n", evict.array[i]);
    //     }
    // }
    freeArray(&evict);

    printf("\n\n");
}

int main(void)
{
    int run = 1;

    int val;

    stack = NULL;
    temp = temp1 = NULL;

    while (run == 1)
    {

        struct Frame_Data frame =
        {
            {
                0, 1, 2, 3,
                2, 4, 5, 3,
                4, 1, 6, 3,
                7, 8, 7, 8,
                4, 9, 7, 8,
                1, 2, 9, 5,
                4, 5, 0, 2
            }, 0, 0, 0, 0
        };
        struct Frame_Data *fr = &frame;

        printf("####################\n");
        printf("# Make a selection #\n");
        printf("####################\n\n");
        printf("NOTE: Only looking for single digits.\n");
        printf("      If more than 1 is entered, the\n");
        printf("      first digit is used.\n\n");
        printf("1 -- Least-Recently-Used (LRU)\n");
        printf("2 -- CLOCK Algorithm\n");
        printf("3 -- Quit\n\n");

        if ( get_int ( &val ) != BFALSE )
            if (val == 1)
            {
                lru(fr);
            }
            else if (val == 2)
            {
                clock_replace(fr);
            }
            else if (val == 3)
            {
                printf("GOOD BYE\n");
                run = 0;
            }
            else
            {
                /* Keep going */
            }
        else
        {
            printf("Invalid decision. Choose again.\n\n");
        }
    }

    return 0;
}
