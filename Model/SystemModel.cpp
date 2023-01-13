//
// Created by Nguyen Hoang Minh Khoi on 12/12/22.
//
#define sysLog(x) cout << x;
#define inputStr(x) getline(cin, x);
#define fileErrLog(x) cout << "Error!!! file " << x << " not found.";
#define formatErr(x) cout << "Error: Invalid " << x << " format \n";
#define skipline() cout << "\n";
#define sysLogInfo(x) cout << Colors::BOLD_GREEN_CLS << x << Colors::RESET << "\n";

#include "SystemModel.h"
#include "iostream"
#include <random>
#include "fstream"
#include <sstream>

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

    //Work on Mac, CLion
    return "../Data/" + file;

    //Work on VSCode, Window
//    return "./Data/" + file;
}


Date::Date() {};
Date::~Date() {}

Date::Date(const Date &otherDate) {
    day = otherDate.day;
    month = otherDate.month;
    year = otherDate.year;
}

Date &Date::operator=(const Date &otherDate) {
    day = otherDate.day;
    month = otherDate.month;
    year = otherDate.year;
    return * this;
}

string Date::dateToString() {
    std::stringstream  ss;
    ss  << std::setfill('0') << std::setw(2) << day << '/'
        << std::setfill('0') << std::setw(2) << month << '/'
        << year;
    return ss.str();
}

int Date::compareDate(Date dateInSys, Date inputDate) {
    //Check if year is conflict
    if (dateInSys.getYear() > inputDate.getYear()) {
        return -1;
    } else if (dateInSys.getYear() < inputDate.getYear()) {
        return 1;
    } else {
        //Check if month is conflict
        if (dateInSys.getMonth() > inputDate.getMonth()) {
            return -1;
        } else if (dateInSys.getMonth() < inputDate.getMonth()) {
            return 1;
        } else {
            //Check if day is conflict
            if (dateInSys.getDay() > inputDate.getDay()) {
                return -1;
            } else if (dateInSys.getDay() < inputDate.getDay()) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}



//---------------------------Getter and setter------------------//
int Date::getMonth() const {
    return month;
}

int Date::getDay() const {
    return day;
}

int Date::getYear() const {
    return year;
}

void Date::setMonth(int month) {
    Date::month = month;
}

void Date::setDay(int date) {
    Date::day = date;
}

void Date::setYear(int year) {
    Date::year = year;
}

bool Date::isDateValid(string date) {
    // Date format dd/MM/yyyy
    //1. Check if the length of the date is valid

    if(date.length() != 10) {
        return false;
    }

    //2. Check if the format of the date is valid
    if (!isdigit(date[0]) || !isdigit(date[1]) || date[2] != '/' ||
        !isdigit(date[3]) || !isdigit(date[4]) || date[5] != '/' ||
        !isdigit(date[6]) || !isdigit(date[7]) || !isdigit(date[8]) ||
        !isdigit(date[9])) {
        return false;
    }

    //Convert input string to Date attribute
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));

    //3. Check if date is valid
    if (day < 1 || day > 31) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    if (year < thisYear()) {
        return false;
    }
    // check if month is 2;
    if (month == 2) {
        if (year % 4 == 0) {
            if (day > 29) {
                return false;
            }
        } else {
            if (day > 28) {
                return false;
            }
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return false;
        }
    }

    return true;
}

Date Date::parseDate(string date) {
    Date dateTemp;
    dateTemp.setDay(std::stoi(date.substr(0, 2)));
    dateTemp.setMonth(std::stoi(date.substr(3, 2)));
    dateTemp.setYear(std::stoi(date.substr(6, 4)));
    return dateTemp;
}


int checkMonth(int month, int year, int duration) {
    if (month == 1 || month == 3 || month == 5 || month == 7 ||
        month == 8 || month == 10 || month == 12) {
        duration += 31;
    } else if (month == 2) {
        if (year % 4 == 0) {
            duration += 29;
        } else {
            duration += 28;
        }
    } else {
        duration += 30;
    }
    return duration;
}

int Date::getDuration(Date start, Date end) {
    int durations = 0;
    int temp = 0;

    int startDay = start.getDay();
    int startMonth = start.getMonth();
    int startYear = start.getYear();

    int endDay = end.getDay();
    int endMonth = end.getMonth();

    if (startMonth == endMonth) {
        durations = endDay - startDay;
    } else {
        for (int i = startMonth; i < endMonth; i++) {
            durations = ::checkMonth(i, startYear, temp);
        }
        durations += endDay;
    }

    return durations;
}






Guest::Guest() {};

Guest::~Guest() {};

Member * Guest::registerNewMember() {
    System * system = System::getInstance();
    Member member;
    string userName;
    string fullName;
    string phoneNumStr;
    string password;

    sysLog("Please enter the required information to create account\n")
    sysLog("Enter username: ");
    inputStr(userName);

    sysLog("Enter password: ")
    inputStr(password);
    sysLog("Enter full name: ");
    inputStr(fullName);
    sysLog("Enter phone number: ");
    inputStr(phoneNumStr);

    if (!system->isInteger(phoneNumStr))  {
        skipline();
        sysErrLog("Invalid, phone must be number.");
        return nullptr;
    }

    member.setUserName(userName);
    member.setFullName(fullName);
    member.setPhoneNum(stoi(phoneNumStr));
    member.setPassword(password);
    member.setHouse(nullptr);
    member.setRequest(nullptr);

    return system->registerMember(member);
}

Member* Guest::login() {
    System * system = System::getInstance();

    string username;
    string password;
    sysLog("Please enter your username and password to login \n")
    sysLog("Username: ");
    inputStr(username);
    sysLog("Password: ");
    inputStr(password);

    return system->login(username, password);;
}




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
        for (int i = 0; i < ratingVal.size(); i++) {
            totalScore += ratingVal[i]->getScore();
        }
        return totalScore / ratingVal.size();
    }
    return 0;
}


bool House::approveRequest(vector<Request*> &requestList){
    System * system = System::getInstance();
    // Check request status
    Member * owner = system->getCurrentMem();

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
    for (int i = 0; i < requestList.size(); i++) {
        if (strBuffer == requestList[i]->getId()) {
            request = requestList[i];
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
        request->setStatus(APPROVED);
        request->getHouse()->setOccupier(request->getRequester());
        sysLogSuccess("\nApproved request successfully, you will receive " << Colors::LIGHT_YELLOW_CLS << to_string(totalCreditPoint)
                                                                           << " after the house is checked out")
        sysLog("Your current balance: " << owner->getCreditP() << "\n")
        for (int i= 0;i < requestList.size(); i++) {
            if (requestList[i]->getId() != request->getId() && requestList[i]->getStatus() ==PENDING) {
                requestList[i]->setStatus(DENIED);
            }
        }
        return true;
    } else {
        sysErrLog("Cannot find request with ID " + strBuffer + " in your request list");
        return false;
    }
}




Member::Member() {};
Member::~Member() {

}

void Member::showInfo() {

    sysLogInfo("ID: " + this->id);
    sysLogInfo("Username: " + this->userName);
    sysLogInfo("Full name: " + this->fullName);
    sysLogInfo("Phone number: " << this->phoneNum);
    sysLogInfo("Credit points: " + to_string(this->creditP));

}

//Getter
string Member::getId() {
    return id;
}

string Member::getUserName() {
    return userName;
}

string Member::getFullName() {
    return fullName;
}

int Member::getPhoneNum() {
    return phoneNum;
}

string Member::getPassword() {
    return password;
}

int Member::getCreditP() {
    return creditP;
}

House *Member::getHouse()  {
    return house;
}

Request *Member::getRequest()  {
    return request;
}

//Setter
void Member::setUserName(string userName) {
    Member::userName = userName;
}

void Member::setFullName(string fullName) {
    Member::fullName = fullName;
}

void Member::setPhoneNum(int phoneNum) {
    Member::phoneNum = phoneNum;
}

void Member::setPassword(string password) {
    Member::password = password;
}

void Member::setCreditP(int creditP) {
    Member::creditP = creditP;
}

void Member::setHouse(House *house) {
    Member::house = house;
}

void Member::setRequest(Request *request) {
    Member::request = request;
}

void Member::setId(string id) {
    Member::id = id;
};

//Authentication function
//Member * Member::registerNewMember() {
//    sysLog("You are already logged in");
//    return this;
//};

//Member * Member::login() {
//    sysLog("You are already logged in");
//    return this;
//}

bool Member::memLogout() {
    return System::getInstance()->logout();
}

bool Member::registerHouse() {
    bool isHouseExisted = this->getHouse() != nullptr;

    string location, description;
    int creditPointsPerDay;
    Date endDate;
    Date startDate;
    float minimumRequiredScore;

    System *system = System::getInstance();
    system->getAvailableLocation();

    sysLog("Enter your house information to register \n");
    sysLog("Location: ");
    inputStr(location);

    while (!system->checkLocation(location)) {
        sysLog('\n');
        sysLog("Location is not available, please try again \n");
        sysLog("Location: ");
        inputStr(location);
    }

    sysLog("House description: ");
    inputStr(description);


    sysLog("Enter house listing start date and end date \n")

    string temp = "";
    sysLog("Start date: ");
    inputStr(temp);
    if (!Date::isDateValid(temp)) {
        sysErrLog("Invalid date format");
        return false;
    }

    startDate = Date::parseDate(temp);

    if (Date::compareDate(system->currentDate(), startDate) < 0) {
        sysErrLog("Date must be greater than or equal current date " + system->currentDate().dateToString());
        return false;
    }

    temp = "";
    sysLog("End date: ");
    inputStr(temp);
    if (!Date::isDateValid(temp)) {
        sysErrLog("Invalid date format");
        return false;
    }

    endDate = Date::parseDate(temp);

    if (Date::compareDate(startDate, endDate) < 0) {
        sysErrLog("End date must be greater than the start date " + startDate.dateToString());
        return false;
    }

    temp = "";
    sysLog("Credit points per day: ");
    inputStr(temp);
    while (!system->isInteger(temp)) {
        sysLog("Invalid format, please try again \n");
        inputStr(temp);
    }

    creditPointsPerDay = std::stoi(temp);

    temp = "";
    sysLog("Minimum required score (0.0): ");
    inputStr(temp);
    minimumRequiredScore = stof(temp);
    if (minimumRequiredScore < 0) {
        sysErrLog("Invalid minimum required score will be set to 0.0");
        minimumRequiredScore = 0;
    }

    House house;

    house.setOwner(this);
    house.setLocation(location);
    house.setDescription(description);
    house.setStartListDate(startDate);
    house.setEndListDate(endDate);
    house.setCreditPointsPerDay(creditPointsPerDay);
    house.setMinimumOccupierRating(minimumRequiredScore);

    string houseID = isHouseExisted ? this->getHouse()->getId() : "";

    if (isHouseExisted) {
        house.setId(houseID);
    }

    House * stored = System::getInstance()->addHouseToSys(house);

    if (stored != nullptr) {
        setHouse(stored);
        sysLogSuccess("Registered house successfully!\n");
    } else {
        sysErrLog("Unable to register house\n");
    }
    return stored != nullptr;
}


bool Member::changePassword(){
    string newPassword;
    string oldPassword;

    sysLog("Current password: ");
    inputStr(oldPassword);
    sysLog("New password: ");
    inputStr(newPassword);

    bool succeed  = System::getInstance()->changePassword(newPassword, oldPassword);

    int limitTime = 4;
    while(!succeed){
        if (limitTime > 0) {
            sysErrLog("Current password is incorrect ! Please re-type: ")
            inputStr(oldPassword);
            succeed  = System::getInstance()->changePassword(newPassword, oldPassword);
            limitTime -= 1;
        }
        else {
            sysErrLog("You have enter incorrect password 4 times and will be bring back.");
            return false;
        }
    }

    sysLogSuccess("Password changed successfully !");
    return succeed;
}

bool Member::updateInfo(){
    System * system = System::getInstance();
    string input;
    string option;
    sysLog("Enter your option: ");
    sysLog("1. Change username \n");
    sysLog("2. Change fullname \n");
    sysLog("3. Change phone number \n");
    sysLog("4. Change password \n");
    inputStr(option);

    switch (stoi(option)) {
        case 1:
            sysLog("Enter new username: ");
            inputStr(input);
            system->getCurrentMem()->setUserName(input);
            skipline();
            sysLogSuccess("Change username successfully !")
            break;
        case 2:
            sysLog("Enter new fullname: ");
            inputStr(input);
            system->getCurrentMem()->setFullName(input);
            skipline();
            sysLog("Change fullname successfully !");
            break;
        case 3:
            sysLog("Enter new phone number: ");
            inputStr(input);
            if (system->isInteger(input)) {
                skipline();
                sysErrLog("Invalid format, must be number");
                break;
            }
            system->getCurrentMem()->setPhoneNum(stoi(input));
            skipline();
            sysLog("Change phone number successfully !")
            break;
        case 4:
            changePassword();
            break;
    }
    return true;
}
bool Member::deleteProfile() {
    System * system =  System::getInstance();
    string option;
    sysLog("Are you sure you want to delete your profile (Y/N) \n");
    sysLog("Your option: ");
    inputStr(option);
    if (option == "N" || option == "n" ) {
        skipline();
        return false;
    }

    if (option == "Y" || option == "y") {
        string password;
        sysLog("Enter your password: ");
        inputStr(password);
        bool succeed = system->deleteProfile(password);
        if (succeed) {
            sysLogSuccess("Successfully delete profile");
            return succeed;
        } else {
            sysErrLog("Failed to delete profile");
            return succeed;
        }
    }

    skipline();
    sysErrLog("Invalid option");
    skipline();
    return false;
}

//-------------------------------Rating function--------------------------//
Rating * Member::rateHouse() {

    System * system = System::getInstance();
    string comment;
    string score;

    if (this->getRequest() == nullptr) {
        sysErrLog("Cannot find any house\n");
        return nullptr;
    }

    if (this->getRequest()->getStatus() != FINISHED) {
        sysErrLog("Your duration is not end yet")
        return nullptr;
    }

    sysLog("How was your experience from -10 to 10 : ");
    inputStr(score);
    if (!system->isInteger(score)) {
        sysErrLog("Invalid format number")
        return nullptr;
    }


    if(stod(score) < -10 || stod(score) > 10) {
        sysErrLog("Invalid score, score must be in range from -10 to 10");
        return nullptr;
    }

    sysLog("You can leave a comment for more details: ");
    inputStr(comment);

    Rating rating;
    rating.setRater(this);
    rating.setHouse(this->getRequest()->getHouse());
    rating.setScore(stod(score));
    rating.setComment(comment);

    Rating * newRating  =  &rating;

    system->addRatingToSys(rating);
    return newRating;
}

Rating * Member::rateOccupier() {
    System * system = System::getInstance();
    string comment;
    string score;

    if (this->getRequest() == nullptr) {
        sysLog("\nCannot find any occupier\n");
        return nullptr;
    }

    if (this->getRequest()->getStatus() != FINISHED) {
        sysErrLog("The request of your house is not finished")
        return nullptr;
    }

    sysLog("How would you rate your occupier from -10 to 10 : ");
    inputStr(score);
    if (!system->isInteger(score)) {
        sysErrLog("Invalid format number");
        return nullptr;
    }

    if (stod(score) < -10 || stod(score) > 10) {
        sysLog("Invalid score, score must be in range from -10 to 10");
        return nullptr;
    }

    sysLog("Leave a comment for more details: ");
    inputStr(comment);

    Rating  rating;
    rating.setRater(this);
    rating.setOccupier(this->getRequest()->getRequester());
    rating.setScore(stod(score));
    rating.setComment(comment);

    system->addRatingToSys(rating);

    Rating * newRating = &rating;
    return newRating;
}

bool Member::hasRatings() {
    System * system = System::getInstance();
    vector<Rating*> ratingVal;
    system->getRatingFromSys(ratingVal, this);

    return !ratingVal.empty();
}


float Member::sumRating() {
    System * system = System::getInstance();
    if (hasRatings()) {
        vector<Rating*> ratingVal;
        system->getRatingFromSys(ratingVal, this);
        float totalScore = 0.0;
        for (int i = 0; i < ratingVal.size(); i++) {
            totalScore += ratingVal[i]->getScore();
        }
        return totalScore / ratingVal.size();
    }
    return 0;
}


bool Member::bookAccommodation() {
    System * system = System::getInstance();
    vector<House *> availableHouse;
    string startStr, endStr;
    Date startDate, endDate;
    Member * member = system->getCurrentMem();

    string temp;
    system->getAvailableLocation();

    sysLog("Please enter your demand city: ");
    inputStr(temp);
    if(!system->checkLocation(temp)) {
        sysErrLog("Your city is not available, please try again!!\n");
        return false;
    }

    sysLog("Please enter your start and end date\n")
    sysLog("Start date: ");
    inputStr(startStr);
    if (!Date::isDateValid(startStr)) {
        sysErrLog("Wrong date format, please try again!!");
        return false;
    }

    startDate = Date::parseDate(startStr);

    sysLog("End date: ");
    inputStr(endStr);
    if (!Date::isDateValid(endStr)) {
        sysErrLog("Wrong date format, please try again!!");
        return false;
    }
    endDate = Date::parseDate(endStr);

    system->getAvailableHouses(availableHouse, true, temp, startDate, endDate);

    if (availableHouse.empty()) {
        sysErrLog("There are not any available houses");
        return false;
    }

    for (int i = 0; i < availableHouse.size(); i++) {
        sysLog("House no." << (i + 1) << "\n");
        availableHouse[i]->showInfo();
    }

    string choice;

    sysLog("Please enter the house's number you want to book \n");
    sysLog("House no: ");
    inputStr(choice);
    while (stoi(choice) < 1 || stoi(choice) > (availableHouse.size() + 1)) {
        sysErrLog("Invalid house's number, please try again");
        sysLog("House no: ");
        inputStr(choice);
    }


    House * house =  availableHouse[stoi(choice) - 1];

    bool isEligible = system->isHouseSuitable(*house, startDate.dateToString(), endDate.dateToString());

    if (!isEligible) {
        sysErrLog("Your credit points balance is not enough, please add more");
        return false;
    }

    Request request;
    request.setRequester(member);
    request.setHouse(house);
    request.setStartDate(startDate);
    request.setEndDate(endDate);
    request.setStatus(PENDING);

    Request * newRequest  =  system->addRequestToSys(request);
    if (newRequest == nullptr) {
        sysErrLog("Failed to add request");
        return false;
    }

    sysLogSuccess("Add request successfully")
    sysLogInfo("Your request info: ");
    member->setRequest(newRequest);
    newRequest->showInfo();
    return true;
}



// Constructor
Rating::Rating(Member *rater, double score, string comment) {

}

Rating::Rating() {};
Rating::~Rating() {}



void Rating::setRating(Member * rater, double score, string comment) {
    this->rater = rater;
    this->score =  score;
    this->comment = comment;
}

void Rating::setRater(Member *rater) {
    Rating::rater = rater;
}

void Rating::setScore(double score) {
    Rating::score = score;
}

void Rating::setComment(const string &comment) {
    Rating::comment = comment;
}

Member *Rating::getRater() const {
    return rater;
}

double Rating::getScore() const {
    return score;
}

string Rating::getComment() const {
    return comment;
}

void Rating::setHouse(House *house) {
    Rating::house = house;
}

void Rating::setOccupier(Member *occupier) {
    Rating::occupier = occupier;
}

House *Rating::getHouse() const {
    return house;
}

Member *Rating::getOccupier() const {
    return occupier;
}




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
    if (currentMem->getHouse()  == nullptr) {
        return false;
    }

    int count = 0;
    for (Request & request : requestVect) {
        if (request.getHouse()->getId() ==  currentMem->getHouse()->getId()) {
            count += 1;
        }
    }

    sysLog("You have received " << count << " request(s) \n");
    return true;
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
            bool isVerified = verifyPassword(i.getPassword(), password);
            int limitTime = 4;
            while(!isVerified){
                if (limitTime > 0) {
                    sysErrLog("Current password is incorrect ! Please re-type: ")
                    inputStr(password);
                    isVerified = verifyPassword(i.getPassword(), password);
                    limitTime -= 1;
                }
                else {
                    sysErrLog("You have enter incorrect password 4 times and will be bring back.");
                    return nullptr;
                }
            }

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

            hasRequest();

            sysLogSuccess("Logged in successfully\n")
            return &i;
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
    for (int i = 0; i < houseVect.size(); i++) {
        if (houseVect[i].getId() == ID) {
            return &houseVect[i];
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
    for (int i = 0;  i < availableLocation.size(); i++) {
        sysLog(" -"+ to_string(count) +"- " + availableLocation[i]);
        count += 1;
    }
    sysLog("\n");
}

bool System::checkLocation(string location) {
    for (int i = 0;  i < availableLocation.size(); i++) {
        if (availableLocation[i] ==  location) {
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

bool System::verifyPassword(string inputPassword, string memberPassword) {
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
        sysLogSuccess("Occupier phone: " << house->getOccupier()->getPhoneNum());
    }

}

void System::viewAllHouse() {
    if (houseVect.empty()) {
        sysLog("There are not any house in the system")
        return;
    }

    if (isUser()) {
        for (int i = 0; i < houseVect.size(); i++) {
            houseVect[i].showInfo();
            sysLogSuccess("Listing start date: " + houseVect[i].getStartListDate().dateToString());
            sysLogSuccess("Listing end date: " + houseVect[i].getEndListDate().dateToString());


            if (houseVect[i].hasRatings()) {
                float ratingScore = houseVect[i].sumRating();
                sysLogSuccess("Rating: " << std::fixed << std::setprecision(2) << ratingScore);
            }

            skipline()
        }
        return;
    }

    if(isAdmin()) {
        for (int i = 0; i < houseVect.size(); i++) {
            houseVect[i].showInfo();
            sysLogSuccess("Listing start date: " + houseVect[i].getStartListDate().dateToString());
            sysLogSuccess("Listing end date: " + houseVect[i].getEndListDate().dateToString());

            if (houseVect[i].getOccupier() != nullptr) {
                sysLogSuccess("Occupier name: " + houseVect[i].getOccupier()->getFullName());
                sysLogSuccess("Occupier phone: " << houseVect[i].getOccupier()->getPhoneNum());
            }
            if (houseVect[i].hasRatings()) {
                float ratingScore = houseVect[i].sumRating();
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
        for (int i = 0 ;i < houseVect.size(); i++) {
            if (houseVect[i].getId() == houseTmp->getId()) {
                found = true;
                houseTmp = &houseVect[i];
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
    for (int i = 0; i < ratingVect.size(); i++) {
        if (ratingVect[i].getOccupier() != nullptr && ratingVect[i].getOccupier()->getId() == requester->getId()) {
            ratingVal.push_back(&ratingVect[i]);
        }
    }
}

void System::getRatingFromSys(vector<Rating *>& ratingVal, House *house) {
    for (int i = 0; i < ratingVect.size(); i++) {
        if (ratingVect[i].getOccupier() == nullptr && ratingVect[i].getHouse()->getId() == house->getId()) {
            ratingVal.push_back(&ratingVect[i]);
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

    sysLogSuccess("Data loaded successfully, system started without any interruption");
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

    for (int i = 0; i < houseVect.size(); i++) {
        if (Date::compareDate(houseVect[i].getStartListDate(), start) >= 0
        && Date::compareDate(houseVect[i].getEndListDate(), end) <= 0) {
            if (isHouseSuitable(houseVect[i], start.dateToString() , end.dateToString())) {
            availableHouse.push_back(&houseVect[i]);
            }
        }
    }
}

void System::getHouseByLoc(vector<House*>& availableHouse, const string& location){
    for (int i = 0; i < houseVect.size(); i++) {
        if (houseVect[i].getLocation() == location) {
            if (isHouseSuitable(houseVect[i], "", "")) {
                availableHouse.push_back(&houseVect[i]);
            }
        }
    }
}

void System::getHouseWithCreditPoint(vector<House *> &availableHouse) {
    int temp = currentMem->getCreditP();
    for (int i = 0; i <  houseVect.size(); i++) {
        if (temp - houseVect[i].getCreditPointsPerDay() >= 0) {
            availableHouse.push_back(&houseVect[i]);
        }
    }
}

void System::getHouseByCreditInRange(vector<House*> &availableHouse, int creditFrom, int creditTo) {
    for (int i = 0; i < houseVect.size(); i++) {
        if (houseVect[i].getCreditPointsPerDay() >= creditFrom && houseVect[i].getCreditPointsPerDay() <= creditTo) {
            availableHouse.push_back(&houseVect[i]);
        }
    }
}


int System::changeStatusOfRequestAuto() {
    for (int i = 0; i < requestVect.size(); i++) {
        if (Date::compareDate(currentDate(), requestVect[i].getEndDate()) >= 0 && requestVect[i].getStatus() == APPROVED) {

            int totalCreditPoint = getTotalConsumptionPoint(requestVect[i].getStartDate(),
                                                            requestVect[i].getEndDate(),
                                                            requestVect[i].getHouse()->getCreditPointsPerDay());

            addCreditPoints(requestVect[i].getHouse()->getOwner(), totalCreditPoint);
            removeCreditPoints(requestVect[i].getRequester(), totalCreditPoint);
            requestVect[i].setStatus(FINISHED);
            return FINISHED;
        } else if (Date::compareDate(currentDate(), requestVect[i].getEndDate()) >= 0 && requestVect[i].getStatus() == PENDING) {
            requestVect[i].setStatus(DENIED);
            return DENIED;
        }
    }
    return 0;
}





// method