//
// Created by Nguyen Hoang Minh Khoi on 12/12/22.
//
#define sysLog(x) cout << x;
#define inputStr(x) getline(cin, x);
#define fileErrLog(x) cout << "Error!!! file " << x << " not found.";
#define formatErr(x) cout << "Error: Invalid " << x << " format \n";
#define successMess(x, y, z) cout << x << " " << y << " " << z << "\n";
#define skipline() cout << "\n";

#include "SystemModel.h"
#include "iostream"
#include <random>
#include "fstream"
#include <sstream>
#include <cmath>

// define log message with color;
#define sysErrLog(x) cout << Colors::BOLD_RED_CLS << x << Colors::RESET << "\n" ; //log error and new line
#define sysLogSuccess(x) cout << Colors::BOLD_GREEN_CLS << x << Colors::RESET << "\n"; //Log data information with green color



const string MEMBERS = "members.dat";
const string HOUSES = "houses.dat";
const string REQUESTS = "requests.dat";
const string RATINGS = "ratings.dat";


#include "../Libs/Config.h"
//Helper functions
string getFilePath(const string &file) {
    return "../Data/" + file;
}



Date System::currentDate() {
    std::time_t t = std::time(nullptr);
    std::tm *const pointerInfo =  std::localtime(&t);
    int month = pointerInfo->tm_mon + 1;
    int year = thisYear();
    int day = pointerInfo->tm_mday;
    Date currentDate;
    currentDate.setDay(day);
    currentDate.setMonth(month);
    currentDate.setYear(year);

    return currentDate;
}




//int Member::unListHouse(vector<House> &houseVector) {
//    if (this == nullptr) {
//        sysLog("You have not logged in the system yet");
//        return 0;
//    }
//    string choice;
//    sysLog("Do you really want to remove this house ? (Y/N)");
//    getline(cin, choice);
//    bool found = false;
//    int count  = 0;
//    if (choice == "Y" || choice ==  "y") {
//        for (auto & i : houseVector) {
//            if (i.getOwner() ==  this) {
//                found = true;
//            }
//            count += 1;
//        }
//        if (found) {
//            this->setHouse(nullptr);
//            houseVector.erase(houseVector.begin() + count);
//            sysLog("Remove house successfully");
//            return 0;
//        } else {
//            sysLog("Your house does not exist in the system");
//            return 0;
//        }
//    } else if (choice == "N" || choice == "n") {
//        return 0;
//    }
//    return 0;
//}
// Getter and setter function




//Setter


//void House::showInfo() {
//
////    int ptsPerDay = 0;
////    double occupierRating;
////    Member * owner = nullptr;
////    Member* occupier = nullptr;
//    cout << "House: " << this->id << "\n";
//    cout << "Location: " << this->location << "\n";
//    cout << "Description: " << this->description << "\n";
//    cout << "Points per day: " << this->ptsPerDay << "\n";
//    cout << "Owner: " << this->owner->getUserName() << "\n \n";
//}


//Getter and setter
//Getter




System::System() {

}
System::~System() {
    delete this->instancePointer;
}

System * System::instancePointer = nullptr;

System *System::getInstance() {
    if (instancePointer == nullptr) {
        instancePointer = new System();
    }
    return instancePointer;
}


//Current user functions
void System::setCurrentMem(Member *currentMem) {
    this->currentMem = currentMem;
}

void System::setIsLoggedIn(bool isLoggedIn) {
    this->isLoggedIn = isLoggedIn;
}

void System::setIsAdmin(bool isAdmin) {
    this->isAdminLoggedin = isAdmin;
}

bool System::hasRequest() {
    if (currentMem->getHouse()  != nullptr) {
        return false;
    } else {
        for (Request & request : requestVect) {
            if (request.getHouse()->getId() ==  currentMem->getHouse()->getId()) {
                return true;
            }
        }
    }
    return false;
}

// ------------------------ * Current user * ------------------------//


Member *System::getCurrentMem() {
    return currentMem;
}

bool System::isUser(){
    return isLoggedIn;
}

bool System::isAdmin(){
    return isAdminLoggedin;
}

string System::generateID(int &count) {
    string ID;
    count += 1;
    ID = std::to_string(count);
    return ID;
}

Member * System::registerMember(Member member) {
    Member * newMem = addMemberToSys(member);
    if (newMem == nullptr) {
        sysErrLog("Sign up failed, please try again! \n");
        return newMem;
    }
    setCurrentMem(newMem);
    setIsLoggedIn(true);
    sysLogSuccess("Sign up successfully! awarded with 500 points. \n");
//    skipline();

    return newMem;
}

Member *System::login(string username, string password) {
    if (username == adminUsername) {
        if (password == adminPassword) {
            setCurrentMem(nullptr);
            setIsLoggedIn(true);
            setIsAdmin(true);
            sysLogSuccess("\nLogged in as an admin\n");
            return nullptr;
        } else {
            sysErrLog("Incorrect password.");
            return nullptr;
        }
    }

    for (Member & i : memberVect) {
        if (i.getUserName() == username) {
            if (i.getPassword() == password) {
                setCurrentMem(&i);
                setIsLoggedIn(true);
                if (i.getHouse() != nullptr) {
                    for (Request& request : requestVect) {
                        if (request.getHouse()->getOwner()->getId() == i.getId() && request.getStatus() == APPROVED) {
                            i.getHouse()->setOccupier(request.getRequester());
                        }
                    }
                }

                if (i.getRequest() != nullptr) {
                    if (i.getRequest()->getStatus() == APPROVED) {
                        sysLog("You have been approved to occupy house: ");
                        i.getRequest()->getHouse()->showInfo();
                    }
                }
                sysLogSuccess("Logged in successfully\n")
                return &i;
            } else {
                sysErrLog("Wrong password, please try again")
                return nullptr;
            }
        }
    }
    sysErrLog("Username not found!");
    return nullptr;
}

bool System::logout() {
    setCurrentMem(nullptr);
    setIsLoggedIn(false);
    setIsAdmin(false);

    sysLogSuccess("\nLogout successfully \n ")
    return true;
}

bool System::deleteProfile(string password) {
    Member member = *currentMem;

    for (int i = 0; i < memberVect.size(); i++) {
        if (memberVect[i].getId() == member.getId()) {
            if (memberVect[i].getPassword() != password) {
                sysErrLog("Incorrect password");
                return false;
            }

            for (int j = 0; j < houseVect.size(); j++) {
                if (houseVect[j].getId() == member.getHouse()->getId()) {
                    houseVect.erase(houseVect.begin() + i);
                }
            }

            memberVect.erase(memberVect.begin() + i);

            for (int k = 0; k < houseVect.size(); k++ ) {
                houseVect[k].setId(to_string(k + 1));
            }

            for (int u = 0; u < memberVect.size(); u ++) {
                memberVect[u].setId(to_string(u + 1));
            }

            countMem = stoi(memberVect.back().getId());
            countHouse = stoi(houseVect.back().getId());

            setCurrentMem(nullptr);
            setIsLoggedIn(false);
            setIsAdmin(false);

            return true;
        }
    }
    sysErrLog("Profile not found!!!");
    return false;
}


//---------------- Add data to system---------------------//
Member * System::addMemberToSys(Member member) {
    for (Member & i : memberVect) {
        if (i.getUserName() == member.getUserName()) {
            sysErrLog("This username is already existed \n");
            return nullptr;
        }
    }

    memberVect.push_back(member);
    Member * newMem = &memberVect.back();
    if (newMem->getId().empty()) {
        string id = generateID(countMem);
        newMem->setId(id);
    }
    return newMem;
};

House * System::addHouseToSys(House house) {
    if (house.getId().empty()) {
        string houseID = generateID(countHouse);

        houseVect.push_back(house);
        House * newHouse = &houseVect.back();
        newHouse->setId(houseID);
        return newHouse;
    } else {
        for (auto  & houseTmp: houseVect) {
            if (houseTmp.getId() == house.getId()) {
                houseTmp = house;
                houseTmp.setId(house.getId());

                return &houseTmp;
            }
        }
        return nullptr;
    }
}

Rating * System::addRatingToSys(Rating rating) {
    //Check if rating already exist in system
    for (Rating & temp : ratingVect) {
        if (temp.getHouse()->getId() == rating.getHouse()->getId()
            && temp.getRater()->getId() == rating.getRater()->getId()) {
            temp = rating;
            return &temp;
        }
    }
    ratingVect.push_back(rating);
    Rating * newRating = &ratingVect.back();
    return newRating;
}

Request * System::addRequestToSys(Request request) {
    //When the request ID is empty

    for (Request & i : requestVect) {

        //check if date conflict
        if (i.getHouse()->getId() == request.getHouse()->getId()) {
            //check if start date in system is greater
            if (Date::compareDate(i.getStartDate(), request.getStartDate()) < 0) {
                if (Date::compareDate(i.getEndDate(), request.getEndDate()) <= 0) {
                    break;
                }
                else {
                    sysErrLog("This house is not available for that date;")
                    return nullptr;
                }
            }
            //check if start date in system is smaller
            if (Date::compareDate(i.getStartDate(), request.getStartDate()) > 0) {
                if (Date::compareDate(i.getEndDate(), request.getEndDate()) >= 0) {
                    break;
                } else {
                    sysErrLog("This house is not available for that date;")
                    return nullptr;
                }
            } else {
                sysErrLog("This house is not available for that date;")
                return nullptr;
            }

        } else {
            continue;
        }
    }

    if (request.getId().empty()) {
        //When request is already exist but cannot find ID
        if (currentMem->getRequest() != nullptr && currentMem->getRequest()->getStatus() ==  PENDING) {
            request = *currentMem->getRequest();
            return &request;
        }
        string ID = generateID(countRequest);

        requestVect.push_back(request);
        Request * newRequest = &requestVect.back();

        newRequest->setId(ID);
        return newRequest;
    } else {
        for (Request & temp : requestVect) {
            if (temp.getId() ==  request.getId()) {
                temp = request;
                temp.setId(request.getId());
                return &temp;
            }
        }
    }

    return nullptr;
}
//

//------------------------Function to add and decrease credit points-----------------------//
bool System::addCreditPoints(Member * member, int creditP) {
    if (member == nullptr) {
        sysErrLog("Member not found!!!");
        return false;
    }

    int newPoints = member->getCreditP() + creditP;
    if (newPoints < 0) {
        sysErrLog("Your credit points balance is not enough!!!");
        return false;
    }

    member->setCreditP(newPoints);
    return true;
}

bool System::removeCreditPoints(Member *member, int creditP) {
    if (member == nullptr) {
        sysErrLog("Member not found!!!");
        return false;
    }

    int newPoint = member->getCreditP() - creditP;
    if (newPoint < 0) {
        sysErrLog("Your credit points balance is not enough!!!");
        return false;
    }

    member->setCreditP(newPoint);
    return true;
}


//--------------------Save data to files-------------------//
bool System::saveMember() {
    std::ofstream file;
    string filePath = getFilePath(MEMBERS);

    file.open(filePath, std::ios::out);
    if (!file.is_open()) {
        fileErrLog(filePath);
        return false;
    }

    for (Member member : memberVect) {
        file << member.getId() << "," << member.getUserName() << ","
            << member.getPassword() << "," << member.getFullName() << ","
            << member.getPhoneNum() << "," << member.getCreditP() << "\n";
    }
    file.close();
    sysLogSuccess("Saved " +  std::to_string(memberVect.size()) + " member(s)");
    return true;
}

bool System::saveHouse() {
    std::ofstream  file;
    string filePath = getFilePath(HOUSES);

    file.open(filePath, std::ios::out);
    if (!file.is_open()) {
        fileErrLog(filePath);
        return false;
    }

    for (House house : houseVect) {
        file
             << house.getId() << ","
             << house.getLocation() << ","
             << house.getDescription() << ","
             << house.getStartListDate().dateToString() << ","
             << house.getEndListDate().dateToString() << ","
             << house.getCreditPointsPerDay() << ","
             << house.getMinimumOccupierRating() << ","
             << house.getOwner()->getId() << "\n";
    }

    file.close();
    sysLogSuccess("Saved " + std::to_string(houseVect.size()) + " house(s)");
    return true;
}

bool System::saveRequest() {
    std::ofstream file;
    string filePath = getFilePath(REQUESTS);

    file.open(filePath, std::ios::out);
    if (!file.is_open()) {
        fileErrLog(filePath);
        return false;
    }

    for (Request request : requestVect) {
        file << request.getId() << ","
             << request.getRequester()->getId() << ","
             << request.getHouse()->getId() << ","
             << request.getStartDate().dateToString() << ","
             << request.getEndDate().dateToString() << ","
             << request.getStatus() << "\n";
    }
    file.close();
    sysLogSuccess("Saved " + to_string(requestVect.size()) + " request(s)");
    return true;
}

bool System::saveRating() {
    std::ofstream file;
    string filePath = getFilePath(RATINGS);

    file.open(filePath, std::ios::out);
    if (!file.is_open()) {
        fileErrLog(filePath);
        return false;
    }

    for (Rating& rating : ratingVect) {
        file << rating.getRater()->getId() << ","
             << rating.getHouse()->getId() << ","
             << (rating.getOccupier() != nullptr ? rating.getOccupier()->getId() : "NONE") << ","
             << rating.getScore() << ","
             << rating.getComment() << "\n";
    }

    file.close();
    sysLogSuccess("Saved " + to_string(ratingVect.size()) + " rating(s)");
    return true;
}

//Function to change pasword
bool System::changePassword(string newpwd, string oldpwd) {
    if (this->currentMem->getPassword() == oldpwd) {
        this->currentMem->setPassword(newpwd);
        return true;
    }
    else {
        return false;
    }
}


//-------------------Load data from file------------------//
bool System::loadMember() {
    std::ifstream file;
    string filePath = getFilePath(MEMBERS);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        fileErrLog(filePath);
        return false;
    }

    string line;
    while(getline(file, line)) {
        std::stringstream ss(line);
        string attribute;
        vector<string> tokens;

        while(getline(ss, attribute, ',')) {
            tokens.push_back(attribute);
        }

        if (tokens.size() != 6) {
            formatErr("member");
            continue;
        }

        Member member;

        member.setId(tokens[0]);
        member.setUserName(tokens[1]);
        member.setPassword(tokens[2]);
        member.setFullName(tokens[3]);
        member.setPhoneNum(stoi(tokens[4]));
        member.setCreditP(std::stoi(tokens[5]));


        memberVect.push_back(member);
    }

    countMem = std::stoi(memberVect.back().getId());
    file.close();
    sysLogSuccess("Loaded " + std::to_string(memberVect.size()) + " member(s)");
    return true;
}

bool System::loadHouse() {
    std::ifstream file;
    string filePath = getFilePath(HOUSES);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        fileErrLog(filePath);
        return false;
    }

    string line;
    while(getline(file, line)) {
        std::stringstream ss(line);
        string attribute;
        vector<string> tokens;
        while (getline(ss, attribute, ',')) {
            tokens.push_back(attribute);
        }
        if (tokens.size() != 8) {
            formatErr(Colors::BOLD_RED_CLS  + "house");
            continue;
        }

        House house;

        string ownerID = tokens[7];
        Member * owner = getMember(ownerID);
        if (owner == nullptr) {
            sysErrLog("Error: Owner with ID " + ownerID + " not found");
            continue;
        }

        house.setOwner(owner);
        house.setId(tokens[0]);
        house.setLocation(tokens[1]);
        house.setDescription(tokens[2]);
        house.setStartListDate(Date::parseDate(tokens[3]));
        house.setEndListDate(Date::parseDate(tokens[4]));
        house.setCreditPointsPerDay(std::stoi(tokens[5]));
        house.setMinimumOccupierRating(std::stof(tokens[6]));

        houseVect.push_back(house);
        House * newHouse = &houseVect.back();

        owner->setHouse(newHouse);
    }

    countHouse = std::stoi(houseVect.back().getId());

    file.close();
    sysLogSuccess("Loaded " + std::to_string(houseVect.size()) + " house(s)");
    return true;
}

bool System::loadRating() {
    std::ifstream file;
    string filePath = getFilePath(RATINGS);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        fileErrLog(Colors::BOLD_RED_CLS + filePath);
        return false;
    }

    string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        string attribute;
        vector<string> tokens;

        while (getline(ss, attribute, ',')) {
            tokens.push_back(attribute);
        }

        if (tokens.size() != 5) {
            formatErr(Colors::BOLD_RED_CLS + "rating")
            continue;
        }

        Rating rating;

        string raterID = tokens[0];
        string houseId = tokens[1];
        string occupierID = tokens[2];
        string scoreStr = tokens[3];
        string comment = tokens[4];

        House* house = getHouse(houseId);
        Member* rater = getMember(raterID);
        Member* occupier;
        if (occupierID == "NONE") {
            occupier = nullptr;
        } else {
            occupier = getMember(occupierID);
        }

        if (house == nullptr) {
            sysErrLog("House with ID: " + house->getId() + " not found!!!");
            continue;
        }

        if (rater == nullptr) {
            sysErrLog("Author with ID: " + rater->getId() + " not found!!!");
            continue;
        }

        rating.setHouse(house);
        rating.setRater(rater);
        rating.setOccupier(occupier);
        rating.setScore(std::stof(scoreStr));
        rating.setComment(comment);

        ratingVect.push_back(rating);
    }

    file.close();
    sysLogSuccess("Loaded " + std::to_string(ratingVect.size()) + " rating(s)");

    return true;
}

bool System::loadRequest() {
    std::ifstream file;
    string filePath = getFilePath(REQUESTS);

    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        fileErrLog(Colors::BOLD_RED_CLS + filePath);
        return false;
    }

    string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        string attribute;
        vector<string> tokens;

        while (getline(ss, attribute, ',')) {
            tokens.push_back(attribute);
        }

        if (tokens.size() != 6) {
            formatErr(Colors::BOLD_RED_CLS + "rating")
            continue;
        }

        Request request;

        string requesterID = tokens[1];
        string houseId = tokens[2];

        House* house = getHouse(tokens[2]);
        Member* requester = getMember(tokens[1]);

        if (house == nullptr) {
            sysErrLog("House with ID: " + house->getId() + " not found!!!");
            continue;
        }

        if (requester == nullptr) {
            sysErrLog("Member with ID: " + requester->getId() + " not found!!!");
            continue;
        }

        request.setId(tokens[0]);
        request.setRequester(requester);
        request.setHouse(house);
        request.setStartDate(Date::parseDate(tokens[3]));
        request.setEndDate(Date::parseDate(tokens[4]));
        request.setStatus(stoi(tokens[5]));

        requestVect.push_back(request);
    }

    file.close();
    countRequest = stoi(requestVect.back().getId());
    sysLogSuccess("Loaded " + std::to_string(ratingVect.size()) + " request(s)");

    return true;
}


//---------------------Instance getter-------------//
Member * System::getMember(string ID) {
    for (Member &member : memberVect) {
        if (member.getId() ==  ID) {
            return &member;
        }
    }
    return nullptr;
}

House * System::getHouse(string ID) {
    for (House &house : houseVect) {
        if (house.getId() == ID) {
            return &house;
        }
    }
    return nullptr;
}

void System::getAvailableHouses(vector<House *> &availableHouses, bool isQualified, const string& location, Date startingDate,
                                Date endingDate) {
    for (auto & i : houseVect) {
        if (isQualified && i.getLocation() != location)
            continue;

        if (isQualified &&
            (Date::compareDate(i.getStartListDate(), startingDate) < 0 ||
             Date::compareDate(i.getEndListDate(), endingDate) > 0))
            continue;

        if (isQualified && i.getOwner() == currentMem)
            continue;

        availableHouses.push_back(&i);
    }
}

int System::getTotalConsumptionPoint(Date startDate, Date endDate, int creditPoints) {
    return Date::getDuration(startDate, endDate) * creditPoints;
}

void System::getAvailableLocation() {
    sysLog("Available locations: ");
    int count = 1;
    for (string loc : availableLocation) {
        sysLog(" -"+ to_string(count) +"- " + loc);
        count += 1;
    }
    sysLog("\n");
}

bool System::checkLocation(string location) {
    for (string loc : availableLocation) {
        if (loc ==  location) {
            return true;
        }
    }
    return false;
}

bool System::isInteger(const string& input) {
    for (char i : input) {
        if (!isdigit(i)) {
            return false;
        }
    }
    return true;
}

bool verifyPassword(string inputPassword, string memberPassword) {
    return inputPassword == memberPassword;
}

//-----------------------------Function to view information--------------------------//

void System::viewMember() {
    if (currentMem == nullptr && !isAdminLoggedin) {
        sysErrLog("\n Please login first");
        return;
    }
    if (isAdminLoggedin) {
        for (Member & member: memberVect) {
            member.showInfo();
            skipline();
        }
        return;
    }
    if (currentMem != nullptr) {
        currentMem->showInfo();
        if (currentMem->getHouse() != nullptr) {
            viewHouseDetail();
        }
        bool hasRatings = currentMem->hasRatings();
        if (hasRatings) {
            float ratingScore = currentMem->sumRating();
            sysLogSuccess("Rating: " << std::fixed << std::setprecision(2) << to_string(ratingScore));
            skipline();

        } else {
            sysLog("You have not been rated yet.");
        }
        return;
    }
}

void System::viewHouseDetail() {
    if (currentMem == nullptr) {
        sysErrLog("\n Please login to view house details");
        return;
    }

    House * house = currentMem->getHouse();

    if (house == nullptr) {
        sysLog("You have not registered any house yet");
        string choice;
        sysLog("Do you want to register your house ? (Y/N)");
        inputStr(choice);
        if (choice == "N" || choice == "n") {
            return;
        }
        if (choice != "Y" || choice  != "y") {
            sysLog(" \n Invalid response \n");
            return;
        }
        currentMem->registerHouse();
        return;
    }

    house->showInfo();
    sysLogSuccess("Listing start date: " + house->getStartListDate().dateToString());
    sysLogSuccess("Listing end date: " + house->getEndListDate().dateToString());
    bool hasRatings = house->hasRatings();

    if (hasRatings) {
        float ratingScore = house->sumRating();
        sysLogSuccess("Rating: " << std::fixed << std::setprecision(2) << ratingScore);
    } else {
        sysErrLog("Your house has not been rated yet");
    }

    if (house->getOccupier() != nullptr) {
        sysLogSuccess("Occupier name: " + house->getOccupier()->getFullName());
        sysLogSuccess("Occupier phone: " + house->getOccupier()->getPhoneNum());
    }

}

void System::viewAllHouse() {
    if (houseVect.empty()) {
        sysLog("There are not any house in the system")
        return;
    }

    if (isUser()) {
        for (House & house : houseVect) {
            house.showInfo();
            sysLogSuccess("Listing start date: " + house.getStartListDate().dateToString());
            sysLogSuccess("Listing end date: " + house.getEndListDate().dateToString());


            if (house.hasRatings()) {
                float ratingScore = house.sumRating();
                sysLogSuccess("Rating: " << std::fixed << std::setprecision(2) << ratingScore);
            }

            skipline()
        }
        return;
    }

    if(isAdmin()) {
        for (House & house : houseVect) {
            house.showInfo();
            sysLogSuccess("Listing start date: " + house.getStartListDate().dateToString());
            sysLogSuccess("Listing end date: " + house.getEndListDate().dateToString());

            if (house.getOccupier() != nullptr) {
                sysLogSuccess("Occupier name: " + house.getOccupier()->getFullName());
                sysLogSuccess("Occupier phone: " + house.getOccupier()->getPhoneNum());
            }
            if (house.hasRatings()) {
                float ratingScore = house.sumRating();
                sysLogSuccess("Rating: " << std::fixed << std::setprecision(2) << ratingScore);
            }
            skipline();
        }
        return;
    }

    for (House & house : houseVect) {
        house.showInfo();
        skipline();
    }
}

void System::getAndShowRequest(vector<Request *> &requestList, House * house) {
    if (currentMem == nullptr) {
        sysErrLog("You have not logged in yet \n");
        return;
    }

    if (requestVect.empty()) {
        sysLog("There are 0 request in the system \n");
        return;
    }

    for (Request & request : requestVect) {
        if (request.getHouse()->getId() == house->getId()) {
            requestList.push_back(&request);
        }
    }
}

bool System::removeHouse() {
    if (currentMem == nullptr) {
        sysLog("You must login first !\n \n");
        return false;
    }

    House * houseTmp = currentMem->getHouse();

    if (houseTmp == nullptr) {
        sysLog("You have not register any house yet");
        skipline();
        return false;
    }
    string res = "";
    sysLog("Are you sure you want to remove your house from system ? (Y/N) \n");
    sysLog("Your response: ");
    inputStr(res);

    if (res == "N" || res == "n") {
        skipline();
        return false;
    }

    bool found = false;
    if (res == "Y" || res == "y") {
        for (House & house  : houseVect) {
            if (house.getId() == houseTmp->getId()) {
                found = true;
                houseTmp = &house;
                break;
            } else {
                continue;
            }
        }
    }

    if (found) {
        currentMem->setHouse(nullptr);
        houseVect.erase(houseVect.begin() + (stoi(houseTmp->getId()) - 1));
        skipline();
        sysLogSuccess("Remove house successfully!!");
        return true;
    } else {
        skipline();
        sysErrLog("Cannot find your house in the system");
        return false;
    }

    sysErrLog("Invalid response");
    return false;
}



//------------------------Get rating function----------------//
void System::getRatingFromSys(vector<Rating*>& ratingVal, Member * requester) {
    for (Rating & rating : ratingVect) {
        if (rating.getOccupier() != nullptr && rating.getOccupier()->getId() == requester->getId()) {
            ratingVal.push_back(&rating);
        }
    }
}

void System::getRatingFromSys(vector<Rating *>& ratingVal, House *house) {
    for (Rating & rating : ratingVect) {
        if (rating.getOccupier() == nullptr && rating.getHouse()->getId() == house->getId()) {
            ratingVal.push_back(&rating);
        }
    }
}

//void System::getRequestFromSys(vector<Request*> &requestVal, House * house) {
//    for (Request & request : requestVect) {
//        if (request.getHouse()->getId() == house->getId()) {
//            requestVal.push_back(&request);
//        }
//    }
//}

//------------------------Get request by location function----------------//

//------------------------start and exit---------------//

bool System::systemStart() {
    changeStatusOfRequestAuto();
    sysLog("Loading data....\n");

    if (!loadMember()) {
        sysErrLog("Failed to load members!!!");
        return false;
    }

    if (!loadHouse()) {
        sysErrLog("Failed to load houses!!!");
        return false;
    }

    if (!loadRating()) {
        sysErrLog("Failed to load ratings!!!");
        return false;
    }

//
    if (!loadRequest()) {
        sysLog("Failed to load requests!!!");
        return false;
    }

    sysLogSuccess("Data loaded successfully");
    return true;
}

bool System::systemShutdown() {
    sysLog("\nSaving data....\n");

    if (!saveMember()) {
        sysErrLog("Failed to save members!!!");
        return false;
    }

    if (!saveHouse()) {
        sysErrLog("Failed to save houses!!!");
        return false;
    }

    if (!saveRating()) {
        sysErrLog("Failed to save ratings!!!");
        return false;
    }
//
    if (!saveRequest()) {
        sysLog("Failed to save requests!!!");
        return false;
    }
    sysLogSuccess("Saved data successfully ");
    sysLog("Shutting down.......");
    skipline();
    return true;
}


//--------------------------------Request function--------------------------------//

bool System::isHouseSuitable(House house, string start, string end) {
    int totalConsumptionPoints;
    if (start == "" || end == "" ) {
        totalConsumptionPoints = 0;
    } else {
        totalConsumptionPoints = getTotalConsumptionPoint(Date::parseDate(start), Date::parseDate(end), house.getCreditPointsPerDay());
    }

    if (currentMem->getCreditP() - house.getCreditPointsPerDay() <= 0) {
        return false;
    }
    if (currentMem->getCreditP() - totalConsumptionPoints <= 0) {
         return false;
    }
    if (currentMem->hasRatings()) {
        if (currentMem->sumRating() - house.getMinimumOccupierRating() >= 0) {
            return false;
        }
    }

    return true;
}
void System::getHouseByDate(vector<House*> &availableHouse,  Date start,  Date end) {

    for (auto & i : houseVect) {
        if (Date::compareDate(i.getStartListDate(), start) >= 0
        && Date::compareDate(i.getEndListDate(), end) <= 0) {
            if (isHouseSuitable(i, start.dateToString() , end.dateToString())) {
            availableHouse.push_back(&i);
            }
        }
    }
}

void System::getHouseByLoc(vector<House*>& availableHouse, const string& location){
    for (House & i : houseVect) {
        if (i.getLocation() == location) {
            if (isHouseSuitable(i, "", "")) {
                availableHouse.push_back(&i);
            }
        }
    }
}

void System::getHouseWithCreditPoint(vector<House *> &availableHouse) {
    int temp = currentMem->getCreditP();
    for (House & house : houseVect) {
        if (temp - house.getCreditPointsPerDay() >= 0) {
            availableHouse.push_back(&house);
        }
    }
}

void System::getHouseByCreditInRange(vector<House*> &availableHouse, int creditFrom, int creditTo) {
    for (House & house : houseVect) {
        if (house.getCreditPointsPerDay() >= creditFrom && house.getCreditPointsPerDay() <= creditTo) {
            availableHouse.push_back(&house);
        }
    }
}


int System::changeStatusOfRequestAuto() {
    for (Request & request : requestVect) {
        if (Date::compareDate(currentDate(), request.getEndDate()) >= 0 && request.getStatus() == APPROVED) {

            int totalCreditPoint = getTotalConsumptionPoint(request.getStartDate(),
                                                            request.getEndDate(),
                                                            request.getHouse()->getCreditPointsPerDay());

            addCreditPoints(request.getHouse()->getOwner(), totalCreditPoint);
            removeCreditPoints(request.getRequester(), totalCreditPoint);
            request.setStatus(FINISHED);
            return FINISHED;
        } else if (Date::compareDate(currentDate(), request.getEndDate()) >= 0 && request.getStatus() == PENDING) {
            request.setStatus(DENIED);
            return DENIED;
        }
    }
    return 0;
}





// method