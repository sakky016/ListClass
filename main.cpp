#include "header.h"
#include "list.h"
#include "priority_list.h"
#include<signal.h>

#define RANDOM_NUMBER_MAX 100

#define DO_DELETION false
#define DO_SWAPPING true
#define DO_REVERSING true

unsigned int totalInserted = 0;
unsigned int totalDeleted = 0;
unsigned int totalSwapped = 0;
unsigned int totalReversed = 0;


//List list1;
PriorityList list1;


int generateRandomNumber()
{
    struct timeval tp;
    static int id = 1;
    time_t tm;

    /* Generate a random number */
    gettimeofday(&tp, NULL);
    srand(tp.tv_usec);
    int num = rand() % (RANDOM_NUMBER_MAX + 1);
    return num;
}

void displayStats()
{
    printf("\n");
    printf("+---------------------------------------------+\n");
    printf("|                STATISTICS                   |\n");
    printf("+---------------------------------------------+\n");
    printf("Total inserted   : %u\n", totalInserted);
    printf("Total reversed   : %u\n", totalReversed);
    printf("Total deleted    : %u\n", totalDeleted);
    printf("Total swapped    : %u\n", totalSwapped);
    printf("-----------------------------------------------\n");
    printf("\n");
}

/* This handler just makes sure the destructor is called for the list
   in case Ctr+C is pressed by the user. */
void intHandler(int signalType)
{
    list1.~List();
    printf("\n\n>> Terminating application...\n");
    exit (0);
}

int main()
{
    int retval = 0;
    int val = 0;
    time_t currTime = 0;
    time_t lastDisplayed = 0;

    signal(SIGINT, intHandler);

    while (1)
    {
        currTime = time(&currTime);
        val = generateRandomNumber();
        retval = list1.insert(val);
        if (SUCCESS == retval)
        {
            printf("\n%d inserted to list\n", val);
            totalInserted++;
            list1.display();
        }

        if (DO_REVERSING)
        {
            /* Reverse the list depending on random number outcome */
            val = generateRandomNumber();
            if (val < 50)
            {
                printf("Reverse List:\n");
                //list1.reverse();
                list1.reverseInGroups(3);
                totalReversed++;
                list1.display();
            }
        }

        if (DO_DELETION)
        {
            /* Generate a random number to delete */
            val = generateRandomNumber();
            printf("Delete %d... ", val);

            retval = list1.deleteAllNodesWithValue(val);
            if (0 != retval)
            {
                printf(">> %d occurance(s) of %d DELETED from list\n", retval, val);
                totalDeleted = totalDeleted + retval;
                list1.display();
            }
            else
            {
                printf("%d not found in list\n", val);
            }
        }

        if (DO_SWAPPING)
        {
            /* Swap 2 numbers */
            bool swapResult = false;
            int val1 = generateRandomNumber();
            int val2 = generateRandomNumber();
            printf("Swap %d and %d\n", val1, val2);
            swapResult = list1.swapNodes(val1, val2);
            if (swapResult)
            {
                printf(">> %d and %d SWAPPED\n", val1, val2);
                totalSwapped++;
                list1.display();
            }
            else
            {
                printf("Values not found. Could not swap\n");
            }
        }

        /* Display statistics */
        if (currTime - lastDisplayed >= DISPLAY_INTERVAL)
        {
            displayStats();
            lastDisplayed = currTime;
        }

    }

    return 0;
}
