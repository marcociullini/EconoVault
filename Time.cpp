//
// Created by ciullo on 28/05/24.
//

#include <ctime>
#include "Time.h"

std::string Time::getTime() {
    time_t rawTime;
    std::time(&rawTime);
    struct tm *rawTimeA;
    rawTimeA = localtime(&rawTime);
    return asctime(rawTimeA);
}