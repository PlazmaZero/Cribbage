#include "test_player.h"
#include "Player.h"
#include <iostream>

using namespace std;

bool test_player_score_pairs_no_pairs(){
    // make a frequency count with no pairs
    int counts[13] = {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
    
    int score = score_pairs(counts);

    if (score != 0){
        cout << "Failed test_player_score_pairs_no_pairs" << endl;
        return false;
    }
    cout << "Passed test_player_score_pairs_no_pairs" << endl;
    return true;
}

bool test_player_score_pairs_one_pair(){
    // make a frequency count with one pair
    int counts[13] = {0, 1, 1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0};
    
    int score = score_pairs(counts);
     
    if (score != 2){
        cout << "Failed test_player_score_pairs_one_pair" << endl;
        return false;
    }
    cout << "Passed test_player_score_pairs_one_pair" << endl;
    return true;
    
}

bool test_player_score_pairs_three_of_a_kind(){
    // make a frequency count with one pair
    int counts[13] = {0, 1, 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0};
    
    int score = score_pairs(counts);
    
    if (score != 6){
        cout << "Failed test_player_score_pairs_three_of_a_kind" << endl;
        return false;
    }
    cout << "Passed test_player_score_pairs_three_of_a_kind" << endl;
    return true;
    
}

bool test_player_score_pairs_four_of_a_kind(){
    // make a frequency count with one pair
    int counts[13] = {0, 0, 0, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0};
    
    int score = score_pairs(counts);
    
    if (score != 12){
        cout << "Failed test_player_score_pairs_four_of_a_kind" << endl;
        return false;
    }
    cout << "Passed test_player_score_pairs_four_of_a_kind" << endl;
    return true;
}

bool test_player_score_pairs_two_distinct_pairs(){
    // make a frequency count with one pair
    int counts[13] = {0, 0, 0, 0, 2,0 , 0, 0, 0, 0, 0, 2, 0};
    
    int score = score_pairs(counts);
     
    if (score != 4){
        cout << "Failed test_player_score_pairs_two_distinct_pairs" << endl;
        return false;
    }
    cout << "Passed test_player_score_pairs_two_distinct_pairs" << endl;
    return true;
}

bool test_player_score_pairs_two_and_three(){
    // make a frequency count with one pair
    int counts[13] = {0, 0, 0, 0, 2,0 , 0, 0, 0, 0, 0, 0, 3};
    
    int score = score_pairs(counts);
    
    if (score != 8){
        cout << "Failed test_player_score_pairs_two_and_three" << endl;
        return false;
    }
    cout << "Passed test_player_score_pairs_two_and_three" << endl;
    return true;
}

int score_pair_tests(){
    int passed_tests = 0;
    passed_tests += test_player_score_pairs_no_pairs();
    passed_tests += test_player_score_pairs_one_pair();
    passed_tests += test_player_score_pairs_three_of_a_kind();
    passed_tests += test_player_score_pairs_four_of_a_kind();
    passed_tests += test_player_score_pairs_two_distinct_pairs();
    passed_tests += test_player_score_pairs_two_and_three();
    return passed_tests;
}

bool test_player_score_flush_none(){
    vector<Card> hand = {Card(4, 'H'), Card(5, 'S'), Card(6, 'C'), Card(7, 'D')};
    Card turn_up(5, 'H');
    
    int score_hand = score_flush(hand, turn_up, false);
    int score_crib = score_flush(hand, turn_up, true);
    
    if (score_hand == 0 && score_crib == 0){
        cout << "Passed test_player_score_flush_none" << endl;
        return true;
    }
    cout << "Failed test_player_score_flush_none" << endl;
    return false;
}

bool test_player_score_flush_same_color(){
    vector<Card> hand = {Card(4, 'H'), Card(5, 'D'), Card(6, 'H'), Card(7, 'D')};
    Card turn_up(5, 'H');
    
    int score_hand = score_flush(hand, turn_up, false);
    int score_crib = score_flush(hand, turn_up, true);
    
    if (score_hand == 0 && score_crib == 0){
        cout << "Passed test_player_score_flush_same_color" << endl;
        return true;
    }
    cout << "Failed test_player_score_flush_same_color" << endl;
    return false;
}

bool test_player_score_flush_full_flush(){
    vector<Card> hand = {Card(4, 'H'), Card(5, 'H'), Card(6, 'H'), Card(7, 'H')};
    Card turn_up(5, 'H');
    
    int score_hand = score_flush(hand, turn_up, false);
    int score_crib = score_flush(hand, turn_up, true);
    
    if (score_hand == 5 && score_crib == 5){
        cout << "Passed test_player_score_full_flush" << endl;
        return true;
    }
    cout << "Failed test_player_score_flush_full_flush" << endl;
    return false;
}

bool test_player_score_flush_partial_flush(){
    vector<Card> hand = {Card(4, 'S'), Card(5, 'S'), Card(6, 'S'), Card(7, 'S')};
    Card turn_up(5, 'H');
    
    int score_hand = score_flush(hand, turn_up, false);
    int score_crib = score_flush(hand, turn_up, true);
    
    if (score_hand == 4 && score_crib == 0){
        cout << "Passed test_player_score_partial_flush" << endl;
        return true;
    }
    cout << "Failed test_player_score_flush_partial_flush" << endl;
    return false;
}

int score_flush_tests(){
    int passed_tests = 0;
    passed_tests += test_player_score_flush_none();
    passed_tests += test_player_score_flush_same_color();
    passed_tests += test_player_score_flush_full_flush();
    passed_tests += test_player_score_flush_partial_flush();
    return passed_tests;
}

bool test_player_score_fifteens_full_add(){
    // make a frequency count with one pair
    vector<Card> hand = {Card(1, 'S'), Card(2, 'S'), Card(3, 'S'), Card(4, 'S')};
    Card turn_up(5, 'H');
    
    int score = score_fifteens(hand, turn_up);
    if (score != 2){
        cout << "Failed test_player_score_fifteens_full_add" << endl;
        return false;
    }
    cout << "Passed test_player_score_fifteens_full_add" << endl;
    return true;
}

bool test_player_score_fifteens_none(){
    // make a frequency count with one pair
    vector<Card> hand = {Card(1, 'S'), Card(1, 'S'), Card(5, 'S'), Card(5, 'S')};
    Card turn_up(6, 'H');
    
    int score = score_fifteens(hand, turn_up);
     
    if (score != 0){
        cout << "Failed test_player_score_fifteens_none" << endl;
        return false;
    }
    cout << "Passed test_player_score_fifteens_none" << endl;
    return true;
}

bool test_player_score_fifteens_share_number(){
    // make a frequency count with one pair
    vector<Card> hand = {Card(5, 'H'), Card(5, 'S'), Card(5, 'D'), Card(13, 'S')};
    Card turn_up(13, 'H');
    
    int score = score_fifteens(hand, turn_up);
    if (score != 14){
        cout << "Failed test_player_score_fifteens_share_number" << endl;
        return false;
    }
    cout << "Passed test_player_score_fifteens_share_number" << endl;
    return true;
}

bool test_player_score_fifteens_distinct_fifteens(){
    // make a frequency count with one pair
    vector<Card> hand = {Card(6, 'S'), Card(9, 'S'), Card(7, 'S'), Card(8, 'S')};
    Card turn_up(12, 'H');
    
    int score = score_fifteens(hand, turn_up);
     
    if (score != 4){
        cout << "Failed test_player_score_fifteens_distinct_fifteens" << endl;
        return false;
    }
    cout << "Passed test_player_score_fifteens_distinct_fifteens" << endl;
    return true;
}


int score_fifteen_tests(){
    int passed_tests = 0;
    passed_tests += test_player_score_fifteens_full_add();
    passed_tests += test_player_score_fifteens_none();
    passed_tests += test_player_score_fifteens_share_number();
    passed_tests += test_player_score_fifteens_distinct_fifteens();
    return passed_tests;
}

bool test_player_score_knobs_none(){
    // make a frequency count with one pair
    vector<Card> hand = {Card(6, 'S'), Card(9, 'S'), Card(7, 'S'), Card(8, 'S')};
    Card turn_up(12, 'H');
    
    int score = score_knobs(hand, turn_up);
     
    if (score != 0){
        cout << "Failed test_player_score_knobs_none" << endl;
        return false;
    }
    cout << "Passed test_player_score_knobs_none" << endl;
    return true;
}

bool test_player_score_knobs_jack_no_suite(){
    // make a frequency count with one pair
    vector<Card> hand = {Card(11, 'S'), Card(9, 'S'), Card(7, 'S'), Card(8, 'S')};
    Card turn_up(12, 'H');
    
    int score = score_knobs(hand, turn_up);
     
    if (score != 0){
        cout << "Failed test_player_score_knobs_jack_no_suite" << endl;
        return false;
    }
    cout << "Passed test_player_score_knobs_jack_no_suite" << endl;
    return true;
}

bool test_player_score_knobs_turn_up_jack(){
    // make a frequency count with one pair
    vector<Card> hand = {Card(11, 'S'), Card(9, 'S'), Card(7, 'S'), Card(8, 'S')};
    Card turn_up(11, 'H');
    
    int score = score_knobs(hand, turn_up);
     
    if (score != 0){
        cout << "Failed test_player_score_knobs_turn_up_jack" << endl;
        return false;
    }
    cout << "Passed test_player_score_knobs_turn_up_jack" << endl;
    return true;
}


bool test_player_score_knobs_suite_no_jack(){
    // make a frequency count with one pair
    vector<Card> hand = {Card(10, 'H'), Card(9, 'S'), Card(7, 'S'), Card(8, 'S')};
    Card turn_up(13, 'H');
    
    int score = score_knobs(hand, turn_up);
     
    if (score != 0){
        cout << "Failed test_player_score_knobs_suite_no_jack" << endl;
        return false;
    }
    cout << "Passed test_player_score_knobs_turn_suite_no_jack" << endl;
    return true;
}

bool test_player_score_knobs_true(){
    // make a frequency count with one pair
    vector<Card> hand = {Card(11, 'H'), Card(9, 'S'), Card(7, 'S'), Card(8, 'S')};
    Card turn_up(13, 'H');
    
    int score = score_knobs(hand, turn_up);
     
    if (score != 1){
        cout << "Failed test_player_score_knobs_suite_true" << endl;
        return false;
    }
    cout << "Passed test_player_score_knobs_turn_suite_true" << endl;
    return true;
}

int score_knobs_tests(){
    int passed_tests = 0;
    passed_tests += test_player_score_knobs_none();
    passed_tests += test_player_score_knobs_jack_no_suite();
    passed_tests += test_player_score_knobs_turn_up_jack();
    passed_tests += test_player_score_knobs_suite_no_jack();
    passed_tests += test_player_score_knobs_true();
    
    return passed_tests;
}

bool test_player_score_runs_none(){
// make a frequency count with one pair
    int counts[13] = {0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0};
    
    int score = score_runs(counts);
    
    if (score != 0){
        cout << "Failed test_player_score_runs_none" << endl;
        return false;
    }
    cout << "Passed test_player_score_runs_none" << endl;
    return true;
}

bool test_player_score_runs_three(){
// make a frequency count with one pair
    int counts[13] = {0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0};
    
    int score = score_runs(counts);
    
    if (score != 3){
        cout << "Failed test_player_score_runs_three" << endl;
        return false;
    }
    cout << "Passed test_player_score_runs_three" << endl;
    return true;
}

bool test_player_score_runs_two_of_three(){
// make a frequency count with one pair
    int counts[13] = {0, 1, 1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0};
    
    int score = score_runs(counts);
    
    if (score != 6){
        cout << "Failed test_player_score_runs_two_of_three" << endl;
        return false;
    }
    cout << "Passed test_player_score_runs_two_of_three" << endl;
    return true;
}

bool test_player_score_runs_four(){
// make a frequency count with one pair
    int counts[13] = {0, 1, 1, 1,1, 0, 0, 0, 0, 0, 0, 0, 0};
    
    int score = score_runs(counts);
    
    if (score != 4){
        cout << "Failed test_player_score_runs_four" << endl;
        return false;
    }
    cout << "Passed test_player_score_runs_four" << endl;
    return true;
}

bool test_player_score_runs_two_of_four(){
// make a frequency count with one pair
    int counts[13] = {0, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    
    int score = score_runs(counts);
    
    if (score != 8){
        cout << "Failed test_player_score_runs_two_of_four" << endl;
        return false;
    }
    cout << "Passed test_player_score_runs_two_of_four" << endl;
    return true;
}

bool test_player_score_runs_five(){
// make a frequency count with one pair
    int counts[13] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
    
    int score = score_runs(counts);
    
    if (score != 5){
        cout << "Failed test_player_score_runs_five" << endl;
        return false;
    }
    cout << "Passed test_player_score_runs_five" << endl;
    return true;
}

int score_runs_tests(){
    int passed_tests = 0;
    passed_tests += test_player_score_runs_none();
    passed_tests += test_player_score_runs_three();
    passed_tests += test_player_score_runs_two_of_three();
    passed_tests += test_player_score_runs_four();
    passed_tests += test_player_score_runs_two_of_four();
    passed_tests += test_player_score_runs_five();
    return passed_tests;
}

void run_player_tests(){
    int passed_tests = 0;
    
    passed_tests += score_pair_tests();
    passed_tests += score_flush_tests();
    passed_tests += score_fifteen_tests();
    passed_tests += score_knobs_tests();
    passed_tests += score_runs_tests();
    
    cout << "Passed "<<passed_tests << "/25 tests." <<endl;
}