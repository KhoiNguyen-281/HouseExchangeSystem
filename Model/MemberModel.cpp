//
// Created by Nguyen Hoang Minh Khoi on 12/24/22.
//

#include "SystemModel.h"
#include "../Libs/Config.h"


#define inputStr(x) getline(cin, x);
#define newline "\n"
#define skipLine() sysLog(newline);
;

// define log message with color;
#define sysLogInfo(x) cout << Colors::BOLD_GREEN_CLS << x << Colors::RESET << "\n";

Member::Member(string userName, string fullName, string phoneNum, string passWord)
        : userName(userName), fullName(fullName), phoneNum(phoneNum), password(passWord) {};
Member::Member() {};
Member::~Member() {

}

void Member::showInfo() {

    sysLogInfo("ID: " + this->id);
    sysLogInfo("Username: " + this->userName);
    sysLogInfo("Full name: " + this->fullName);
    sysLogInfo("Phone number: " + this->phoneNum);
    sysLogInfo("Credit points: " + to_string(this->creditP));
//    sysLog("ID: " << this->id << "\n");
//    sysLog("Username: " << this->userName <<"\n");
//    sysLog("Full name: " << this->fullName <<"\n");
//    sysLog("Phone number: " << this->phoneNum <<"\n");
//    sysLog("Credit point: " << this->creditP << std::endl);
}

//Getter
const string &Member::getId() const {
    return id;
}

const string &Member::getUserName() const {
    return userName;
}

const string &Member::getFullName() const {
    return fullName;
}

const string &Member::getPhoneNum() const {
    return phoneNum;
}

const string &Member::getPassword() const {
    return password;
}

int Member::getCreditP() const {
    return creditP;
}

House *Member::getHouse() const {
    return house;
}

Request *Member::getRequest() const {
    return request;
}

//Setter
void Member::setUserName(const string &userName) {
    Member::userName = userName;
}

void Member::setFullName(const string &fullName) {
    Member::fullName = fullName;
}

void Member::setPhoneNum(const string &phoneNum) {
    Member::phoneNum = phoneNum;
}

void Member::setPassword(const string &password) {
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

void Member::setId(const string &id) {
    Member::id = id;
}


//Authentication function
Member * Member::registerNewMember() {
    sysLog("You are already logged in");
    return this;
};

Member * Member::login() {
    sysLog("You are already logged in");
    return this;
}

bool Member::logout() {
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

    string temp = "";
    sysLog("Enter house listing start date and end date \n")
    sysLog("Start date: ");
    inputStr(temp);
    while (!Date::isDateValid(temp)) {
        sysLog("Invalid date format, please try again! \n")
        sysLog("Start date: ");
        inputStr(temp);
    }

    startDate = Date::parseDate(temp);

    temp = "";
    sysLog("End date: ");
    inputStr(temp);
    while (!Date::isDateValid(temp)) {
        sysLog("End date: ");
        inputStr(temp);
    }

    endDate = Date::parseDate(temp);

    temp = "";
    sysLog("Credit points per day: ");
    inputStr(temp);
    while (!system->isInteger(temp)) {
        sysLog("Invalid format, please try again \n");
        inputStr(temp);
    }

    creditPointsPerDay = std::stoi(temp);

    sysLog("Minimum required score (0.0): ");
    cin >> minimumRequiredScore;
    while (!cin) {
        sysLog("Invalid format, please try again\n");
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> minimumRequiredScore;
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
        sysLog("Registered house successfully! \n\n");
    } else {
        sysLog("Unable to register house \n\n");
    }

    return stored != nullptr;
}


bool Member::changePassword(){
    string newPassword;
    string oldPassword;
    
    sysLog("Current password: ");
    inputStr(oldPassword);
//    getline(cin, oldPassword);
    sysLog("New password: ");
//    getline(cin, newPassword);
    inputStr(newPassword);

    bool succeed  = System::getInstance()->changePassword(newPassword, oldPassword);

    int limitTime = 4;
    while(!succeed){
        if (limitTime > 0) {
            sysLog("Current password is incorrect ! Please re-type: ")
//        getline(cin, oldPassword);
            inputStr(oldPassword);
            succeed  = System::getInstance()->changePassword(newPassword, oldPassword);
            limitTime -= 1;
        }
        else {
            sysLog("You have enter incorrect password 4 times and will be bring back.");
            return false;
        }
    }

    sysLog("Password changed successfully ! \n");
    return succeed;
}

bool Member::updateInfo(){
    int option;
    string input;
//    string newUname;
//    string newFname;
//    string newNum;
//    int phone;
//    sysLog("Your information: ");
//    skipLine();
//
//    sysLog("Username: ")
////    System::getInstance()->getCurrentMem()->getUserName();
//    skipLine();
//
//    sysLog("Fullname: ")
////    System::getInstance()->getCurrentMem()->getFullName();
//    skipLine();
//
//    sysLog("Phone: ");
////    System::getInstance()->getCurrentMem()->getPhoneNum();
//    skipLine();


    // Function to show information
    this->showInfo();

    sysLog("Enter your option: ");
    sysLog("1. Change username");
    skipLine();
    sysLog("2. Change fullname");
    skipLine();
    sysLog("3. Change phone number");
    skipLine();
    sysLog("4. Change password");
    skipLine();
    cin >> option;

    switch (option) {
        case 1:
            sysLog("Enter new username: ");
            inputStr(input);
            this->setUserName(input);
            skipLine();
            sysLog("Change username successfully !")
            break;
        case 2:
            sysLog("Enter new fullname: ");
            inputStr(input);
            this->setFullName(input);
            skipLine();
            sysLog("Change fullname successfully !");
            break;
        case 3:
            sysLog("Enter new phone number: ");
            inputStr(input);
//            cin >> phone;
//            newNum = to_string(phone);
//            getline(cin, newNum);
//            System::getInstance()->getCurrentMem()->setPhoneNum(newNum);
            this->setPhoneNum(input);
            skipLine();
            sysLog("Change phone number successfully !")
            break;
        case 4:
            changePassword();
            break;
    }

//    if(option == "1"){
//        sysLog("Enter new username: ");
//        inputStr(input);
//        System::getInstance()->getCurrentMem()->setUserName(input);
//        skipLine();
//        sysLog("Change username successfully !")
//    }
//    else if(option == "2"){
//        sysLog("Enter new fullname: ");
//        ;
//        System::getInstance()->getCurrentMem()->setFullName(newFname);
//        skipLine();
//        sysLog("Change fullname successfully !")
//    }
//    else if(option == "3"){
//        sysLog("Enter new phone number: ");
//        cin >> phone;
//        newNum = to_string(phone);
//        getline(cin, newNum);
//        System::getInstance()->getCurrentMem()->setPhoneNum(newNum);
//        skipLine();
//        sysLog("Change phone number successfully !")
//    }
//    else if(option == "4"){
//        changePassword();
//    }
    return true;
}

//-------------------------------Rating function--------------------------//
Rating * Member::rateHouse() {

    System * system = System::getInstance();
    string comment;
    double score;


    sysLog("How was your experience from -10 to 10 : ");
    cin >> score;
    while(score < -10 || score > 10) {
        sysLog("Invalid score, score must be in range from -10 to 10: ");
        cin >> score;
    }

    sysLog("You can leave a comment for more details: ");
    inputStr(comment);

    Rating rating;
    rating.setRater(this);
    rating.setHouse(this->getRequest()->getHouse());
    rating.setScore(score);
    rating.setComment(comment);

    system->addRatingtoSys(rating);
    return &rating;
}

Rating * Member::rateOccupier() {
    System * system = System::getInstance();
    string comment;
    double score;

    sysLog("How would you rate your occupier from -10 to 10 : ");
    cin >> score;
    while (score < -10 || score > 10) {
        sysLog("Invalid score, score must be in range from -10 to 10: ");
        cin >> score;
    }

    sysLog("Leave a comment for more details: ");
    inputStr(comment);

    Rating  rating;
    rating.setRater(this);
    rating.setOccupier(this->getRequest()->getRequester());
    rating.setScore(score);
    rating.setComment(comment);

    system->addRatingtoSys(rating);
    return &rating;
}

bool Member::hasRatings() {
    System * system = System::getInstance();
    vector<Rating*> ratingVal;
    system->getRatingFromSys(ratingVal, this);

    return ratingVal.size() > 0;
}


float Member::sumRating() {
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

