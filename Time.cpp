//
// Created by ciullo on 28/05/24.
//

#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Time.h"
#include "Date.h"

std::string Time::printCurrentTime() const {
    time_t rawTime;
    std::time(&rawTime);
    struct tm *rawTimeA;
    rawTimeA = localtime(&rawTime);
    return asctime(rawTimeA);
}

void Time::getUserInputDate() {
    int year, month, day;
    std::cout << "Enter year: ";
    std::cin >> year;
    std::cout << "Enter month (1-12): ";
    std::cin >> month;
    std::cout << "Enter day (1-31): ";
    std::cin >> day;

    Date date(day, month, year);

    std::tm userDate = {};
    userDate.tm_year = date.getYear() - 1900; // tm_year is years since 1900
    userDate.tm_mon = date.getMonth() - 1; // tm_mon is 0-based
    userDate.tm_mday = date.getDay();

    std::time_t t = std::mktime(&userDate);
    std::tm *userTime = std::localtime(&t);
    this->time = asctime(userTime);
}

void Time::printTime() const {
    std::cout << time << std::endl;
}

void Time::setTime() {
    time_t rawTime;
    std::time(&rawTime);
    struct tm *rawTimeA;
    rawTimeA = localtime(&rawTime);
    this->time = asctime(rawTimeA);
}

std::string Time::formatDate(const std::string &date) {
    // Creation of a string stream named iss to handle the date fields
    std::istringstream iss(date);
    // Creation of an empty structure tm in order to manipulate the data fields
    std::tm tm = {};
    // initializing tm with all the values of date
    iss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
    // Creation of a string stream named oss to output the formatted data fields
    std::ostringstream oss;
    // Selecting the data fields for the output
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}