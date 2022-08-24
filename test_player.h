#ifndef TEST_Player
#define TEST_Player

bool test_player_score_pairs_no_pairs ();
bool test_player_score_pairs_one_pair();
bool test_player_score_pairs_three_of_a_kind();
bool test_player_score_pairs_four_of_a_kind();
bool test_player_score_pairs_two_distinct_pairs();
bool test_player_score_pairs_two_and_three();
int score_pair_tests();

bool test_player_score_flush_none();
bool test_player_score_flush_same_color();
bool test_player_score_flush_full_flush();
bool test_player_score_flush_partial_flush();
int score_flush_tests();

bool test_player_score_fifteens_full_add();
bool test_player_score_fifteens_none();
bool test_player_score_fifteens_share_number();
bool test_player_score_fifteens_distinct_fifteens();
int score_fifteen_tests();
    
bool test_player_score_knobs_none();
bool test_player_score_knobs_jack_no_suite();
bool test_player_score_knobs_turn_up_jack();
bool test_player_score_knobs_suite_no_jack();
bool test_player_score_knobs_true();
int score_knobs_tests();

bool test_player_score_runs_none();
bool test_player_score_runs_three();
bool test_player_score_runs_two_of_three();
bool test_player_score_runs_four();
bool test_player_score_runs_two_of_four();
bool test_player_score_runs_five();
int score_runs_tests();

void run_player_tests ();
#endif
