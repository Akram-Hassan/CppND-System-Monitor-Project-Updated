#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "cpu_data.h"
#include "linux_parser.h"

class Processor {
 public:
    Processor();
    float Utilization();  // TODO: See src/processor.cpp

 private:
    LinuxParser::LinuxParser linuxParser_{};
    CpuData cpuData_;
};

#endif