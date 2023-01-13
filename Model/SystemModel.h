//
// Created by Nguyen Hoang Minh Khoi on 12/12/22.
//

#ifndef SED_GROUP_SYSTEMMODEL_H
#define SED_GROUP_SYSTEMMODEL_H
#include <iostream>
#include "string"
#include <ctime>


using std::cin;
using std::cout;
using std::string;
using std::to_string;
using std::vector;
#include <vector>

#define CREDIT_POINT 500;


//Create enum for request status
enum Status {
    PENDING,
    APPROVED,
    DENIED,
    FINISHED
};


//Get current year
int thisYear() {
    std::time_t t = std::time(nullptr);
    std::tm *const pointerInfo = std::localtime(&t);
    return 1900 + pointerInfo->tm_year;
}


//Prototype classes
class Guest;
class Member;
class House;
class Request;
class Rating;


class Date {
private:
    int month;
    int day;
    int year = thisYear();

public:
    Date();

    ~Date();

    Date(const Date &date);

//    Overload method to re-assign date to another date;
    Date &operator = (const Date&otherDate);

    //getter
    int getMonth() const;
    int getDay() const;
    int getYear() const;

    //Setter
    void setMonth(int month);
    void setDay(int date);
    void setYear(int year);

//    Method to validate date with format dd/MM/yyyy
    static bool isDateValid(string date);
//    Method to convert string type to Date
    static Date parseDate( string date);
//    Method to get duration between two date
    static int getDuration(Date start, Date end);
//    Method to compare two date
    static int compareDate(Date dateInSys, Date inputDate);
//    Method to convert Date type to string
    string dateToString();

};

class Guest {
public:
    Guest();
    virtual ~Guest();
//    Method to register new member
    static Member* registerNewMember();
//    Method for user to login as member
    static Member* login();

};

class Member : public Guest{
private:
    string id;
    string userName;
    string fullName;
    int phoneNum;
    string password;
    int creditP = CREDIT_POINT;
    House *house = nullptr;
    Request *request = nullptr;

public:
    Member();

//    Method to show information of member
    void showInfo();

    // getter
    string getId();
    string getUserName();
    string getFullName();
    int getPhoneNum();
    string getPassword();
    int getCreditP();
    House *getHouse();
    Request *getRequest();
    float sumRating();

    // Setter
    void setId(string id);
    void setUserName(string userName);
    void setFullName(string fullName);
    void setPhoneNum(int phoneNum);
    void setPassword(string password);
    void setCreditP(int creditP);
    void setHouse(House *house);
    void setRequest(Request *request);

//    Authenticate method, override from system
//    Member* registerNewMember();
//    Member* login();
    static bool memLogout();

//    Method to modified member profile
    bool changePassword();
    bool updateInfo();
    bool deleteProfile();

    bool registerHouse();
//    bool isHouseAvailable(House * house, Date startDate, Date endDate);


//    bool denyRequest(vector<string> &ID);


    Rating * rateHouse();
    Rating * rateOccupier();

    bool hasRatings();

//    bool bookAccommodation(House *house, Date startingDate, Date endingDate);
    bool bookAccommodation();
    virtual ~Member();
};

class House {
private:
    string id;
    string location;
    string description = "";

    int creditPointsPerDay = 0;
    float minimumOccupierRating = 0.0;

    Member *owner = nullptr;
    Member *occupier = nullptr;
    //
    Date startListDate;
    Date endListDate;

public:

    House();
    virtual ~House();

    void showInfo();

    // setter
    void setOwner(Member *owner);
    void setOccupier(Member *occupier);
    void setId(const string &id);
    void setLocation(const string &location);
    void setDescription(const string &description);
    void setCreditPointsPerDay(int consumptionPts);
    void setMinimumOccupierRating(float minimumOccupierRating);
    void setStartListDate( Date startListDate);
    void setEndListDate( Date endListDate);

    // getter
    Member *getOwner() const;
    Member *getOccupier() const;
    const string &getId() const;
    string getLocation();
    const string &getDescription() const;
    int getCreditPointsPerDay() const;
    float getMinimumOccupierRating() const;
    Date getStartListDate();
    Date getEndListDate();

    bool hasRatings();
    float sumRating();

    bool approveRequest(vector<Request *>& requestList);


    // Friend function
    // Set new occupier to the house after successfully request
//    friend House* addNewOccupierToHouse(House* house, Member * occupier);
};

class Request
{
private:
    string id = "";

    House *house = nullptr;
    Member *requester = nullptr;

    Date start_date = Date();
    Date end_date = Date();

    int status = PENDING;

public:
    // Default constructor
    Request();

    // Destructor
    ~Request();

    void showInfo();

    // Setters
    void setId(const string &id);

    void setHouse(House *house);

    void setRequester(Member *requester);

    void setStartDate(const Date &startDate);

    void setEndDate(const Date &endDate);

    void setStatus(int status);

    // Getters
    string getId();

    House *getHouse() const;

    Member *getRequester() const;

    Date getStartDate();

    Date getEndDate();

    int getStatus() const;
};

class Rating {
private:
    // Attributes
    Member *rater = nullptr;
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


    // Friend class
    //    friend class Member;
    //    friend class House;
};


class System {
private:
    int countMem = 0;
    int countHouse = 0;
    int countRequest = 0;

    static System *instancePointer;
    System();

    const std::string hanoi = "Ha Noi";
    const std::string saigon = "Sai Gon";
    const std::string hue = "Hue";

    vector<string> availableLocation{hanoi, hue, saigon};

    // Admin login info
    string adminUsername = "admin";
    string adminPassword = "admin123";

    // Vector database;
    vector<Member> memberVect;
    vector<House> houseVect;
    vector<Rating> ratingVect;
    vector<Request> requestVect;

    // Current user
    Member *currentMem = nullptr;
    bool isLoggedIn = false;
    bool isAdminLoggedin = false;

    // setter
public:
    Date currentDate();
    static System *getInstance();

    // Current user functions
    void setCurrentMem(Member *currentMem);
    void setIsLoggedIn(bool isLoggedIn);
    void setIsAdmin(bool isAdmin);
    bool hasRequest();

    Member *getCurrentMem();
    bool isUser();
    bool isAdmin();
    bool changePassword(string newpwd, string oldpwd);
    bool updateInfo();

    // Function to generate id automatically
    string generateID(int &count);

    // Authentication functions
    Member * registerMember(Member member);
    Member *login(string username, string password);
    bool logout();
    bool deleteProfile(string password);

    // Function to add objects to vector
    Member *addMemberToSys(Member member);
    House *addHouseToSys(House house);
    Rating *addRatingToSys(Rating rating);
    Request *addRequestToSys(Request request);

    // Function to add or remove credit points of members
    bool addCreditPoints(Member *member, int creditP);
    bool removeCreditPoints(Member *member, int creditP);

    // Function to get objects by ID
    Member *getMember(string ID);
    House *getHouse(string ID);
    Rating *getRating(string houseID, string memberID);
    Request *getRequest(string ID);

    // Function to save data to file text
    bool saveMember();
    bool saveHouse();
    bool saveRating();
    bool saveRequest();

    // Funciton to load data from file
    bool loadMember();
    bool loadHouse();
    bool loadRating();
    bool loadRequest();

    // View functions
    void viewMember();
    void viewHouseDetail();
    void viewAllHouse();
    void viewRating();

    int getTotalConsumptionPoint(Date startDate, Date endDate, int creditPoints);
    void getAvailableHouses(vector<House *> &list_of_houses, bool isQualified, const string& location, Date start_date, Date end_date);
    void getAvailableLocation();
     // vector<House* > getHouseByID(vector<House *> &house, int id);

    // Verify input function
    bool checkLocation(string location);
    static bool isInteger(const string &input);
    bool verifyPassword(string inputPassword, string memberPass);


    bool removeHouse();

    bool isHouseSuitable(House house, string start, string end);


    //Function to get rating from system
    void getRatingFromSys(vector<Rating*>& ratingVal, Member * requester);
    void getRatingFromSys(vector<Rating*>& ratingVal, House * house);


    //Function to manipulate request
    void getAndShowRequest(vector<Request *> & requestList, House * house);

    //Function to search house
//    void searchHouse(vector<House *> &availableHouse, string location,Date startDate, Date endDate);
    void getHouseByDate(vector<House*>& availableHouse, Date start, Date end);
    void getHouseByLoc(vector<House*>& house, const string& location);
    void getHouseWithCreditPoint(vector<House*> &house);
    void getHouseByCreditInRange(vector<House*> &house, int creditFrom, int creditTo);

    int changeStatusOfRequestAuto();

    bool systemStart();
    bool systemShutdown();


    virtual ~System();
};

#endif // SED_GROUP_SYSTEMMODEL_H
