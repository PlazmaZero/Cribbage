#include "Card.h" 
#include <string>
#include <iostream>
using namespace std;

string NAMES[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

Card::Card() {
    this->name = "Other";
    this->suite = 'F';
    this->value = -1;
}

Card::Card(int value, char suite): value(value), suite(suite) {
    if (value < 1 || value > 13){
        throw (value);
    }
    
    // Diamonds, Hearts, Spade, Clubs
    char acceptable_suite[] = {'D', 'H', 'S', 'C'};
    bool found = false;
    for (int i = 0; i<4; i++){
        if (suite == acceptable_suite[i]){
            found = true;
            break;
        }
    }
    if (!found){
        throw (suite);
    }
    
    this->name = NAMES[value-1];

}

string Card::get_name() const{
    return this->name;
}

int Card::get_value() const{
    return this->value;
}

char Card::get_suite() const{
    return this->suite;
}

bool Card::operator==(Card right){
    return this->value == right.get_value() && this->suite == right.get_suite();
}

bool Card::operator<(Card right){
    return this->get_value() < right.get_value();
}

ostream & operator << (ostream & os, const Card & card){
    os << card.get_name();
    os << card.get_suite();
    
    return os;
}