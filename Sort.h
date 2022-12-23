#pragma once
#include <vector>
#include <functional>
#include "Record.h"

class Sort
{
public:
    static void swap(Record* x, Record* y)
    {
        Record temp = *x;
        *x = *y;
        *y = temp;
    }
    
    // A function to implement bubble sort
    static void bubbleSort(std::vector<Record>& arr, std::function<bool(Record&, Record&)> predicate)
    {
        int i, j;
        int n = arr.size();

        for (i = 0; i < n - 1; i++)

            // Last i elements are already in place
            for (j = 0; j < n - i - 1; j++)
                if (predicate(arr[i], arr[j]))
                    swap(&arr[j], &arr[j + 1]);
    }
};

