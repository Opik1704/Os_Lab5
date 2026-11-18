#include <windows.h>
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

static int LoadLibraryFunctions(int libraryNumber, HMODULE* library, PiFunction* piFunction, SortFunction* sortFunction)
{
    const char* libraryName;
    HMODULE loadedLibrary;
    FARPROC functionAddress;
    DWORD errorCode;

    if (libraryNumber == 1)
    {
        libraryName = "AlgorithmLibrary1.dll";
    }
    else
    {
        libraryName = "AlgorithmLibrary2.dll";
    }

    loadedLibrary = LoadLibraryA(libraryName);

    if (loadedLibrary == NULL)
    {
        printf("LoadLibraryA failed. Windows error: %lu\n", GetLastError());
        return 0;
    }

    functionAddress = GetProcAddress(loadedLibrary, "Pi");

    if (functionAddress == NULL)
    {
        errorCode = GetLastError();
        if (!FreeLibrary(loadedLibrary))
        {
            printf("FreeLibrary failed. Windows error: %lu\n", GetLastError());
        }

        printf("Pi was not found. Windows error: %lu\n", errorCode);
        return 0;
    }

    *piFunction = (PiFunction)functionAddress;

    functionAddress = GetProcAddress(loadedLibrary, "Sort");

    if (functionAddress == NULL)
    {
        errorCode = GetLastError();
        if (!FreeLibrary(loadedLibrary))
        {
            printf("FreeLibrary failed. Windows error: %lu\n", GetLastError());
        }

        printf("Sort was not found. Windows error: %lu\n", errorCode);
        return 0;
    }

    *sortFunction = (SortFunction)functionAddress;
    *library = loadedLibrary;

    return 1;
}

static void PrintMenu(int libraryNumber)
{
    printf("\n");
    printf("Library: %d\n", libraryNumber);

    if (libraryNumber == 1)
    {
        printf("Pi: Leibniz; Sort: bubble sort\n");
    }
    else
    {
        printf("Pi: Wallis; Sort: quicksort\n");
    }

    printf("0         - switch library\n");
    printf("1 K       - calculate Pi\n");
    printf("2 N a1... - sort N integers\n");
    printf("q         - quit\n");
    printf("Command: ");
}

static void CalculatePi(PiFunction piFunction)
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

    printf("Pi: %.7f\n", piFunction(count));
}

static void SortNumbers(SortFunction sortFunction)
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

    int* sortedArray = sortFunction(array);

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
    HMODULE currentLibrary = NULL;
    PiFunction piFunction = NULL;
    SortFunction sortFunction = NULL;
    int currentLibraryNumber = 1;
    char command[16];

    if (!LoadLibraryFunctions(currentLibraryNumber, &currentLibrary, &piFunction, &sortFunction))
    {
        printf("Could not load the library.\n");
        return 1;
    }

    for (;;)
    {
        PrintMenu(currentLibraryNumber);

        if (scanf("%15s", command) != 1)
        {
            break;
        }

        if (strcmp(command, "q") == 0 || strcmp(command, "Q") == 0)
        {
            break;
        }

        if (strcmp(command, "0") == 0)
        {
            int newLibraryNumber = currentLibraryNumber == 1 ? 2 : 1;
            HMODULE newLibrary = NULL;
            PiFunction newPiFunction = NULL;
            SortFunction newSortFunction = NULL;

            if (LoadLibraryFunctions(newLibraryNumber, &newLibrary, &newPiFunction, &newSortFunction))
            {
                if (!FreeLibrary(currentLibrary))
                {
                    DWORD errorCode = GetLastError();
                    FreeLibrary(newLibrary);
                    printf("Could not unload the previous library. Windows error: %lu\n", errorCode);
                    printf("Library %d is still active.\n", currentLibraryNumber);
                }
                else
                {
                    currentLibrary = newLibrary;
                    piFunction = newPiFunction;
                    sortFunction = newSortFunction;
                    currentLibraryNumber = newLibraryNumber;
                    printf("Library %d loaded.\n", currentLibraryNumber);
                }
            }
            else
            {
                printf("Switch failed. Library %d is still active.\n", currentLibraryNumber);
            }
        }
        else if (strcmp(command, "1") == 0)
        {
            CalculatePi(piFunction);
        }
        else if (strcmp(command, "2") == 0)
        {
            SortNumbers(sortFunction);
        }
        else
        {
            printf("Unknown command.\n");
            ClearInputLine();
        }
    }

    if (currentLibrary != NULL && !FreeLibrary(currentLibrary))
    {
        printf("Could not unload the library. Windows error: %lu\n", GetLastError());
        return 1;
    }

    return 0;
}
