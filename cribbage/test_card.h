#ifndef TEST_CARD
#define TEST_CARD
bool test_card_creation_empty();
bool test_card_creation();
bool test_card_creation_fail_suite();
bool test_card_creation_fail_value_under();
bool test_card_creation_fail_value_over();
bool test_card_equals_true();
bool test_card_equals_mismatch_completely();
bool test_card_equals_mismatch_suite();
bool test_card_equals_mismatch_value();
bool test_card_less_than_true();
bool test_card_less_than_false_same();
bool test_card_less_than_false_greater();
void run_card_tests();
#endif