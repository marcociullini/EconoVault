//
// Created by ciullo on 28/05/24.
//

#ifndef ECONOVAULT_TIME_H
#define ECONOVAULT_TIME_H


#include <string>

class Time {
public:
    std::string printCurrentTime() const;

    std::string getUserInputDate();

    void printTime() const;

    void setTime();

    std::string getTime() const {
        return time;
    }

    std::string formatDate(const std::string &date);

private:
    std::string time;
};

#endif //ECONOVAULT_TIME_H
