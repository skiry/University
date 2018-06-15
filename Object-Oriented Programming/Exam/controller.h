#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "repository.h"
#include "observer.h"

class Controller : public Observable
{
private:
    Repository r;
public:
    Controller();
    Controller(Repository& repo) : r{repo} {}
    void increaseScore(std::string name, int score);
    std::vector<Question> getAll();
    std::vector<Question> getAllPr();
    void add(int id, std::string n, std::string an, int sc);
};

#endif // CONTROLLER_H
