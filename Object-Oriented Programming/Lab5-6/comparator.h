#ifndef COMPARATOR_H
#define COMPARATOR_H
#include "tutorial.h"
#include <vector>
#include "algorithm"

template <typename T>
class Comparator
{
public:
    virtual bool compare(T, T) = 0;
};

class CompareDescByLikes : public Comparator<Tutorial>
{
public:
    bool compare(Tutorial a, Tutorial b) override{
        return a.getLikes() > b.getLikes();
    }
};

class CompareAscByMinutes : public Comparator<Tutorial>
{
public:
    bool compare(Tutorial a, Tutorial b) override{
        return a.getTime().getMinutes() < b.getTime().getMinutes();
    }
};

template <typename T>
void sorft(std::vector<T>& tuts, Comparator<T>* comp){
    std::sort(tuts.begin(), tuts.end(), [comp](T t1, T t2) { return comp -> compare(t1, t2); } );
}

void testComparator(){
    std::vector<Tutorial> tuts;

    Duration d = Duration(3,22);
    Duration d1 = Duration(5,59);
    Duration d2 = Duration(1,4);
    Tutorial tut = Tutorial("Easy C++", "Johnny", d, 1500, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
    Tutorial tut2 = Tutorial("Easy C--", "Johny", d1, 10, "www.google.com");
    Tutorial tut3 = Tutorial("Easy C", "Johnnie", d2, 150, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");
    Tutorial tut4 = Tutorial("Easy Pyhton", "John", d, 15, "http://www.cs.ubbcluj.ro/~iuliana/oop/Laboratories/Lab5-6.pdf");

    tuts.push_back(tut);
    tuts.push_back(tut2);
    tuts.push_back(tut3);
    tuts.push_back(tut4);

    Comparator<Tutorial>* mins = new CompareAscByMinutes{};
    Comparator<Tutorial>* likes = new CompareDescByLikes{};

    for(auto it : tuts) std::cout << it.getTitle() << " has " << it.getTime().getMinutes()
                                  << " minutes and " << it.getLikes() << "likes\n";
    sorft<Tutorial>(tuts, mins);
    std::cout << "Sorting ascending by the length of the tutorial...\n";
    for(auto it : tuts) std::cout << it.getTitle() << " has " << it.getTime().getMinutes()
                                  << " minutes and " << it.getLikes() << "likes\n";
    sorft<Tutorial>(tuts, likes);
    std::cout << "Sorting descending by the number of likes...\n";
    for(auto it : tuts) std::cout << it.getTitle() << " has " << it.getTime().getMinutes()
                                  << " minutes and " << it.getLikes() << "likes\n";
}

#endif // COMPARATOR_H
