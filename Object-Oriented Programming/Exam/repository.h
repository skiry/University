#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "question.h"

class Repository
{
private:
    std::vector<Question> q;
    std::vector<Participant> p;
    std::string qfile, pfile;
public:
    Repository();
    void readFromFile();
    Repository(std::string qf, std::string pf) : qfile{qf}, pfile{pf}
    {
        readFromFile();
    }
    std::vector<Question> getQ()
    {
        return q;
    }
    std::vector<Participant> getP()
    {
        return p;
    }
    void writeToFile();
    void increaseScore(std::string name, int score);
    //increase the score of participant which has the name `name` with `score` units

    void add(Question qu);
    //add the question `qu` to the set of questions
};

#endif // REPOSITORY_H
