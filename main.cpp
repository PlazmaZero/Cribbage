/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
#include "Card.h"
#include "Player.h"
#include "test_card.h"
#include "test_player.h"
using namespace std;

#define GAME_MAX_SCORE 121

auto rng = std::default_random_engine {};
Card FAILED_CARD;

void shuffle_deck(vector<Card>& deck){
    std::shuffle(std::begin(deck), std::end(deck), rng);
}

vector<Card> create_deck(){
    vector<Card> deck;
    char letters[] = {'D', 'S', 'H', 'C'};
    
    for (int suite_index = 0; suite_index < 4; suite_index++){
        for (int card_num = 1; card_num < 14; card_num ++){
            Card temp(card_num, letters[suite_index]);
            deck.push_back(temp);
        }
    }
    return deck;
}

int determine_number_cards(int num_players, int game_version){
    // Regular cribbage runs with 6 cards, ten hand runs with 10
    int num_cards = (game_version == 1) ? 6 :  10;
    
    // If there are more than two players, every player gets one fewer card
    if (num_players != 2){
        num_cards -= 1;
    }
    
    return num_cards;
}

void deal(vector<Player>& players, vector<Card> deck, int num_cards){

    shuffle_deck(deck);
    for (int i = 0; i < num_cards; i++){
        for (int j = 0; j < players.size(); j++){
            players[j].add_card_hand(deck[i*players.size() + j]);
        }
    }

}

void print_scores(vector<Player> players){
    for(int i = 0; i < players.size(); i++){
        cout << "Player "<<i+1 << ": "<< players[i].get_score() << endl;
    }
}

bool check_player_won(vector<Player> players){
    if (players.size() == 4){
        // Check the first and third vs the second and fourth
        int team1 = players[0].get_score() + players[2].get_score();
        int team2 = players[1].get_score() + players[3].get_score();
        
        if (team1 >= GAME_MAX_SCORE){
            cout << "Team one won!" << endl;
            print_scores(players);
            return true;
        }
        if(team2 >= GAME_MAX_SCORE){
            cout << "Team two won!" <<endl;
            print_scores(players);
            return true;
        }
        return false;
    }
    
    for (int i = 0; i < players.size(); i++){
        if (players[i].get_score() >= GAME_MAX_SCORE){
            cout << "Player "<<i+1 << " Won!" <<endl;
            print_scores(players);
            return true;
        }
    }
    return false;
}

void select_crib(vector<Player>& players, int crib, int num_cards_per_player, vector<Card> deck){
    // Run a round selecting the crib
    vector<Card> crib_hand;
    
    for (int i = 0; i < players.size(); i++){
        // start with the player who is to the right of the one with the crib
        int player_num = (crib + i + 1)%(players.size());
        vector<Card> crib_add_on;
        
        if (player_num == 0){
            crib_add_on = players[player_num].human_pick_crib(player_num == crib);
        }
        else{
            crib_add_on = players[player_num].pick_crib();
        }
        
        for(int i = 0; i < crib_add_on.size(); i++){
            crib_hand.push_back(crib_add_on[i]);
        }
    }
    
    if (crib_hand.size() < 4)
        crib_hand.push_back(deck[(players.size()*num_cards_per_player) + 1]);
            
    players[crib].crib = crib_hand;
}

void select_turn_up(vector<Player>& players, vector<Card>& deck, int number_cards){
    Card turn_up = deck[number_cards*players.size()];
    players[0].set_turn_up(turn_up);
        
    cout << "The turn-up card is: " << turn_up << endl;
}

bool score_hands(vector<Player>& players, int crib){
    for (int i = 0; i < players.size(); i++){
        int player_num = (crib + i + 1)%(players.size());
        
        int score = players[player_num].calculate_hand_score();
         
        cout << "Player "<< i+1 << endl;
        players[player_num].print_hand(players[player_num].hand);
        cout << "Player " << i+1 << " scored " << score << " points in their hand."<< endl;
            
        if (check_player_won(players)) {
            return true;
        }
    }
    return false;
}

bool score_second_cribs(vector<Player>& players, int crib){
    for (int i = 0; i < players.size(); i++){
        int player_num = (crib + i + 1)%(players.size());
        
        int score = players[player_num].calculate_second_crib_score();
         
        cout << "Player "<< i+1 << endl;
        players[player_num].print_hand(players[player_num].second_crib);
        cout << "Player " << i+1 << " scored " << score << " points in their second crib."<< endl;
            
        if (check_player_won(players)) {
            return true;
        }
    }
    return false;
}

bool score_crib(vector<Player>& players, int crib){
    int score = players[crib].calculate_crib_score();
    
    players[crib].print_hand(players[crib].crib);
    cout << "Player " << crib + 1 << " scored " << score << " points in their crib."<< endl;
            
    if (check_player_won(players)) {
        return true;        
    }
    
    return false;
}

int select_game_version(){
    int game_version = -1;
    
    cout << "Select your game: \n1) Cribbage or \n2) Ten Hand Cribbage" <<endl;
    while (game_version != 1 && game_version != 2){
        cin >> game_version;
    }
    
    return game_version;
}

int select_num_players(){
    int num_players = -1;
    cout << "How many players? (2-4) " <<endl;
    while (num_players <= 1 || num_players > 4){
        cin >> num_players;
    }
    
    return num_players;
}

int run_round(vector<Player>& players, int starting_position){
    int cur_count = 0;
    vector<bool> can_go;
    int player_can_go = players.size();
    int pos = starting_position;
    
    for (int i = 0; i < players.size(); i++){
        can_go.push_back(true);
    }
    
    vector<Card> past;
    
    while (cur_count < 31 && player_can_go > 0){
        cout << "The current count in play is " <<cur_count<<endl;
        
        // Skip players that have previosly been skipped
        if (!can_go[pos]){
            pos = (pos + 1)%players.size();
            continue;
        }
        
        Card placed;
        if (pos == 0){
            placed = players[pos].human_play_hand(past, cur_count);
        }
        else{
            placed = players[pos].play_hand(past, cur_count);
        }
            
        // This player does not have any more valid moves this round
        if (placed == FAILED_CARD){
            can_go[pos] = false;
            player_can_go -= 1;
            
            pos = (pos + 1)%players.size();
            continue; 
        }
        
        // The move was valid.
        pos = (pos + 1)%players.size();
        past.push_back(placed);
        cur_count += min(placed.get_value(), 10);
        
        if (check_player_won(players))
            return pos;
    }
    
    cout << "That was the last card to 31, the board has reset." <<endl;
    // Last player gets one point
    if (cur_count != 31)
        players[pos].score += 1;
    
    if (check_player_won(players))
        return pos;
            
    return pos;
    
}

bool cards_left(vector<Player>&players){
    for (int i = 0; i < players.size(); i++){
        for (int j = 0; j < 4; j ++){
            if (players[i].used_card[j] == false)
                return true;
        }
    }
    return false;
}
bool run_play(vector<Player>& players, int crib){
    int player_num = (crib+1)%(players.size());
    int cur_count = 0;
    int last_pos = crib;
    
    while (cards_left(players)){
        last_pos = run_round(players, last_pos+1);
        
        if (check_player_won(players))
            return true;
    }
    
    return false;

}

void play_game(int game_version, int num_players){
    // Set Up 
    int number_cards = determine_number_cards(num_players, game_version);
    vector<Card> deck = create_deck();
    
    // Create a player object up to the number needed by the game_version
    vector<Player> players(num_players);
    players[0].set_game_version(game_version);
    players[0].set_num_players(num_players);
    int crib = 0;
    
    // Acutally play the game
    bool game_over = false;
    while (!game_over){
        cout << "\n\nA new round is starting."<<endl;
        
        for (int i = 0; i< num_players; i++){
            cout << "Player "<<i+1<<" has "<< players[i].get_score() << " points." << endl;
        }
        
        // Deal to each player
        deal(players, deck, number_cards);
        
        //Run a round, selecting the crib
        select_crib(players, crib, number_cards, deck);
        
        // Select the turn up
        select_turn_up(players, deck, number_cards);
        
        // Run choices in play
        game_over = run_play(players, crib);
        
        if (game_over)
            break;

        // Add player_scores, inch the crib forward and reset their hands
        game_over = score_hands(players, crib);
        
        if (game_over)
            break;
        
        // Add the crib scoring if ten hand
        if (game_version == 2){
            game_over  = score_second_cribs(players, crib);
            
            if (game_over)
                break;
        }
        
        // Add the real crib score
        game_over = score_crib(players, crib);
  
        // Increment the crib and reset the hands
        crib = (crib+1)%(num_players);        
        for (int i = 0; i < num_players; i++){
            players[i].reset_hands();
        }
    }
}


void practice(int game_version, int num_players){
    vector<Card> deck = create_deck();
    Player temp_player;
    Player human_player;
    temp_player.set_game_version(game_version);
    temp_player.set_num_players(num_players);
    int num_cards = determine_number_cards(num_players, game_version);
    bool play = true;
    string response = "Y";
    
    while (response == "Y"){
        // Shuffle the deck, assign the cards to the computer and human
        shuffle_deck(deck);
        
        for(int i = 0; i < num_cards; i++){
            temp_player.add_card_hand(deck[i]);
            human_player.add_card_hand(deck[i]);
        }
    
        // Have the computer select its hand
        temp_player.pick_crib();
        
        // Display the human hand
        int human_expected_value = human_player.human_practice();
        
        // Check to see if the expected value of the human hand matches that of the computer
        int expected_value = temp_player.expected_value;
        
        // If not, print the computer's choice
        if (human_expected_value == expected_value){
            cout << "You were right!" << endl;
        }
        else{
            cout << "Sorry a better pick would have been " << endl;
            temp_player.print_hand(temp_player.hand);
            
            if (game_version == 2)
                 temp_player.print_hand(temp_player.second_crib);
        }
        cout << "Play another round? [Y/N]?" << endl;
        cin >> response;
        
        temp_player.reset_hands();
        human_player.reset_hands();
    }
}

int main()
{
    int game_version = select_game_version();
    int num_players = select_num_players();
    cout << "Would you like to 1) Practice or 2) Play? " << endl;
    int activity = -1;
    while (activity < 1 || activity > 2){
        cin >> activity;
    }
    
    if (activity == 1)
        practice(game_version, num_players);
    else
        play_game(game_version, num_players);
}

