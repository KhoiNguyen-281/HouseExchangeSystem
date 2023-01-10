//
// Created by Nguyen Hoang Minh Khoi on 1/10/23.
//
#include "HomepageController.h"
#include "HomepageController.cpp"
#include "../Model/SystemModel.h"

using namespace HomepageComponent;
namespace HomepageComponent{

    //0.  Exit
    //1.  View Information
    //2. List available houses. --> call registerNewHouse
    //	3. Unlist current house -- call removeHouse
    //	4. Request new house. --> call bookAccommodation
    //	5. Search available house. --> display available house;
    // 6. View request (approve, deny);
    // 7. Give feedback (occupier, house)
//    System * system = System::getInstance();

    void searchHouseMenu(System system);
    void ratingMenu(System system);

    int inputOption() {
        int option;
        sysLog("Please enter your option: ");
        cin >> option;
        return option;
    }

    void oldMemberMenu(System system) {
        sysLog("0. Exit\n");
        sysLog("1. View information\n");
        sysLog("2. Register new house\n");
        sysLog("3. Remove house\n");
        sysLog("4. Book a house\n");
        sysLog("5. Search houses\n");
        sysLog("6. View request\n");
        sysLog("7. Give feedback\n")

        switch (inputOption()) {
            case 0:
                system.systemShutdown();
                break;
            case 1:
                system.viewMember();
                break;
            case 2:
                system.getCurrentMem()->registerHouse();
                break;
            case 3:
                system.removeHouse();
                break;
            case 4:
                system.getCurrentMem()->bookAccommodation();
                break;
            case 5:
                searchHouseMenu(system);
                break;
            case 6: {
                vector<Request *> requestList;
                system.getAndShowRequest(requestList, system.getCurrentMem()->getHouse());
                break;
            }
            case 7:
                ratingMenu(system);
                break;
            default:
                sysErrLog("Invalid option")
                break;

//                string location;
//                Date startDate, endDate;

//                sysLog("Please enter your demand location, sta")
        }
    }

    void searchHouseMenu(System system) {
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

        vector<House*> houseList;
        string location, dateTemp;
        Date startDate, endDate;
        switch (inputOption()) {
            case 0:
                break;
            case 1:
                system.getAvailableLocation();
                sysLog("Please enter your demand location: ");
                cin.ignore();
                inputStr(location);
                if (!system.checkLocation(location)) {
                    sysErrLog("Invalid location \n");
                    break;
                }
                system.getHouseByLoc(houseList, location);
                if (houseList.empty()) {
                    sysLog("There are not any available house with location " + location);
                    break;
                }
                for (House * house : houseList) {
                    house->showInfo();
                }
                break;
            case 2:
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

                system.getHouseByDate(houseList, startDate, endDate);
                if (houseList.empty()) {
                    sysLog("There are not any available houses from "
                    + startDate.dateToString() + " to "
                    + endDate.dateToString() + "\n");
                    break;
                }

                for (House * house : houseList) {
                    house->showInfo();
                }
                break;
            case 3:
                system.getHouseWithCreditPoint(houseList);
                if (houseList.empty()) {
                    sysLog("There are not any available with your credit points\n");
                    break;
                }
                break;
            case 4: {
                string pointsFrom, pointsTo;
                sysLog("Please enter your demand range of credit points \n");
                sysLog("Credit points from: ");
                inputStr(pointsFrom);
                if (!system.isInteger(pointsFrom)) {
                    sysErrLog("Invalid format\n");
                    break;
                }

                sysLog("Credit points to: ");
                inputStr(pointsTo);
                if (!system.isInteger(pointsTo)) {
                    sysErrLog("Invalid format\n");
                    break;
                }

                system.getHouseByCreditInRange(houseList, stoi(pointsFrom), stoi(pointsTo));

                if (houseList.empty()) {
                    sysLog("There are not any house available from "
                                   << Colors::LIGHT_YELLOW_CLS << pointsFrom << " to " << pointsTo << Colors::RESET << endl);
                    break;
                }

                for (House * house : houseList) {
                    house->showInfo();
                }
                break;
            }
            case 5:
                system.viewAllHouse();
                break;
            default:
                sysErrLog("Invalid option!!!")
                break;
        }

    }

    void ratingMenu(System system) {
        sysLog(newline);
        sysLog(DIVIDER);
        sysLog("                       FEEDBACK MENU                      \n");
        sysLog(DIVIDER);
        sysLog(newline);

        sysLog("0. Exit\n");
        sysLog("1. Rate occupier\n");
        sysLog("2. Rate house\n");

        switch (inputOption()) {
            case 0:
                break;
            case 1:
                system.getCurrentMem()->rateOccupier();
                break;
            case 2:
                system.getCurrentMem()->rateHouse();
                break;
            default:
                sysErrLog("Invalid option");
                break;
        }
    }
}

