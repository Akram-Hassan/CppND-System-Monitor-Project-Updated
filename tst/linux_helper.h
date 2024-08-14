#ifndef LINUX_HELPER_H
#define LINUX_HELPER_H

#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>


namespace LinuxHelper
{
    std::string exec(std::string cmd) {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
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

    int GetRandomPIDFor1000()
    {
        std::string command {"ps -eo pid,uid | awk '$2 == 1000 {print $1}' | shuf -n 1"};
        std::string pid = exec(command);
        
        return std::stoi(pid);
    }

    std::string Get1000UserName()
    {
        return exec("getent passwd 1000 | awk -F: '{print $1}'");
    }
}
#endif

