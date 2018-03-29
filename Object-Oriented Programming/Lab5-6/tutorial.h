#ifndef TUTORIAL_H
#define TUTORIAL_H
#include <string>

class Duration{
    //a Duration class needed for representing Tutorial's running time
private:
    int Minutes;
    int Seconds;
public:
    Duration() {};
    Duration(int m, int s) : Minutes(m), Seconds(s) {};
    Duration(const Duration& d);
    Duration& operator=(const Duration& d);
    ~Duration() {};
    int getMinutes() const { return this -> Minutes; };
    int getSeconds() const { return this -> Seconds; };
};

class Tutorial{
    //the main class for a Tutorial
private:
    std::string Title;
    std::string Presenter;
    Duration Time;
    int Likes;
    std::string Link;
public:
    Tutorial() {};
    Tutorial(std::string t, std::string p, Duration d, int l, std::string link);
    Tutorial(const Tutorial& tut);
    Tutorial& operator=(const Tutorial& tut);
    ~Tutorial() {};
    std::string getTitle() const { return this -> Title; };
    std::string getPresenter() const { return this -> Presenter; };
    Duration getTime() const { return this -> Time; };
    int getLikes() const { return this -> Likes; };
    std::string getLink() const { return this -> Link; };
};

#endif // TUTORIAL_H
