//
// Created by Nguyen Hoang Minh Khoi on 12/12/22.
//

#ifndef SED_GROUP_SYSTEMMODEL_H
#define SED_GROUP_SYSTEMMODEL_H
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::vector;
using std::to_string;
#include <vector>

#define CREDIT_POINT 500;

class Guest;
class Member;
class House;
class Request;
class Rating;

class Date {
private:
    int month;
    int date;
    int year;

public:
    Date();

    ~Date();
    Date(Date &date);

    Date &operator = (Date&otherDate);
};

class Guest {
public:
    Guest();
    virtual ~Guest();

    static Member* registerNewMember();

    static Member* login();
};

class Member : public Guest{
private:


    string id;
    string userName;
    string fullName;
    string phoneNum;
    string password;
    int creditP = CREDIT_POINT;
    House* house = nullptr;
    Request* request = nullptr;

public:
    Member(string userName, string fullName, string phoneNum, string passWord);
    Member();
    void showInfo();

    //getter
    [[nodiscard]] const string &getId() const;
    [[nodiscard]] const string &getUserName() const;
    [[nodiscard]] const string &getFullName() const;
    [[nodiscard]] const string &getPhoneNum() const;
    [[nodiscard]] const string &getPassword() const;
    [[nodiscard]] int getCreditP() const;
    [[nodiscard]] House *getHouse() const;
    [[nodiscard]] Request *getRequest() const;

    //Setter
    void setId(const string &id);
    void setUserName(const string &userName);
    void setFullName(const string &fullName);
    void setPhoneNum(const string &phoneNum);
    void setPassword(const string &password);
    void setCreditP(int creditP);
    void setHouse(House *house);
    void setRequest(Request *request);

    //Function authentication
    Member* registerNewMember();
    Member* login();

    static bool logout();

    bool verifyPassword(string password);
    bool changePassword();

    bool updateInfo();
    bool deleteProfile();

    bool registerHouse();
    int unListHouse(vector<House> &houseVector);

    virtual ~Member();

};

class House {
private:

    string id;
    string location;
    string description = "";

    int creditPointsPerDay = 0;

    Member* owner = nullptr;
    Member* occupier = nullptr;

//    Date listingStart;
//    Date listingEnd;

public:
    House(Member *owner, string id, string location, string description, int consumptionPts);

    House();
    virtual ~House();

    void showInfo();

    //setter
    void setOwner(Member *owner);
    void setOccupier(Member *occupier);
    void setId(const string &id);
    void setLocation(const string &location);
    void setDescription(const string &description);
    void setCreditPointsPerDay(int consumptionPts);


    //getter
    Member *getOwner() const;
    Member *getOccupier() const;
    const string &getId() const;
    const string &getLocation() const;
    const string &getDescription() const;
    int getCreditPointsPerDay() const;


};

class System {
private:
    int countMem = 0;
    int countHouse = 0;
    int countRequest = 0;
    int countRating = 0;

    static System * instancePointer;
    System();

    vector<string> availableLocation = {"Ha Noi", "Ho Chi Minh", "Da Nang"};

    //Admin login info
    string adminUsername = "admin";
    string adminPassword = "admin123";

    //Vector database;
    vector<Member> memberVect;
    vector<House> houseVect;
//    vector<Request> requestVect;

    //Current user
    Member* currentMem = nullptr;
    bool isUserLoggedIn = false;
    bool isAdminLoggedin = false;

    //setter
public:
    static System * getInstance();

    //Current user functions
    void setCurrentMem(Member *currentMem);
    void setIsLoggedIn(bool isLoggedIn);
    void setIsAdmin(bool isAdmin);

    Member *getCurrentMem();
    bool isUser() const;
    bool isAdmin() const;
    bool changePassword(string newpwd, string oldpwd);
    bool updateInfo();

    //Function to generate id automatically
    string generateID(int &count);

    //Authentication functions
    Member* registerMember(Member member);
    Member* login(string username, string password);
    bool logout();



    //Function to add objects to vector
    Member* addMemberToSys(Member member);
    House* addHouseToSys(House house);
    Rating* addRatingtoSys(Rating rating);
    Request* addRequest(Request request);

    //Function to add or remove credit points of members
    bool addCreditPoints(Member * member, int creditP);
    bool removeCreditPoints(Member * member, int creditP);


    //Function to get objects by ID
    Member *getMember(string ID);
    House *getHouse(string ID);
    Rating *getRating(string houseID, string memberID);
    Request *getRequest(string ID);


    //Function to save data to file text
    bool saveMember();
    bool saveHouse();
    bool saveRating();
    bool saveRequest();

    //Funciton to load data from file
    bool loadMember();
    bool loadHouse();
    bool loadRating();
    bool loadRequest();

    //View functions
    bool showMember();
    void showHouseDetail();

    void showAllHouse();

    void getAvailableLocation();

    bool checkLocation(string location);
    bool isInteger(const string& input);


    bool systemStart();
    bool systemShutdown();

    virtual ~System();
};

#endif //SED_GROUP_SYSTEMMODEL_H
