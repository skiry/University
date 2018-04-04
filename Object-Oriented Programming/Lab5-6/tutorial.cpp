#include "tutorial.h"

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
};
Tutorial& Tutorial::operator=(const Tutorial& tut) {
    this -> Title = tut.getTitle();
    this -> Presenter = tut.getPresenter();
    this -> Time = tut.getTime();
    this -> Likes = tut.getLikes();
    this -> Link = tut.getLink();
};

Duration::Duration(const Duration& d) {
    this -> Minutes = d.getMinutes();
    this -> Seconds = d.getSeconds();
};
Duration& Duration::operator=(const Duration& d) {
    this -> Minutes = d.getMinutes();
    this -> Seconds = d.getSeconds();
};

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