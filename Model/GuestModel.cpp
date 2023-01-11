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
    string phoneNum;
    string password;

    sysLog("Enter username: ");
    inputStr(userName);

    sysLog("Enter password: ")
//    cout << "Enter password: ";
    inputStr(password);
    sysLog("Enter full name: ");
    inputStr(fullName);
    sysLog("Enter phone number: ");
//    cout << "Enter phone number: ";
    inputStr(phoneNum);

//    string id;
//    string userName;
//    string fullName;
//    string phoneNum;
//    string password;
//    int creditP = CREDIT_POINT;
//    House *house = nullptr;
//    Request *request = nullptr;

    member.setUserName(userName);
    member.setFullName(fullName);
    member.setPhoneNum(phoneNum);
    member.setPassword(password);
    member.setHouse(nullptr);
    member.setRequest(nullptr);

    return system->registerMember(member);
}

Member* Guest::login() {
    string username;
    string password;
    sysLog("Please enter your username and password to login \n")
    sysLog("Username: ");
    inputStr(username);
    sysLog("Password: ");
    inputStr(password)
    return System::getInstance()->login(username, password);;
}
