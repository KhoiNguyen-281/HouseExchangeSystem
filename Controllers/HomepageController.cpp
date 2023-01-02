#include "HomepageController.h"
#include "../Model/SystemModel.h"
#include <iostream>
#include "string"

using std::string;
using std::cout;
using std::cin;

using namespace HomepageComponent;

namespace HomepageComponent{
    int optionInput() {
        string option;
        cout << ("Enter the option: ");
        getline(cin, option);

        return std::stoi(option);
    }

    string fieldInput(string field){
        string result;
        cout << "Enter your " << field << ": ";
        getline(cin, result);

        return result;
    }

    void displayHousesOption(){
        System *system = System::getInstance();
        cout << "\n—----------------- Accommodations options —-----------------\n"
                "\t0.  Exit\n"
                "\t1.  Display all available houses\n"
                "\t2.  Display the affordable houses by searching available locations.\n";
        int option = optionInput();
        switch (option){
            case 0: exit(1);
            case 1: {
                system->loadMember();
                system->loadHouse();

                system->viewAllHouse();
                break;
            }
            case 2: {
                displayLocationOption();
                break;
            }
        }
    }

    void displayLocationOption(){
        cout << "\n—----------------- Available Locations —-----------------\n"
                "\t0.  Exit\n"
                "\t1.  Hanoi\n"
                "\t2.  Hue.\n"
                "\t3.  Saigon\n";

        int option = optionInput();

        switch(option){
            case 0: exit(1);
            case 1: {
                cout << "Houses in hanoi";

                break;
            }
            case 2: {
                cout << "Houses in Hue";
                break;
            }
            case 3: {
                cout << "Houses in Saigon";
                break;
            }
            default: {
                cout << "Invalid location";
                break;
            }
        }
    }

    void displayMemberHomepage(string user_name){
        cout << "\n—----------------- Homepage —-----------------\n"
                "This is your menu:\n"
                "\t0.  Exit\n"
                "\t1.  View Information\n"
                "\t2.  List available houses.\n"
                "\t3.  Unlist current house\n"
                "\t4.  Search available house.\n";
        int option = optionInput();

        switch (option){
            case 0:
                exit(1);
                break;
            case 1:
                /// view Information
                cout << "View information\n";
                cout << user_name << "\n";
                break;
            case 2:
                /// List available house
                displayHousesOption();
                break;
            case 3:
                /// Unlist current house
                cout << "Unlist current house \n";
                break;
            case 4:
                /// Search available house
                cout << "Search available house\n";
                break;
            default:
                cout << "Invalid option, please try again....\n";
//                displayMemberHomepage();
        }
    }

    void displayGuestHomepage(){
        System *system = System::getInstance();
        cout << "\n—----------------- Guest Homepage —-----------------\n"
                "This is your menu:\n"
                "\t0.  Exit\n"
                "\t1.  Regisger\n"
                "\t2.  Login\n"
                "\t3.  View house details.\n";
        int option = optionInput();

        switch (option){
            case 0:
                exit(1);
                break;
            case 1:
                /// view Information
                cout << "Register\n";
                break;
            case 2: {
                /// Unlist current house
                string userName = fieldInput("userName");
                string password = fieldInput("password");

                Member* member = system->login(userName, password);

                if(member){
                    displayMemberHomepage(userName);
                }
                break;
            }
            case 3:
                /// Search available house
                cout << "View available houses \n";
                break;
            default:
                cout << "Invalid option, please try again....\n";
                displayGuestHomepage();
        }
    }

    void displayAdminHomepage(){
        cout << "\n—----------------- Admin Homepage —-----------------\n"
                "\t0.  Exit\n"
                "\t1.  Add new account\n"
                "\t2.  Add new house\n"
                "\t3.  View all accounts\n"
                "\t4.  View all houses\n";

        int option = optionInput();

        switch (option){
            case 0:
                exit(1);
                break;
            case 1:
                /// view Information
                cout << "Add new account\n";
                break;
            case 2:
                /// List available house
                cout << "Add new house \n";
                break;
            case 3:
                /// Unlist current house
                cout << "View all accounts \n";
                break;
            case 4:
                /// Search available house
                cout << "View all houses\n";
                break;
            default:
                cout << "Invalid option, please try again....\n";
                displayAdminHomepage();
        }
    }

    void displayAppHomepage(){
        cout << "EEET2482/COSC2082 ASSIGNMENT \n"
                "VACATION HOUSE EXCHANGE APPLICATION\n"
                "\n"
                "Instructors: Mr. Linh Tran & Phong Ngo\n"
                "Group: Group Name\n"
                "sXXXXXXX, Student Name\n"
                "sXXXXXXX, Student Name\n"
                "sXXXXXXX, Student Name\n"
                "\n"
                "Use the app as 1. Guest   2. Member   3. Admin\n";
        int option = optionInput();

        System* system = System::getInstance();

        switch (option){
            case 0:
                exit(1);
            case 1:
                displayGuestHomepage();
                break;
            case 2:{
                string userName = fieldInput("userName");
                string password = fieldInput("password");

                Member* member = system->login(userName, password);

                if(member != nullptr){
                    displayMemberHomepage(userName);
                }
                displayGuestHomepage();
                break;
            }
            case 3:
                displayAdminHomepage();
                break;
            default:
                cout << "Invalid option, please try again....\n";
//                displayMemberHomepage();
        }
    }

}

