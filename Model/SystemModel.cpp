//
// Created by Nguyen Hoang Minh Khoi on 12/12/22.
//
#define sysLog(x) cout << x;
#define inputStr(x) getline(cin, x);
#define fileErrLog(x) cout << "Error!!! file " << x << " not found.";
#define formatErr(x) cout << "Error: Invalid " << x << " format \n";
#define successMess(x, y, z) cout << x << " " << y << " " << z << "\n";
#define skip() cout << "\n\n";

#include "SystemModel.h"
#include <random>
#include "fstream"
#include <sstream>

const string MEMBERS = "members.dat";
const string HOUSES = "houses.dat";
const string REQUESTS = "requests.dat";
const string RATINGS = "requests.dat";

#include "../Libs/Config.h"
// define log message with color;
#define sysErrLog(x) cout << BOLD_RED_CLS << x << "\n";       // log error and new line
#define sysLogSuccess(x) cout << BOLD_GREEN_CLS << x << "\n"; // Log data information with green color

// Helper functions
string getFilePath(const string &file)
{
    return "../Data/" + file;
}

void Member::showInfo()
{
    sysLog("ID: " << this->id << "\n");
    sysLog("Username: " << this->userName << "\n");
    sysLog("Full name: " << this->fullName << "\n");
    sysLog("Phone number: " << this->phoneNum << "\n");
    sysLog("Credit point: " << this->creditP << std::endl);
}

bool Member::bookAccommodation(House *house, Date startingDate, Date endingDate)
{
    System *system = System::getInstance();
    // Create a new request
    Request request;

    // Set request data.
    request.setRequester(this);
    request.setHouse(house);
    request.setStartingDate(startingDate);
    request.setEndingDate(endingDate);

    // cout << "current ID = " << request.getId() << "\n";

    //    request.showInfo();
    // Add a new request to the system.
    Request *newRequest = System::getInstance()->addRequest(request, request.getId());

    //    newRequest->showInfo();

    // Check if the request was added successfully.
    if (newRequest != nullptr)
    {
        cout << "Request added successfully.\n";
        setRequest(newRequest);

        return true;
    }
    else
    {
        cout << "Request failed.\n";
        return false;
    }
}

// int Member::unListHouse(vector<House> &houseVector) {
//     if (this == nullptr) {
//         sysLog("You have not logged in the system yet");
//         return 0;
//     }
//     string choice;
//     sysLog("Do you really want to remove this house ? (Y/N)");
//     getline(cin, choice);
//     bool found = false;
//     int count  = 0;
//     if (choice == "Y" || choice ==  "y") {
//         for (auto & i : houseVector) {
//             if (i.getOwner() ==  this) {
//                 found = true;
//             }
//             count += 1;
//         }
//         if (found) {
//             this->setHouse(nullptr);
//             houseVector.erase(houseVector.begin() + count);
//             sysLog("Remove house successfully");
//             return 0;
//         } else {
//             sysLog("Your house does not exist in the system");
//             return 0;
//         }
//     } else if (choice == "N" || choice == "n") {
//         return 0;
//     }
//     return 0;
// }
//  Getter and setter function

// Setter

// void House::showInfo() {
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

Request::Request() {}

// Destructor
Request::~Request() {}

// Setters
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

void Request::showInfo()
{
    //    string id = "";
    //
    //    House *house = nullptr;
    //    Member *requester = nullptr;
    //
    //    Date start_date = Date();
    //    Date end_date = Date();
    //
    //    int status = PENDING;

    cout << "Request ID: " + this->id << "\n";
    cout << "Requester: ";
    this->getRequester()->showInfo();
    cout << "Start date: " + this->getStartingDate().dateToString() << "\n";
    cout << "End date: " + this->getEndingDate().dateToString() << "\n";
    switch (status)
    {
    case 0:
        cout << "PENDING\n";
        break;
    case 1:
        cout << "APPROVED\n";
        break;
    case 2:
        cout << "DENIED\n";
        break;
    case 3:
        cout << "FINISHED\n";
        break;

    default:
        cout << "N/A\n";
        break;
    }
}

System::System()
{
}
System::~System()
{
    delete this->instancePointer;
}

System *System::instancePointer = nullptr;

System *System::getInstance()
{
    if (instancePointer == nullptr)
    {
        instancePointer = new System();
    }
    return instancePointer;
}

// Current user functions
void System::setCurrentMem(Member *currentMem)
{
    this->currentMem = currentMem;
}

void System::setIsLoggedIn(bool isLoggedIn)
{
    this->isLoggedIn = isLoggedIn;
}

void System::setIsAdmin(bool isAdmin)
{
    this->isAdminLoggedin = isAdmin;
}

// ------------------------ * Current user * ------------------------//

Member *System::getCurrentMem()
{
    return currentMem;
}

bool System::isUser() const
{
    return isLoggedIn;
}

bool System::isAdmin() const
{
    return isAdminLoggedin;
}

string System::generateID(int &count)
{
    string ID;
    count += 1;
    ID = std::to_string(count);
    return ID;
}

Member *System::registerMember(Member member)
{
    Member *newMem = addMemberToSys(member);
    if (newMem == nullptr)
    {
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

Member *System::login(string username, string password)
{
    if (username == adminUsername)
    {
        if (password == adminPassword)
        {
            setCurrentMem(nullptr);
            setIsLoggedIn(true);
            setIsAdmin(true);
            sysLog("\nLogged in as an admin\n");
            return nullptr;
        }
        else
        {
            sysLog("Incorrect password.");
            return nullptr;
        }
    }

    for (auto &i : memberVect)
    {
        if (i.getUserName() == username)
        {
            if (i.getPassword() == password)
            {
                setCurrentMem(&i);
                setIsLoggedIn(true);

                sysLog("Login successfully");
                return &i;
            }
            else
            {
                sysLog("Incorrect password") return nullptr;
            }
        }
    }
    sysLog("Username not found!");
    return nullptr;
}

bool System::logout()
{
    setCurrentMem(nullptr);
    setIsLoggedIn(false);
    setIsAdmin(false);

    sysLog("Logout successfully") return true;
}

//---------------- Add data to system---------------------//
Member *System::addMemberToSys(Member member)
{
    for (auto &i : memberVect)
    {
        if (i.getUserName() == member.getUserName())
        {
            sysLog("This username is already existed \n");
            return nullptr;
        }
    }

    memberVect.push_back(member);
    Member *newMem = &memberVect.back();
    if (newMem->getId().empty())
    {
        string id = generateID(countMem);
        newMem->setId(id);
    }
    return newMem;
};

House *System::addHouseToSys(House house)
{
    if (house.getId().empty())
    {
        string houseID = generateID(countHouse);

        houseVect.push_back(house);
        House *newHouse = &houseVect.back();
        newHouse->setId(houseID);
        return newHouse;
    }
    else
    {
        for (auto &houseTmp : houseVect)
        {
            if (houseTmp.getId() == house.getId())
            {
                houseTmp = house;
                houseTmp.setId(house.getId());

                return &houseTmp;
            }
        }
        return nullptr;
    }
}

Request *System::addRequest(Request request, string id)
{   
    if (id.empty())
    {
        // Check if the current user has any request.
        // If they do, return nullptr.
        if (currentMem->getRequest() != nullptr && currentMem->getRequest()->getStatus() == PENDING)
        {
            cout << "You already have a request.\n";
            return nullptr;
        }
            
        int requestSize = requestVect.size();       
        // cout << "You already have a request.\n";
        string id = generateID(requestSize);

        cout << "Id generated = " << id << "\n";
        // Add request to requests vector
        requestVect.push_back(request);

        Request *newRequest = &requestVect.back();
        newRequest->setId(id);

        return newRequest;
    }
    else{
        // Check if request already exists
        // if it does, update the request
        for (int i = 0; i < requestVect.size(); i++)
        {
            if (requestVect[i].getId() == id)
            {
                requestVect[i] = request;
                requestVect[i].setId(id);

                return &requestVect[i];
            }
        }

        return nullptr;
    }
}
//
// Rating * System::addRatingtoSys(Rating rating) {}

//--------------------Save data to files-------------------//
bool System::saveMember()
{
    std::ofstream file;
    string filePath = getFilePath(MEMBERS);

    file.open(filePath, std::ios::out);
    if (!file.is_open())
    {
        fileErrLog(filePath);
        return false;
    }

    for (Member member : memberVect)
    {
        file << member.getId() << "," << member.getUserName() << ","
             << member.getPassword() << "," << member.getFullName() << ","
             << member.getPhoneNum() << "," << member.getCreditP() << "\n";
    }
    file.close();
    successMess("Saved", std::to_string(memberVect.size()), "member(s)");
    return true;
}

bool System::saveHouse()
{
    std::ofstream file;
    string filePath = getFilePath(HOUSES);

    file.open(filePath, std::ios::out);
    if (!file.is_open())
    {
        fileErrLog(filePath);
        return false;
    }

    for (House house : houseVect)
    {
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
    successMess("Saved", std::to_string(houseVect.size()), "house(s)");
    return true;
}

bool System::saveRequest()
{
    std::fstream file;
    string filePath = getFilePath(REQUESTS);

    file.open(filePath, std::ios::out);
    if (!file.is_open())
    {
        fileErrLog(filePath);
        return false;
    }

    for (Request request : requestVect)
    {
        file << request.getId() << ","
             << request.getRequester()->getId() << ","
             << request.getHouse()->getId() << ","
             << request.getStartingDate().dateToString() << ","
             << request.getEndingDate().dateToString() << ","
             << request.getStatus() << "\n";
    }
    file.close();
    sysLogSuccess("Saved " + to_string(requestVect.size()) + " request(s)");
    return true;
}

// Function to change pasword
bool System::changePassword(string newpwd, string oldpwd)
{
    if (this->currentMem->getPassword() == oldpwd)
    {
        this->currentMem->setPassword(newpwd);
        return true;
    }
    else
    {
        return false;
    }
}

//-------------------Load data from file------------------//
bool System::loadMember()
{
    std::fstream file;
    string filePath = getFilePath(MEMBERS);

    file.open(filePath, std::ios::in);

    if (!file.is_open())
    {
        fileErrLog(filePath);
        return false;
    }

    string line;
    while (getline(file, line))
    {
        std::stringstream ss(line);
        string attribute;
        vector<string> tokens;

        while (getline(ss, attribute, ','))
        {
            tokens.push_back(attribute);
        }

        if (tokens.size() != 6)
        {
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

bool System::loadHouse()
{
    std::fstream file;
    string filePath = getFilePath(HOUSES);

    file.open(filePath, std::ios::in);

    if (!file.is_open())
    {
        fileErrLog(filePath);
        return false;
    }

    string line;
    while (getline(file, line))
    {
        std::stringstream ss(line);
        string attribute;
        vector<string> tokens;
        while (getline(ss, attribute, ','))
        {
            tokens.push_back(attribute);
        }

        if (tokens.size() != 8)
        {
            formatErr("house");
            continue;
        }

        System *system = System::getInstance();

        House house;

        string ownerID = tokens[7];
        Member *owner = system->getMember(ownerID);
        if (owner == nullptr)
        {
            sysLog("Error: Owner with ID " + ownerID + " not found");
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
        House *newHouse = &houseVect.back();

        owner->setHouse(newHouse);
    }

    countHouse = std::stoi(houseVect.back().getId());

    file.close();
    successMess("Load", std::to_string(houseVect.size()), "house(s)");
    return true;
}

bool System::loadRating()
{
    std::fstream file;
    string filePath = getFilePath(RATINGS);

    file.open(filePath, std::ios::in);

    if (!file.is_open())
    {
        fileErrLog(BOLD_RED_CLS + filePath);
        return false;
    }

    string line;

    while (getline(file, line))
    {
        std::stringstream ss(line);
        string attribute;
        vector<string> tokens;

        while (getline(ss, attribute, ','))
        {
            tokens.push_back(attribute);
        }

        if (tokens.size() != 5)
        {
            formatErr(BOLD_RED_CLS + "rating") continue;
        }

        Rating rating;

        string raterID = tokens[0];
        string houseId = tokens[1];
        string occupierID = tokens[2];
        string scoreStr = tokens[3];
        string comment = tokens[4];

        House *house = getHouse(houseId);
        Member *rater = getMember(raterID);
        Member *occupier;
        if (occupierID == "NONE")
        {
            occupier = nullptr;
        }
        else
        {
            occupier = getMember(occupierID);
        }

        if (house == nullptr)
        {
            sysErrLog("House with ID: " + house->getId() + " not found!!!");
            continue;
        }

        if (rater == nullptr)
        {
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

bool System::loadRequest()
{
    std::fstream file;
    string filePath = getFilePath(REQUESTS);

    file.open(filePath, std::ios::in);

    if (!file.is_open())
    {
        fileErrLog(BOLD_RED_CLS + filePath);
        return false;
    }

    string line;

    while (getline(file, line))
    {
        std::stringstream ss(line);
        string attribute;
        vector<string> tokens;

        while (getline(ss, attribute, ','))
        {
            tokens.push_back(attribute);
        }

        if (tokens.size() != 6)
        {
            formatErr(BOLD_RED_CLS + "rating") continue;
        }

        Request request;

        string requesterID = tokens[1];
        string houseId = tokens[2];

        House *house = getHouse(tokens[2]);
        Member *requester = getMember(tokens[1]);

        if (house == nullptr)
        {
            sysErrLog("House with ID: " + house->getId() + " not found!!!");
            continue;
        }

        if (requester == nullptr)
        {
            sysErrLog("Member with ID: " + requester->getId() + " not found!!!");
            continue;
        }

        request.setId(tokens[0]);
        request.setRequester(requester);
        request.setHouse(house);
        request.setStartingDate(Date::parseDate(tokens[3]));
        request.setEndingDate(Date::parseDate(tokens[4]));
        request.setStatus(stoi(tokens[5]));

        requestVect.push_back(request);
    }

    file.close();

    sysLogSuccess("Loaded " + std::to_string(ratingVect.size()) + " request(s)");

    return true;
}

//---------------------Instance getter-------------//
Member *System::getMember(string ID)
{
    for (Member &member : memberVect)
    {
        if (member.getId() == ID)
        {
            return &member;
        }
    }
    return nullptr;
}

House *System::getHouse(string ID)
{
    for (House &house : houseVect)
    {
        if (house.getId() == ID)
        {
            return &house;
        }
    }
    return nullptr;
}

void System::getAvailableHouses(vector<House *> &list_of_houses, bool isQualified, string location, Date startingDate,
                                Date endingDate)
{
    for (int i = 0; i < houseVect.size(); i++)
    {
        if (isQualified && houseVect[i].getLocation().compare(location) != 0)
            continue;

        if (isQualified &&
            (Date::compareDate(startingDate, houseVect[i].getStartListDate()) < 0 ||
             Date::compareDate(endingDate, houseVect[i].getEndListDate()) > 0))
            continue;

        if (isQualified && houseVect[i].getOwner() == currentMem)
            continue;

        list_of_houses.push_back(&houseVect[i]);
    }
}

int System::getTotalConsumptionPoint(int currentCreditPoint, int startingDate, int endingDate)
{
    return ((endingDate - startingDate) * currentCreditPoint);
}

void System::viewAllHouseBySearchingLocation(bool isQualified, string location, Date startingDate, Date endingDate)
{
    if (houseVect.empty())
    {
        cout << "There are no houses on our system.\n";
        return;
    }

    // Display all houses

    if (isQualified)
    {
        vector<House *> fetchAvailableHouses;

        getAvailableHouses(fetchAvailableHouses, true, location, startingDate, endingDate);

        if (fetchAvailableHouses.empty())
        {
            cout << "There are no qualified houses.\n";
            return;
        }

        int duration = Date::getDuration(startingDate, endingDate);

        for (int i = 0; i < fetchAvailableHouses.size(); i++)
        {
            cout << LIGHT_CYAN_CLS << "\n\t\tHouse " << LIGHT_GREEN_CLS << std::to_string(i + 1) << "\n";

            cout << "\nLocation: " << fetchAvailableHouses[i]->getLocation() << "\n";
            cout << "Description: " << fetchAvailableHouses[i]->getDescription() << "\n";
            cout << "Available from: " << fetchAvailableHouses[i]->getStartListDate().dateToString() << "\n";
            cout << "Available until: " << fetchAvailableHouses[i]->getEndListDate().dateToString() << "\n";
            cout << "Consumption points (per day): " << std::to_string(fetchAvailableHouses[i]->getCreditPointsPerDay()) << "\n";
            cout << "Expected consumption points: " << System::getTotalConsumptionPoint(duration, startingDate.getDay(), endingDate.getDay()) << "\n";
        }
    }
    else
    {
        for (int i = 0; i < houseVect.size(); i++)
        {
            cout << "\n\t\tHouse " << std::to_string(i + 1) << "\n";

            cout << "Location: " << houseVect[i].getLocation() << "\n";
            cout << "Description: " << houseVect[i].getDescription() << "\n";

            cout << "Listing start: " << houseVect[i].getStartListDate().dateToString() << "\n";
            cout << "Listing end: " << houseVect[i].getEndListDate().dateToString() << "\n";
            cout << "Consumption points (per day): " << std::to_string(houseVect[i].getCreditPointsPerDay()) << "\n";
            cout << "Owner ID: " << houseVect[i].getOwner()->getId() << "\n";
            cout << "Owner Username: " << houseVect[i].getOwner()->getUserName() << "\n";
            cout << "Owner Name: " << houseVect[i].getOwner()->getFullName() << "\n";
        }
    }
}

void System::getAvailableLocation()
{
    sysLog("Available locations: ");
    int count = 1;
    for (string loc : availableLocation)
    {
        sysLog(" -" + to_string(count) + "- " + loc);
        count += 1;
    }

    sysLog("\n");
}

void System::getHouseByDate(vector<House *> &availableHouse, Date start, Date end)
{
    for (House &house : houseVect)
    {
        if (Date::compareDate(house.getStartListDate(), start) > 1 && Date::compareDate(house.getEndListDate(), end) > 1)
        {
            availableHouse.push_back(&house);
        }
    }
}

// vector<House* > System::getHouseByID(vector<House *> &availableHouse, int id)
// {
// vector<House* > getSpecificHouse;
// for (House & eachHouse: houseVect) {
//     if (std::stoi(eachHouse.getId()) == id) {
//         availableHouse.push_back(&eachHouse);
//     }
// }

// return getSpecificHouse;
// }

bool System::checkLocation(string location)
{
    for (string loc : availableLocation)
    {
        if (loc == location)
        {
            return true;
        }
    }
    return false;
}

bool System::isInteger(const string &input)
{
    for (char i : input)
    {
        if (!isdigit(i))
        {
            return false;
        }
    }
    return true;
}

void System::viewHouseDetail()
{
    if (currentMem == nullptr)
    {
        sysLog("Please log in to view house details");
        return;
    }

    House *house = currentMem->getHouse();

    if (house == nullptr)
    {
        sysLog("You have not registered any house yet");
        string choice;
        sysLog("Do you want to register your house ? (Y/N)");
        inputStr(choice);
        if (choice == "N" || choice == "n")
        {
            return;
        }
        if (choice != "Y" || choice != "y")
        {
            sysLog(" \n Invalid response \n");
            return;
        }
        currentMem->registerHouse();
        return;
    }

    house->showInfo();
    sysLog("Listing start date: " + house->getStartListDate().dateToString() + "\n");
    sysLog("Listing end date: " + house->getEndListDate().dateToString() + "\n");

    if (house->getOccupier() != nullptr)
    {
        sysLog("Occupier name: " + house->getOccupier()->getFullName() + "\n");
        sysLog("Occupier phone: " + house->getOccupier()->getPhoneNum() + "\n");
    }
}

void System::viewAllHouse()
{

    if (!isLoggedIn)
    {
        for (House &house : houseVect)
        {
            house.showInfo();
        }
    }
    else
    {
        for (House &house : houseVect)
        {
            house.showInfo();
            sysLog("Listing start from: " + house.getStartListDate().dateToString());
            sysLog("Listing end at: " + house.getEndListDate().dateToString());
        }
    }
}

bool System::removeHouse()
{
    if (currentMem == nullptr)
    {
        sysLog("You must login first !\n \n");
        return false;
    }

    House *houseTmp = currentMem->getHouse();

    if (houseTmp == nullptr)
    {
        sysLog("You have not register any house yet");
        skip();
        return false;
    }
    string res = "";
    sysLog("Are you sure you want to remove your house from system ? (Y/N) \n");
    inputStr(res);

    if (res == "N" || res == "n")
    {
        skip();
        return false;
    }

    if (res == "Y" || res == "y")
    {
        for (House &house : houseVect)
        {
            if (house.getId() == houseTmp->getId())
            {
                currentMem->setHouse(nullptr);

                houseVect.erase(houseVect.begin() + (std::stoi(house.getId()) - 1));
                skip();
                sysLog("Remove house successfully!!");
                return true;
            }
            else
            {
                skip();
                sysLog("Cannot find your house in the system");
                return false;
            }
        }
    }

    sysLog("Invalid response");
    return false;
}

//------------------------start and exit---------------//

bool System::systemStart()
{
    sysLog("Loading data....\n");

    if (!loadMember())
    {
        sysLog("Failed to load members!!!");
        return false;
    }

    if (!loadHouse())
    {
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

bool System::systemShutdown()
{
    sysLog("Saving data....\n");

    if (!saveMember())
    {
        sysLog("Failed to save members!!!");
        return false;
    }

    if (!saveHouse())
    {
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

    sysLog("Saved data successfully ");
    skip();
    sysLog("Shutting down.......");
    skip();
    return true;
}