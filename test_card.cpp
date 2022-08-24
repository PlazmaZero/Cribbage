#include "Card.h"
#include <iostream>
#include "test_card.h"
using namespace std;

bool test_card_creation_empty(){
    Card card_obj;
    
    if (card_obj.get_suite() != 'F' || card_obj.get_value() != -1 || card_obj.get_name() != "Other"){
        cout << "Failed test_card_creation_empty" << endl;
        return false;
    }
    
    cout << "Passed test_card_creation_empty." << endl;
    return true;
}

bool test_card_creation(){
    char suites[] = {'C', 'D', 'H', 'S'};
    string names[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    
    for (int i = 0; i < 4; i++){
        for(int j = 1; j < 14; j++){
            Card new_card(j, suites[i]);
            
            if (new_card.get_suite() != suites[i] || new_card.get_name() != names[j-1] || new_card.get_value() != j){
                cout << "Failed test_card_creation" << endl;
                return false;
            }
        }
    }
    
    cout << "Passed test_card_creation" << endl;
    return true;
    
}

bool test_card_creation_fail_suite(){
    // E is not a valid suite character
    try{
        Card new_card(2, 'E');
    }
    catch(char suite){
        if (suite == 'E'){
            cout << "Passed test_card_creation_fail_suite" << endl;
            return true;
        }
    }
    
    // Did not throw an error when the program should have
    cout << "Failed test_card_creation_fail_suite" << endl;
    return false;
}

bool test_card_creation_fail_value_under(){
    try {
        Card new_card(0, 'S');
    }
    catch (int number) {
        if (number == 0){
            cout << "Passed test_card_creation_fail_suite_under" << endl;
            return true;
        }
    }
    
    cout << "Failed test_card_creation_fail_suite_under" << endl;
    return false;
}


bool test_card_creation_fail_value_over(){
    try {
        Card new_card(14, 'S');
    }
    catch (int number) {
        if (number == 14){
            cout << "Passed test_card_creation_fail_suite_over" << endl;
            return true;
        }
    }
    
    cout << "Failed test_card_creation_fail_suite_over" << endl;
    return false;
}

bool test_card_equals_true(){
    Card card1(3, 'D');
    Card card2(3, 'D');
    
    if (card1 == card2){
        cout << "Passed test_card_equals_true" << endl;
        return true;
    }
    
    cout << "Failed test_card_equals_true" << endl;
    return false;
}

bool test_card_equals_mismatch_completely(){
    Card card1(3, 'D');
    Card card2(2, 'H');
    
    if (!(card1 == card2)){
        cout << "Passed test_card_equals_mismatch_completely" << endl;
        return true;
    }
    
    cout << "Failed test_card_equals_mismatch_completely" << endl;
    return false;
}

bool test_card_equals_mismatch_suite(){
    Card card1(3, 'D');
    Card card2(3, 'H');
    
    if (!(card1 == card2)){
        cout << "Passed test_card_equals_mismatch_suite" << endl;
        return true;
    }
    
    cout << "Failed test_card_equals_mismatch_suite" << endl;
    return false;
}

bool test_card_equals_mismatch_value(){
    Card card1(3, 'D');
    Card card2(2, 'D');
    
    if (!(card1 == card2)){
        cout << "Passed test_card_equals_mismatch_value" << endl;
        return true;
    }
    
    cout << "Failed test_card_equals_mismatch_value" << endl;
    return false;
}

bool test_card_less_than_true(){
    Card card1(4, 'S');
    Card card2(5, 'H');
    
    if (card1 < card2){
        cout << "Passed test_card_less_than_true" << endl;
        return true;
    }
    
    cout << "Failed test_card_less_than_true" << endl;
    return false;
}

bool test_card_less_than_false_same(){
    Card card1(4, 'S');
    Card card2(4, 'H');
    
    if (!(card1 < card2)){
        cout << "Passed test_card_less_than_false_same" << endl;
        return true;
    }
    
    cout << "Failed test_card_less_than_false_same" << endl;
    return false;
}

bool test_card_less_than_false_greater(){
    Card card1(13, 'S');
    Card card2(5, 'H');
    
    if (!(card1 < card2)){
        cout << "Passed test_card_less_than_false_greater" << endl;
        return true;
    }
    
    cout << "Failed test_card_less_than_false_greater" << endl;
    return false;
}

void run_card_tests(){
    int passed_tests = 0;
    
    passed_tests += test_card_creation_empty();
    passed_tests += test_card_creation();
    passed_tests += test_card_creation_fail_suite();
    passed_tests += test_card_creation_fail_value_under();
    passed_tests += test_card_creation_fail_value_over();
    passed_tests += test_card_equals_true();
    passed_tests += test_card_equals_mismatch_completely();
    passed_tests += test_card_equals_mismatch_suite();
    passed_tests += test_card_equals_mismatch_value();
    passed_tests += test_card_less_than_true();
    passed_tests += test_card_less_than_false_same();
    passed_tests += test_card_less_than_false_greater();
    
    cout << passed_tests << "/12 tests were passed." << endl;
}