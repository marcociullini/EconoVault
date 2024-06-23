//
// Created by ciullo on 28/05/24.
//

#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Time.h"

std::string Time::printCurrentTime() const {
    time_t rawTime;
    std::time(&rawTime);
    struct tm *rawTimeA;
    rawTimeA = localtime(&rawTime);
    return asctime(rawTimeA);
}

std::string Time::getUserInputDate() {
    int year, month, day;
    std::cout << "Enter year: ";
    std::cin >> year;
    std::cout << "Enter month (1-12): ";
    std::cin >> month;
    std::cout << "Enter day (1-31): ";
    std::cin >> day;

    struct tm userTime = {0};
    userTime.tm_year = year - 1900; // tm_year is years since 1900
    userTime.tm_mon = month - 1; // tm_mon is 0-based
    userTime.tm_mday = day;

    // Convert tm struct to time_t
    time_t rawTime = mktime(&userTime);

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

std::string Time::formatDate(const std::string& date) {
    std::istringstream iss(date);
    std::tm tm = {};
    iss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}