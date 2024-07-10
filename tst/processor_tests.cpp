#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

#include "linux_parser.h"
#include "processor.h"
#include "cpu_data.h"


TEST(ProcessorTests, ReadProcessorData) {
    std::ifstream file{"/proc/stat"};
    std::string expectedLine{};

    std::getline(file, expectedLine);

    std::cout << expectedLine << "\n";

    std::vector<int> cpuData = LinuxParser::CpuData();
    std::string readLine{"cpu  "};
    for(auto& value: cpuData)
    {
        readLine += std::to_string(value) + " ";
    }
    
    ASSERT_STREQ((expectedLine + " ").c_str(), readLine.c_str());
}

TEST(ProcessorTests, TestCalculateIdle) {
    std::vector<int> cpuData {
            1,2,3,4,5,6,7,8,9,10
    };

    CpuData cpuDataObj {cpuData};

    EXPECT_EQ(
        cpuDataObj.Idle(),
        cpuData[static_cast<int>(CpuDataField::idle)] +
        cpuData[static_cast<int>(CpuDataField::iowait)]
        );

}

TEST(ProcessorTests, TestCalculateTotal) {
    std::vector<int> cpuData {
            1,2,3,4,5,6,7,8,9,10
    };


    CpuData cpuDataObj {cpuData};

    EXPECT_EQ(
        cpuDataObj.Total(),
        cpuData[static_cast<int>(CpuDataField::user)] +
        cpuData[static_cast<int>(CpuDataField::nice)] +
        cpuData[static_cast<int>(CpuDataField::system)] +
        cpuData[static_cast<int>(CpuDataField::idle)] +
        cpuData[static_cast<int>(CpuDataField::iowait)] +
        cpuData[static_cast<int>(CpuDataField::irq)] +
        cpuData[static_cast<int>(CpuDataField::softirq)] +
        cpuData[static_cast<int>(CpuDataField::steal)]
        );

}

TEST(ProcessorTests, TestCalculateUtilizationInitial) {
    Processor processor{};
    auto cpuData = CpuData(LinuxParser::CpuData());

    auto expected_utilization = static_cast<float>((cpuData.Total()- cpuData.Idle())) / cpuData.Total();
    EXPECT_FLOAT_EQ(expected_utilization,  processor.Utilization());
}

TEST(ProcessorTests, TestCalculateUtilization) {
    auto cpuDataBefore = CpuData(LinuxParser::CpuData());
    Processor processor;

    sleep(3);

    auto cpuDataAfter = CpuData(LinuxParser::CpuData());

    int totald = cpuDataAfter.Total() - cpuDataBefore.Total();
    int idled = cpuDataAfter.Idle() - cpuDataBefore.Idle();

    float expected_utilization = static_cast<float>(totald- idled)/totald;

    EXPECT_FLOAT_EQ(expected_utilization, processor.Utilization());
}