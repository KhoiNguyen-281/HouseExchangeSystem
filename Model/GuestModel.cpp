//
// Created by Nguyen Hoang Minh Khoi on 12/24/22.
//



#include "SystemModel.h"
#include "MemberModel.cpp"
#include <sstream>



Guest::Guest() = default;

Guest::~Guest() = default;

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
