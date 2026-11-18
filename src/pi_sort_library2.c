#include "contracts.h"

static void QuickSort(int* array, int left, int right)
{
    int i = left;
    int j = right;
    int pivot = array[left + (right - left) / 2];

    while (i <= j)
    {
        while (array[i] < pivot)
        {
            i++;
        }

        while (array[j] > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            int temporary = array[i];
            array[i] = array[j];
            array[j] = temporary;
            i++;
            j--;
        }
    }

    if (left < j)
    {
        QuickSort(array, left, j);
    }

    if (i < right)
    {
        QuickSort(array, i, right);
    }
}
// Вычисление числа Pi по формуле Валлиса: Pi = 2 * (4/3 * 16/15 * 36/35 * ...).
float Pi(int K)
{
    if (K <= 0)
    {
        return -1.0f;
    }

    long double product = 1.0L;

    for (long long n = 1; n <= K; n++)
    {
        long double number = (long double)n;
        long double numerator = 4.0L * number * number;
        product *= numerator / (numerator - 1.0L);
    }

    return (float)(2.0L * product);
}

int* Sort(int* array)
{
    if (array == NULL || array[0] < 0)
    {
        return NULL;
    }

    int count = array[0];

    if (count > 1)
    {
        QuickSort(array, 1, count);
    }

    return array;
}
