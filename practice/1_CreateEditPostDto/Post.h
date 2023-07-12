#include <string>
#include <vector>

using namespace std;

class Post {
private:
    int id;
    string title;
    string content;
    string date;
    vector<Question> questions;

public:
    Post(int id, const string &title, const string &content, const string &date, const vector<Question> &questions)
            : id(id), title(title), content(content), date(date), questions(questions) {};

    int getId() const {
        return id;
    }

    const string &getTitle() const {
        return title;
    }

    const string &getContent() const {
        return content;
    }

    const string &getDate() const {
        return date;
    }

    const vector<Question> &getQuestions() const {
        return questions;
    }
};
