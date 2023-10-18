﻿#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

template<class T>
class BlockedQueue {
public:
    void push(T& item) {
        lock_guard<mutex> l(m_locker);
        // обычный потокобезопасный push
        m_task_queue.push(std::move(item));
        // делаем оповещение, чтобы поток, вызвавший
        // pop проснулся и забрал элемент из очереди
        m_notifier.notify_one();
    }
    // блокирующий метод получения элемента из очереди
    void pop(T& item) {
        unique_lock<mutex> l(m_locker);
        if (m_task_queue.empty())
            // ждем, пока вызовут push
            m_notifier.wait(l, [&] {return !m_task_queue.empty(); });
        item = std::move(m_task_queue.front());
        m_task_queue.pop();
    }
    // неблокирующий метод получения элемента из очереди
    // возвращает false, если очередь пуста
    bool fast_pop(T& item) {
        lock_guard<mutex> l(m_locker);
        if (m_task_queue.empty())
            // просто выходим
            return false;
        // забираем элемент
        item = std::move(m_task_queue.front());
        m_task_queue.pop();
        return true;
    }
private:
    // очередь задач
    queue<T> m_task_queue;
    mutex m_locker;
    // уведомитель
    condition_variable m_notifier;
};