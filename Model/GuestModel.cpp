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
    inputStr(password)
    Member * member = System::getInstance()->login(username, password);
    int count = 1;
    while (member == nullptr) {
        if (count == 4) {
            sysErrLog("Wrong password 4 times, try again later");
            break;
        } else {
            sysErrLog("Password does not match, please try again");
            sysLog("Password: ");
            inputStr(password);
            member = System::getInstance()->login(username, password);
            count +=1;
        }
    }

    return member;
}
