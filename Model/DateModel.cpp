//
// Created by Nguyen Hoang Minh Khoi on 12/27/22.
//
#include "SystemModel.h"


int checkMonth(int month, int year, int duration) {
    if (month == 1 || month == 3 || month == 5 || month == 7 ||
        month == 8 || month == 10 || month == 12) {
        duration += 31;
    } else if (month == 2) {
        if (year % 4 == 0) {
            duration += 29;
        } else {
            duration += 28;
        }
    } else {
        duration += 30;
    }
    return duration;
}

#define sysLog(x) cout << x;

Date::Date() {};
Date::~Date() {}

Date::Date(const Date &otherDate) {
    date = otherDate.date;
    month = otherDate.month;
    year = otherDate.year;
}

Date &Date::operator=(const Date &otherDate) {
    date = otherDate.date;
    month = otherDate.month;
    year = otherDate.year;
    return * this;
}

string Date::dateToString() {
    std::stringstream  ss;
    ss  << std::setfill('0') << std::setw(2) << date << '/'
        << std::setfill('0') << std::setw(2) << month << '/'
        << year;
    return ss.str();
}

int Date::compareDate(Date dateInSys, Date inputDate) {
    //Check if year is conflict
    if (dateInSys.getYear() > inputDate.getYear()) {
        return -1;
    } else if (dateInSys.getYear() < inputDate.getYear()) {
        return 1;
    } else {
        //Check if month is conflict
        if (dateInSys.getMonth() > inputDate.getMonth()) {
            return -1;
        } else if (dateInSys.getMonth() < inputDate.getMonth()) {
            return 1;
        } else {
            //Check if day is conflict
            if (dateInSys.getDate() > inputDate.getDate()) {
                return -1;
            } else if (dateInSys.getDate() < inputDate.getDate()) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}



//---------------------------Getter and setter------------------//
int Date::getMonth() const {
    return month;
}

int Date::getDate() const {
    return date;
}

int Date::getYear() const {
    return year;
}

void Date::setMonth(int month) {
    Date::month = month;
}

void Date::setDate(int date) {
    Date::date = date;
}

void Date::setYear(int year) {
    Date::year = year;
}

bool Date::isDateValid(string date) {
    // Date format dd/MM/yyyy
    //1. Check if the length of the date is valid

    if(date.length() != 10) {
        return false;
    }

    //2. Check if the format of the date is valid
    if (!isdigit(date[0]) || !isdigit(date[1]) || date[2] != '/' ||
        !isdigit(date[3]) || !isdigit(date[4]) || date[5] != '/' ||
        !isdigit(date[6]) || !isdigit(date[7]) || !isdigit(date[8]) ||
        !isdigit(date[9])) {
        return false;
    }

    //Convert input string to Date attribute
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));

    //3. Check if date is valid
    if (day < 1 || day > 31) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    if (year < thisYear()) {
        return false;
    }
    // check if month is 2;
    if (month == 2) {
        if (year % 4 == 0) {
            if (day > 29) {
                return false;
            }
        } else {
            if (day > 28) {
                return false;
            }
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return false;
        }
    }

    return true;
}

Date Date::parseDate(string date) {
    Date dateTemp;
    dateTemp.setDate(std::stoi(date.substr(0, 2)));
    dateTemp.setMonth(std::stoi(date.substr(3, 2)));
    dateTemp.setYear(std::stoi(date.substr(6, 4)));
    return dateTemp;
}

int Date::getDuration(Date start, Date end) {
    int durations = 0;
    int temp = 0;

    int startDay = start.getDate();
    int startMonth = start.getMonth();
    int startYear = start.getYear();

    int endDay = end.getDate();
    int endMonth = end.getMonth();

    if (startMonth == endMonth) {
        durations = endDay - startDay;
    } else {
        for (int i = startMonth; i < endMonth; i++) {
            durations = checkMonth(i, startYear, temp);
        }
        durations += endDay;
    }

    return durations;
}



