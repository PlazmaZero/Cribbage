#include "Card.h"
#include <vector>
#ifndef PLAYER
#define PLAYER

int score_pairs(int counts[]);
int score_flush(vector<Card> hand, Card turn_up, bool if_crib_hand);
int score_fifteens_helper(vector<Card> hand, int index, int sum);
int score_fifteens(vector<Card> hand, Card turn_up);
int score_runs(int counts[]);
int score_knobs(vector<Card> hand, Card turn_up);
class Player {
    public:
        Player();
        int get_score() const;
        void print_hand(vector<Card> hand) const;
        
        int increase_score();
        void set_num_players(int num_players);
        int set_game_version(int game_version);
        void set_turn_up(Card turn_up);
        void add_card_hand(Card new_card);
        void add_card_crib(Card new_card);
        void reset_hands();
        
        vector<Card> create_extra_deck();
        
        
        
        
        
        int score_hand(vector<Card>& hand, Card turn_up, bool if_crib_hand) const;
        int calculate_hand_score();
        int calculate_second_crib_score();
        int calculate_crib_score();
        
        void select_normal(int index, vector<Card>& subset, vector< vector<Card> >& ans);
        void select_ten_hand(int index, vector<Card>& subset, vector< vector<Card>> & ans);
        
        vector<Card> pick_crib_ten_hand(vector<Card>& extra_deck);
        vector<Card> pick_crib_normal(vector<Card>& extra_deck);
        vector<Card> pick_crib();
        vector<Card> human_pick_crib(bool if_crib);
        int human_practice();
        Card play_hand(vector<Card> prev_deck, int cur_score);
        Card human_play_hand(vector<Card> prev_deck, int cur_score);
        
        void remove_from_hand(vector<Card> old_cards);
    
        static int game_version;
        static Card turn_up;
        static int num_players;
        int score;
        vector<Card> hand;
        vector<bool> used_card;
        vector<Card> crib;
        vector<Card> second_crib;
        int expected_value;
};
#endif