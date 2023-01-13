//
// Created by Nguyen Hoang Minh Khoi on 12/24/22.
//



#include "SystemModel.h"
#include "MemberModel.cpp"


#define sysLog(x) cout << x;
#define inputStr(x) getline(cin, x);
#define fileErrLog(x) cout << "Error!!! file " << x << " not found.";
#define formatErr(x) cout << "Error: Invalid " << x << " format \n";
#define skipline() cout << "\n";

#include "iostream"
#include <random>


// define log message with color;
#define sysErrLog(x) cout << Colors::BOLD_RED_CLS << x << Colors::RESET << "\n" ; //log error and new line
#define sysLogSuccess(x) cout << Colors::BOLD_GREEN_CLS << x << Colors::RESET << "\n"; //Log data information with green color




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
