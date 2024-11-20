//
// Created by amir on 22.09.24.
//

#include <gtest/gtest.h>
#include <filter.h>

TEST(Filter, Test){
    std::vector<std::string> correct_output = {
            "1.1.234.8\n"
            "1.29.168.152\n"
            "1.70.44.170\n"
            "1.87.203.225\n"
            "1.231.69.33\n"
    };

    std::stringstream str;

    for(auto& it: correct_output)
        str << it;

    std::vector<ipv4_addr> ip_pool;

    for (std::string line; std::getline(str, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.emplace_back(split(v.at(0), '.'));
    }

    str.clear();
    filter_any(ip_pool, 29, str);

    std::string line;
    std::getline(str, line);

    ASSERT_TRUE(line == "1.29.168.152");

}

int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}