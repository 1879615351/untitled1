#include <iostream>
#include <thread>
#include <chrono>
#include "pin.hpp"
#include "Recorder.h"
using namespace std;
void writeFun(Pin::Tx<int> &&tx)
{
    int num = 0;
    while (true)
    {
        num++;
        if (tx.send(std::move(num)))
        {
            std::cout << "write " << num << std::endl;
        }
        if(num>=500)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds (1));
    }
}
int main()
{
        Pin::Tx<int> tx;
        Pin::Rx<int> rx;
       //使用该函数创建的rx和tx可以直接使用，使用Rx和Tx类直接创建的对象。
       //必须用setSource()初始化资源，否则空指针异常。
        std::tie(rx, tx) = Pin::getRxTx<int>();
        Recorder recorder(std::move(rx));
        recorder.start();
        std::thread t = std::thread(writeFun ,std::move(tx));
        std::this_thread::sleep_for(std::chrono::seconds(2));
        recorder.stop();
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        return 0;
}
