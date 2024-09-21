//
// Created by amir on 21.09.24.
//

#ifndef IP_FILTER_SORT_H
#define IP_FILTER_SORT_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

//using ipv4_addr = std::vector<std::string>;

struct ipv4_addr{

    struct OutOfRange{
        int index;
    };

    ipv4_addr(std::vector<std::string>& ip):ip{ip}
    {
        for (auto& octet: ip) {
            ip_decimal.emplace_back(std::atoi(octet.c_str()));
        }
    }

    void print(){
        for(std::vector<std::string>::const_iterator ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
        {
            if (ip_part != ip.cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }

    bool operator>(ipv4_addr& other){
        int i = 0;
        for ( ; (*this)[i] == other[i] && i < 4 ; i++)
            ;
        if(i < 4){
            return (*this)[i] > other[i];
        }

        return false;
    }

    char operator[](uint8_t index){
        try{
            if(index < ip_decimal.size())
                return ip_decimal[index];
            else
                throw OutOfRange{.index = index};
        }
        catch (OutOfRange& ex){
            std::cout << "Index is out of range " << ex.index << std::endl;
        }

    }

    std::vector<std::string> ip;
    std::vector<uint8_t> ip_decimal;

};

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


std::vector<ipv4_addr> create_ip_pool(const std::string filename) {

    try {

        std::ifstream in(filename);

        std::vector<std::vector<std::string> > ip_pool;

        for (std::string line; std::getline(std::cin, line);) {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }
        return ip_pool;
    }

    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}


void filter(std::vector<ipv4_addr>& pool, int octet){
    std::for_each()
}

#endif //IP_FILTER_SORT_H
