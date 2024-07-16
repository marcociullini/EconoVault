//
// Created by ciullo on 28/05/24.
//

#ifndef ECONOVAULT_TIME_H
#define ECONOVAULT_TIME_H


#include <string>

class Time {
public:
    Time();

    std::string printCurrentTime() const;

    void printTime() const;

    void setTime();

    std::string getTime() const{
        return time;
    }

private:
    std::string time;
};

#endif //ECONOVAULT_TIME_H
