//
// Created by amir on 22.09.24.
//

#include "filter.h"

ipv4_addr::ipv4_addr(std::vector<std::string> ip):ip{ip}
{
    for (auto& octet: ip) {
        ip_decimal.emplace_back(std::atoi(octet.c_str()));
    }
}

void ipv4_addr::print(std::stringstream& str){
    for(std::vector<std::string>::iterator ip_part = ip.begin(); ip_part != ip.end(); ++ip_part)
    {
        if (ip_part != ip.cbegin())
        {
            str << ".";
        }
        str << *ip_part;
    }
    str << std::endl;
}

void ipv4_addr::print() {
    for (std::vector<std::string>::const_iterator ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {
        if (ip_part != ip.cbegin()) {
            std::cout << ".";
        }
        std::cout << *ip_part;
    }
    std::cout << std::endl;
}


bool ipv4_addr::operator>(ipv4_addr& other){
    int i = 0;
    for ( ; i < 4 && (*this)[i] == other[i]  ; i++)
        ;
    if(i < 4){
        return (*this)[i] > other[i];
    }
    return false;
}

bool ipv4_addr::operator<(ipv4_addr& other){
    return other > *this;
}

int ipv4_addr::operator[](uint8_t index){
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

        std::ifstream in;

        in.open(filename);

        // check stream status
        if (!in) std::cerr << "Can't open input file! " << filename;

        std::vector<ipv4_addr> ip_pool;

        for (std::string line; std::getline(in, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.emplace_back(split(v.at(0), '.'));
        }
        return ip_pool;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}


void filter(std::vector<ipv4_addr>& pool, uint8_t octet){
    std::for_each(pool.begin(), pool.end(), [octet](ipv4_addr& ip){
        if(ip[0] == octet)
            ip.print();
    });
}

void filter(std::vector<ipv4_addr>& pool, uint8_t octet_1, uint8_t octet_2){
    std::for_each(pool.begin(), pool.end(), [octet_1, octet_2](ipv4_addr& ip){
        if(ip[0] == octet_1 && ip[1] == octet_2)
            ip.print();
    });
}

void filter_any(std::vector<ipv4_addr>& pool, uint8_t octet){
    std::for_each(pool.begin(), pool.end(), [octet](ipv4_addr& ip){
        if(ip[0] == octet || ip[1] == octet || ip[2] == octet || ip[3] == octet)
            ip.print();
    });
}


void filter(std::vector<ipv4_addr>& pool, uint8_t octet, std::stringstream& stream){
    std::for_each(pool.begin(), pool.end(), [octet, &stream](ipv4_addr& ip){
        if(ip[0] == octet)
            ip.print(stream);
    });
}

void filter(std::vector<ipv4_addr>& pool, uint8_t octet_1, uint8_t octet_2, std::stringstream& stream){
    std::for_each(pool.begin(), pool.end(), [octet_1, octet_2, &stream](ipv4_addr& ip){
        if(ip[0] == octet_1 && ip[1] == octet_2)
            ip.print(stream);
    });
}

void filter_any(std::vector<ipv4_addr>& pool, uint8_t octet, std::stringstream& stream){
    std::for_each(pool.begin(), pool.end(), [octet, &stream](ipv4_addr& ip){
        if(ip[0] == octet || ip[1] == octet || ip[2] == octet || ip[3] == octet)
            ip.print(stream);
    });
}