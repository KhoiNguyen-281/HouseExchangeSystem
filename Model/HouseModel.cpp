//
// Created by Nguyen Hoang Minh Khoi on 12/27/22.
//
#include "SystemModel.h"
#include "../Libs/Config.h"

#define sysLog(x) cout << x;

#define sysErrLog(x) cout << Colors::BOLD_RED_CLS << x << Colors::RESET << "\n"; //log error and new line
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

const string &House::getLocation() const {
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
