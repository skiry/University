#include "repository.h"
#include "exception.h"
Repository::Repository()
{

}

std::vector<std::string> tokenize(std::string line, char delimiter)
{
    std::vector<std::string> rez;
    std::stringstream ss(line);
    std::string token;

    while (getline(ss, token, delimiter)) {
        rez.push_back(token);
    }

    return rez;
}

void Repository::readFromFile()
{
    std::ifstream file{ qfile };

    if (!file.is_open()) {
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = tokenize(line, ',');
        std::string name = tokens[1];
        int id = std::stoi(tokens[0]);
        std::string an = tokens[2];
        int score = std::stoi(tokens[3]);
        Question qu{ id, name, an, score };
        this->q.push_back(qu);
    }

    file.close();

    std::ifstream filee{ pfile };

    if (!filee.is_open()) {
        return;
    }

    while (std::getline(filee, line)) {
        std::vector<std::string> tokens = tokenize(line, ',');
        std::string name = tokens[0];
        int score = std::stoi(tokens[1]);

        Participant t{ name, score };
        this->p.push_back(t);

    }

    std::cout << q.size() << " " << p.size();
    filee.close();
    writeToFile();
}

void Repository::writeToFile()
{
    std::ofstream g{qfile};

    for (auto& i : q) {
        g << i.getId() << "," << i.getText() << "," << i.getAnswer() << "," << i.getScore() << '\n';
    }
}

void Repository::increaseScore(std::string name, int score)
{
    for (auto& i : p)
        if ( i .getName() == name ) {
            i.addScore(score);
        }
}

void Repository::add(Question qu)
{
    if (qu.getText() == "" ) throw Exception{"Empty text"};

    for (auto& i : q)
        if (i.getId() == qu.getId())
            throw Exception{"Existing id"};

    q.push_back(qu);

    writeToFile();
}
