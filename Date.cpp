//
// Created by ciullo on 23/06/24.
//

#include "Date.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

Date::Date() {
    time_t rawTime;
    std::time(&rawTime);
    struct tm *rawTimeA;
    rawTimeA = localtime(&rawTime);
    dateTime = asctime(rawTimeA);
}

Date::Date(int day, int month, int year) {
    if ((year >= 2000 && year <= 2100)) {
        if (month > 0 && month < 13) {

            int maxDays = getMaxDays(month, year);

            if (day > 0 && day <= maxDays) {
                std::time_t now = std::time(0);
                std::tm *currentDate = std::localtime(&now);

                std::tm givenDate = {};
                givenDate.tm_year = year - 1900;
                givenDate.tm_mon = month - 1;
                givenDate.tm_mday = day;
                givenDate.tm_hour = 23;
                givenDate.tm_min = 59;
                givenDate.tm_sec = 59;

                std::time_t givenTime = std::mktime(&givenDate);
                std::time_t currentTime = std::mktime(currentDate);

                if (givenTime < currentTime) {
                    throw std::out_of_range("Date already passed!");
                } else {
                    // creation of the date string
                    std::tm userDate = {};
                    userDate.tm_year = year - 1900; // tm_year is years since 1900
                    userDate.tm_mon = month - 1; // tm_mon is 0-based
                    userDate.tm_mday = day;

                    std::time_t t = std::mktime(&userDate);
                    std::tm *userTime = std::localtime(&t);
                    dateTime = asctime(userTime);
                }
            } else
                throw std::out_of_range("Date not valid!");
        } else
            throw std::out_of_range("Month not valid!");
    } else
        throw std::out_of_range("Year not valid!");
}

bool Date::isLeapYear(int year) {
    bool isLeap;
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                isLeap = true;
            else
                isLeap = false;
        } else
            isLeap = true;
    } else
        isLeap = false;
    return isLeap;
}

int Date::getMaxDays(int month, int year) {
    int maxDays;
    switch (month) {
        case 2:
            //February
            if (isLeapYear(year))
                maxDays = 29;

            else
                maxDays = 28;
            break;
        case 4:
            // April
        case 6:
            // June
        case 9:
            // September
        case 11:
            // November
            maxDays = 30;
            break;
        default:
            // The other months have 31 days
            maxDays = 31;
    }
    return maxDays;
}

bool Date::checkFutureDate(const Date &date) {
    Date currentDate;  // Crea una data con la data e ora corrente

    std::tm timeinfo1 = {};
    std::istringstream ss1(date.dateTime);
    ss1 >> std::get_time(&timeinfo1, "%a %b %d %H:%M:%S %Y");

    std::tm timeinfo2 = {};
    std::istringstream ss2(currentDate.dateTime);
    ss2 >> std::get_time(&timeinfo2, "%a %b %d %H:%M:%S %Y");

    std::time_t time1 = std::mktime(&timeinfo1);
    std::time_t time2 = std::mktime(&timeinfo2);

    if (time1 <= time2) {
        throw std::out_of_range("Date not valid, already passed!");
    } else
        return true;
}

std::string Date::formatDate(Date date) {
    // Creation of a string stream named iss to handle the date fields
    std::istringstream iss(date.getDateTime());
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

Date Date::addDays(int days) const {
    struct tm timeinfo = {};
    std::istringstream ss(dateTime);
    ss >> std::get_time(&timeinfo, "%a %b %d %H:%M:%S %Y");

    timeinfo.tm_mday += days;
    std::mktime(&timeinfo);  // Normalizza la data

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", &timeinfo);
    return Date(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
}

Date Date::addMonths(int months) const {
    struct tm timeinfo = {};
    std::istringstream ss(dateTime);
    ss >> std::get_time(&timeinfo, "%a %b %d %H:%M:%S %Y");

    timeinfo.tm_mon += months;
    std::mktime(&timeinfo);  // Normalizza la data

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", &timeinfo);
    return Date(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
}

Date Date::addYears(int years) const {
    struct tm timeinfo = {};
    std::istringstream ss(dateTime);
    ss >> std::get_time(&timeinfo, "%a %b %d %H:%M:%S %Y");

    timeinfo.tm_year += years;
    std::mktime(&timeinfo);  // Normalizza la data

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", &timeinfo);
    return Date(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
}

bool Date::operator<=(const Date &other) const {
    std::tm time1 = {}, time2 = {};
    std::istringstream ss1(this->dateTime);
    std::istringstream ss2(other.dateTime);
    ss1 >> std::get_time(&time1, "%a %b %d %H:%M:%S %Y");
    ss2 >> std::get_time(&time2, "%a %b %d %H:%M:%S %Y");
    return std::mktime(&time1) <= std::mktime(&time2);
}