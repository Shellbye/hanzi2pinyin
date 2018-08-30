//
// Created by tal on 18-8-29.
//
#include "transfer.h"
#include <iostream>
#include <codecvt>


Transfer::Transfer(const std::string &pinyin_file) {
    boost::property_tree::ini_parser::read_ini(pinyin_file, pt);

    boost::log::add_file_log
            (
                    boost::log::keywords::auto_flush = true,
                    boost::log::keywords::file_name = "gen_voice_tf.log",
                    boost::log::keywords::format = "[%TimeStamp%]: %Message%"
            );
    boost::log::add_common_attributes();

    int log_level = pt.get<int>("log_level", 4);
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= log_level);

}

Transfer::~Transfer() {}

std::string Transfer::get_pinyin(const std::string &word) {
    std::string ret;
    std::vector<std::string> words = split_name(word);
    for (auto const &w : words) {
        // chinese character to code point
        int code_point = get_code_point(w);

        // use code point to get pinyin

        std::string pinyin = pt.get<std::string>(std::to_string(code_point));
        // adjust digit position
        std::string replaced = refactor_pinyin(pinyin);
        // move digit backwards
        std::vector<std::string> result = move_digit_backward(replaced);
        ret.append(result[0]); // for those has many, pick the first one
        ret.append(" ");
    }
    ret.append(".");
    return ret;
}


std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int Transfer::get_code_point(const std::string &name) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cv;
    auto str32 = cv.from_bytes(name);
    int name_code_point = 0;
    for (auto c : str32)
        name_code_point = uint_least32_t(c);
    return name_code_point;
}

std::string Transfer::refactor_pinyin(const std::string &pinyin) {
    std::vector<std::string> results = split(pinyin, ' ');
    std::string replaced;
    for (auto const &s : results) {
        std::string unit = s;
        if (yindiao_dict.find(s) != yindiao_dict.end()) {
            unit = yindiao_dict[s];
        }
        replaced += unit;
    }
    return replaced;
}

std::vector<std::string> Transfer::move_digit_backward(const std::string &replaced) {
    // std::string replaced2 = "ba4i,b1o";
    std::vector<std::string> results2 = split(replaced, ',');
    std::vector<std::string> ret;
    for (auto a : results2) {
        for (auto n : {"1", "2", "3", "4"}) {
            auto found = a.find(n);
            if (found != std::string::npos) {
                a.replace(found, 1, "");
                a += n;
                ret.push_back(a);
            }
        }
    }
    return ret;
}

std::vector<std::string> Transfer::split_name(std::string name) {
    std::vector<std::string> words;
    for (size_t j = 0; j < name.length();) {
        size_t cplen = 1;
        if ((name[j] & 0xf8) == 0xf0)
            cplen = 4;
        else if ((name[j] & 0xf0) == 0xe0)
            cplen = 3;
        else if ((name[j] & 0xe0) == 0xc0)
            cplen = 2;
        if ((j + cplen) > name.length())
            cplen = 1;
        words.push_back(name.substr(j, cplen));
        j += cplen;
    }
    return words;
}
