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



int main() {

    System * system = System::getInstance();
    bool isLoggedIn = system->isUser();
    bool isAdmin = system->isAdmin();
    Guest::registerNewMember();
    // system->saveMember();
    Guest::login();
    Member::changePassword();
    cout << system->getCurrentMem()->getPassword();

}
