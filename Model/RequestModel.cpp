//
// Created by Nguyen Hoang Minh Khoi on 1/3/23.
//
#include "SystemModel.h"

Request::Request() {}
Request::~Request() {

}
//Getter functions
void Request::setId(string id)
{
    this->id = id;
}

void Request::setHouse(House *house)
{
    this->house = house;
}

void Request::setRequester(Member *requester)
{
    this->requester = requester;
}

void Request::setStartingDate(Date startingDate)
{
    this->start_date = startingDate;
}

void Request::setEndingDate(Date endingDate)
{
    this->end_date = endingDate;
}

void Request::setStatus(int status)
{
    this->status = status;
}

// Getters
string Request::getId()
{
    return this->id;
}

House *Request::getHouse()
{
    return this->house;
}

Member *Request::getRequester()
{
    return this->requester;
}

Date Request::getStartingDate()
{
    return this->start_date;
}

Date Request::getEndingDate()
{
    return this->end_date;
}

int Request::getStatus()
{
    return this->status;
}
