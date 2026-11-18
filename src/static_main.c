#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contracts.h"

static void ClearInputLine(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF)
    {
    }
}

static void PrintMenu(void)
{
    printf("\n");
    printf("1 K       - calculate Pi\n");
    printf("2 N a1... - sort N integers\n");
    printf("q         - quit\n");
    printf("Command: ");
}

static void CalculatePi(void)
{
    int count;

    printf("Number of terms: ");

    if (scanf("%d", &count) != 1)
    {
        printf("Invalid integer.\n");
        ClearInputLine();
        return;
    }

    ClearInputLine();

    if (count <= 0)
    {
        printf("The number of terms must be positive.\n");
        return;
    }

    printf("Pi: %.7f\n", Pi(count));
}

static void SortNumbers(void)
{
    int count;

    printf("Number of elements: ");

    if (scanf("%d", &count) != 1)
    {
        printf("Invalid integer.\n");
        ClearInputLine();
        return;
    }

    if (count < 0 || (size_t)count > (size_t)-1 / sizeof(int) - 1)
    {
        printf("Invalid number of elements.\n");
        ClearInputLine();
        return;
    }

    int* array = (int*)malloc(((size_t)count + 1) * sizeof(int));

    if (array == NULL)
    {
        printf("Memory allocation failed.\n");
        ClearInputLine();
        return;
    }

    array[0] = count;

    printf("Enter %d integers: ", count);

    for (int i = 1; i <= count; i++)
    {
        if (scanf("%d", &array[i]) != 1)
        {
            printf("Invalid array element.\n");
            free(array);
            ClearInputLine();
            return;
        }
    }

    ClearInputLine();

    int* sortedArray = Sort(array);

    if (sortedArray == NULL)
    {
        printf("Sorting failed.\n");
        free(array);
        return;
    }

    printf("Sorted: ");

    for (int i = 1; i <= count; i++)
    {
        printf("%d", sortedArray[i]);

        if (i < count)
        {
            printf(" ");
        }
    }

    printf("\n");
    free(array);
}

int main(void)
{
    char command[16];

    for (;;)
    {
        PrintMenu();

        if (scanf("%15s", command) != 1)
        {
            break;
        }

        if (strcmp(command, "q") == 0 || strcmp(command, "Q") == 0)
        {
            break;
        }

        if (strcmp(command, "1") == 0)
        {
            CalculatePi();
        }
        else if (strcmp(command, "2") == 0)
        {
            SortNumbers();
        }
        else
        {
            printf("Unknown command.\n");
            ClearInputLine();
        }
    }

    return 0;
}
