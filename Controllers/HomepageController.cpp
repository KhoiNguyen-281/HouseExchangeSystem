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
    System * system = System::getInstance();
//    bool isUser = system->isUser();
//    bool isAdmin = system->isAdmin();



    void loginPage() {
        Guest guest;
        sysLog("You are logging in\n");
        guest.login();
        if (system->isAdmin()) {
            adminPage();
        } else if (system->isUser() && system->hasRequest()) {
            oldMemberMenu();
        } else {
            newMemberMenu();
        }
    }

//    void registerPage() {
//        sysLog("You are registering as new member\n")
//        Member * newMem = Guest::registerNewMember();
//        if (newMem == nullptr) {
//            return;
//        }
//    }

    int inputOption() {
        int option;
        sysLog("Please enter your option: ");
        cin >> option;
        return option;
    }

    int continueOption(int choice) {
        skipline();
        sysLog("Do you want to continue ? \n")
        sysLog("0. Exit\n");
        sysLog("1. Continue\n");
        choice = inputOption();
        return choice;
    }

    void displayStartPage() {
        logInfo(APP_HEADER);
        logInfo(APP_NAME);
        logInfo(INSTRUCTOR);
        logInfo(GROUP_NAME);
        logInfo(STUDENT1);
        logInfo(STUDENT2);
        logInfo(STUDENT3);
        logInfo(STUDENT4);

        skipline();
        sysLog("Use the app as 1.Guest 2.Member 3.Admin 0.Shutdown\n");
        int choice = inputOption();
        switch (choice) {
            case 0:
                system->systemShutdown();
                delete system;
                break;
            case 1:
                skipline();
                displayGuestHomepage();
                break;
            case 2:
                skipline();
                cin.ignore();
                loginPage();
                break;
            case 3:
                cin.ignore();
                loginPage();
                if (system->isAdmin()) {
                    adminPage();
                    break;
                }
                sysErrLog("Wrong admin authentication")
                break;
        }
    }

    void displayGuestHomepage() {
        sysLog(DIVIDER);
        sysLog("                       WELCOME TO OUR SYSTEM                      \n");
        sysLog(DIVIDER);
        skipLine()
        sysLog("0. Exit\n");
        sysLog("1. View all houses\n");
        sysLog("2. Register\n");
        sysLog("3. Login\n";);
        int choice = inputOption();

        string option;

        switch (choice) {
            case 0:
                exit(1);
            case 1: {
                skipline();
                system->viewAllHouse();
                break;
            }
            case 2:{
                skipline();
                cin.ignore();
                sysLog("You are registering as new member\n")
                Member * member = Guest::registerNewMember();
//                system->setCurrentMem(newMember);
                sysLog("Please exit and login again to use member features")
                break;
            }
            case 3: {
                skipline();
                cin.ignore();
                loginPage();
                break;
            }
            default:
                skipline();
                sysErrLog("Invalid option")
                displayGuestHomepage();
                break;
        }

        switch (continueOption(choice)) {
            case 1:
                displayGuestHomepage();
                break;
            case 0:
                displayStartPage();
                break;
            default:
                sysErrLog("Invalid option");
                continueOption(choice);
                break;
        }
    }

    void adminPage(){
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
        switch (continueOption(choice)) {
            case 1:
                adminPage();
                break;
            case 0:
                displayStartPage();
                break;
            default:
                sysErrLog("Invalid option");
                continueOption(choice);
                break;
        }
    }

    void oldMemberMenu() {
        skipLine()
        sysLog(DIVIDER);
        sysLog("                       WELCOME BACK                      \n");
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
                displayStartPage();
                break;
            case 1:
                skipline();
                system->viewMember();
                break;
            case 2:
                skipline();
                cin.ignore();
                system->getCurrentMem()->registerHouse();
                break;
            case 3:
                skipline();
                cin.ignore();
                system->removeHouse();
                break;
            case 4:
                skipline();
                cin.ignore();
                system->getCurrentMem()->bookAccommodation();
                break;
            case 5:
                skipline();
                searchHouseMenu();
                break;
            case 6: {
                vector<Request *> requestList;
                skipline();
                system->getAndShowRequest(requestList, system->getCurrentMem()->getHouse());
                if (!system->hasRequest()) {
                    sysLog("You have not received any request yet");
                    break;
                }
                for (Request * request : requestList) {
                    request->showInfo();
                    skipline();
                }
                cin.ignore();
                system->getCurrentMem()->getHouse()->approveRequest(requestList);
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

        switch (continueOption(choice)) {
            case 1:
                oldMemberMenu();
                break;
            case 0:
                displayStartPage();
                break;
            default:
                sysErrLog("Invalid option")
                continueOption(choice);
                break;
        }

    }

    void searchHouseMenu() {
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
                cin.ignore();
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
                cin.ignore();
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
                cin.ignore();
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
        switch (continueOption(choice)) {
            case 1:
                searchHouseMenu();
                break;
            case 0:
                break;
            default:
                sysErrLog("Invalid option")
                break;
        }
    }

    void ratingMenu() {
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
                system->getCurrentMem()->rateOccupier();
                break;
            case 2:
                system->getCurrentMem()->rateHouse();
                break;
            default:
                sysErrLog("Invalid option");
                break;
        }
        switch (continueOption(choice)) {
            case 1:
                ratingMenu();
                break;
            case 0:
                break;
            default:
                sysErrLog("Invalid option");
                break;
        }
    }



    void newMemberMenu() {
        skipLine()
        sysLog(DIVIDER);
        sysLog("                       WELCOME TO OUR SYSTEM                      \n");
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
                break;
            case 1: {
                skipline();
                system->viewMember();
                break;
            }
            case 2: {
                skipline();
                system->getCurrentMem()->registerHouse();
                break;
            }
            case 3: {
                skipline();
                system->getCurrentMem()->bookAccommodation();
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
        switch (continueOption(choice)) {
            case 1:
                newMemberMenu();
                break;
            case 0:
                break;
            default:
                sysErrLog("Invalid option");
                continueOption(choice);
                break;
        }
    }


}

