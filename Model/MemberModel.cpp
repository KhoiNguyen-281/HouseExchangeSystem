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

//    string id;
//    string userName;
//    string fullName;
//    string phoneNum;
//    string password;
//    int creditP = CREDIT_POINT;
//    House* house = nullptr;
//    Request* request = nullptr;

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
string Member::getId() {
    return id;
}

string Member::getUserName() {
    return userName;
}

string Member::getFullName() {
    return fullName;
}

string Member::getPhoneNum() {
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

void Member::setPhoneNum(string phoneNum) {
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
            skipLine();
            sysLogSuccess("Change username successfully !")
            break;
        case 2:
            sysLog("Enter new fullname: ");
            inputStr(input);
            system->getCurrentMem()->setFullName(input);
            skipLine();
            sysLog("Change fullname successfully !");
            break;
        case 3:
            sysLog("Enter new phone number: ");
            inputStr(input);
            system->getCurrentMem()->setPhoneNum(input);
            skipLine();
            sysLog("Change phone number successfully !")
            break;
        case 4:
            changePassword();
            break;
    }

//
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

    sysLog("How was your experience from -10 to 10 : ");
    inputStr(score);
//    if (!system->isInteger(score)) {
//        sysErrLog("Invalid format number")
//        return nullptr;
//    }
//

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

    system->addRatingToSys(rating);
    return &rating;
}

Rating * Member::rateOccupier() {
    System * system = System::getInstance();
    string comment;
    string score;

    sysLog("How would you rate your occupier from -10 to 10 : ");
    inputStr(score);
//    if (!system->isInteger(score)) {
//        sysErrLog("Invalid format number");
//        return nullptr;
//    }
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
    return &rating;
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
        for (Rating * rating : ratingVal) {
            totalScore += rating->getScore();
        }
        return totalScore / ratingVal.size();
    }
    return 0;
}


//bool Member::bookAccommodation(House *house, Date startDate, Date endDate) {
//    System *system = System::getInstance();
//    // Create a new request
//    Request request;
//
//    // Set request data.
//    request.setRequester(this);
//    request.setHouse(house);
//    request.setStartDate(startDate);
//    request.setEndDate(endDate);
//
//    // cout << "current ID = " << request.getId() << "\n";
//
//    //    request.showInfo();
//    // Add a new request to the system.
//    Request *newRequest = system->addRequestToSys(request);
//
//    //    newRequest->showInfo();
//
//    // Check if the request was added successfully.
//    if (newRequest != nullptr) {
//        sysLogSuccess("You have successfully request house");
//        setRequest(newRequest);
//        return true;
//    }
//    else {
//        sysErrLog("Failed to create request!!!");
//        return false;
//    }
//}

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

    bool isEligible = system->isHouseSuitable(*house, startDate, endDate);

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

//bool Member::denyRequest(vector<string> &ID) {
//    if (ID.empty()) {
//        return false;
//    }
//
//    System * system =  System::getInstance();
//    Request * request;
//    for (string temp : ID) {
//        request = system->getRequest(temp);
//        request->setStatus(DENIED);
//    }
//    return true;
//}