#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>

class Timer
{
    std::thread Thread;
    bool Alive = false;
    long CallNumber = -1L;
    long repeat_count = -1L;

    std::chrono::milliseconds interval = std::chrono::milliseconds(0);

    std::function<void(void)> funct = nullptr;

    void sleepAndRun()
    {
        std::this_thread::sleep_for(interval);
        if(Alive)
            Function()();
    }

    void ThreadFunc()
    {
        if(CallNumber == Infinite)
            while(Alive)
                sleepAndRun();
        else
            while(repeat_count--)
                sleepAndRun();
    }

public:
    static const long Infinite = -1L;

    Time(){};

    Timer(const std::function<void(void)> &f) : funct(f) {}

    Timer(const std::function<void(void)> &f,
          const unsigned long &i,
          const long repeat = Timer::Infinite) : funct(f),
                                                 interval(std::chrono::milliseconds(i)),
                                                 CallNumber(repeat) {}

    void Start(bool Async = true)
    {
        if(isAlive())
            return;
        Alive = true;
        repeat_count = CallNumber;
        if(Async)
            Thread = std::thread(ThreadFunc(), this);
        else
            this->ThreadFunc();
    }

    void Stop()
    {
        Alive = false;
        Thread.join();
    }

    void SetFunction(const std::function<void(void)> &f)
    {
        funct = f;
    }

    bool isAlive() const {return Alive;}

    void RepeatCount(const long r)
    {
        if(Alive)
            return;
        CallNumber = r;
    }

    long getLeftCount() const {return repeat_count;}

    long repeatCount() const {return CallNumber;}

    void setInterval(const unsigned long &i)
    {
        if(Alive)
            return;
        interval = std::chrono::milliseconds(i);
    }
};

#endif // TIMER_H
