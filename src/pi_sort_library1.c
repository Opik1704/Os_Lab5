#include "contracts.h"
// Вычисление числа Pi по формуле Валлиса: Pi = 2 * (4/3 * 16/15 * 36/35 * ...).
float Pi(int K)
{
    if (K <= 0)
    {
        return -1.0f;
    }

    long double sum = 0.0L;

    for (int i = 0; i < K; i++)
    {
        long double term = 1.0L / (2.0L * i + 1.0L);

        if (i % 2 == 0)
        {
            sum += term;
        }
        else
        {
            sum -= term;
        }
    }

    return (float)(4.0L * sum);
}

int* Sort(int* array)
{
    if (array == NULL || array[0] < 0)
    {
        return NULL;
    }

    int count = array[0];

    for (int i = 1; i < count; i++)
    {
        for (int j = 1; j < count - i + 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temporary = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temporary;
            }
        }
    }

    return array;
}
