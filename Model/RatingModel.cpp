#include "SystemModel.h"

#define sysLog(x) cout << x;
#define inputStr(x) getline(cin, x);
#define fileErrLog(x) cout << "Error!!! file " << x << " not found.";
#define formatErr(x) cout << "Error: Invalid " << x << " format \n";
#define skipline() cout << "\n";

// define log message with color;
#define sysErrLog(x) cout << Colors::BOLD_RED_CLS << x << Colors::RESET << "\n" ; //log error and new line
#define sysLogSuccess(x) cout << Colors::BOLD_GREEN_CLS << x << Colors::RESET << "\n"; //Log data information with green color



using namespace std;

/* -------------------- * Rating Function Implementation * -------------------- */

// Constructor
Rating::Rating(Member *rater, double score, string comment) {

}

Rating::Rating() {};
Rating::~Rating() {}



void Rating::setRating(Member * rater, double score, string comment) {
    this->rater = rater;
    this->score =  score;
    this->comment = comment;
}

void Rating::setRater(Member *rater) {
    Rating::rater = rater;
}

void Rating::setScore(double score) {
    Rating::score = score;
}

void Rating::setComment(const string &comment) {
    Rating::comment = comment;
}

Member *Rating::getRater() const {
    return rater;
}

double Rating::getScore() const {
    return score;
}

string Rating::getComment() const {
    return comment;
}

void Rating::setHouse(House *house) {
    Rating::house = house;
}

void Rating::setOccupier(Member *occupier) {
    Rating::occupier = occupier;
}

House *Rating::getHouse() const {
    return house;
}

Member *Rating::getOccupier() const {
    return occupier;
}


// Setter Methods


//Getter Methods


