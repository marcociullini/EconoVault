//
// Created by ciullo on 28/05/24.
//

#include <ctime>
#include <iostream>
#include "Time.h"

Time::Time() {
    time_t rawTime;
    std::time(&rawTime);
    struct tm *rawTimeA;
    rawTimeA = localtime(&rawTime);
    this->time = asctime(rawTimeA);
}

std::string Time::printCurrentTime() const {
    time_t rawTime;
    std::time(&rawTime);
    struct tm *rawTimeA;
    rawTimeA = localtime(&rawTime);
    return asctime(rawTimeA);
}
void Time::printTime() const{
    std::cout << time << std::endl;
}

void Time::setTime(){
    time_t rawTime;
    std::time(&rawTime);
    struct tm *rawTimeA;
    rawTimeA = localtime(&rawTime);
    this->time = asctime(rawTimeA);
}