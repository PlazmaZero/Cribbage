using namespace std;
#include <string>

#ifndef __CARD__
#define __CARD__
class Card {
    public:
        Card();
        Card(int value, char suite);
        
        string get_name() const;
        int get_value() const;
        char get_suite() const;
        
        bool operator==(Card right);
        bool operator<(Card right);
        
        friend ostream & operator << (ostream &, const Card &);
        
    private:
        string name;
        int value;
        char suite;
};
#endif