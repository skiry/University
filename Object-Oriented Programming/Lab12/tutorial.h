#ifndef TUTORIAL_H
#define TUTORIAL_H
#include <string>
#include <iostream>
#include <bits/stdc++.h>

class Duration
{
    //a Duration class needed for representing Tutorial's running time
private:
    int Minutes;
    int Seconds;
public:
    Duration() {}
    //basic constructor
    Duration(int m, int s) : Minutes(m), Seconds(s) {}
    //duration constructor
    Duration(const Duration& d);
    Duration& operator=(const Duration& d);
    ~Duration() {}
    int getMinutes() const
    {
        return this -> Minutes;
    }
    int getSeconds() const
    {
        return this -> Seconds;
    }
};

class Tutorial
{
    //the main class for a Tutorial
private:
    std::string Title;
    std::string Presenter;
    Duration Time;
    int Likes;
    std::string Link;
public:
    Tutorial() : Title{ "" }, Presenter{ "" }, Time{ Duration(0, 0) }, Likes{ 0 }, Link{ "" } {}
    //standard constructor

    Tutorial(std::string t, std::string p, Duration d, int l, std::string link);
    //tutorial constructor

    Tutorial(const Tutorial& tut);
    //copy constructor

    Tutorial& operator=(const Tutorial& tut);
    //assignment operator

    ~Tutorial() {}
    //destructor

    void setLikes(int lk)
    {
        std::cout << "have, got" << Likes << " " << lk;
        Likes = lk;
    }
    //set the number of likes

    std::string getTitle() const
    {
        return this -> Title;
    }
    //title getter

    std::string getPresenter() const
    {
        return this -> Presenter;
    }
    //presenter getter

    Duration getTime() const
    {
        return this -> Time;
    }
    //time getter

    int getLikes() const
    {
        return this -> Likes;
    }
    //likes getter

    std::string getLink() const
    {
        return this -> Link;
    }
    //link getter

    void operator++()
    {
        this-> Likes++;
    }
    //likes incrementor

    void like()
    {
        this -> Likes++;
    }

    bool operator==(const Tutorial& tut);
    //equality tutorial overloading

    friend std::istream& operator>>(std::istream &, Tutorial& );

    friend std::ostream& operator<<(std::ostream &, const Tutorial& );

    std::string toStr()
    {
        std::string result;

        result += "<tr>";
        result += "<td>" + this -> getTitle() + "</td>";
        result += "<td>" + this -> getPresenter() + "</td>";
        result += "<td>" + std::to_string(this -> getTime().getMinutes()) + ":"
                  + std::to_string(this -> getTime().getSeconds()) + "</td>";
        result += "<td>" + std::to_string(this -> getLikes()) + "</td>";
        result += "<td><a href=\"" + this -> getLink() + "\">Link</a></td>";
        result += "</tr>";

        return result;
    }
};

#endif // TUTORIAL_H
