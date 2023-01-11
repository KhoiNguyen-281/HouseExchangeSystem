#include <iostream>

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
//using namespace HomepageComponent;


int main() {
//    std::system("cls");
    System * system = System::getInstance();
//    bool isLoggedIn = system->isUser();
//    bool isAdmin = system->isAdmin();
    bool isStarted = system->systemStart();

    if (!isStarted) {
        throw std::runtime_error("System failed to start correctly.");
        return 1;
    }
//    Member * member = Guest::registerNewMember();
//    system->registerMember(*member);
//    cout << system->currentDate().dateToString();

//    system->getCurrentMem()->getHouse()->approveRequest();
//    system->getCurrentMem()->bookAccommodation();
//    system->systemShutdown();

//    Member * member = Guest::registerNewMember();
//    Guest::login();
//    cout << member->getUserName() << "----" << system->getCurrentMem()->getUserName();

    displayStartPage();
//    searchHouseMenu(*system);

}
