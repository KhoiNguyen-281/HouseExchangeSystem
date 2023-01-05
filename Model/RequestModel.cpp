//
// Created by Nguyen Hoang Minh Khoi on 1/3/23.
//
#include "SystemModel.h"

Request::Request() {}
Request::~Request() {

}

void Request::setId(const string &id) {
    Request::id = id;
}

void Request::setHouse(House *house) {
    Request::house = house;
}

void Request::setRequester(Member *requester) {
    Request::requester = requester;
}

void Request::setStartDate(const Date &startDate) {
    start_date = startDate;
}

void Request::setEndDate(const Date &endDate) {
    end_date = endDate;
}

void Request::setStatus(int status) {
    Request::status = status;
}

const string &Request::getId() const {
    return id;
}

House *Request::getHouse() const {
    return house;
}

Member *Request::getRequester() const {
    return requester;
}

const Date &Request::getStartDate() const {
    return start_date;
}

const Date &Request::getEndDate() const {
    return end_date;
}

int Request::getStatus() const {
    return status;
}
//Getter functions
