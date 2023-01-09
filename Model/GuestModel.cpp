//
// Created by Nguyen Hoang Minh Khoi on 12/24/22.
//



#include "SystemModel.h"
#include "MemberModel.cpp"
#include <sstream>



Guest::Guest() = default;

Guest::~Guest() = default;

Member * Guest::registerNewMember() {
    Member member;
    string userName;
    string fullName;
    string phoneNum;
    string password;

    sysLog("Enter username: ");
    getline(cin, userName);

    sysLog("Enter password: ")
//    cout << "Enter password: ";
    getline(cin, password);
    sysLog("Enter full name: ");
    getline(cin, fullName);
    sysLog("Enter phone number: ");
//    cout << "Enter phone number: ";
    getline(cin, phoneNum);


    member.setUserName(userName);
    member.setFullName(fullName);
    member.setPhoneNum(phoneNum);
    member.setPassword(password);

    return System::getInstance()->registerMember(member);
}

Member * Guest::login() {
    string username;
    string password;
    bool notFound = true;

    sysLog("Please enter your username and password to login \n")
    sysLog("Username: ");
    getline(cin, username);
    sysLog("Password: ");
    getline(cin, password);

    return System::getInstance()->login(username, password);
}
