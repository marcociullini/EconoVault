//
// Created by ciullo on 23/06/24.
//

#ifndef ECONOVAULT_DATE_H
#define ECONOVAULT_DATE_H


class Date {
public:
    Date(int day, int month, int year);

    Date() : day(1), month(1), year(2000) {}

    int getDay() const;

    int getMonth() const;

    int getYear() const;

    void setDay(int day);

    void setMonth(int month);

    void setYear(int year);

    bool operator==(const Date &right) const;

    void printDate() const;

    int getDaysOfMonth(int month, int year) const;

    bool isLeap(int year) const;

    bool validDate(int day, int month, int year);

    bool validDay(int day, int month, int year) const;

    bool validMonth(int month);

    bool validYear(int year);

private:
    int day;
    int month;
    int year;
};

#endif //ECONOVAULT_DATE_H
