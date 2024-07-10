#ifndef PROCESSOR_DATA_H
#define PROCESSOR_DATA_H

#include <vector>

enum class CpuDataField
{
    user = 0,
    nice,
    system,
    idle,
    iowait,
    irq,
    softirq,
    steal,
    guest,
    guest_nice
};

class CpuData {
 public:
    CpuData(std::vector<int> linux_data);
    
    int Total();
    int Idle();

 private:
    int user{};
    int nice{};
    int system{};
    int idle{};
    int iowait{};
    int irq{};
    int softirq{};
    int steal{};
};

#endif