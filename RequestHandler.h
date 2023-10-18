﻿#pragma once

#include "ThreadPool.h"

class RequestHandler {
public:
    RequestHandler();
    ~RequestHandler();
    // отправка запроса на выполнение
    void pushRequest(FuncType f, int* array, int left, int right);
private:
    // пул потоков
    ThreadPool m_tpool;
};