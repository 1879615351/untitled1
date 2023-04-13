#pragma once
#include "concurrentqueue.h"
#include <tuple>
namespace Pin
{
    template<typename  T>
    class Base;
    template<typename  T>
    class Rx;
    template<typename  T>
    class Tx;
    template<typename  T>
    std::tuple<Rx<T> ,Tx<T>> getRxTx()
    {
        std::shared_ptr<moodycamel::ConcurrentQueue<T>> sp_lockfree_q =std::make_shared<moodycamel::ConcurrentQueue<T>>() ;
        std::shared_ptr<bool> isConnecting =std::make_shared<bool>(true);
        Rx<T> rx;
        Tx<T> tx;
        rx.setSource(sp_lockfree_q,isConnecting);
        tx.setSource(sp_lockfree_q,isConnecting);
        return std::make_tuple(std::move(rx),std::move(tx));
    }
    template<typename  T>
    void connect(Rx<T> &rx,Tx<T> &tx,std::shared_ptr<moodycamel::ConcurrentQueue<T>> sp_q)
    {
        std::shared_ptr<moodycamel::ConcurrentQueue<T>> sp_lockfree_q =std::make_shared<moodycamel::ConcurrentQueue<T>>();
        std::shared_ptr<bool> isConnecting =std::make_shared<bool>(true);
        rx.setSource(sp_lockfree_q,isConnecting);
        tx.setSource(sp_lockfree_q,isConnecting);
    }
}
template<typename  T>
class Pin::Base{
protected:
    std::shared_ptr<moodycamel::ConcurrentQueue<T>> msp_lockfree_q;
    std::shared_ptr<bool> m_isConnecting;
public:
    void setSource(std::shared_ptr<moodycamel::ConcurrentQueue<T>> p_lockfree_q,std::shared_ptr<bool> p_bool)
    {
        msp_lockfree_q.reset();
        msp_lockfree_q = p_lockfree_q;
        m_isConnecting = p_bool;
    }
};
template<typename  T>
class Pin::Rx:public Pin::Base<T>{
public:
    bool read(T & item)
    {
        return msp_lockfree_q->try_dequeue(item);
    }
    int  getBufferedNum()
    {
        return msp_lockfree_q->size_approx();
    }
    void disconnect()
    {
        *m_isConnecting = false;
    }
};
template<typename  T>
class Pin::Tx:public Pin::Base<T>{
public:
    bool send(T && item)
    {
        if(*m_isConnecting==true)
        {
            return msp_lockfree_q->try_enqueue(std::forward<T>(item));
        }
        else
        {
            return false;
        }
    }
};
