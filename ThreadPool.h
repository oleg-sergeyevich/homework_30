#pragma once

#include <vector>
#include <thread>
#include <future>

#include "Queue.h"

// удобное определение для сокращения кода
using task_type = function<void()>;
// тип указатель на функцию, которая является эталоном для функций задач
using FuncType = void (*) (int* ,int, int);

// пул потоков
class ThreadPool {
public:
    ThreadPool();
    ~ThreadPool() = default;
    // запуск:
    void start();
    // прерывание:
    void stop();
    // проброс задач
    void push_task(FuncType f, int* array, int left, int right);
    // функция входа для потока
    void threadFunc(size_t qindex);
private:
    // количество потоков
    int m_thread_count = 0;
    // потоки
    vector<thread> m_threads;
    // очереди задач для потоков
    vector<BlockedQueue<task_type>> m_thread_queues;
    // для равномерного распределения задач
    int m_index = 0;
};