#include "processor.h"
#include "linux_parser.h"

Processor::Processor() : cpuData_{linuxParser_.CpuData()}
{
}

float Processor::Utilization()
{ 
    auto now = CpuData(linuxParser_.CpuData());
    int totald = now.Total() - cpuData_.Total();

    if(totald == 0)
        return static_cast<float>(now.Total() - now.Idle()) / now.Total();

    int idled = now.Idle() - cpuData_.Idle();

    cpuData_ = now;

    return static_cast<float>(totald - idled)/totald ;
}