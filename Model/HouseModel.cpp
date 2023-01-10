//
// Created by Nguyen Hoang Minh Khoi on 12/27/22.
//
#include "SystemModel.h"
#include "../Libs/Config.h"

//#define sysLog(x) cout << x;

//#define sysErrLog(x) cout << Colors::BOLD_RED_CLS << x << Colors::RESET << "\n"; //log error and new line
#define sysLogInfo(x) cout << Colors::BOLD_GREEN_CLS << x << Colors::RESET << "\n";

House::House(Member *owner, string id, string location, string description, int consumptionPts)
        : owner(owner), id(id), location(location), description(description), creditPointsPerDay(consumptionPts) {}

House::House() {};

House::~House() {};


//---------------------------Setter-------------------------------//
void House::setOwner(Member *owner) {
    House::owner = owner;
}

void House::setOccupier(Member *occupier) {
    House::occupier = occupier;
}

void House::setId(const string &id) {
    House::id = id;
}

void House::setLocation(const string &location) {
    House::location = location;
}

void House::setDescription(const string &description) {
    House::description = description;
}

void House::setCreditPointsPerDay(int creditPointsPerDay) {
    House::creditPointsPerDay = creditPointsPerDay;
}

void House::setMinimumOccupierRating(float minimumOccupierRating) {
    House::minimumOccupierRating = minimumOccupierRating;
}


//-----------------------------Getter-----------------------//
Member *House::getOwner() const {
    return owner;
}

Member *House::getOccupier() const {
    return occupier;
}

const string &House::getId() const {
    return id;
}

string House::getLocation() {
    return location;
}

const string &House::getDescription() const {
    return description;
}

int House::getCreditPointsPerDay() const {
    return creditPointsPerDay;
}

float House::getMinimumOccupierRating() const {
    return minimumOccupierRating;
}

void House::setStartListDate( Date startListDate) {
    House::startListDate = startListDate;
}

void House::setEndListDate( Date endListDate) {
    House::endListDate = endListDate;
}

Date House::getStartListDate() {
    return startListDate;
}

Date House::getEndListDate() {
    return endListDate;
}



//Show info function
void House::showInfo() {

//    string id;
//    string location;
//    string description = "";
//
//    int creditPointsPerDay = 0;
//    float minimumOccupierRating = 0.0;
//
//    Member* owner = nullptr;
//    Member* occupier = nullptr;
////
//    Date startListDate;
//    Date endListDate;

    sysLogInfo("House ID: " + this->id);
    sysLogInfo("Location: " + this->location);
    sysLogInfo("Description: " + this->description);
    sysLogInfo("Credit points per day: " + to_string(this->creditPointsPerDay));
    sysLogInfo("Minimum rating required: " << std::fixed << std::setprecision(2) << this->getMinimumOccupierRating());

}

//---------------------------Rating function---------------//
bool House::hasRatings() {
    System * system = System::getInstance();
    vector<Rating*> ratingVal;
    system->getRatingFromSys(ratingVal, this);

    return ratingVal.size() > 0;
}

float House::sumRating() {
    System * system = System::getInstance();
    if (hasRatings()) {
        vector<Rating*> ratingVal;
        system->getRatingFromSys(ratingVal, this);
        float totalScore = 0.0;
        for (Rating * rating : ratingVal) {
            totalScore += rating->getScore();
        }
        return totalScore / ratingVal.size();
    }
    return 0;
}


bool House::approveRequest(){
    System * system = System::getInstance();
    // Check request status
    Member * owner = system->getCurrentMem();

    vector<Request*> requestList;
    system->getAndShowRequest(requestList, this);

//    if (request->getStatus() != PENDING)
//    {
//        sysErrLog("The request is not in pending");
//        return false;
//    }

    string strBuffer;
    sysLog("Please enter the ID of the request you want to approve: ");
    inputStr(strBuffer);
    bool found = false;
    while (!system->isInteger(strBuffer)) {
        sysErrLog("Invalid format, please try again");
        inputStr(strBuffer);
    }

    Request * request;
    for (Request * requestTemp : requestList) {
        if (strBuffer == requestTemp->getId()) {
            request = requestTemp;
            found = true;
            break;
        } else {
            found = false;
        }
    }

    if (request->getRequester()->getId() == owner->getId()) {
        sysErrLog("You cannot accept your own request");
        return false;
    }

    if (found) {
        if (request->getStatus() != PENDING) {
            sysErrLog("You have approved or denied this request");
            return false;
        }

        int totalCreditPoint = system->getTotalConsumptionPoint(request->getStartDate(), request->getEndDate(), request->getHouse()->getCreditPointsPerDay());
        if (request->getRequester()->getCreditP() - totalCreditPoint < 0) {
            sysErrLog("Requester credit balance is not enough");
            return false;
        }
        system->addCreditPoints(request->getHouse()->getOwner(), totalCreditPoint);
        system->removeCreditPoints(request->getRequester(), totalCreditPoint);
        request->setStatus(APPROVED);
        request->getHouse()->setOccupier(request->getRequester());
        sysLogSuccess("\nApproved request successfully, you received " << Colors::LIGHT_YELLOW_CLS << to_string(totalCreditPoint))
        sysLog("Your current balance: " << owner->getCreditP() << "\n")
        for (Request * temp : requestList) {
            if (temp->getId() != request->getId() && temp->getStatus() ==PENDING) {
                temp->setStatus(DENIED);
            }
        }
        return true;
    } else {
        sysErrLog("Cannot find request with ID " + strBuffer + " in your request list");
        return false;
    }


}

//bool denyRequest(Request* request){
//    return true;
//}
