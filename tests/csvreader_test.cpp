#include <gtest/gtest.h>
#include "application_layer/question.hpp"
#include "utils/csvreader.hpp"
#include <vector>
#include <string>

using namespace shenshang::question;
using namespace shenshang::utils::csv;

TEST(CSVReaderTest, ParseSimpleQuestionCSV) {
    const std::string file = "/home/antaresz/Projects/ShenShang/temp/TestQuestions.csv";
    std::vector<Question> questions;

    ASSERT_NO_THROW({
        questions = parseCSV(file);
    });

    ASSERT_FALSE(questions.empty());
    const auto& q = questions[0];

    // 根据实际 TestQuestions.csv 填入你想断言的内容
    EXPECT_EQ(q.type, QuestionType::SingleChoice);
    EXPECT_EQ(q.description, "职业道德是人们在一定的职业活动范围内所遵循的（    ）的总和。");
    ASSERT_TRUE(q.options.count("A") > 0);
    EXPECT_EQ(q.options.at("A"), "行为意识");
    EXPECT_EQ(q.answers.size(), 1);
    EXPECT_EQ(q.answers[0], "B");
    EXPECT_TRUE(q.explanation.size() >= 0);
}
