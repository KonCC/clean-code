#include <string>

using namespace std;

class QuestionDto {
public:
    int order;
    string content;

    QuestionDto(int order, const string &content) : order(order), content(content) {}
};
