//
// Created by Macbook Pro Silver on 27/12/2022.
//

#ifndef SED_GROUP_HOMEPAGECONTROLLER_H
#define SED_GROUP_HOMEPAGECONTROLLER_H

#include "../Model/SystemModel.h"

namespace HomepageComponent {
    int inputOption();
    int continueOption(int choice);

    void registerPage();
    void loginPage();
    void newMemberMenu();
    void displayGuestHomepage(Guest guest);

    void oldMemberMenu();
    void searchHouseMenu();
    void ratingMenu();

    void adminPage();
    void displayAppHomepage();
    void displayStartPage(); //


};

#endif // SED_GROUP_HOMEPAGECONTROLLER_H
