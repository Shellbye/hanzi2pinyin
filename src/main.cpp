//
// Created by tal on 18-8-29.
//
#include "include/transfer.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <transfer.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0]
                  << " pinyin_config_file word" << std::endl;
        return 1;
    }

    const std::string pinyin_config_file = argv[1];
    const std::string word = argv[2];
    Transfer t(pinyin_config_file);
    std::cout << t.get_pinyin(word) << std::endl;
    return 0;
}
