//
// Created by Macbook Pro Silver on 11/01/2023.
//
#include "HomepageController.h"
#include "../Model/SystemModel.h"

using namespace HomepageComponent;

namespace HomepageComponent
{
    void newMemberMenu(Member *member)
    {
        System *system = System::getInstance();
        cout << "\n0. Exit\n"
                "1. View Information\n"
                "2. List available houses.\n"
                "3. Unlist current house\n"
                "4. Request new house.\n"
                "5. Search available house.\n";

        string option;
        cout << "Enter your option: ";
        getline(cin, option);

        switch (std::stoi(option))
        {
        case 1:
        {
            member->showInfo();
            newMemberMenu(member);
            break;
        }
        case 2:
        {
            member->registerHouse();
            newMemberMenu(member);
            break;
        }
        case 3:
        {
            system->removeHouse();
            newMemberMenu(member);
            break;
        }
        case 4:
        {
            member->bookAccommodation();
            newMemberMenu(member);
            break;
        }
        case 5:
        {
            system->viewAllHouse();
            newMemberMenu(member);
            break;
        }
        default:
        {
            break;
        }
        }
    }
    void displayGuestHomepage()
    {
        cout << "0. Exit\n"
                "1. View all houses\n"
                "2. Register\n"
                "3. Login\n";
        string option;
        System *system = System::getInstance();
        Guest *guest;
        cout << "Enter your option: ";
        getline(cin, option);
        switch (std::stoi(option))
        {
        case 0:
            exit(1);
        case 1:
        {
            system->viewAllHouse();
            displayGuestHomepage();
            break;
        }
        case 2:
        {
            Member *registeredMember = Guest::registerNewMember();

            if (!registeredMember->getId().empty())
            {
                cout << "Welcome to House Exchange System, you became new member of our business.\n";
                newMemberMenu(registeredMember);
            }
            break;
        }
        case 3:
        {
            Member *member = Guest::login();

            if (member)
            {
                newMemberMenu(member);
            }
            else
            {
                cout << "Sorry, your account is not exist, please sign up to become new member.\n";
                displayGuestHomepage();
            }
        }
        default:
            cout << "Invalid option, try again !!!!\n";
            displayGuestHomepage();
            break;
        }
    }
}

// #include "../Libs/Config.h"
// #include <iostream>
// #include "string"
//
// using std::string;
// using std::cout;
// using std::cin;
//
// #define logInfo(x) sysLog(x << newLine)
//
// #define newLine "\n";
// #define DIVIDER "-----------------------------------------------"
//
// #define APP_HEADER "EEET2482/COSC2082 ASSIGNMENT"
// #define APP_NAME "VACATION HOUSE EXCHANGE APPLICATION"
// #define INSTRUCTOR "Instructors: Mr. Linh Tran & Phong Ngo"
// #define GROUP_NAME "Group 4"
// #define STUDENT1 "s3759804, NGUYEN HOANG MINH KHOI"
// #define STUDENT2 ""
// #define STUDENT3 ""
// #define STUDENT4 ""
//
// using namespace HomepageComponent;
//
// namespace HomepageComponent{
//
//     int choice;
//
//
//     int optionInput() {
//         string option;
//         cout << ("Enter the option: ");
//         getline(cin, option);
//
//         return std::stoi(option);
//     }
//
//     void displayStartPage() {
//         System * system = System::getInstance();
//         system->systemStart();
//
//         logInfo(APP_HEADER);
//         logInfo(APP_NAME);
//         logInfo(newline);
//         logInfo(INSTRUCTOR);
//         logInfo(GROUP_NAME);
//         logInfo(STUDENT1);
//         logInfo(STUDENT2);
//         logInfo(STUDENT3);
//         logInfo(STUDENT4);
//
//         sysLog("Use the app as 1.Guest 2.Member 3.Admin 0.Shutdown");
//         sysLog("Enter your choice: ");
//         cin >> choice;
//
//         switch (choice) {
//             case 0:
//                 system->systemShutdown();
//                 break;
//             case 1:
//                 //
//                 break;
//             case 2:
//
//                 break;
//         }
//     }
//
//
//
//     int houseIDInput(){
//         string houseID;
//         cout << ("Enter the option: ");
//         getline(cin, houseID);
//
//         return std::stoi(houseID);
//     }
//
//     string fieldInput(string field){
//         string result;
//         cout << "Enter your " << field << ": ";
//         getline(cin, result);
//
//         return result;
//     }
//
//     void displayRequestOption(Member *member, House *requestHouse)
//     {
//         // System *system = System::getInstance();
//         // Request* currentRequest;
//         // cout << LIGHT_CYAN_CLS << "\n—----------------- Accommodations options —-----------------\n"
//         //     "\t1.  Request to occupy the house\n"
//         //     "\t2.  Back\n";
//         // int option = optionInput();
//
//         //                     switch (option)
//         // {
//         // case 1:
//         //     // newRequest->setRequester(member);
//         //     system->addRequest(currentRequest, houseSize)
//         //         // system->saveRequest()
//         //         break;
//         // default:
//         //     break;
//         // }
//     }
//
//     void displaySpecificHouseOption(vector<House *> &availableHouses)
//     {
//         // System *system = System::getInstance();
//         // string houseNumber;
//         // cout << "Enter the house ID: ";
//         // getline(cin, houseNumber);
//         // vector<House *> getSpecificHouseByID = system->getHouseByID(availableHouses, std::stoi(houseNumber));
//         // getSpecificHouseByID[0]->showInfo();
//         // displayRequestOption();
//     }
//
//     void displayHousesOption(){
//         System *system = System::getInstance();
//         cout << Colors::LIGHT_CYAN_CLS << "\n—----------------- Accommodations options —-----------------\n"
//                 "\t0.  Exit\n"
//                 "\t1.  Display all available houses\n"
//                 "\t2.  Display the affordable houses by searching available locations.\n";
//         int option = optionInput();
//         switch (option){
//             case 0: exit(1);
//             case 1: {
//                 system->loadMember();
//                 system->loadHouse();
//
//                 system->viewAllHouse();
//                 break;
//             }
//             case 2: {
//                 displayLocationOption();
//                 break;
//             }
//         }
//     }
//
//     void displayLocationOption(Member* member){
//         cout << "\n—----------------- Available Locations —-----------------\n"
//                 "\t0.  Exit\n"
//                 "\t1.  Ha Noi\n"
//                 "\t2.  Da Nang.\n"
//                 "\t3.  Ho Chi Minh\n";
//         System* system = System::getInstance();
//
//         int option = optionInput();
//
//         switch(option){
//             case 0: exit(1);
//             case 1: {
//                 cout << "Houses in Ha Noi\n";
//                 vector<House* > availableHouses;
//                 Date startingDate = Date::parseDate(fieldInput("starting date"));
//                 Date endingDate = Date::parseDate(fieldInput("ending date"));
//
//                 system->getAvailableHouses(availableHouses, true, "Ha Noi", startingDate, endingDate);
//                 system->viewAllHouseBySearchingLocation(true, "Ha Noi", startingDate, endingDate);
//
//                 string houseID;
//                 cout << "Enter the house ID: ";
//                 inputStr(houseID);
//
//                 House* getSearchingHouseByID;
//
//                 for(auto & availableHouse : availableHouses){
//                     if(availableHouse->getId() == houseID){
//                         getSearchingHouseByID = system->getHouse(houseID);
//                     }
//                     else{
//                         cout << "\nSorry, house not found !!!\n";
//                         displayLocationOption(member);
//                     }
//                 }
//                 getSearchingHouseByID->showInfo();
//
//                 int houseNumber = availableHouses.size();
//
//                 cout << "Do you want to book this house ? " << "\n";
//                 cout << "1. Yes\n 2. No\n";
//                 int option = optionInput();
//
////                system->loadRequest();
//
//                switch (option)
//                {
//                    case 1: {
//                        if(member->getCreditP() < getSearchingHouseByID->getCreditPointsPerDay()){
//                            cout << "Your credit point is not enough to book this house.\n";
//                            displayHousesOption(member);
//                            break;
//                        }
//                        else{
////                            member->bookAccommodation(getSearchingHouseByID, startingDate, endingDate);
//                            system->saveRequest();
//                            displayHousesOption(member);
//                        }
//                    }
//                    case 2: {
//                        displayHousesOption(member);
//                    }
//
//                    default:
//                        break;
//                }
//                break;
//            }
//            case 2: {
//                cout << "Houses in Da Nang\n";
//                vector<House* > availableHouses;
//                Date startingDate = Date::parseDate(fieldInput("starting date"));
//                Date endingDate = Date::parseDate(fieldInput("ending date"));
//
//
//                system->getAvailableHouses(availableHouses, true, "Da Nang", startingDate, endingDate);
//                system->viewAllHouseBySearchingLocation(true, "Da Nang", startingDate, endingDate);
//
//                string houseID;
//                cout << "Enter the house ID: ";
//                inputStr(houseID);
//
//                House* getSearchingHouseByID;
//
//                for(auto & availableHouse : availableHouses){
//                    if(availableHouse->getId() == houseID){
//                        getSearchingHouseByID = system->getHouse(houseID);
//                    }
//                    else{
//                        cout << "\nSorry, house not found !!!\n";
//                        displayLocationOption(member);
//                    }
//                }
//                getSearchingHouseByID->showInfo();
//                int houseNumber = availableHouses.size();
//
//                cout << "Do you want to book this house ? " << "\n";
//                cout << "1. Yes\n 2. No\n";
//                int option = optionInput();
//
////                system->loadRequest();
//
//                switch (option)
//                {
//                    case 1: {
//                        if(member->getCreditP() < getSearchingHouseByID->getCreditPointsPerDay()){
//                            cout << "Your credit point is not enough to book this house.\n";
//                            displayHousesOption(member);
//                            break;
//                        }
//                        else{
////                            member->bookAccommodation(getSearchingHouseByID, startingDate, endingDate);
//                            system->saveRequest();
//                            displayHousesOption(member);
//                        }
//                    }
//                    case 2: {
//                        displayHousesOption(member);
//                    }
//
//                    default:
//                        break;
//                }
//                break;
//            }
//            case 3: {
//                vector<House* > availableHouses;
//                Date startingDate = Date::parseDate(fieldInput("starting date"));
//                Date endingDate = Date::parseDate(fieldInput("ending date"));
//
//                system->getAvailableHouses(availableHouses, true, "Ho Chi Minh", startingDate, endingDate);
//                system->viewAllHouseBySearchingLocation(true, "Ho Chi Minh", startingDate, endingDate);
//
//                string houseID;
//                cout << "Enter the house ID: ";
//                inputStr(houseID);
//
//                House* getSearchingHouseByID;
//
//                for(auto & availableHouse : availableHouses){
//                    if(availableHouse->getId() == houseID){
//                        getSearchingHouseByID = system->getHouse(houseID);
//                    }
//                    else{
//                        cout << "\nSorry, house not found !!!\n";
//                        displayLocationOption(member);
//                    }
//                }
//                getSearchingHouseByID->showInfo();
//
//                int houseNumber = availableHouses.size();
//
//                cout << "Do you want to book this house ? " << "\n";
//                cout << "1. Yes\n 2. No\n";
//                int option = optionInput();
//
////                system->loadRequest();
//
//                switch (option)
//                {
//                    case 1: {
//                        if(member->getCreditP() < getSearchingHouseByID->getCreditPointsPerDay()){
//                            cout << "Your credit point is not enough to book this house.\n";
//                            displayHousesOption(member);
//                            break;
//                        }
//                        else{
////                            member->bookAccommodation(getSearchingHouseByID, startingDate, endingDate);
//                            system->saveRequest();
//                            displayHousesOption(member);
//                        }
//                    }
//                    case 2: {
//                        displayHousesOption(member);
//                    }
//
//                    default:
//                        break;
//                }
//                break;
//            }
//            default: {
//                cout << "Invalid location";
//                break;
//            }
//        }
//    }
//
//    void displayHousesOption(Member* member){
//        System *system = System::getInstance();
//        cout << "\n—----------------- Accommodations options —-----------------\n"
//                                  "\t0.  Exit\n"
//                                  "\t1.  Display all available houses\n"
//                                  "\t2.  Display the affordable houses by searching available locations.\n"
//                                  "\t3.  Back to the homepage.\n";
//
//        int option = optionInput();
//        switch (option){
//            case 0: exit(1);
//            case 1: {
////                system->loadHouse();
//                system->viewAllHouse();
//                displayMemberHomepage(member);
//                break;
//            }
//            case 2: {
//                displayLocationOption(member);
//                break;
//            }
//            case 3: {
//                displayMemberHomepage(member);
//                break;
//            }
//        }
//    }
//
//    void displayMemberHomepage(Member* member){
//        cout << "\n—----------------- Homepage —-----------------\n"
//                "This is your menu:\n"
//                "\t0.  Exit\n"
//                "\t1.  View Information\n"
//                "\t2.  List available houses.\n"
//                "\t3.  Unlist current house\n"
//                "\t4.  Search available house.\n";
//        int option = optionInput();
//
//        switch (option){
//            case 0:
//                exit(1);
//                break;
//            case 1:{
//                /// view Information
//                cout << "View information\n";
//                member->showInfo();
//                break;
//            }
//            case 2:
//                /// List available house
//                displayHousesOption(member);
//                break;
//            case 3:
//                /// Unlist current house
//                cout << "Unlist current house \n";
//                break;
//            case 4:
//                /// Search available house
//                cout << "Search available house\n";
//                break;
//            default:
//                cout << "Invalid option, please try again....\n";
////                displayMemberHomepage();
//        }
//    }
//
//
//
//    void displayAdminHomepage(){
//        cout << "\n—----------------- Admin Homepage —-----------------\n"
//                "\t0.  Exit\n"
//                "\t1.  Add new account\n"
//                "\t2.  Add new house\n"
//                "\t3.  View all accounts\n"
//                "\t4.  View all houses\n";
//
//        int option = optionInput();
//
//        switch (option){
//            case 0:
//                exit(1);
//                break;
//            case 1:
//                /// view Information
//                cout << "Add new account\n";
//                break;
//            case 2:
//                /// List available house
//                cout << "Add new house \n";
//                break;
//            case 3:
//                /// Unlist current house
//                cout << "View all accounts \n";
//                break;
//            case 4:
//                /// Search available house
//                cout << "View all houses\n";
//                break;
//            default:
//                cout << "Invalid option, please try again....\n";
//                displayAdminHomepage();
//        }
//    }
//
//    void displayAppHomepage(){
//        System* system = System::getInstance();
//        system->loadMember();
//        system->loadHouse();
//        system->loadRequest();
//        cout << "EEET2482/COSC2082 ASSIGNMENT \n"
//                "VACATION HOUSE EXCHANGE APPLICATION\n"
//                "\n"
//                "Instructors: Mr. Linh Tran & Phong Ngo\n"
//                "Group: Group Name\n"
//                "sXXXXXXX, Student Name\n"
//                "sXXXXXXX, Student Name\n"
//                "sXXXXXXX, Student Name\n"
//                "\n"
//                "Use the app as 1. Guest   2. Member   3. Admin\n";
//        int option = optionInput();
//
//
//        switch (option){
//            case 0:
//                exit(1);
//            case 1:
//                displayGuestHomepage();
//                break;
//            case 2:{
//                string userName = fieldInput("userName");
//                string password = fieldInput("password");
//
//                Member* member = system->login(userName, password);
//
//                if(member != nullptr){
//                    displayMemberHomepage(member);
//                }
//                else{
//                    displayGuestHomepage();
//                }
//                break;
//            }
//            case 3:
//                displayAdminHomepage();
//                break;
//            default:
//                cout << "Invalid option, please try again....\n";
////                displayMemberHomepage();
//        }
//    }
//
//}
//
