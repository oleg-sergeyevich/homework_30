#include "RequestHandler.h"

RequestHandler::RequestHandler() {
    m_tpool.start();
}

RequestHandler::~RequestHandler() {
    m_tpool.stop();
}

void RequestHandler::pushRequest(FuncType f, int* array, int left, int right) {
    m_tpool.push_task(f, array, left, right);
}