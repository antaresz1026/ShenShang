#include "application_layer/question.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <locale>

using namespace shenshang::question;

namespace shenshang::parser {

    std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> tokens;
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            if (!item.empty())
                tokens.push_back(item);
        }
        return tokens;
    }

    std::vector<Question> parseCSV(const std::string& filepath) {
        std::ifstream fin(filepath);
        if (!fin.is_open()) throw std::runtime_error("无法打开文件：" + filepath);

        std::string line;
        std::getline(fin, line); // 跳过表头

        std::vector<Question> result;
        int idCounter = 1;

        while (std::getline(fin, line)) {
            std::stringstream ss(line);
            std::vector<std::string> fields;
            std::string field;

            while (std::getline(ss, field, ',')) {
                fields.push_back(field);
            }

            if (fields.size() < 18) continue;

            Question q;
            q.id = idCounter++;
            q.type = questionTypeFromStr(fields[0]);
            q.difficulty = fields[1];
            q.consistency = fields[2];
            for (int i = 3; i <= 6; ++i) {
                if (!fields[i].empty())
                    q.knowledgeTags.push_back(fields[i]);
            }
            q.description = fields[7];
            q.answers = split(fields[8], ',');
            try {
                q.score = std::stod(fields[9]);
            } catch (...) {
                q.score = 1.0;
            }

            char opt = 'A';
            for (int i = 10; i <= 14; ++i, ++opt) {
                if (!fields[i].empty()) {
                    q.options[std::string(1, opt)] = fields[i];
                }
            }

            q.explanation = fields[15];
            q.source = fields[16];
            q.errorInfo = fields[17];

            result.push_back(q);
        }
        return result;
    }
}