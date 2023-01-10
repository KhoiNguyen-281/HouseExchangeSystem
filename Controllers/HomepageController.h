//
// Created by Macbook Pro Silver on 27/12/2022.
//

#ifndef SED_GROUP_HOMEPAGECONTROLLER_H
#define SED_GROUP_HOMEPAGECONTROLLER_H


#include "../Model/SystemModel.h"

namespace HomepageComponent {
    int optionInput();

    void displayStartPage();
    void displayGuestHomepage();
//    string fieldInput(std::string field);
    void displayRequestOption(Member *member, House* requestHouse);
    void displayHousesOption(Member* member);
    void displaySpecificHouseOption(); 
    void displayLocationOption();
    void displayMemberHomepage(Member *member);

    void displayAdminHomepage();
    void displayAppHomepage();

};


#endif //SED_GROUP_HOMEPAGECONTROLLER_H
