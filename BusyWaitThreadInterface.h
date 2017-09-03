#ifndef BUSYWAITTHREADINTERFACE_H
#define BUSYWAITTHREADINTERFACE_H
#include <atomic>

class BusyWaitThreadInterface
{
public:
    enum TStatus
    {
        OK,
        BAD
    };
    BusyWaitThreadInterface();
    virtual ~BusyWaitThreadInterface();

    virtual runThreadCollectData() = 0;
    virtual stopThreadCollectData() = 0;

protected:
    std::thread _thread;
    std::atomic<bool> _stopThread;
};

#endif // BUSYWAITTHREADINTERFACE_H
