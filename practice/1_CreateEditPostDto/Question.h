#include <string>

using namespace std;

class Question {
private:
    int id;
    int order;
    string content;
public:
    Question(int id, int order, const string &content) : id(id), order(order), content(content) {}

    int getId() const {
        return id;
    }

    int getOrder() const {
        return order;
    }

    const string &getContent() const {
        return content;
    }
};
