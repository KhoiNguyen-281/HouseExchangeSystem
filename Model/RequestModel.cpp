#include "SystemModel.h"

Request::Request() {}
Request::~Request() {

}

void Request::setHouse(House *house) {
    Request::house = house;
}

void Request::setRequester(Member *requester) {
    Request::requester = requester;
}

void Request::setStatus(int status) {
    Request::status = status;
}


//Getter functions