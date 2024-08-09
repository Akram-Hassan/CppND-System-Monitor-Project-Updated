#include <gtest/gtest.h>
#include <filesystem>
#include <vector>

#include "process.h"
#include "system.h"

TEST(ProcessTests, CreateProcess) {

    Process proc(3);

    ASSERT_EQ(3, proc.Pid());
}


std::vector<int> GetSysPIDS()
{
    const std::filesystem::path proc{"/proc"};
    std::vector<int> result{};

    for (auto const& dir_entry : std::filesystem::directory_iterator{proc})
    {
        std::string file_name(dir_entry.path().filename().string());
        if(std::all_of(file_name.begin(), file_name.end(),isdigit))
        {
            result.push_back(std::stoi(file_name));
        } 
    }

    return result;
}

TEST(ProcessTests, PIDList)
{
    System sys{};
    auto plist = sys.Processes();
    auto pids = GetSysPIDS();

    ASSERT_EQ(pids.size(), plist.size());

    bool valid{true};
    for(int i=0; i < plist.size(); i++)
    {
        if(plist[i].Pid() != pids[i])
        {
            valid = false;
            break;
        }
    }

    ASSERT_TRUE(valid);
}

TEST(ProcessTests, ProcessCount)
{
    System sys{};
    auto total = sys.TotalProcesses();
    auto pids = GetSysPIDS();

    ASSERT_EQ(pids.size(), total);
}