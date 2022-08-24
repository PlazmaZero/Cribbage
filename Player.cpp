using namespace std;
#include <vector>
#include <iostream>
#include "Player.h"
#include "Card.h"
#define NUM_CARDS_VALUE 13
#define FIFTEEN 15


int Player::game_version = 1;
int Player::num_players = 2;
Card Player::turn_up;

int min(int a, int b){
    if (a < b)
        return a;
    return b;
}

int score_knobs(vector<Card> hand, Card turn_up){
    if (turn_up.get_value() == 11){
        return 0;
    }
    
    for (int i = 0; i < 4; i++){
        if (hand[i].get_value() == 11 && hand[i].get_suite() == turn_up.get_suite()){
            return 1;
        }
    }
    return 0;
}
Player::Player() {
    this->score = 0;
    this->expected_value = 0;
    for (int i = 0; i< 4; i++){
        this->used_card.push_back(false);
    }
};

int Player::get_score() const {
    return this->score;
}


void Player::print_hand(vector<Card> hand) const{
    for (int i = 0; i < hand.size(); i ++){
        cout << i << ") ";
        cout << hand[i].get_name();
        cout << hand[i].get_suite() << "\t";
    }
    cout << endl;
}
int Player::set_game_version(int game_version) {
    if (game_version < 1 or game_version > 2)
        return -1;
    
    this->game_version = game_version;
    return 0;
}

void Player::set_turn_up(Card turn_up){
    this->turn_up = turn_up;
}

void Player::set_num_players(int num_players){
    this->num_players = num_players;
}
void Player::add_card_hand(Card new_card){
    this->hand.push_back(new_card);
}

void Player::add_card_crib(Card new_card){
    this->crib.push_back(new_card);
}

void Player::reset_hands(){
    this->crib.clear();
    this->hand.clear();
    
    for (int i = 0; i < 4; i++){
        this->used_card[i] = false;
    }
}

int score_pairs(int counts[NUM_CARDS_VALUE]) {
    int score = 0;
    // loop through the counts to calculate the points
    for (int i = 0; i < NUM_CARDS_VALUE; i++){
        if (counts[i] > 1){
            // There are 2 points per pair.
            // There are summation [1, n-1] pairs in n card
            int num_pairs = ((counts[i]*(counts[i]-1))/2);
            score += 2*num_pairs;
        }
    }
    
    return score;
}

int score_runs(int counts[NUM_CARDS_VALUE]){
    int multiplier = 1;
    int run = 0;
    int index = 0;
    int score = 0;
    
    while (index < NUM_CARDS_VALUE) {
        run = 0;
        multiplier = 1;
            
        while (index < NUM_CARDS_VALUE and counts[index] >= 1){
            run += 1;
            multiplier *= counts[index];
            index += 1;
        }
            
        if (run >= 3)
            score += multiplier*run;
    
        index += 1;
    }
    
    return score;
}

int score_fifteens_helper(vector<Card> hand, int index, int sum) {
  
    // Hit the subset max
    if (sum == FIFTEEN)
        return 2; 
        
    // Failure due to too far or no cards left
    if (sum > FIFTEEN || index >= 5)
        return 0;
        
    int card_value = min(hand[index].get_value(), 10);
    return score_fifteens_helper(hand, index+1, sum+card_value) + score_fifteens_helper(hand, index+1, sum);
        
}

int score_fifteens(vector<Card> hand, Card turn_up) {
    // Count subset sum, each number can be included or not 
    vector<Card> new_hand = hand;
    new_hand.push_back(turn_up);
    return score_fifteens_helper(new_hand, 0, 0);
}

int score_flush(std::vector<Card> hand, Card turn_up, bool if_crib_hand)  {
    char first_suite = hand[0].get_suite();
    
    //Check if the whole player's hand matches
    for (int i = 0; i < hand.size(); i++){
        if (hand[i].get_suite() != first_suite){
            return 0;
        }
    }
    
    // Check if the turn up card matches the suite
    bool matches_turn_up = false;
    if (turn_up.get_suite() == first_suite)
        matches_turn_up = true;
    
    // If the turn_up matches, the flush is earned + 1
    if (matches_turn_up)
        return hand.size() + 1;
    
    // If the turn up does not match and the player's crib, the
    // return is 0
    if (!matches_turn_up && if_crib_hand)
        return 0;
    
    // There is a flush without the turn up
    return hand.size();
}

int Player::score_hand(vector<Card>& hand, Card turn_up, bool if_crib_hand) const{
    int score = 0;
    
    // Count each card's frequency
    int counts[NUM_CARDS_VALUE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < hand.size(); i++){
        counts[hand[i].get_value()-1] += 1;
    }
    counts[turn_up.get_value() - 1] += 1;
    
    // 4 ways to make points: flush, pairs, runs, fifteens
    score += score_flush(hand, turn_up, if_crib_hand);
    score += score_pairs(counts);
    score += score_runs(counts);
    score += score_fifteens(hand, turn_up);
    score += score_knobs(hand, turn_up);
    return score;
}

vector<Card> Player::create_extra_deck(){
    vector<Card> deck;
    char letters[] = {'D', 'S', 'H', 'C'};
    
    for (int suite_index = 0; suite_index < 4; suite_index++){
        for (int card_num = 1; card_num < 14; card_num ++){
            Card temp(card_num, letters[suite_index]);
            
            for (int i = 0; i < this->hand.size(); i++) {
                if (temp == this->hand[i]){
                    continue;
                }
            }
            
            deck.push_back(temp);
        }
    }
    return deck;
}

void Player::select_normal(int index, vector<Card>& subset, vector< vector<Card> >& ans) {
    if (subset.size() == 4){
        ans.push_back(subset);
        return;
    }
    
    if (index >= this->hand.size()){
        return;
    }
    
    // The number can be skipped
    this->select_normal(index+1, subset, ans);
    
    // The number can be selected
    subset.push_back(this->hand[index]);
    this->select_normal(index+1, subset, ans);
    subset.pop_back();
}

void Player::select_ten_hand(int index, vector<Card>& subset, vector< vector<Card> >& ans){
    if (subset.size() == 4) {
        // combinations of 4 from what is left 
        vector<Card> new_subset;
        vector< vector<Card> > complements;
        this->select_normal(index, new_subset, complements);
        
        // Enter into ans every combination of subset, complements
        for (int i = 0; i < complements.size(); i ++) {
            vector<Card> templist;
            for (int j = 0; j < 4; j++){
                templist.push_back(new_subset[j]);
            }
            for (int j = 0; j < 4; j++){
                templist.push_back(complements[i][j]);
            }
            ans.push_back(templist);
        }
        return;
    }
    
    if (index >= this->hand.size())
        return;
        
    // Can choose to add the Card
    this->select_ten_hand(index+1, subset, ans);
    
    // Add a new Card
    subset.push_back(this->hand[index]);
    this->select_ten_hand(index+1, subset, ans);
    subset.pop_back();
    
    return;
}

vector<Card> Player::pick_crib_normal(vector<Card>& extra_deck){
    vector<Card> subset;
    int max_score = 0;
    vector<Card> max_hand;
    vector< vector<Card> > combinations;
    this->select_normal(0, subset, combinations);
    
    for (int i = 0; i < combinations.size(); i++){
        int score = 0;
        for (int j = 0; j < extra_deck.size(); j++){
            score += this->score_hand(combinations[i], extra_deck[j], false);
        }
        
        if (score > max_score) {
            max_score = score;
            max_hand = combinations[i];
        }
    }
    
    // Determine what cards were removed from max_hand 
    vector<Card> removed;
    for (int i = 0; i < this->hand.size(); i++){
        bool found = false;
        for (int j = 0; j < max_hand.size(); j++){
            if (max_hand[j] == this->hand[i]){
                found = true;
                break;
            }
        }
        if (!found){
            removed.push_back(this->hand[i]);
        }
    }
    
    // Set the player's card to the correct hand
    this->hand = max_hand;
    this->expected_value = max_score;
    
    return removed;
    
}

vector<Card> Player::pick_crib_ten_hand(vector<Card>& extra_deck){
    vector<Card> subset;
    int max_score = 0;
    vector<Card> max_hand;
    vector<Card> max_second_crib;
    vector< vector <Card>  > combinations;
    this->select_ten_hand(0, subset, combinations);
    
    for (int i = 0; i < combinations.size(); i++){
        int score = 0;
        
        vector<Card> hand1;
        vector<Card> hand2;
        
        for(int j = 0; j < 4; j++){
            hand1.push_back(combinations[i][j]);
            hand2.push_back(combinations[i][j+4]);
        }
        
        for (int j = 0; j < extra_deck.size(); j++){
            score += this->score_hand(hand1, extra_deck[j], false) + this->score_hand(hand2, extra_deck[j], true);
        }
        
        if (score > max_score){
            max_score = score;
            max_hand = hand1;
            max_second_crib = hand2;
        }
        
    }
    
    vector<Card> removed;
    for (int i = 0; i < this->hand.size(); i++){
        bool found = false;
        for (int j = 0; j < max_hand.size(); j++){
            if (max_hand[j] == this->hand[i] || max_second_crib[j] == this->hand[i]){
                found = true;
                break;
            }
        }
        
        if (!found){
            removed.push_back(this->hand[i]);
        }
    }
    
    this->hand = max_hand;
    this->second_crib = max_second_crib;
    this->expected_value = max_score;
    return removed;
    
}
vector<Card> Player::pick_crib(){
    //Potential add ons 
    vector<Card> extra_deck = this->create_extra_deck();
    
    // Create permutations of 4
    if (this->game_version == 1){
        return this->pick_crib_normal(extra_deck);
    }
    return this->pick_crib_ten_hand(extra_deck);
    
}

void Player::remove_from_hand(vector<Card> old_cards){
    int i = 0;
    
    while (i < old_cards.size()){
        int j = 0;
        while (j < this->hand.size()){
            if (this->hand[i] == old_cards[j]){
                cout << "Found the card "<<endl;
                this->hand.erase(this->hand.begin() + j);
                cout << "After bad alloc "<<endl;
                break;
            }
            j++;
        }
        i++;
    }
}
vector<Card> Player::human_pick_crib(bool if_crib){
    vector<Card> crib;
    vector<Card> playing_hand;
    vector<Card> second_crib;
    
    int num_crib_cards = 2;
    
    if(this->num_players  != 2)
        num_crib_cards -= 1;

    // Ask for crib cards
    if (if_crib)
        cout << "Select "<<num_crib_cards<<" cards to put in your crib." << endl;
    else
        cout << "Select "<<num_crib_cards<<" cards to put in your opponent's crib." <<endl;
    this->print_hand(this->hand);
    
    // move responses into list
    int num_response;
    vector<int> prev_responses;
    while (crib.size() < num_crib_cards){
        cin >> num_response;
        
        if (num_response < 0 or num_response >= this->hand.size())
            continue;
            
        // Check that the number is not used already
        bool found = false;
        for (int i = 0; i < prev_responses.size(); i++){
            if (num_response == prev_responses[i]){
                found = true;
                break;
            }
        }
        
        if (found)
            continue;
            
        prev_responses.push_back(num_response);
        crib.push_back(this->hand[num_response]);
    }
    
    // If game version > 1, then pick a second hand
    if (this->game_version == 2){
        cout << "Now select the second crib." <<endl;
        
        while (second_crib.size() < 4){
            cin >> num_response;
        
            if (num_response < 0 or num_response >= this->hand.size())
                continue;
            
            // Check that the number is not used already
            bool found = false;
            for (int i = 0; i < prev_responses.size(); i++){
                if (num_response == prev_responses[i]){
                    found = true;
                }
            }
        
            if (found)
                continue;
                
            prev_responses.push_back(num_response);
            second_crib.push_back(this->hand[num_response]);
        }
    }
    
    // Place the rest into the hand
    sort(prev_responses.begin(), prev_responses.end());
    int prev_responses_index = 0;
    for(int i = 0; i < this->hand.size(); i++){
        if (prev_responses[prev_responses_index] == i){
            prev_responses_index += 1;
            continue;
        }
        
        // Add the item to the playing_hand
        playing_hand.push_back(this->hand[i]);
    }
    
    this->hand = playing_hand;
    this->second_crib = second_crib;
    return crib;
}

int Player::calculate_hand_score(){
    int score = this->score_hand(this->hand, this->turn_up, false);
    this->score += score;
    return score;
}

int Player::calculate_second_crib_score(){
    int score = this->score_hand(this->second_crib, this->turn_up, true);
    this->score += score;
    return score;
}

bool too_far(Card card, int cur_score){
    int card_value = min(card.get_value(), 10);
            
    if (cur_score + card_value <= 31){
        return false;
    }
    return true;
}
int Player::calculate_crib_score(){
    int score = this->score_hand(this->crib, this->turn_up, true);
    this->score += score;
    return score;
}

int score_card_in_play(vector<Card> prev_deck, Card new_card, int cur_score){
    int value_new_card = min(new_card.get_value(), 10);
    
    int score = 0;
    
    // 15
    if (value_new_card + cur_score == 15){
        score += 2;
    }
    
    // 31
    if (value_new_card + cur_score == 31){
        score += 2;
    }
    
    // Pairs 
    int index = prev_deck.size() - 1;
    int count = 1;
    while (index >= 0 and prev_deck[index].get_value() == new_card.get_value()){
        count += 1;
        index -= 1;
    }
    score += count*(count-1);
    
    // Runs
    int counts[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    counts[new_card.get_value() - 1] += 1;
    
    index = prev_deck.size() - 1;
    int max_score = 0;
    while (index >= 0){
        counts[prev_deck[index].get_value()-1] += 1;
        int run_score = score_runs(counts);
        
        if (run_score > max_score)
            max_score = run_score;
        index -= 1;
    }
    score += max_score;
    
    return score;
}

Card Player::play_hand(vector<Card> prev_deck, int cur_score){
    Card best_card;
    int best_score = -1;
    int best_index = -1;
    // For each usable card, determine the player score
    for(int i = 0; i<4; i++){
        if (this->used_card[i]){
            continue;
        }
        
        if (too_far(this->hand[i], cur_score)){
            continue;
        }
        
        int card_score = score_card_in_play(prev_deck, this->hand[i], cur_score);
        
        if (card_score > best_score){
            best_score = card_score;
            best_card = this->hand[i];
            best_index = i;
        }
    }
    
    if (best_index != -1){
        this->used_card[best_index] = true;
        this->score += best_score;
        cout << "Opponent played "<< best_card << " for "<<best_score<< " points." <<endl;
    }
    return best_card;
    
}

Card Player::human_play_hand(vector<Card> prev_deck, int cur_score){
    // Print all the cards that can go
    Card failure;
    bool flag_usable_card = false;
    for (int i = 0; i < 4; i++){
        if (!this->used_card[i]){
            cout << i << ") " << this->hand[i] <<" ";
            
            if (!too_far(this->hand[i], cur_score)){
                flag_usable_card = true;
            }
        }
        
    }
    cout << endl;
    
    if (!flag_usable_card){
        cout << "You cannot go!" << endl;
        return failure;
    }
    
    // Check if that card is an option {loop}
    cout << "Select the card to go." <<endl;
    int response = -1;
    while (response < 0 || response >= 4){
        cin >> response;
        
        if (this->used_card[response]){
            cout << "That card has been used." <<endl;
            response = -1;
            continue;
        }
        
        if (too_far(this->hand[response], cur_score)){
            cout << "That card is not eligible because it goes over 31" <<endl;
            response = -1;
            continue;
        }
    
    }
    int score = score_card_in_play(prev_deck, this->hand[response], cur_score);
    this->score += score;
    cout << "You played "<< this->hand[response]<< " for "<<score<< " points."<<endl;
    this->used_card[response] = true;
    
    return this->hand[response];
}

int Player::human_practice(){
    // Collect the extra cards
    vector<Card> extra_deck = this->create_extra_deck();
    
    this->human_pick_crib(false);
    int expected_value = 0;
    for(int i = 0; i< extra_deck.size(); i++){
        expected_value += this->score_hand(this->hand, extra_deck[i], false);
        
        if (this->game_version == 2){
            expected_value += this->score_hand(this->second_crib, extra_deck[i], true);
        }
    }
    return expected_value;
    
    
}