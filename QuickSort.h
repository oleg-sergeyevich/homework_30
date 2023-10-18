#pragma once

#include <algorithm>

#include "RequestHandler.h"

bool make_thread = true;

void quicksort(int* array, int left, int right) {
    if (left >= right) return;
    int left_bound = left;
    int right_bound = right;
    int middle = array[(left_bound + right_bound) / 2];

    do {
        while (array[left_bound] < middle) {
            left_bound++;
        }
        while (array[right_bound] > middle) {
            right_bound--;
        }

        //Меняем элементы местами
        if (left_bound <= right_bound) {
            std::swap(array[left_bound], array[right_bound]);
            left_bound++;
            right_bound--;
        }
    } while (left_bound <= right_bound);

    if (true == make_thread && right_bound - left > 10000)
    {
        RequestHandler pool;
        pool.pushRequest(quicksort, array, left, right_bound);
        pool.pushRequest(quicksort, array, left_bound, right);
    }
    else {
        quicksort(array, left, right_bound);
        quicksort(array, left_bound, right);
    }
}