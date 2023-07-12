#include <iostream>
#include "Question.h"
#include "QuestionDto.h"
#include "Post.h"
#include "EditPostDto.h"

using namespace std;

Post findPostById(int postId);

EditPostDto getEditPostFormById(int postId) {
    // postId == test number
    Post post = findPostById(postId);

    EditPostDto editPostDto = EditPostDto(post.getId(), post.getTitle(), post.getContent());

    vector<Question> questions = post.getQuestions();
    for (const Question &question: questions) {
        QuestionDto questionDto = QuestionDto(question.getOrder(), question.getContent());
        editPostDto.questionDtoList.push_back(questionDto);
    }

    for (int i = questions.size() + 1; i <= 3; ++i) {
        QuestionDto questionDto = QuestionDto(i, "");
        editPostDto.questionDtoList.push_back(questionDto);
    }
    return editPostDto;
}

int main() {
    // Don't edit this method for test

    for (int testNumber = 1; testNumber <= 4; ++testNumber) {
        cout << "================ Test" << testNumber << "================\n";
        EditPostDto editPostDto = getEditPostFormById(testNumber);
        bool isCorrect = true;
        isCorrect &= (editPostDto.title == "title" + to_string(testNumber));
        cout << "  title =====> " << boolalpha << isCorrect << "\n";
        isCorrect &= (editPostDto.content == "content" + to_string(testNumber));
        cout << "  content =====> " << boolalpha << isCorrect << "\n";
        isCorrect &= (editPostDto.postId == testNumber);
        cout << "  postId =====> " << boolalpha << isCorrect << "\n";

        cout << "  == questionDto vector ==\n";

        isCorrect &= (editPostDto.questionDtoList.size() == 3);
        cout << "    vector size =====> " << boolalpha << isCorrect << "\n";

        for (int i = 0; i < editPostDto.questionDtoList.size(); ++i) {
            cout << "    index " << i << "\n";
            isCorrect &= (editPostDto.questionDtoList[i].order == i + 1);
            cout << "      order =====> " << boolalpha << isCorrect << "\n";

            if (i < 4 - testNumber)
                isCorrect &= (editPostDto.questionDtoList[i].content == "questionContent" + to_string(i + 1));
            else
                isCorrect &= (editPostDto.questionDtoList[i].content == "");
            cout << "      content =====> " << boolalpha << isCorrect << "\n";
        }
        cout << "\n\n";
    }
}

Post findPostById(int postId) {
    // Don't edit this method
    if (postId == 1) {
        vector<Question> questions;
        questions.emplace_back(1, 1, "questionContent1");
        questions.emplace_back(3, 2, "questionContent2");
        questions.emplace_back(2, 3, "questionContent3");
        return Post(1, "title1", "content1", "2023-07-12", questions);
    }
    if (postId == 2) {
        vector<Question> questions;
        questions.emplace_back(1, 1, "questionContent1");
        questions.emplace_back(3, 2, "questionContent2");
        return Post(2, "title2", "content2", "2023-07-13", questions);
    }
    if (postId == 3) {
        vector<Question> questions;
        questions.emplace_back(1, 1, "questionContent1");
        return Post(3, "title3", "content3", "2023-07-14", questions);
    }
    if (postId == 4) {
        vector<Question> questions;
        return Post(4, "title4", "content4", "2023-07-15", questions);
    }
}

