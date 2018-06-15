#include "controller.h"

Controller::Controller()
{

}

void Controller::increaseScore(std::string name, int score)
{
    r.increaseScore(name, score);
}
std::vector<Question> Controller::getAll()
{
    std::vector<Question> v = this->r.getQ();
    sort(v.begin(), v.end(), [] (Question a, Question b) {
        return a.getScore() > b.getScore();
    });
    return v;
}

std::vector<Question> Controller::getAllPr()
{
    std::vector<Question> v = this->r.getQ();
    sort(v.begin(), v.end(), [] (Question a, Question b) {
        return a.getId() < b.getId();
    });
    return v;
}

void Controller::add(int id, std::string n, std::string an, int sc)
{
    Question q{id, n, an, sc};
    r.add(q);
    notify();
}
