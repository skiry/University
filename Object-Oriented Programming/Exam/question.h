#ifndef QUESTION_H
#define QUESTION_H
#include <bits/stdc++.h>

class Question
{
private:
    int id, score;
    std::string text, answer;
public:
    Question();
    Question(int i, std::string t, std::string a, int s) : id{i}, text{t}, answer{a}, score{s} {}
    int getId()
    {
        return id;
    }
    int getScore()
    {
        return score;
    }
    std::string getText()
    {
        return text;
    }
    std::string getAnswer()
    {
        return answer;
    }
};

class Participant
{
private:
    std::string name;
    int score;
public:
    Participant() {}
    Participant(std::string n) : name{n}, score{0} {}
    Participant(std::string n, int s) : name{n}, score{s} {}
    std::string getName()
    {
        return name;
    }
    int getScore()
    {
        return score;
    }
    void addScore(int s)
    {
        std::cout << "edited score from to" << score;

        score += s;
        std::cout << " " << score;
    }
};
#endif // QUESTION_H
