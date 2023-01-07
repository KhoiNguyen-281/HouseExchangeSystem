//
// Created by Nguyen Hoang Minh Khoi on 12/12/22.
//

#include "SystemModel.h"
#include <random>
#include "fstream"
#include <sstream>
#include "../Libs/Config.h"

#define sysLog(x) cout << x << Colors::RESET;
#define inputStr(x) getline(cin, x);
#define fileErrLog(x) cout << "Error!!! file " << x << " not found.";
#define formatErr(x) cout << "Error: Invalid " << x <<" format \n";

#define skip() cout << "\n\n";


// define log message with color;
#define sysErrLog(x) cout << Colors::BOLD_RED_CLS << x << Colors::RESET << "\n" ; //log error and new line
#define sysLogSuccess(x) cout << Colors::BOLD_GREEN_CLS << x << Colors::RESET << "\n"; //Log data information with green color



const string MEMBERS = "members.dat";
const string HOUSES = "houses.dat";
const string REQUESTS = "requests.dat";
const string RATINGS = "ratings.dat";

//Helper functions
string getFilePath(const string &file) {
    return "./Data/" + file;
}


// Setters

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


// ------------------------ * Current user * ------------------------//


Member *System::getCurrentMem() {
    return currentMem;
}

bool System::isUser() const{
    return isLoggedIn;
}

bool System::isAdmin() const{
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
        sysLog("Sign up failed, please try again! \n");
        return newMem;
    }
    setCurrentMem(newMem);
    setIsLoggedIn(true);
    string username, password, fullName, phone;
    sysLog("Sign up successfully! awarded with 500 points.");
    skip();


    return newMem;
}

Member *System::login(string username, string password) {
    if (username == adminUsername) {
        if (password == adminPassword) {
            setCurrentMem(nullptr);
            setIsLoggedIn(true);
            setIsAdmin(true);
            sysLog("\nLogged in as an admin\n");
            return nullptr;
        } else {
            sysLog("Incorrect password.");
            return nullptr;
        }
    }

    for (auto & i : memberVect) {
        if (i.getUserName() == username) {
            if (i.getPassword() == password) {
                setCurrentMem(&i);
                setIsLoggedIn(true);

                sysLogSuccess("\nLogin successfully \n ");
                return &i;
            } else {
                sysErrLog("Incorrect password")
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


//---------------- Add data to system---------------------//
Member * System::addMemberToSys(Member member) {
    for (auto & i : memberVect) {
        if (i.getUserName() == member.getUserName()) {
            sysErrLog(" \n This username is already existed \n");
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

Rating * System::addRatingtoSys(Rating rating) {
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

Request * System::addRequest(Request request) {
    //When the request ID is empty
    if (request.getId().empty()) {
        //When request is already exist but cannot find ID
        if (currentMem->getRequest() != nullptr && currentMem->getRequest()->getStatus() ==  PENDING) {
            sysLog("\nYou have already request a house \n\n");
            return nullptr;
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

//bool System::saveRequest() {
//    std::fstream file;
//    string filePath = getFilePath(REQUESTS);
//
//    file.open(filePath, std::ios::out);
//    if (!file.is_open()) {
//        fileErrLog(filePath);
//        return false;
//    }
//
//    for (Request request : requestVect) {
//
//    }
//}

bool System::saveRating() {
    std::fstream file;
    string filePath = getFilePath(RATINGS);

    file.open(filePath, std::ios::out);
    if (!file.is_open()) {
        fileErrLog(filePath);
        return false;
    }

    for (const Rating& rating : ratingVect) {
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
    std::fstream file;
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
        member.setPhoneNum(tokens[4]);
        member.setCreditP(std::stoi(tokens[5]));


        memberVect.push_back(member);
    }

    countMem = std::stoi(memberVect.back().getId());

    file.close();
    sysLogSuccess("Loaded " + std::to_string(memberVect.size()) + " member(s)");
    return true;
}

bool System::loadHouse() {
    std::fstream file;
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
    std::fstream file;
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

void System::getAvailableHouse(vector<House *> &list_of_houses, bool isQualified, string location, Date start_date, Date end_date)
{
    for (int i = 0; i < houseVect.size(); i++)
    {
        if (isQualified && houseVect[i].getLocation().compare(location) != 0)
            continue;

        if (isQualified &&
            (Date::compareDate(start_date, houseVect[i].getStartListDate()) < 0 ||
             Date::compareDate(end_date, houseVect[i].getEndListDate()) > 0))
            continue;

        if (isQualified && houseVect[i].getOwner() == currentMem)
            continue;

        list_of_houses.push_back(&houseVect[i]);
    }
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

//-----------------------------Function to view information--------------------------//
void System::viewMember() {
    if (currentMem == nullptr && !isAdminLoggedin) {
        sysErrLog("\n Please login first");
        return;
    }
    if (isAdminLoggedin) {
        for (Member & member: memberVect) {
            member.showInfo();
        }
        return;
    }
    if (currentMem != nullptr) {
        currentMem->showInfo();

        bool hasRatings = currentMem->hasRatings();
        if (hasRatings) {
            float ratingScore = currentMem->sumRating();
            sysLogSuccess("Rating: " << std::fixed << std::setprecision(2) << to_string(ratingScore));
            skip();
        } else {
            skip();
            sysLog("You have not been rated yet. \n\n ");
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
    if (!isLoggedIn) {
        for (House & house : houseVect) {
            house.showInfo();
        }
        return;
    } else if(isAdminLoggedin) {
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
        }
        return;
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
        skip();
        return false;
    }
    string res = "";
    sysLog("Are you sure you want to remove your house from system ? (Y/N) \n");
    inputStr(res);

    if (res == "N" || res == "n") {
        skip();
        return false;
    }

    if (res == "Y" || res == "y") {
        for (House & house  : houseVect) {
            if (house.getId() == houseTmp->getId()) {
                currentMem->setHouse(nullptr);
                houseVect.erase(houseVect.begin() + (std::stoi(house.getId()) - 1));
                skip();
                sysLogSuccess("Remove house successfully!!");
                return true;
            } else {
                skip();
                sysErrLog("Cannot find your house in the system");
                return false;
            }
        }
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

//------------------------start and exit---------------//

bool System::systemStart() {
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
//    if (!loadRequest()) {
//        sysLog("Failed to load requests!!!");
//        return false;
//    }

    sysLogSuccess("Data loaded successfully");
    return true;
}

bool System::systemShutdown() {
    sysLog("Saving data....\n");

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
//    if (!saveRequest()) {
//        sysLog("Failed to save requests!!!");
//        return false;
//    }

    sysLogSuccess("Saved data successfully ");
    skip();
    sysLog("Shutting down.......");
    skip();
    return true;
}





