#include <string>

using namespace std;
#ifndef QUESTION_H
#define QUESTION_H
class Question {
 private:
  int id;
  int order;
  string content;

 public:
  Question(int id, int order, const string &content)
      : id(id), order(order), content(content) {}

  int getId() const { return id; }

  int getOrder() const { return order; }

  const string &getContent() const { return content; }
};
#endif  // QUESTION_H