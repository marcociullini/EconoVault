//
// Created by ciullo on 23/06/24.
//

#ifndef ECONOVAULT_DATE_H
#define ECONOVAULT_DATE_H


#include <string>

class Date {
public:

    Date();

    Date(int day, int month, int year);

    std::string getDateTime() const{
        return dateTime;
    };

    static bool isLeapYear(int year);

    static int getMaxDays(int month, int year);

    static bool checkFutureDate(const Date& date);

    static std::string formatDate(Date date);

    Date addDays(int days) const;

    Date addMonths(int months) const;

    Date addYears(int years) const;

    bool operator<=(const Date &other) const;

private:
    std::string dateTime;
};

#endif //ECONOVAULT_DATE_H
