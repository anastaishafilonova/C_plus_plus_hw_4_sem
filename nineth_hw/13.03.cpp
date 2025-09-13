#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

enum class procstatus {suspended, running, stopped, zombie};

std::map<procstatus, std::string> procstatus_string = {
    {procstatus::suspended, "suspended"},
    {procstatus::running, "running"},
    {procstatus::stopped, "stopped"},
    {procstatus::zombie, "zombie"}
};

struct procinfo {
    int id;
    std::string name;
    procstatus status;
    std::string owner;
};

void print_processes(std::vector<procinfo> processes) {
    std::sort(
        std::begin(processes), std::end(processes),
        [](procinfo const & p1, procinfo const & p2) {
            return p1.name < p2.name; 
        }
    );
    for (auto const & p : processes) {
        std::cout << std::left << std::setw(25) << std::setfill(' ') << p.name;
        std::cout << std::left << std::setw(8) << std::setfill(' ') << p.id;
        std::cout << std::left << std::setw(12) << std::setfill(' ') << procstatus_string[p.status];
        std::cout << std::left << std::setw(15) << std::setfill(' ') << p.owner;
        std::cout << std::endl;
    }
}

int main() {
    using namespace std::string_literals;
    std::vector<procinfo> processes {
        {512, "a.out"s, procstatus::zombie, "username"s},
        {1044, "chrome.exe"s, procstatus::running, "root"s},
        {7108, "explorer.exe"s, procstatus::running, "root"s},
        {10100, "yandex.exe"s, procstatus::running, "root"s},
        {22456, "skype.exe"s, procstatus::suspended, "root"s},
    };
    print_processes(processes);
}
