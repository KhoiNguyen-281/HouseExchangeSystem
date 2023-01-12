#include "HomepageController.h"
#include <iostream>
#include "string"

using std::string;
using std::cout;
using std::cin;

#define logInfo(x) sysLog(x << "\n")

#define DIVIDER "----------------------------------------------------------------\n"

#define APP_HEADER "EEET2482/COSC2082 ASSIGNMENT"
#define APP_NAME "VACATION HOUSE EXCHANGE APPLICATION"
#define INSTRUCTOR "Instructors: Mr. Linh Tran & Phong Ngo"
#define GROUP_NAME "Group 4"
#define STUDENT1 "s3759804, NGUYEN HOANG MINH KHOI"
#define STUDENT2 ""
#define STUDENT3 ""
#define STUDENT4 ""

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
        sysLog("Use the app as 1.Guest  2.Member  3.Admin  0.Shutdown\n");
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
        skipLine()
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
        skipLine()
        sysLog(DIVIDER);
        sysLog("                       WELCOME BACK ADMIN                      \n");
        sysLog(DIVIDER);
        skipLine();
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
        if (!system->isUser()) {
            skipline();
            displayStartPage();
            return;
        }
        skipLine()
        sysLog(DIVIDER);
        sysLog("                       WELCOME BACK OUR MEMBER                     \n");
        sysLog(DIVIDER);
        skipLine()
        sysLog("0. Exit\n");
        sysLog("1. View information\n");
        sysLog("2. Register new house\n");
        sysLog("3. Remove house\n");
        sysLog("4. Book a house\n");
        sysLog("5. Search houses\n");
        sysLog("6. View request\n");
        sysLog("7. Give feedback\n")
        int choice = inputOption();
        switch (choice) {
            case 0:
                member->logout();
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
                searchHouseMenu();
                break;
            case 6: {
                vector<Request *> requestList;
                skipline();
                system->getAndShowRequest(requestList, member->getHouse());
                if (!system->hasRequest()) {
                    sysLog("You have not received any request yet");
                    break;
                }
                for (Request * request : requestList) {
                    request->showInfo();
                    skipline();
                }
                member->getHouse()->approveRequest(requestList);
                break;
            }
            case 7:
                skipline();
                ratingMenu();
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

    void searchHouseMenu() {
        System * system = System::getInstance();
        sysLog(newline);
        sysLog(DIVIDER);
        sysLog("                       SEARCH HOUSE MENU                      \n");
        sysLog(DIVIDER);
        sysLog(newline);

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
                for (House *house: houseList) {
                    house->showInfo();
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

                for (House *house: houseList) {
                    house->showInfo();
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

                for (House * house : houseList) {
                    house->showInfo();
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
                                   << endl);
                    break;
                }

                for (House *house: houseList) {
                    house->showInfo();
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
                searchHouseMenu();
                break;
            } else {
                sysErrLog("Invalid option");
                choice = inputOption();
            }
        }
        skipline();
        oldMemberMenu();
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
    }

    void newMemberMenu() {
        System * system = System::getInstance();
        Member * member = system->getCurrentMem();
        skipLine()
        sysLog(DIVIDER);
        sysLog("                       WELCOME OUR NEW MEMBER                      \n");
        sysLog(DIVIDER);
        skipLine()

        sysLog("0. Exit\n");
        sysLog("1. View Information\n");
        sysLog("2. Register house\n");
        sysLog("3. Book a house\n";);
        sysLog("4. Search houses\n");

        int choice  = inputOption();
        switch (choice) {
            case 0:
                member->logout();
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
                searchHouseMenu();
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

