#include <iostream>
#include <chrono>
#include <ctime>
#include <random>

#include "QuickSort.h"

using namespace std::chrono;

int main()
{
    srand(time(0));
    int size = 100000000;
    int* array = new int[size];
    int* array_copy = new int[size];

    for (long i = 0; i < size; i++)
    {
        array[i] = rand() % 100;
        array_copy[i] = array[i];
    }
    
    // многопоточный запуск
    auto t_start = system_clock::now();
    {
        RequestHandler pool;
        pool.pushRequest(quicksort, array, 0, size - 1);
    }
    auto t_end = system_clock::now();
    auto time = duration_cast<milliseconds>(t_end - t_start).count();
    std::cout << "threads, time: " << time << std::endl;

    for (int i = 0; i < size - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            std::cout << "Unsorted" << std::endl;
            break;
        }
    }
    delete[] array;


    // однопоточный запуск
    make_thread = false;
    t_start = system_clock::now();
    quicksort(array_copy, 0, size - 1);
    t_end = system_clock::now();
    time = duration_cast<milliseconds>(t_end - t_start).count();
    std::cout << "1 thread, time: " << time << std::endl;

    for (int i = 0; i < size - 1; i++)
    {
        if (array_copy[i] > array_copy[i + 1])
        {
            std::cout << "Unsorted" << std::endl;
            break;
        }
    }
    delete[] array_copy;

    return 0;
}