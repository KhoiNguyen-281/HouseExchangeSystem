#include <iostream>

using std::string;
using std::cout;
using std::cin;

// using std::vector;
#include <vector>

//#include "Libs/Config.cpp"
#include "Controllers/HomepageController.h"


using namespace HomepageComponent;
int main() {

    System * system = System::getInstance();
    bool isLoggedIn = system->isUser();
    bool isAdmin = system->isAdmin();
    bool isStarted = system->systemStart();

    displayAppHomepage();
    displayStartPage();


    bool isShutDown = system->systemShutdown();

    delete system;

    if (!isShutDown) {
        throw std::runtime_error("System failed to shutdown correctly.");
        return 2;
    }
//    searchHouseMenu(*system);

}


