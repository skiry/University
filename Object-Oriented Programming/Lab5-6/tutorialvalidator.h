#ifndef TUTORIALVALIDATOR_H
#define TUTORIALVALIDATOR_H
#include <exception>
#include <string>
#include "tutorial.h"

class TutorialException : public std::exception
{
private:
    std::string message;
public:
    TutorialException(std::string);
    const char* what() const noexcept override;

};

class TutorialValidator
{
public:
    TutorialValidator() {}
    static void validate(const Tutorial&);
};
#endif // TUTORIALVALIDATOR_H
