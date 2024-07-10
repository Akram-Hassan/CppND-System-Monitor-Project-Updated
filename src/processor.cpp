#include "processor.h"
#include "linux_parser.h"

Processor::Processor() : cpuData_{LinuxParser::CpuData()}
{
}

float Processor::Utilization()
{ 
    auto now = CpuData(LinuxParser::CpuData());
    int totald = now.Total() - Processor::cpuData_.Total();

    if(totald == 0)
        return static_cast<float>(now.Total() - now.Idle()) / now.Total();

    int idled = now.Idle() - Processor::cpuData_.Idle();

    cpuData_ = now;

    return static_cast<float>(totald - idled)/totald ;
}