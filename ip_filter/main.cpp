//
// Created by amir on 21.09.24.
//

#include <vector>
#include "filter.h"


int main(int argc, char const *argv[]) {

    std::vector<ipv4_addr> ip_pool;

    for (std::string line; std::getline(std::cin, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.emplace_back(split(v.at(0), '.'));
    }

    std::sort(ip_pool.begin(), ip_pool.end());

    std::reverse(ip_pool.begin(), ip_pool.end());

    /// print sorted list
    std::for_each(ip_pool.begin(), ip_pool.end(), [](ipv4_addr& ip){ip.print();});

    filter(ip_pool, 1);
    filter(ip_pool, 46, 70);
    filter_any(ip_pool, 46);

    return 0;
}

