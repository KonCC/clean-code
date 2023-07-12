# Practice 1



## Overview

- 해당 애플리케이션은 Entity인 `Post`와 `Quesiton` 으로부터 DTO인 `EditPostDto`를 생성하는 기능을 수행합니다.

- 해당 애플케이션은 다음과 같은 환경에서 제작 및 테스트 되었습니다.

  - OS : Mac Ventura 13.4.1
  - gcc version : Apple clang version 14.0.3

- 자유롭게 함수 생성, 클래스 생성, 변수 변경 등을 수행하셔도 됩니다. 단, 각 클래스의 멤버 변수는 변경하면 안됩니다.

- 실행 방법(또는 개인 환경의 IDE에서 실행해도 됩니다.)

  ```shell
  g++ -o main main.c
  ./main
  ```

- 올바른 실행 결과 예시(이때 출력되는 실행 결과는 해당 테스트 번호의 누적 결과입니다.)

  ```
  ================ Test1================
    title =====> true
    content =====> true
    postId =====> true
    [ questionDto vector ]
      vector size =====> true
      index 0
        order   =====> true
        content =====> true
      index 1
        order   =====> true
        content =====> true
      index 2
        order   =====> true
        content =====> true
  
  ... {중략} ...
  
  ================ Test4================
    title =====> true
    content =====> true
    postId =====> true
    [ questionDto vector ]
      vector size =====> true
      index 0
        order   =====> true
        content =====> true
      index 1
        order   =====> true
        content =====> true
      index 2
        order   =====> true
        content =====> true
  ```

  


## 로직

- `main.cpp`

  - `Post findPostById(int postId);` : 가상의 repository에서 `Post` 를 조회하는 함수입니다. 수정하면 안되는 함수입니다.
  - `EditPostDto getEditPostFormById(int postId)` : `EditPostDto`를 생성하는 함수입니다. 이 함수를 리팩토링 하시면 됩니다.
  - `int main()` : 리펙토링이 올바르게 되었는지 확인하기 위해, 테스트를 진행합니다. 수정하면 안되는 함수입니다.

- 가상 repository에서 조회한 `Post`는 다음을 보장합니다.

  -  `Post` 의 멤버 변수인 `questions`은 vector 크기가 최소 0 ~ 최대 3 입니다.
    - 이때 `question`은 vector 인덱스 순서대로 `order`가 1씩 증가합니다.(`order`는 1부터 시작)

- `EditPostDto`은 다음의 조건을 만족해야 합니다. (이 조건을 지키면서 리팩토링 되어야 합니다.)

  - 멤버 변수인 `questionDtoList` 는 vector 크기가 3이어야 합니다.
  - 만약 `Post`의 `questions`의 사이즈가 3이 아니라면, `QuestionDto.content`는 `""`의 값을 갖도록 추가하여야 합니다.
    - 이때 `order`는 순서대로 유지되어야 합니다.

  ```c++
  vector<Question> questions = post.getQuestions();
  for (const Question &question: questions) {
      QuestionDto questionDto = QuestionDto(question.getOrder(), question.getContent());
      editPostDto.questionDtoList.push_back(questionDto);
  }
  
  // 사이즈가 3보다 작다면, content가 ""인 QuestionDto로 채워야합니다.
  for (int i = questions.size() + 1; i <= 3; ++i) {
      QuestionDto questionDto = QuestionDto(i, "");
      editPostDto.questionDtoList.push_back(questionDto);
  }
  ```

  

## 구조

- 4개의 헤더 파일

- `Post.h`, `Question.h`

  ```c++
  class Post {
      int id;
      string title;
      string content;
      string date;
      vector<Question> questions;
  }
  
  class Question {
      int id;
      int order;
      string content;
  }
  ```

- `EditPostDto.h`, `QuestionDto.h`

  ```c++
  class EditPostDto {
      int postId;
      string title;
      string content;
      vector<QuestionDto> questionDtoList;
  }
  
  class QuestionDto {
      int order;
      string content;
  }
  ```



---

Copyright 2023. redcarrot1 all rights reserved.