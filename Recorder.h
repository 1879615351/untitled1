#ifndef UNTITLED1_RECORDER_H
#define UNTITLED1_RECORDER_H
#include "pin.hpp"
class Recorder{
    Pin::Rx<int> m_rx;
    std::thread m_thread;
    bool isCanRunning = false;
public:
    Recorder(Pin::Rx<int> &&rx)
    {
        m_rx = rx;
    }
    void run();
    void start();
    void stop();
};
#endif //UNTITLED1_RECORDER_H
