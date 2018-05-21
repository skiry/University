#include "tutorialvalidator.h"
#include "tutorial.h"

TutorialException::TutorialException(std::string _message)
{
    this -> message = _message;
}

const char* TutorialException::what() const noexcept{
    return this -> message.c_str();
}

void TutorialValidator::validate( const Tutorial & tut ){
    std::string errors;

    if( tut.getTime().getMinutes() < 0 || tut.getTime().getMinutes() > 105 )
        errors += std::string("This amount of minutes is inadequate!\n");
    if( tut.getTime().getSeconds() < 0 || tut.getTime().getSeconds() >= 60 )
        errors += std::string("This amount of seconds is inadequate!\n");
    if( tut.getLink().size() < 8 )
        errors += std::string("Invalid link!\n");
    if( tut.getPresenter().size() < 3 )
        errors += std::string("The presenter's name cannot be less than 2 characters!\n");
    if( tut.getTitle().size() < 3 )
        errors += std::string("The title cannot be less than 2 characters!\n");

    size_t posWww = tut.getLink().find("www");
    size_t posHttp = tut.getLink().find("http");
    if (posWww != 0 && posHttp != 0)
        errors += std::string("The link must start with one of the following strings: \"www\" or \"http\"\n");

    if( errors.size() )
        throw TutorialException( errors );
}
