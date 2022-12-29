#include <iostream>

#include "string"
using std::string;
using std::cout;
using std::cin;
// using std::vector;
#include <vector>

#include "Model/SystemModel.h"
#include "Model/SystemModel.cpp"
#include "Model/GuestModel.cpp"
#include "Model/HouseModel.cpp"
#include "Model/DateModel.cpp"



int main() {

    System * system = System::getInstance();
    bool isLoggedIn = system->isUser();
    bool isAdmin = system->isAdmin();

//    system->registerMember(*Guest::registerNewMember());
    Guest::login();
    Guest::registerNewMember();
    // system->saveMember();
    Guest::login();
    Member::changePassword();
    cout << system->getCurrentMem()->getPassword();


}
