#include "Player.hpp"
#include "unit_test_framework.hpp"
#include <cassert>
#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;
}
 

TEST(testSP_maketrumpPassR1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, HEARTS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, HEARTS));
    
  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  delete bob;
}
TEST(testSP_make_trumpR2orderup) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, CLUBS));
  bob->add_card(Card(TEN, CLUBS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(KING, CLUBS));
  bob->add_card(Card(ACE, CLUBS));
    
  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}

TEST(testSP_make_trumpR2orderup_1card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(KING, DIAMONDS));
  bob->add_card(Card(ACE, DIAMONDS));
    
  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}

TEST(testSP_make_trumpR2pass) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, HEARTS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, HEARTS));
    
  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    false,           // Bob is also the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  delete bob;
}

TEST(testSP_makeTrumpRoundOrderUp) {
    Player * alice = Player_factory("Alice", "Simple");
    Card upcard(JACK, HEARTS);
    Suit order_up_suit;

    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(KING, HEARTS));
    alice->add_card(Card(ACE, HEARTS));

    bool result = alice->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_TRUE(result); 
    ASSERT_EQUAL(HEARTS, order_up_suit);  
    delete alice;
}

TEST(testSP_makeTrumpRoundOrderUp_leftbower) {
    Player * alice = Player_factory("Alice", "Simple");
    Card upcard(JACK, HEARTS);
    Suit order_up_suit;

    alice->add_card(Card(JACK, DIAMONDS));
    alice->add_card(Card(KING, HEARTS));
    alice->add_card(Card(ACE, SPADES));

    bool result = alice->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_TRUE(result); 
    ASSERT_EQUAL(HEARTS, order_up_suit);  
    delete alice;
}


TEST(testSP_makeTrumpRoundOrderUp2cards) {
    Player * alice = Player_factory("Alice", "Simple");
    Card upcard(JACK, HEARTS);
    Suit order_up_suit;

    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(KING, HEARTS));
    alice->add_card(Card(ACE, SPADES));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(QUEEN, SPADES));


    bool result = alice->make_trump(upcard, false, 1, order_up_suit);
    ASSERT_TRUE(result); 
    ASSERT_EQUAL(HEARTS, order_up_suit);  
    delete alice;
}

TEST(test_screw_the_dealer) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));
    
  // Bob makes trump
  Card upcard(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    upcard,    // Upcard
    true,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}

/*
TEST(test_add_and_discard) {
  Player * bob = Player_factory("Bob", "Simple");

  //Old hand
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));
  Card upcard(QUEEN, CLUBS);

  bob->add_and_discard(upcard);
    
  ASSERT_EQUAL(bob->hand[2].get_rank(), QUEEN);

}
*/

TEST(ledcardSP_allTrump){
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  Card playedCard = bob->lead_card(SPADES);
  ASSERT_EQUAL(playedCard.get_rank(), ACE);
  ASSERT_EQUAL(playedCard.get_suit(), SPADES);
  delete bob;
}

TEST(ledcardSP_noTrump){
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  Card playedCard = bob->lead_card(HEARTS);
  ASSERT_EQUAL(playedCard.get_rank(), ACE);
  ASSERT_EQUAL(playedCard.get_suit(), SPADES);
  delete bob;
}

TEST(ledcardSP_mixedTrump){
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(KING, CLUBS));
  bob->add_card(Card(ACE, SPADES));

  Card playedCard = bob->lead_card(HEARTS);
  ASSERT_EQUAL(playedCard.get_rank(), ACE);
  ASSERT_EQUAL(playedCard.get_suit(), SPADES);
  delete bob;
}

TEST(playcardSP_followsuit){
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, DIAMONDS));
    bob->add_card(Card(TEN, DIAMONDS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(KING, DIAMONDS));
    bob->add_card(Card(JACK, DIAMONDS));

    Card c(ACE, DIAMONDS);

    Card playedCard = bob->play_card(c, DIAMONDS);
    ASSERT_EQUAL(playedCard.get_rank(), JACK);
    ASSERT_EQUAL(playedCard.get_suit(), DIAMONDS); 
    delete bob;
}


TEST(playcardSP_LeftBower){
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, DIAMONDS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(KING, CLUBS));
    bob->add_card(Card(JACK, HEARTS));

    Card c(JACK, HEARTS);

    Card playedCard = bob->play_card(c, DIAMONDS);
    ASSERT_EQUAL(playedCard.get_rank(), JACK);

    ASSERT_EQUAL(playedCard.get_suit(), HEARTS); 
    delete bob;
}

TEST(playcardSP_playLow){
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, DIAMONDS));
    bob->add_card(Card(TEN, DIAMONDS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(KING, DIAMONDS));
    bob->add_card(Card(ACE, DIAMONDS));

    Card c(NINE, HEARTS);

    Card playedCard = bob->play_card(c, CLUBS);
    ASSERT_EQUAL(playedCard.get_rank(), NINE);
    ASSERT_EQUAL(playedCard.get_suit(), DIAMONDS); 
    delete bob;
}

TEST(test_add_discard_leftbower_ignoreTrump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(JACK, DIAMONDS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead (highest non-trump)
  Card leader(ACE, SPADES);
  ASSERT_EQUAL(card_led, leader); //check led card

  delete bob;
}

TEST(test_add_discard_leftbower_allTrump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, HEARTS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(JACK, DIAMONDS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead (highest non-trump)
  Card leader(JACK, DIAMONDS);
  ASSERT_EQUAL(card_led, leader); //check led card

  delete bob;
}

TEST(test_add_discard_newHighest) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, DIAMONDS));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(KING, DIAMONDS));
  bob->add_card(Card(ACE, DIAMONDS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(JACK, DIAMONDS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(DIAMONDS);

  // Verify the card Bob selected to lead (highest non-trump)
  Card leader(JACK, DIAMONDS);
  ASSERT_EQUAL(card_led, leader); //check led card

  delete bob;
}
// Add more tests here

TEST_MAIN()
