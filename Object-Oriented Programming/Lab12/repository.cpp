#include "tutorialvalidator.h"
#include "repository.h"
#include <utility>
#include <algorithm>
#include <bits/stdc++.h>

Repository::Repository()
{
	//this -> repo = DynamicArray<Tutorial>(10);
    /*Duration d = Duration(3, 22);
	Duration d1 = Duration(5, 59);
	Duration d2 = Duration(1, 4);
	Tutorial tut = Tutorial("Easy C++", "Johnny", d, 1500, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
	Tutorial tut2 = Tutorial("Easy C--", "Johny", d1, 10, "www.google.com");
	Tutorial tut3 = Tutorial("Easy C", "Johnnie", d2, 150, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
	Tutorial tut4 = Tutorial("Easy Pyhton", "John", d, 15, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
	Tutorial tut5 = Tutorial("Easy Java", "Ionut", d2, 500, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
	Tutorial tut6 = Tutorial("Easy Info", "Ionutz", d1, 100, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
	Tutorial tut7 = Tutorial("Easy OOP", "Ion", d, 1000, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
	Tutorial tut8 = Tutorial("Easy Everything", "Mc John", d2, 1900, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
	addTut(tut);
	addTut(tut2);
	addTut(tut3);
	addTut(tut4);
	addTut(tut5);
	addTut(tut6);
	addTut(tut7);
	addTut(tut8);
    writeRepo();*/
	this -> length = 0;
}

void Repository::addTut(const Tutorial& tut)
{
	TutorialValidator::validate(tut);

	if (find(tut.getTitle()) == 0) {
		this -> repo.push_back(tut);
	}

	this -> length++;
}

void Repository::rmTut(std::string title)
{
	for (int i = 0; i < this -> repo.size() ; ++i)
		if (this -> repo[i].getTitle().compare(title) == 0) {
			//this -> repo - this->repo[i];
			this -> repo.erase(repo.begin() + i);
			//this -> length--;
		}

	//std::swap(this -> repo[i], this -> repo[--(this -> length)]);
}

int Repository::find(std::string title)
{
	for (int i = 0; i < this -> repo.size() ; ++i)
		if ( this -> repo[i].getTitle() == title ) {
			return 1;
		}

	return 0;
}

int Repository::findW(std::string title)
{
	for (int i = 0; i < this -> wList.size() ; ++i)
		if ( this -> wList[i].getTitle() == title ) {
			return 1;
		}

	return 0;
}

Tutorial Repository::getTut(std::string title)
{
    for ( auto i : repo )
        if ( i.getTitle() == title ) {
            return i;
        }
}

void Repository::updTut(std::string title, const Tutorial& tut)
{
	for (int i = 0; i < this -> repo.size() ; ++i)
		if (this -> repo[i].getTitle().compare(title) == 0) {
			TutorialValidator::validate(tut);
			this -> repo[i] = tut;
		}
}

std::vector<Tutorial> Repository::byPresenter(std::string pr)
{
	std::vector<Tutorial> v;

	for ( int i = 0; i < repo.size() ; ++i )
		if ( repo[i].getPresenter() == pr || pr == "") {
			v.push_back(repo[i]);
		}

	return v;
}

std::vector<Tutorial> Repository::byPresenterWL(std::string pr)
{
    std::vector<Tutorial> v;

    for ( int i = 0; i < wList.size() ; ++i )
        if ( wList[i].getPresenter() == pr) {
            v.push_back(repo[i]);
        }

    return v;
}


std::vector<Tutorial> Repository::getWlist()
{
	std::vector<Tutorial> v;

	for ( int i = 0; i < wList.size() ; ++i ) {
		v.push_back(wList[i]);
	}

	return v;
}

void Repository::increaseLike(std::string title)
{
	/*  for(int i = 0; i < this -> repo.size() ; ++i)
	      if( this -> repo[i].getTitle() == title )
	          ++(this -> repo[i]);*/

	for (auto& it : repo)
		if ( it.getTitle() == title ) {
			it.like();
			std::cout << it.getTitle() << " " << it.getPresenter() << '\n';
		}

	for (auto& it : wList)
		if ( it.getTitle() == title ) {
			it.like();
		}
}

bool Repository::addToPL(const Tutorial& tut)
{
	if ( findW(tut.getTitle()) ) {
		return false;
	}

	this -> wList.push_back(tut);
	//this -> wLen++;

	return true;
}

void Repository::rmFromPL(std::string title)
{
	for (int i = 0; i < this -> wList.size() ; ++i)
		if (this -> wList[i].getTitle().compare(title) == 0) {
			this -> wList.erase(wList.begin() + i);
			//this -> wLen--;
		}
}

void Repository::readRepo()
{
	std::ifstream f( "Tutorials.CSV" );
	Tutorial t{};

	if ( f.is_open() ) {
		this -> repo.clear();

		while ( f >> t ) {
			this -> addTut(t);
		}
	}
}

void Repository::readWlist()
{
	std::ifstream f( "WatchList.CSV" );
	Tutorial t{};

	if ( f.is_open() ) {
		this -> wList.clear();

		while ( f >> t ) {
			this -> addToPL(t);
		}
	}
}

void Repository::writeRepo()
{
    std::ofstream g( "Tutorials.CSV" );

    if ( g.is_open() ) {
		for ( auto it : repo ) {
			g << it;
		}
	}
}

void Repository::writeWList()
{
	std::ofstream g( "WatchList.CSV" );

	if ( g.is_open() ) {
		for ( auto it : wList ) {
			g << it;
		}
	}
}

Repository& Repository::getRepo()
{
	return *this;
}





