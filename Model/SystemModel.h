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

    House * registerHouse(vector<House> &houseVector);
    int unListHouse(vector<House> &houseVector);

    virtual ~Member();

};

class House {
private:
    string id;
    string location;
    string description;
    bool available = false;
    int ptsPerDay = 0;
    double occupierRating;
    Member * owner = nullptr;
    Member* occupier = nullptr;

//    Date listingStart;
//    Date listingEnd;

public:
    House(string location, string description, int pricePerDay, double occupierRating,Member * owner);
    House();
    virtual ~House();

    void showInfo();

    //Getter
    const string &getLocation() const;
    const string &getDescription() const;
    bool isAvailable() const;
    int getPtsPerDay() const;
    double getOccupierRating() const;
    Member *getOwner() const;

    //Setter
    void setLocation(const string &location);
    void setDescription(const string &description);
    void setAvailable(bool available);
    void setPtsPerDay(int pricePerDay);
    void setOccupierRating(double occupierRating);
    void setOwner(Member *owner);
};

class System {
private:
    int countMem = 1;

    static System * instancePointer;
    System();

    vector<string> availableLocation = {"Ha Noi", "Ho Chi Minh", "Da Nang"};

    //Admin login info
    string adminUsername = "admin";
    string adminPassword = "admin123";

    //Vector database;
    vector<Member> memberVect;
    vector<House> houseVect;

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


    //Authentication functions
    Member* registerMember(Member member);
    Member* login(string username, string password);
    bool logout();


    string generateID();


    Member* addMemberToSys(Member member);


    //Function to save data to file text
    bool saveMember();

    virtual ~System();
};

#endif //SED_GROUP_SYSTEMMODEL_H
