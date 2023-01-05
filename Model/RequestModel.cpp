//
// Created by Nguyen Hoang Minh Khoi on 1/3/23.
//
#include "SystemModel.h"

Request::Request() {}
Request::~Request() {

}
//Getter functions
const string &Request::getId() const {
    return id;
}

House *Request::getHouse() const {
    return house;
}

Member *Request::getOccupier() const {
    return occupier;
}

const Date &Request::getStartingDate() const {
    return startingDate;
}

const Date &Request::getEndingDate() const {
    return endingDate;
}

int Request::getStatus() const {
    return status;
}

void Request::setId(const string &id) {
    Request::id = id;
}

void Request::setHouse(House *house) {
    Request::house = house;
}

void Request::setOccupier(Member *occupier) {
    Request::occupier = occupier;
}

void Request::setStartingDate(const Date &startingDate) {
    Request::startingDate = startingDate;
}

void Request::setEndingDate(const Date &endingDate) {
    Request::endingDate = endingDate;
}

void Request::setStatus(int status) {
    Request::status = status;
}
