//
// Created by Nguyen Hoang Minh Khoi on 12/27/22.
//
#include "SystemModel.h"
#define sysLog(x) cout << x;

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

