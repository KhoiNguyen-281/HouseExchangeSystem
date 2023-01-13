#include <iostream>

#include "string"
using std::string;
using std::cout;
using std::cin;
using namespace std;
// using std::vector;
#include <vector>

#include "Model/SystemModel.cpp"
#include "Controllers/HomepageController.cpp"


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
