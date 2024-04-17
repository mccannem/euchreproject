#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

TEST(test_default_ctor) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}
TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}
TEST(test_rank){
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(JACK, c.get_rank());
}
TEST(test_suit){
    Card c(TWO, SPADES);
    ASSERT_EQUAL(SPADES, c.get_suit());
}
TEST(test_suit_trump){
    Card c(JACK, HEARTS);
    Card d(QUEEN, HEARTS);
    ASSERT_EQUAL(DIAMONDS, c.get_suit(DIAMONDS));
    ASSERT_EQUAL(HEARTS, d.get_suit(DIAMONDS));
}

TEST(test_is_face_or_ace) {
    Card face(JACK, CLUBS);
    Card nonFace(NINE, CLUBS);
    Card ace(ACE, CLUBS);
    ASSERT_TRUE(face.is_face_or_ace());
    ASSERT_FALSE(nonFace.is_face_or_ace());
    ASSERT_TRUE(ace.is_face_or_ace());
}

TEST(test_is_right_bower){
    Card c(JACK, HEARTS);
    Card d(JACK, DIAMONDS);
    Card e(TWO, HEARTS);
    ASSERT_TRUE(c.is_right_bower(HEARTS));
    ASSERT_FALSE(d.is_right_bower(HEARTS));
    ASSERT_FALSE(e.is_right_bower(HEARTS));
}
TEST(test_is_left_bower){
    Card c(JACK, HEARTS);
    Card d(JACK, DIAMONDS);
    Card e(TWO, HEARTS);
    ASSERT_TRUE(c.is_left_bower(DIAMONDS));
    ASSERT_FALSE(d.is_left_bower(DIAMONDS));
    ASSERT_FALSE(e.is_left_bower(DIAMONDS));
}

TEST(test_is_trump) {
    Card trump(TWO, HEARTS);
    Card leftBower(JACK, DIAMONDS);
    Card nonTrump(TWO, SPADES);
    ASSERT_TRUE(trump.is_trump(HEARTS));
    ASSERT_TRUE(leftBower.is_trump(HEARTS));
    ASSERT_FALSE(nonTrump.is_trump(HEARTS));
}


TEST(test_comparisons) {
    Card c(KING, HEARTS);
    Card d(TWO, SPADES);
    Card e(TWO, SPADES);
    ASSERT_FALSE(c < d);
    ASSERT_TRUE(d < c);
    ASSERT_FALSE(d < e);

    ASSERT_TRUE(e <= d);
    ASSERT_FALSE(c <= d);
    ASSERT_TRUE(d <= c);
    
    ASSERT_FALSE(d > c);
    ASSERT_FALSE(d > e);
    ASSERT_TRUE(c > d);

    ASSERT_TRUE(e >= d);
    ASSERT_FALSE(d >= c);
    ASSERT_TRUE(c >= d);
    
    ASSERT_TRUE(e == d);
    ASSERT_FALSE(c == d);

    ASSERT_FALSE(e != d);
    ASSERT_TRUE(c != d);
}

TEST(test_suit_next) {
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
}

TEST(test_card_less){
    Card c(TWO, SPADES);
    Card d(THREE, SPADES);
    Card e(QUEEN, HEARTS);
    Card f(KING, DIAMONDS);
    Card g(TWO, SPADES);
    Card rightBower(JACK, SPADES);
    Card leftBower(JACK, CLUBS);
    Card highTrump(KING, SPADES);

    //both trump
    ASSERT_TRUE(Card_less(c, d, SPADES));
    ASSERT_FALSE(Card_less(d, c, SPADES));

    //one trump
    ASSERT_FALSE(Card_less(c, e, SPADES));
    ASSERT_TRUE(Card_less(e, c, SPADES));
    
    //no trump
    ASSERT_TRUE(Card_less(e, f, SPADES));
    ASSERT_FALSE(Card_less(f, e, SPADES));

    //same card
    ASSERT_FALSE(Card_less(c, g, SPADES));
    
    //left bower and trump
    ASSERT_TRUE(Card_less(g, leftBower, SPADES));
    ASSERT_FALSE(Card_less(leftBower, g, SPADES));
    ASSERT_FALSE(Card_less(leftBower, highTrump, SPADES));
    ASSERT_TRUE(Card_less(highTrump, leftBower, SPADES));

    //right bower and left bower
    ASSERT_FALSE(Card_less(rightBower, leftBower, SPADES));
    ASSERT_TRUE(Card_less(leftBower, rightBower, SPADES));
}

TEST(test_card_less_led) {
    Card trump(QUEEN, HEARTS);
    Card trump2(KING, HEARTS);
    Card leftBower(JACK, DIAMONDS);
    Card rightBower(JACK, HEARTS);
    Card led(QUEEN, SPADES);
    Card led2(TEN, SPADES);
    Card nonLed(QUEEN, CLUBS);
    Card nonLed2(TEN, CLUBS);

    //left and right bower
    ASSERT_TRUE(Card_less(leftBower, rightBower, led, HEARTS));
    ASSERT_FALSE(Card_less(rightBower, leftBower, led, HEARTS));

    //left bower and trump
    ASSERT_TRUE(Card_less(trump, leftBower, led, HEARTS));
    ASSERT_FALSE(Card_less(leftBower, trump, led, HEARTS));

    //right bower and trump
    ASSERT_TRUE(Card_less(trump, rightBower, led, HEARTS));
    ASSERT_FALSE(Card_less(rightBower, trump, led, HEARTS));
    
    //trump and trump
    ASSERT_TRUE(Card_less(trump, trump2, led, HEARTS));
    ASSERT_FALSE(Card_less(trump2, trump, led, HEARTS));

    //trump and non-trump
    ASSERT_TRUE(Card_less(led, trump, led, HEARTS));
    ASSERT_FALSE(Card_less(trump, led, led, HEARTS));

    //led and led
    ASSERT_TRUE(Card_less(led2, led, led, HEARTS));
    ASSERT_FALSE(Card_less(led, led2, led, HEARTS));

    //led and non-led
    ASSERT_TRUE(Card_less(nonLed, led, led, HEARTS));
    ASSERT_FALSE(Card_less(led, nonLed, led, HEARTS));

    //non-led and non-led
    ASSERT_TRUE(Card_less(nonLed2, nonLed, led, HEARTS));
    ASSERT_FALSE(Card_less(nonLed, nonLed2, led, HEARTS));
     
}
// Add more test cases here

TEST_MAIN()
