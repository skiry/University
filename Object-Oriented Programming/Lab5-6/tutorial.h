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
    //basic constructor
    Duration(int m, int s) : Minutes(m), Seconds(s) {};
    //duration constructor
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
    //standard constructor

    Tutorial(std::string t, std::string p, Duration d, int l, std::string link);
    //tutorial constructor

    Tutorial(const Tutorial& tut);
    //copy constructor

    Tutorial& operator=(const Tutorial& tut);
    //assignment operator

    ~Tutorial() {}
    //destructor

    std::string getTitle() const { return this -> Title; }
    //title getter

    std::string getPresenter() const { return this -> Presenter; }
    //presenter getter

    Duration getTime() const { return this -> Time; }
    //time getter

    int getLikes() const { return this -> Likes; }
    //likes getter

    std::string getLink() const { return this -> Link; }
    //link getter

    void operator++() { this-> Likes++; }
    //likes incrementor

    bool operator==(const Tutorial& tut);
    //equality tutorial overloading
};

#endif // TUTORIAL_H
