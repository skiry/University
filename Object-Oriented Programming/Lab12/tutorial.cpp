#include "tutorial.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

Tutorial::Tutorial(std::string t, std::string p, Duration d, int l, std::string link){
    this -> Title = t;
    this -> Presenter = p;
    this -> Time = d;
    this -> Likes = l;
    this -> Link = link;
}

Tutorial::Tutorial(const Tutorial& tut) {
    this -> Title = tut.getTitle();
    this -> Presenter = tut.getPresenter();
    this -> Time = tut.getTime();
    this -> Likes = tut.getLikes();
    this -> Link = tut.getLink();
}

Tutorial& Tutorial::operator=(const Tutorial& tut) {
    this -> Title = tut.getTitle();
    this -> Presenter = tut.getPresenter();
    this -> Time = tut.getTime();
    this -> Likes = tut.getLikes();
    this -> Link = tut.getLink();

    return *this;
}

Duration::Duration(const Duration& d) {
    this -> Minutes = d.getMinutes();
    this -> Seconds = d.getSeconds();
}

Duration& Duration::operator=(const Duration& d) {
    this -> Minutes = d.getMinutes();
    this -> Seconds = d.getSeconds();

    return *this;
}

bool Tutorial::operator==(const Tutorial& tut){
    if(this -> Title != tut.getTitle()) return false;
    return true;
    if(this -> Presenter != tut.getPresenter()) return false;
    if(this -> Likes != tut.getLikes()) return false;
    if(this -> Link != tut.getLink()) return false;
    if(this -> getTime().getMinutes() != tut.getTime().getMinutes()) return false;
    if(this -> getTime().getSeconds() != tut.getTime().getSeconds()) return false;
    return true;
}

std::vector<std::string> tokenize(std::string str, char delimiter){

    std::vector <std::string> result;
    std::stringstream ss(str);
    std::string token;
    while ( std::getline(ss, token, delimiter) )
        result.push_back(token);

    return result;
}

std::istream & operator>>(std::istream & stream, Tutorial& tut){

        std::string line;
        std::getline( stream, line );

        std::vector< std::string > tokens = tokenize( line, ',' );
        if( tokens.size() != 6 )
            return stream;

        tut.Title = tokens[0];
        tut.Presenter = tokens[1];
        tut.Time = Duration( std::stoi(tokens[2]), std::stoi(tokens[3]) );
        tut.Likes = std::stoi(tokens[4]);
        tut.Link = tokens[5];

        return stream;
}

std::ostream & operator<<(std::ostream & stream, const Tutorial& tut){

        stream << tut.getTitle() << "," << tut.getPresenter() << "," << tut.getTime().getMinutes() << "," <<
                          tut.getTime().getSeconds() << "," << tut.getLikes() << "," << tut.getLink() << "\n";
        return stream;
}
