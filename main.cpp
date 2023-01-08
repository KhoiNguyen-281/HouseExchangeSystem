#include <iostream>
#include <iomanip>

#include "string"
using std::string;
using std::cout;
using std::cin;
using namespace std;
// using std::vector;
#include <vector>

#include "Model/SystemModel.h"
#include "Model/SystemModel.cpp"
#include "Model/GuestModel.cpp"
#include "Model/HouseModel.cpp"
#include "Model/DateModel.cpp"
#include "Model/RatingModel.cpp"

#include "Model/RequestModel.cpp"
#include "Controllers/HomepageController.h"
#include "Controllers/HomepageController.cpp"

using namespace HomepageComponent;


int main() {

    System * system = System::getInstance();
    bool isLoggedIn = system->isUser();
    bool isAdmin = system->isAdmin();
    system->systemStart();
    
//    system->loadMember();
//    system->loadHouse();
//    system->registerMember(*Guest::registerNewMember());

    Guest::login();
    system->viewHouseDetail();
//    system->getCurrentMem()->rateHouse();
//    Guest::registerNewMember();
//    Guest::registerNewMember();

    system->getCurrentMem()->registerHouse();
    system->saveMember();
    system->saveHouse();
system->viewAllHouse();
//    system->getCurrentMem()->registerHouse();
//    system->saveMember();
//    system->saveHouse();

//    system->viewAllHouse();

//    system->viewMember();


    system->systemShutdown();
//    Guest::login();
//    Member::changePassword();
//    cout << system->getCurrentMem()->getPassword();

//    displayHousesOption();
}
