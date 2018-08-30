//
// Created by tal on 18-8-29.
//

#ifndef GEN_VOICE_TF_TRANSFER_H
#define GEN_VOICE_TF_TRANSFER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <string>
#include <map>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

class Transfer {
public:
    explicit Transfer(const std::string &pinyin_file);

    ~Transfer();

    int get_code_point(const std::string &name);

    std::string get_pinyin(const std::string &word);

    std::string refactor_pinyin(const std::string &pinyin);

    std::vector<std::string> move_digit_backward(const std::string &replaced);

    std::vector<std::string> split_name(std::string name);

private:
    boost::property_tree::ptree pt;

    std::map<std::string, std::string> yindiao_dict = {
            {"ā", "a1"},
            {"á", "a2"},
            {"ǎ", "a3"},
            {"à", "a4"},
            {"ē", "e1"},
            {"é", "e2"},
            {"ě", "e3"},
            {"è", "e4"},
            {"ō", "o1"},
            {"ó", "o2"},
            {"ǒ", "o3"},
            {"ò", "o4"},
            {"ī", "i1"},
            {"í", "i2"},
            {"ǐ", "i3"},
            {"ì", "i4"},
            {"ū", "u1"},
            {"ú", "u2"},
            {"ǔ", "u3"},
            {"ù", "u4"},
            {"ü", "v"},
            {"ǖ", "v1"},
            {"ǘ", "v2"},
            {"ǚ", "v3"},
            {"ǜ", "v4"},
            {"ń", "n2"},
            {"ň", "n3"},
            {"ǹ", "n4"},
            {"ḿ", "m2"},

    };
};

#endif //TRANSFER_H
