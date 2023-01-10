//
// Created by Macbook Pro Silver on 27/12/2022.
//

#ifndef SED_GROUP_HOMEPAGECONTROLLER_H
#define SED_GROUP_HOMEPAGECONTROLLER_H


#include "../Model/SystemModel.h"

namespace HomepageComponent {
    int optionInput();

    void displayStartPage(); //

//    Guest menu
    void displayGuestHomepage();
    // 0. Exit
    //1. viewAllHouse
    //2. register -> login page
    //3. login

    // wrong, navigate to signup page

//    Member menu (new)
    void newMemberMenu();
    //0.  Exit
    //1.  View Information
    //2. List available houses. --> call registerNewHouse
    //	3. Unlist current house -- call removeHouse
    //	4. Request new house. --> call bookAccommodation
    //	5. Search available house. --> display available house;

    void oldMemberMenu();
    //0.  Exit
    //1.  View Information
    //2. List available houses. --> call registerNewHouse
    //	3. Unlist current house -- call removeHouse
    //	4. Request new house. --> call bookAccommodation
    //	5. Search available house. --> display available house;
    // 6. View request (approve, deny);
    // 7. Give feedback (occupier, house)

    void ratingMenu();
    // 0. Exit
    // 1. Rate occupier
    // 2. Rate house



//    string fieldInput(std::string field);
    void displayRequestOption(Member *member, House* requestHouse);
    void displayHousesOption(Member* member);
    void displaySpecificHouseOption(); 
    void displayLocationOption();


    void displayAdminHomepage();
    void displayAppHomepage();

};


#endif //SED_GROUP_HOMEPAGECONTROLLER_H
