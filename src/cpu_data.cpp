#include <vector>

#include "cpu_data.h"

CpuData::CpuData(std::vector<int> cpu_data)
{
    user = cpu_data[static_cast<int>(CpuDataField::user)];
    nice = cpu_data[static_cast<int>(CpuDataField::nice)];
    system = cpu_data[static_cast<int>(CpuDataField::system)];
    idle = cpu_data[static_cast<int>(CpuDataField::idle)];
    iowait = cpu_data[static_cast<int>(CpuDataField::iowait)];
    irq = cpu_data[static_cast<int>(CpuDataField::irq)];
    softirq = cpu_data[static_cast<int>(CpuDataField::softirq)];
    steal = cpu_data[static_cast<int>(CpuDataField::steal)];
}

int CpuData::Total()
{
    return user + nice + system + idle + iowait + irq + softirq + steal;
}

int CpuData::Idle()
{
    return idle + iowait;
}