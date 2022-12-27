//
// Created by Nguyen Hoang Minh Khoi on 12/12/22.
//
#define sysLog(x) cout << x;


#include "SystemModel.h"
#include <random>
#include "fstream"
#include <sstream>


const string MEMBERS = "members.dat";
const string HOUSES = "houses.dat";


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

House * Member::registerHouse(vector<House> &houseVector) {
    string location;
    string description;
    string ptsPerDay;
    string occupierRating;
    sysLog("Please enter your house's information: \n");
    sysLog("Location: ");
    getline(cin, location);
    sysLog("Description: ");
    getline(cin, description);
    sysLog("Points per day: ");
    getline(cin, ptsPerDay);
    sysLog("Occupier rating: ");
    getline(cin, occupierRating);

    auto * house = new House(location, description, std::stoi(ptsPerDay),
                             std::stod(occupierRating), this);
    this->setHouse(house);
    houseVector.push_back(*house);
    return house;
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



//House class
House::House(string location, string description, int ptsPerDay, double occupierRating, Member *owner) {
    int n = 1;
    this->id = "00" + std::to_string(n);
    this->location = location;
    this->description = description;
    this->ptsPerDay = ptsPerDay;
    this->owner = owner;
    this->occupierRating = occupierRating;
    this->available = true;
}


void House::showInfo() {

//    int ptsPerDay = 0;
//    double occupierRating;
//    Member * owner = nullptr;
//    Member* occupier = nullptr;
    cout << "House: " << this->id << "\n";
    cout << "Location: " << this->location << "\n";
    cout << "Description: " << this->description << "\n";
    cout << "Points per day: " << this->ptsPerDay << "\n";
    cout << "Owner: " << this->owner->getUserName() << "\n \n";
}
//Getter and setter
//Getter
const string &House::getLocation() const {
    return location;
}

const string &House::getDescription() const {
    return description;
}

bool House::isAvailable() const {
    return available;
}

int House::getPtsPerDay() const {
    return ptsPerDay;
}

double House::getOccupierRating() const {
    return occupierRating;
}

Member *House::getOwner() const {
    return owner;
}

//Setter
void House::setLocation(const string &location) {
    House::location = location;
}

void House::setDescription(const string &description) {
    House::description = description;
}

void House::setAvailable(bool available) {
    House::available = available;
}

void House::setPtsPerDay(int ptsPerDay) {
    House::ptsPerDay = ptsPerDay;
}

void House::setOccupierRating(double occupierRating) {
    House::occupierRating = occupierRating;
}

void House::setOwner(Member *owner) {
    House::owner = owner;
}

House::~House() {

}




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

string System::generateID() {
    string ID;
    ID  = std::to_string(countMem);
    countMem += 1;
    return ID;
}

Member * System::addMemberToSys(Member member) {
    int count = 1;
    for (auto & i : memberVect) {
        if (i.getUserName() == member.getUserName()) {
            sysLog("This username is already existed");
            return nullptr;
        }
    }

    memberVect.push_back(member);
    Member * newMem = &memberVect.back();

    if (newMem->getId().empty()) {
        string id = generateID();
        newMem->setId(id);
    }
    return newMem;
};

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

           sysLog("Logged in as an admin");
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


//Function to save member
bool System::saveMember() {
    std::ofstream file;
    string filePath = getFilePath(MEMBERS);

    file.open(filePath, std::ios::out);
    if (!file.is_open()) {
        sysLog("Error!!! file " + filePath + " not found.");
        return false;
    }

    for (Member member : memberVect) {
        file << member.getId() << "," << member.getUserName() << ","
             << member.getPassword() << "," << member.getFullName()
             << member.getPhoneNum() << "," << member.getCreditP() << "\n";
    }
    file.close();
    sysLog("Save " + std::to_string(memberVect.size()) + " member(s) \n")

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




// method