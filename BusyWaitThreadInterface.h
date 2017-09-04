#ifndef BUSYWAITTHREADINTERFACE_H
#define BUSYWAITTHREADINTERFACE_H
#include <atomic>
#include <thread>
class BusyWaitThreadInterface
{
public:

    BusyWaitThreadInterface(){}
    virtual ~BusyWaitThreadInterface(){}

    virtual int runThreadCollectData() = 0;
    virtual int stopThreadCollectData() = 0;

protected:
    std::thread _thread;
    std::atomic<bool> _stopThread;
};

#endif // BUSYWAITTHREADINTERFACE_H
