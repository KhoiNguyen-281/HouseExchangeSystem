#include "HomepageController.h"
#include "../Model/SystemModel.h"
#include <iostream>
#include "string"
#include "../Libs/Config.h"

using std::string;
using std::cout;
using std::cin;

using namespace Colors;

#define logInfo(x) sysLog(x << "\n")

#define sysLog(x) cout << x;
#define inputStr(x) getline(cin, x);
#define fileErrLog(x) cout << "Error!!! file " << x << " not found.";
#define formatErr(x) cout << "Error: Invalid " << x << " format \n";
#define skipline() cout << "\n";
#include <random>


// define log message with color;
#define sysErrLog(x) cout << Colors::BOLD_RED_CLS << x << Colors::RESET << "\n" ; //log error and new line
#define sysLogSuccess(x) cout << Colors::BOLD_GREEN_CLS << x << Colors::RESET << "\n"; //Log data information with green color




#define DIVIDER "----------------------------------------------------------------\n"

#define APP_HEADER Colors::LIGHT_GREEN_CLS << "EEET2482/COSC2082 ASSIGNMENT" << Colors::RESET
#define APP_NAME "VACATION HOUSE EXCHANGE APPLICATION"
#define INSTRUCTOR Colors::LIGHT_BLUE_CLS << "Instructors: Mr. Linh Tran & Phong Ngo" << Colors::RESET
#define GROUP_NAME "                           GROUP 4"
#define STUDENT1 Colors::LIGHT_MAGENTA_CLS << "s3759804, NGUYEN HOANG MINH KHOI" << Colors::RESET
#define STUDENT2 Colors::LIGHT_MAGENTA_CLS <<"s3740814, DIEN DUC UY MAN"<< Colors::RESET
#define STUDENT3 Colors::LIGHT_MAGENTA_CLS <<"s3916890, NGUYEN PHUC LOI"<< Colors::RESET
#define STUDENT4 Colors::LIGHT_MAGENTA_CLS <<"s3928433, BUI VIET HA"<< Colors::RESET


using namespace HomepageComponent;

namespace HomepageComponent{

//    Member * member = system->getCurrentMem();

    void loginPage() {
        System * system = System::getInstance();
        skipline();
        sysLog("You are currently in login page\n");
        Guest::login();
        if (system->isAdmin()) {
            adminPage();
        } else if (system->isUser()) {
            oldMemberMenu();
        } else {
            displayStartPage();
        }
    }

    int inputOption() {
        string option;
        sysLog("Please enter your option: ");
        inputStr(option)
        if (!System::isInteger(option)) {
            return 10;
        }
        return stoi(option);
    }

    int continueOption() {
        skipline();
        sysLog("Do you want to continue ? \n")
        sysLog("0. Exit\n");
        sysLog("1. Continue\n");
        int choice  = inputOption();
        return choice;
    }

    void switchMenu(int num) {
        if (num == 1) {
            oldMemberMenu();
        }
        if (num == 0) {
            newMemberMenu();
        }
    }

    void displayAppHomepage() {
        skipline();
        logInfo(APP_HEADER);
        logInfo(APP_NAME);
        logInfo(INSTRUCTOR);
        logInfo(GROUP_NAME);
        logInfo(STUDENT1);
        logInfo(STUDENT2);
        logInfo(STUDENT3);
        logInfo(STUDENT4);
    };

    void displayStartPage() {
        System * system = System::getInstance();
//        system->setCurrentMem(nullptr);
//        Guest guest;
        sysLog("Use the app as "
                <<Colors::BOLD_BLUE_CLS <<"1.Guest " <<Colors::RESET
                <<Colors::BOLD_YELLOW_CLS <<"2.Member " <<Colors::RESET
                <<Colors::BOLD_GREEN_CLS << "3.Admin " <<Colors::RESET
                <<Colors::BOLD_RED_CLS <<  "0.Shutdown " << Colors::RESET +"\n");
        int choice = inputOption();
        switch (choice) {
            case 0:
                break;
            case 1:
                skipline();
                displayGuestHomepage();
                break;
            case 2: {
                skipline();
                loginPage();
                break;
            }
            case 3:
                skipline();
                loginPage();
                break;
            default:
                skipline();
                sysErrLog("Invalid option");
                displayStartPage();
                break;
        }
        system->systemShutdown();
        delete system;
    }

    void displayGuestHomepage() {
        System * system = System::getInstance();
        sysLog(DIVIDER);
        sysLog("                       WELCOME TO OUR SYSTEM                      \n");
        sysLog(DIVIDER);
        skipline();
        sysLog("0. Exit\n");
        sysLog("1. View all houses\n");
        sysLog("2. Register\n");
        int choice = inputOption();
        switch (choice) {
            case 0:
                skipline();
                system->logout();
                displayStartPage();
                break;
            case 1: {
                skipline();
                system->viewAllHouse();
                break;
            }
            case 2:{
                skipline();
                sysLog("You are registering as new member\n")
                Guest::registerNewMember();
                if (system->isUser()) {
                    newMemberMenu();
                    break;
                }
                break;
            }
            default:
                skipline();
                sysErrLog("Invalid option")
                displayGuestHomepage();
                break;
        }

        choice = continueOption();
        while (choice != 0) {
            if (choice == 1) {
                displayGuestHomepage();
                break;
            } else {
                sysErrLog("Invalid option");
                choice = inputOption();
            }
        }
        skipline();
        displayStartPage();
    }

    void adminPage(){
        System * system = System::getInstance();
        if (!system->isAdmin()) {
            sysErrLog("Wrong admin authentication")
            return;
        }
        skipline();
        sysLog(DIVIDER);
        sysLog("                       WELCOME BACK ADMIN                      \n");
        sysLog(DIVIDER);
        skipline();
        sysLog("0. Exit\n");
        sysLog("1. View all houses\n");
        sysLog("2. View all member\n");

//        system->setIsAdmin(true);
//        system->setCurrentMem(nullptr);
        int choice = inputOption();

        switch (choice){
            case 0:
                system->logout();
                displayStartPage();
                break;
            case 1:
                /// view Information
                skipline();
                system->viewAllHouse();
                break;
            case 2:
                skipline();
                system->viewMember();
                break;
            default:
                sysErrLog("Invalid option")
                adminPage();
                break;
        }

        choice = continueOption();
        while (choice != 0) {
            if (choice == 1) {
                adminPage();
                break;
            } else {
                sysErrLog("Invalid option");
                choice = inputOption();
            }
        }
        skipline();
        displayStartPage();
    }

    void oldMemberMenu() {
        System * system = System::getInstance();
        Member * member = system->getCurrentMem();

        skipline();
        sysLog(DIVIDER);
        sysLog("                       WELCOME BACK OUR MEMBER                     \n");
        sysLog(DIVIDER);
        skipline();
        sysLog("0. Exit\n");
        sysLog("1. View information\n");
        sysLog("2. Register new house\n");
        sysLog("3. Remove house\n");
        sysLog("4. Book a house\n");
        sysLog("5. Search houses\n");
        sysLog("6. View request\n");
        sysLog("7. Give feedback\n");
        sysLog("8. Profile\n")
        int choice = inputOption();
        switch (choice) {
            case 0:
                member->memLogout();
                displayStartPage();
                return;
            case 1:
                skipline();
                system->viewMember();
                break;
            case 2:
                skipline();
                if (member->getHouse() == nullptr) {
                    member->registerHouse();
                    break;
                }
                sysLog("You have already registered a house, please remove before adding new house\n")
                break;
            case 3:
                skipline();
                system->removeHouse();
                break;
            case 4: {
                skipline();
                member->bookAccommodation();
                break;
            }
            case 5:
                skipline();
                searchHouseMenu(1);
//                oldMemberMenu();
                break;
            case 6: {
                vector<Request *> requestList;
                skipline();
                system->getAndShowRequest(requestList, member->getHouse());
                if (!system->hasRequest()) {
                    sysLog("You have not received any request yet");
                    break;
                }
                for (int i = 0; i < requestList.size(); i++) {
                    requestList[i]->showInfo();
                    skipline();
                }
                member->getHouse()->approveRequest(requestList);
                break;
            }
            case 7:
                skipline();
                ratingMenu();
                break;
            case 8:
                skipline();
                profile();
                break;
            default:
                sysErrLog("Invalid option");
                oldMemberMenu();
                break;
        }
        choice = continueOption();
        while (choice != 0) {
            if (choice == 1) {
                oldMemberMenu();
                break;
            } else {
                sysErrLog("Invalid option");
                choice = inputOption();
            }
        }
        skipline();
        displayStartPage();
    }

    void searchHouseMenu(int num) {
        System * system = System::getInstance();
        skipline();
        sysLog(DIVIDER);
        sysLog("                       SEARCH HOUSE MENU                      \n");
        sysLog(DIVIDER);
        skipline();

        sysLog("0. Exit\n");
        sysLog("1. Search by location\n");
        sysLog("2. Search by date\n");
        sysLog("3. Search by your credit points\n");
        sysLog("4. Search by credit points in range\n");
        sysLog("5. Search all houses\n");

        vector<House *> houseList;
        string location, dateTemp;
        Date startDate, endDate;
        int choice = inputOption();
        switch (choice) {
            case 0:
                switchMenu(num);
                break;
            case 1:
                skipline();
                system->getAvailableLocation();
                sysLog("Please enter your demand location: ");
                inputStr(location);
                if (!system->checkLocation(location)) {
                    sysErrLog("Invalid location \n");
                    break;
                }
                system->getHouseByLoc(houseList, location);
                if (houseList.empty()) {
                    sysLog("There are not any available house with location " + location);
                    break;
                }
                for (int i = 0; i < houseList.size(); i++) {
                    houseList[i]->showInfo();
                    skipline();
                }
                break;
            case 2:
                skipline();
                sysLog("Please enter start and end date with format (dd/MM/yyyy)\n");
                sysLog("Start date: ");
                inputStr(dateTemp);
                if (!Date::isDateValid(dateTemp)) {
                    sysErrLog("Invalid date format!!!");
                    break;
                }

                startDate = Date::parseDate(dateTemp);

                dateTemp = "";
                sysLog("End date: ");
                inputStr(dateTemp);
                if (!Date::isDateValid(dateTemp)) {
                    sysErrLog("Invalid date format!!!");
                    break;
                }

                endDate = Date::parseDate(dateTemp);

                system->getHouseByDate(houseList, startDate, endDate);
                if (houseList.empty()) {
                    sysLog("There are not any available houses from "
                           + startDate.dateToString() + " to "
                           + endDate.dateToString() + "\n");
                    break;
                }

                for (int i = 0; i < houseList.size(); i++) {
                    houseList[i]->showInfo();
                    skipline();
                }
                break;
            case 3:
                skipline();
                system->getHouseWithCreditPoint(houseList);
                if (houseList.empty()) {
                    sysLog("There are not any available with your credit points\n");
                    break;
                }

                for (int i = 0; i < houseList.size(); i++) {
                    houseList[i]->showInfo();
                    skipline();
                }
                break;
            case 4: {
                string pointsFrom, pointsTo;
                skipline();
                sysLog("Please enter your demand range of credit points \n");
                sysLog("Credit points from: ");
                inputStr(pointsFrom);
                if (!system->isInteger(pointsFrom)) {
                    sysErrLog("Invalid format\n");
                    break;
                }

                sysLog("Credit points to: ");
                inputStr(pointsTo);
                if (!system->isInteger(pointsTo)) {
                    sysErrLog("Invalid format\n");
                    break;
                }

                system->getHouseByCreditInRange(houseList, stoi(pointsFrom), stoi(pointsTo));

                if (houseList.empty()) {
                    sysLog("There are not any house available from "
                                   << Colors::LIGHT_YELLOW_CLS << pointsFrom << " to " << pointsTo << Colors::RESET
                                   << std::endl);
                    break;
                }

                for (int i = 0; i < houseList.size(); i++) {
                    houseList[i]->showInfo();
                    skipline();
                }
                break;
            }
            case 5:
                skipline();
                system->viewAllHouse();
                break;
            default:
                sysErrLog("Invalid option!!!")
                break;
        }
        choice = continueOption();
        while (choice != 0) {
            if (choice == 1) {
                searchHouseMenu(num);
                break;
            } else {
                sysErrLog("Invalid option");
                choice = inputOption();
            }
        }
        skipline();
        switchMenu(num);
    }

    void ratingMenu() {
        System * system = System::getInstance();
        Member * member = system->getCurrentMem();
        skipline()
        sysLog(DIVIDER);
        sysLog("                       FEEDBACK MENU                      \n");
        sysLog(DIVIDER);
        skipline()

        sysLog("0. Exit\n");
        sysLog("1. Rate occupier\n");
        sysLog("2. Rate house\n");
        int choice  = inputOption();
        switch (choice) {
            case 0:
                break;
            case 1:
                skipline();
                member->rateOccupier();
                break;
            case 2:
                member->rateHouse();
                break;
            default:
                sysErrLog("Invalid option");
                ratingMenu();
                break;
        }
        choice = continueOption();
        while (choice != 0) {
            if (choice == 1) {
                ratingMenu();
                break;
            } else {
                sysErrLog("Invalid option");
                choice = inputOption();
            }
        }
        skipline();
        oldMemberMenu();
    }

    void profile() {
        System * system = System::getInstance();
        Member * member = system->getCurrentMem();
        skipline()
        sysLog(DIVIDER);
        sysLog("                       MEMBER PROFILE                      \n");
        sysLog(DIVIDER);
        skipline()

        member->showInfo();

        sysLog("0. Exit\n");
        sysLog("1. Update your information\n");
        sysLog("2. Change password\n");
        sysLog("3. Delete your profile\n");
        int choice  = inputOption();
        switch (choice) {
            case 0:
                break;
            case 1:
                skipline();
                member->updateInfo();
                break;
            case 2:
                skipline();
                member->changePassword();
                break;
            case 3:
                skipline();
                member->deleteProfile();
                member->memLogout();
                break;
            default:
                sysErrLog("Invalid option");
                profile();
                break;
        }
        if (choice != 3) {
            choice = continueOption();
            while (choice != 0) {
                if (choice == 1) {
                    profile();
                    break;
                } else {
                    sysErrLog("Invalid option");
                    choice = inputOption();
                }
            }
            skipline();
        }
        displayStartPage();
        return;
    }

    void newMemberMenu() {
        System * system = System::getInstance();
        Member * member = system->getCurrentMem();
        skipline();
        sysLog(DIVIDER);
        sysLog("                       WELCOME OUR NEW MEMBER                      \n");
        sysLog(DIVIDER);
        skipline();

        sysLog("0. Exit\n");
        sysLog("1. View Information\n");
        sysLog("2. Register house\n");
        sysLog("3. Book a house\n";);
        sysLog("4. Search houses\n");

        int choice  = inputOption();
        switch (choice) {
            case 0:
                member->memLogout();
                displayStartPage();
                break;
            case 1: {
                skipline();
                system->viewMember();
                break;
            }
            case 2: {
                skipline();
                member->registerHouse();
                break;
            }
            case 3: {
                skipline();
                member->bookAccommodation();
                break;
            }
            case 4:
                skipline();
                searchHouseMenu(0);
                break;
            default:
                sysErrLog("Invalid option");
                newMemberMenu();
                break;
        }
        choice = continueOption();
        while (choice != 0) {
            if (choice == 1) {
                newMemberMenu();
                break;
            } else {
                sysErrLog("Invalid option");
                choice = inputOption();
            }
        }
        skipline();
        displayStartPage();
    }

}

