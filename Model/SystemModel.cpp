//
// Created by Nguyen Hoang Minh Khoi on 12/12/22.
//
#define sysLog(x) cout << x;
#define inputStr(x) getline(cin, x);
#define fileErrLog(x) cout << "Error!!! file " << x << " not found.";
#define formatErr(x) cout << "Error: Invalid " << x <<" format \n";
#define successMess(x, y, z) cout << x << " " << y << " " << z << "\n";

#include "SystemModel.h"
#include <random>
#include "fstream"
#include <sstream>



const string MEMBERS = "members.dat";
const string HOUSES = "houses.dat";
const string REQUESTS = "requests.dat";


//Helper functions
string getFilePath(const string &file) {
    return "../Data/" + file;
}




void Member::showInfo() {
    sysLog("ID: " << this->id << "\n");
    sysLog("Username: " << this->userName <<"\n");
    sysLog("Full name: " << this->fullName <<"\n");
    sysLog("Phone number: " << this->phoneNum <<"\n");
    sysLog("Credit point: " << this->creditP << std::endl);
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
    this->isUserLoggedIn = isLoggedIn;
}

void System::setIsAdmin(bool isAdmin) {
    this->isAdminLoggedin = isAdmin;
}


// ------------------------ * Current user * ------------------------//


Member *System::getCurrentMem() {
    return currentMem;
}

bool System::isUser() const{
    return isUserLoggedIn;
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
        sysLog("Sign up failed, please try again!");
    }
    setCurrentMem(newMem);
    setIsLoggedIn(true);
    string username, password, fullName, phone;
    sysLog("Sign up successfully! awarded with 500 points. \n\n");


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

                sysLog("Login successfully");
                return &i;
            } else {
                sysLog("Incorrect password")
                return nullptr;
            }
        }
    }
    sysLog("Username not found!");
    return nullptr;
}

bool System::logout() {
    setCurrentMem(nullptr);
    setIsLoggedIn(false);
    setIsAdmin(false);

    sysLog("Logout successfully")
    return true;
}


//---------------- Add data to system---------------------//
Member * System::addMemberToSys(Member member) {
    for (auto & i : memberVect) {
        if (i.getUserName() == member.getUserName()) {
            sysLog("This username is already existed");
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

//Request * System::addRequest(Request request) {
//}
//
//Rating * System::addRatingtoSys(Rating rating) {}

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
    successMess("Save", std::to_string(memberVect.size()), "member(s)");
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
        file << house.getId() << ","
             << house.getLocation() << ","
             << house.getDescription() << ","
             << house.getCreditPointsPerDay() << ","
             << house.getOwner()->getId() << "\n";
    }

    file.close();
    successMess("save", std::to_string(houseVect.size()), "house(s)");
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
    successMess("Load", std::to_string(memberVect.size()), "member(s)");
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

        if (tokens.size() != 5) {
            formatErr("house");
            continue;
        }

        System *system = System::getInstance();

        House house;

        string ownerID = tokens[4];
        Member * owner = system->getMember(ownerID);
        if (owner == nullptr) {
            sysLog("Error: Owner with ID " + ownerID + " not found");
            continue;
        }

        house.setOwner(owner);
        house.setId(tokens[0]);
        house.setLocation(tokens[1]);
        house.setDescription(tokens[2]);
        house.setCreditPointsPerDay(std::stoi(tokens[3]));

        houseVect.push_back(house);
        House * newHouse = &houseVect.back();

        owner->setHouse(newHouse);
    }

    countHouse = std::stoi(houseVect.back().getId());

    file.close();
    successMess("Load", std::to_string(houseVect.size()), "house(s)");
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

void System::getAvailableLocation() {
    sysLog("Available locations: ");
    for (string loc : availableLocation) {
        sysLog(" -- " + loc);
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

void System::showHouseDetail() {
    if (currentMem == nullptr) {
        sysLog("Please log in to view house details");
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

    sysLog("House ID: " + house->getId());
    sysLog("Location: " + house->getLocation());
    sysLog("Description: " + house->getDescription());

    if (house.get)
}

void System::showAllHouse() {

}


//------------------------start and exit---------------//

bool System::systemStart() {
    sysLog("Loading data....\n");

    if (!loadMember()) {
        sysLog("Failed to load members!!!");
        return false;
    }

    if (!loadHouse()) {
        sysLog("Failed to load houses!!!");
        return false;
    }

//    if (!loadRating()) {
//        sysLog("Failed to load ratings!!!");
//        return false;
//    }
//
//    if (!loadRequest()) {
//        sysLog("Failed to load requests!!!");
//        return false;
//    }

    sysLog("Data loaded successfully");
    return true;
}

bool System::systemShutdown() {
    sysLog("Saving data....\n");

    if (!saveMember()) {
        sysLog("Failed to save members!!!");
        return false;
    }

    if (!saveHouse()) {
        sysLog("Failed to save houses!!!");
        return false;
    }

//    if (!saveRating()) {
//        sysLog("Failed to save ratings!!!");
//        return false;
//    }
//
//    if (!saveRequest()) {
//        sysLog("Failed to save requests!!!");
//        return false;
//    }

    sysLog("Saved data successfully \n\n");
    sysLog("Shutting down.......\n\n");
    return true;
}




// method