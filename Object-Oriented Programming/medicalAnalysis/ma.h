#ifndef MA_H
#define MA_H
#include <bits/stdc++.h>

class MA
{
protected:
    std::string date;
public:
    MA(std::string _date) : date{ _date } {}
    virtual bool isResultOK() = 0;
    virtual std::string toString() {
        std::string res = "Medical analysis made on " + date;
        return res;
    }
    int getMonth() { return stoi(date.substr(5,2)); }
};

class BMI : public MA
{
private:
    double value;
public:
    BMI(std::string _date, double val) : MA{ _date }, value{ val } {}
    bool isResultOK() override{
        if( value >= 18.5 && value <= 25) return true;
        return false;
    }

    std::string toString() override{
        std::string res = MA::toString();
        res += " with body mass index " + std::to_string(value) + ".\n";
        return res;
    }
};

class BP : public MA
{
private:
    int sys, dys;
public:
    BP(std::string _date, int s, int d) : MA{ _date }, sys{ s }, dys{ d } {}
    bool isResultOK() override{
        if( sys >= 90 && sys <= 119 && dys >= 60 && dys <= 79 ) return true;
        return false;
    }

    std::string toString() override{
        std::string res = MA::toString();
        res += " with blood presure; systolic value " + std::to_string(sys) + " and diastolic value " + std::to_string(dys) + ".\n";
        return res;
    }
};
#endif // MA_H
