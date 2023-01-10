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
#include "Controllers/OldMemAndRating.cpp"

//using namespace HomepageComponent;


int main() {

    System * system = System::getInstance();
    bool isLoggedIn = system->isUser();
    bool isAdmin = system->isAdmin();

    system->systemStart();
    Guest::login();

//    cout << system->currentDate().dateToString();

//    system->getCurrentMem()->getHouse()->approveRequest();
//    system->getCurrentMem()->bookAccommodation();
//    system->systemShutdown();

    oldMemberMenu(*system);
//    searchHouseMenu(*system);

}
