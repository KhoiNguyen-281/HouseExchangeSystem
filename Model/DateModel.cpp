//
// Created by Nguyen Hoang Minh Khoi on 12/27/22.
//
#include "SystemModel.h"

Date::Date() {};
Date::~Date() {}

Date::Date(Date &otherDate) {
    date = otherDate.date;
    month = otherDate.month;
    year = otherDate.year;
}