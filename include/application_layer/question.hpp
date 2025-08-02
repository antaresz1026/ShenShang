#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <optional>

namespace shenshang::question {

    enum class QuestionType {
        SingleChoice,
        MultipleChoice,
        TrueOrFalse,
        Unknown
    };

    inline QuestionType questionTypeFromStr(const std::string& type) {
        static std::unordered_map<std::string, QuestionType> map = {
            {"单选题", QuestionType::SingleChoice},
            {"多选题", QuestionType::MultipleChoice},
            {"判断题", QuestionType::TrueOrFalse}
        };
        auto it = map.find(type);
        return it != map.end() ? it->second : QuestionType::Unknown;
    }

    inline std::string descQuestionType(QuestionType type) {
        switch (type) {
            case QuestionType::SingleChoice: return "单选题";
            case QuestionType::MultipleChoice: return "多选题";
            case QuestionType::TrueOrFalse:   return "判断题";
            default: return "未知";
        }
    }

    struct Question {
        int id;
        QuestionType type;
        std::string difficulty;
        std::string consistency;
        std::vector<std::string> knowledgeTags; 
        std::string description;
        std::map<std::string, std::string> options;
        std::vector<std::string> answers;
        double score = 1.0;
        std::string explanation;
        std::string source;
        std::string errorInfo;

        bool checkAnswer(const std::vector<std::string>& userAnswer) const {
            return userAnswer == answers;
        }
    };
}