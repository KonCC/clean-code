#include <string>

using namespace std;
#ifndef QUESTIONDTO_H
#define QUESTIONDTO_H
class QuestionDto {
 public:
  int order;
  string content;

  QuestionDto(int order, const string &content)
      : order(order), content(content) {}
};

#endif  // QUESTIONDTO_H