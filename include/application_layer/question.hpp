#include <string>
#include <map>
#include <unordered_map>
#include <vector>

enum class QuestionType {
    SingleChoice,
    MultileChoice,
    TrueOrFalse,
    Unknown
};

enum class QuestonCategory {
    Temp
};

inline QuestionType questionTypeFromLetter(const std::string& typestr) {
    static std::unordered_map<std::string, QuestionType> _map = {
        {"s", QuestionType::SingleChoice},
        {"m", QuestionType::MultileChoice},
        {"t", QuestionType::TrueOrFalse}
    };
    auto it = _map.find(typestr);
    return it != _map.end() ? it->second : QuestionType::Unknown;
}

inline std::string descQuestionType(const QuestionType& qt) {
    switch(qt) {
        case QuestionType::SingleChoice: return "单选题";
        case QuestionType::MultileChoice: return "多选题";
        case QuestionType::TrueOrFalse: return "判断题";
        default: return "未知";
    }
}

class Question {
    int id;
    std::string description;
    std::map<std::string, std::string> options;
    std::string explanation;
    QuestionType type;
    QuestonCategory category;

    virtual std::string getType() const = 0;
    virtual bool checkAnswer(const std::vector<std::string>& userAnswer) const = 0;
    virtual ~Question() = default;
};

