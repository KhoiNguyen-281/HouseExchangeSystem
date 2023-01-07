//
// Created by Nguyen Hoang Minh Khoi on 12/12/22.
//

#ifndef SED_GROUP_SYSTEMMODEL_H
#define SED_GROUP_SYSTEMMODEL_H
#include <iostream>
#include "string"
#include <ctime>


using std::string;
using std::cout;
using std::cin;
using std::vector;
using std::to_string;
#include <vector>

#define CREDIT_POINT 500;

enum Status {
    PENDING,
    APPROVED,
    DENIED,
    FINISHED
};

int thisYear() {
    std::time_t t = std::time(nullptr);
    std::tm *const pTInfo = std::localtime(&t);
    return 1900 + pTInfo->tm_year;
}


class Guest;
class Member;
class House;
class Request;
class Rating;

class Date {
private:
    int month;
    int date;
    int year = thisYear();

public:
    Date();

    ~Date();
    Date(const Date &date);

    Date &operator = (const Date&otherDate);

    //getter
    int getMonth() const;
    int getDate() const;
    int getYear() const;

    //Setter
    void setMonth(int month);
    void setDate(int date);
    void setYear(int year);


    static bool isDateValid(string date);

    static Date parseDate( string date);

    int getDuration(Date start, Date end);

    static int compareDate(Date dateInSys, Date inputDate);

    string dateToString();
};

class Guest {
public:
    Guest();
    virtual ~Guest();

    static Member* registerNewMember();

    static Member* login();

    void showAllHouse();
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
    float sumRating();

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
    bool isHouseAvailable(House * house, Date startDate, Date endDate);



    Rating * rateHouse();
    Rating * rateOccupier();

    bool hasRatings();

    virtual ~Member();

};

class House {
private:

    string id;
    string location;
    string description = "";

    int creditPointsPerDay = 0;
    float minimumOccupierRating = 0.0;

    Member* owner = nullptr;
    Member* occupier = nullptr;
//
    Date startListDate;
    Date endListDate;

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
    void setMinimumOccupierRating(float minimumOccupierRating);
    void setStartListDate( Date startListDate);
    void setEndListDate( Date endListDate);

    //getter
    Member *getOwner() const;
    Member *getOccupier() const;
    const string &getId() const;
    const string &getLocation() const;
    const string &getDescription() const;
    int getCreditPointsPerDay() const;
    float getMinimumOccupierRating() const;
    Date getStartListDate();
    Date getEndListDate();


    bool hasRatings();
    float sumRating();
};


class Request
{
private:
    string id = "";

    House *house = nullptr;
    Member *requester = nullptr;

    Date start_date = Date();
    Date end_date = Date();

    int status = 0;

public:
    // Default constructor
    Request();

    // Destructor
    ~Request();

    // Setters
    void setId(const string &id);

    void setHouse(House *house);

    void setRequester(Member *requester);

    void setStartDate(const Date &startDate);

    void setEndDate(const Date &endDate);

    void setStatus(int status);

    // Getters
    const string &getId() const;

    House *getHouse() const;

    Member *getRequester() const;

    const Date &getStartDate() const;

    const Date &getEndDate() const;

    int getStatus() const;
};

class Rating {
private:
    // Attributes
    Member* rater = nullptr;
    double score;
    House* house = nullptr;
    Member* occupier = nullptr;
    string comment;

public:
    // Constructor
    Rating(Member * rater, double score, string comment);
    Rating();
    ~Rating();

    // Setter Methods
    void setRating(Member* rater, double score, string comment);
    void setRater(Member *rater);
    void setScore(double score);
    void setComment(const string &comment);
    void setHouse(House *house);
    void setOccupier(Member *occupier);

    // Getter Methods
    Member *getRater() const;
    double getScore() const;
    string getComment() const;
    House *getHouse() const;
    Member *getOccupier() const;


    // Friend class]
//    friend class House;
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
    vector<Rating> ratingVect;
    vector<Request> requestVect;

    //Current user
    Member* currentMem = nullptr;
    bool isLoggedIn = false;
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
    Rating* addRatingtoSys(const Rating& rating);
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
    void viewMember();
    void viewHouseDetail();
    void viewAllHouse();

    void getAvailableLocation();

    //Verify input function
    bool checkLocation(string location);
    bool isInteger(const string &input);

    bool removeHouse();


    //Function to get rating from system
    void getRatingFromSys(vector<Rating*>& ratingVal, Member * requester);
    void getRatingFromSys(vector<Rating*>& ratingVal, House * house);

    //Function to search house
    void searchHouse(vector<House*>& houseList, int option);
    void getHouseByDate(vector<House*>& availableHouse, Date start, Date end);

    bool systemStart();
    bool systemShutdown();


    //Current member funciotn

    virtual ~System();
};

#endif //SED_GROUP_SYSTEMMODEL_H
