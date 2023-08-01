#include <string>
#include <vector>

#include "QuestionDto.h"

using namespace std;

class EditPostDto {
 public:
  int postId;
  string title;
  string content;
  vector<QuestionDto> questionDtoList;

  EditPostDto(int postId, const string &title, const string &content)
      : postId(postId), title(title), content(content) {}
};
