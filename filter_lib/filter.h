//
// Created by amir on 21.09.24.
//

#ifndef IP_FILTER_SORT_H
#define IP_FILTER_SORT_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <optional>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]



struct ipv4_addr{

    struct OutOfRange{
        int index;
    };

    ipv4_addr(std::vector<std::string> ip);

    void print(std::stringstream& stream);

    void print();

    bool operator>(ipv4_addr& other);

    bool operator<(ipv4_addr& other);

    int operator[](uint8_t index);

    std::vector<std::string> ip;
    std::vector<uint8_t> ip_decimal;

};

std::vector<std::string> split(const std::string &str, char d);

std::vector<ipv4_addr> create_ip_pool(const std::string filename);

void filter(std::vector<ipv4_addr>& pool, uint8_t octet);

void filter(std::vector<ipv4_addr>& pool, uint8_t octet_1, uint8_t octet_2);

void filter_any(std::vector<ipv4_addr>& pool, uint8_t octet);

/// если хотим выводить результат в файл
void filter(std::vector<ipv4_addr>& pool, uint8_t octet, std::stringstream& stream);

void filter(std::vector<ipv4_addr>& pool, uint8_t octet_1, uint8_t octet_2, std::stringstream& stream);

void filter_any(std::vector<ipv4_addr>& pool, uint8_t octet, std::stringstream& stream);


#endif //IP_FILTER_SORT_H
