#pragma once
#include <vector>
#include <functional>
#include "Record.hpp"

void recordsSort(std::vector<Record>& arr, std::function<bool(Record&, Record&)> predicate)
{
    for (std::size_t i = 0; i + 1 < arr.size(); i++)
        // Last i elements are already in place
        for (std::size_t j = 0; j + 1 < arr.size() - i; j++)
            if (predicate(arr[j], arr[j+1]))
                std::swap(arr[j], arr[j + 1]);
}
