#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "cpu_data.h"

class Processor {
 public:
    Processor();
    float Utilization();  // TODO: See src/processor.cpp

 private:
    CpuData cpuData_;
};

#endif