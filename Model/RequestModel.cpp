#include "SystemModel.h"


#define sysLog(x) cout << x;
#define inputStr(x) getline(cin, x);
#define fileErrLog(x) cout << "Error!!! file " << x << " not found.";
#define formatErr(x) cout << "Error: Invalid " << x << " format \n";
#define skipline() cout << "\n";

#include "iostream"
#include <random>

// define log message with color;
#define sysErrLog(x) cout << Colors::BOLD_RED_CLS << x << Colors::RESET << "\n" ; //log error and new line
#define sysLogSuccess(x) cout << Colors::BOLD_GREEN_CLS << x << Colors::RESET << "\n"; //Log data information with green color



Request::Request() {}
Request::~Request() {

}

void Request::showInfo() {
//    string id = "";
//
//    House *house = nullptr;
//    Member *requester = nullptr;
//
//    Date start_date = Date();
//    Date end_date = Date();
//
//    int status = PENDING;

    sysLogInfo("Request ID: " + this->id);
    sysLogInfo("Requester: ");
    this->getRequester()->showInfo();
    sysLogInfo("Start date: " + this->getStartDate().dateToString());
    sysLogInfo("End date: " + this->getEndDate().dateToString());
    this->getHouse()->showInfo();
    switch (status) {
        case 0:
            sysLogInfo("PENDING");
            break;
        case 1:
            sysLogInfo("APPROVED");
            break;
        case 2:
            sysLogInfo("DENIED");
            break;
        case 3:
            sysLogInfo("FINISHED");
            break;

        default:
            sysLogInfo("N/A");
            break;
    }
    sysLog("\n");
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

Date Request::getStartDate() {
    return start_date;
}

Date Request::getEndDate() {
    return end_date;
}

int Request::getStatus() const {
    return status;
}


//Getter functions

