#include "Recorder.h"
#include <iostream>
#include <chrono>
#include <thread>
void Recorder::run()
{
     while(true)
     {
          int num=0;
          if(m_rx.read(num))
          {
              std::cout<<"record num: "<<num<<std::endl;
          }
         std::this_thread::sleep_for(std::chrono::milliseconds(1));
         if(!isCanRunning&&(m_rx.getBufferedNum()==0)) //退出且读取完毕
         {
             break;
         }
     }
     std::cout<<"recorder end";
}
void Recorder::start()
{
    isCanRunning = true;
    m_thread = std::thread(&Recorder::run,this);
}
void Recorder::stop()
{
    isCanRunning = false;
    m_rx.disconnect();
    m_thread.detach();
}