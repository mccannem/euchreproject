#include "Player.hpp"
#include <cassert>
#include <string>
#include <algorithm>


using namespace std;


class SimplePlayer : public Player {
   private:
   string name;
   vector<Card> hand;
    public:
   SimplePlayer(const string& name)
     : name(name) {}
  
   //EFFECTS returns player's name
   const string& get_name() const override {
       return name;
   }




 //REQUIRES player has less than MAX_HAND_SIZE cards
 //EFFECTS  adds Card c to Player's hand
   void add_card(const Card &c) override{
       hand.push_back(c);
       sort(hand.begin(), hand.end());
       return;
   }


 //REQUIRES round is 1 or 2
 //MODIFIES order_up_suit
 //EFFECTS If Player wishes to order up a trump suit then return true and
 //  change order_up_suit to desired suit.  If Player wishes to pass, then do
 //  not modify order_up_suit and return false.
   bool make_trump(const Card &upcard, bool is_dealer,
                         int round, Suit &order_up_suit) const override{
       Suit trump = upcard.get_suit();
       if (round == 1){
           int count = 0;
           for (int i = 0; i < hand.size(); ++i){
              if (hand[i].is_face_or_ace() && hand[i].is_trump(trump)){
                   count++;
               }
           }
           if (count >= 2){
               order_up_suit = trump;
               return true;
           }
           else {
               return false;
           }
       }
       else {
           if (is_dealer){
               order_up_suit = Suit_next(trump);
               return true;
           }
           else {
             int count = 0;
           for (int i = 0; i < hand.size(); ++i){
              if (hand[i].is_face_or_ace() && hand[i].get_suit() == Suit_next(trump)){
                   count++;
               }
           }
           if (count >= 1){
               order_up_suit = Suit_next(trump);
               return true;
           }
           else {
               return false;
           }
         }
          
       }
   }


 //REQUIRES Player has at least one card
 //EFFECTS  Player adds one card to hand and removes one card from hand.
 void add_and_discard(const Card &upcard) override{


   add_card(upcard);
   Card worstCard = hand[0];
   int worstIndex = 0;
     for (int i = 1; i < hand.size(); ++i) {
         if (Card_less(hand[i], worstCard, upcard.get_suit())) {
           worstCard = hand[i];
            worstIndex = i;
           }
       }
   hand.erase(hand.begin() + worstIndex);
   return;
 }


 //REQUIRES Player has at least one card
 //EFFECTS  Leads one Card from Player's hand according to their strategy
 //  "Lead" means to play the first Card in a trick.  The card
 //  is removed the player's hand.
 Card lead_card(Suit trump) override{
   //play the highest non-trump card in hand
   bool onlyTrump = true;
   Card max(TWO, Suit_next(trump));
   int index = 0;
    for (int i = 0; i < hand.size(); ++i){
     if (!hand[i].is_trump(trump)){
       onlyTrump = false;
     }
   }
   if (onlyTrump){
     for (int i = 0; i < hand.size(); ++i){
       if (Card_less(max, hand[i], trump)){
         max = hand[i];
         index = i;
       }
     }
   }
   else {
     for (int i = 0; i < hand.size(); ++i){
       if (Card_less(max, hand[i], trump) && !hand[i].is_trump(trump)){
         max = hand[i];
         index = i;
       }
     }
   }
   hand.erase(hand.begin() + index);
   return max;
 }


 //REQUIRES Player has at least one card
 //EFFECTS  Plays one Card from Player's hand according to their strategy.
 //  The card is removed from the player's hand.
 Card play_card(const Card &led_card, Suit trump) override{
   bool hasSuit = false;
   int nonTrump = trump;
   nonTrump++;
   Suit notTrump = static_cast<Suit>(nonTrump);
   for (int i = 0; i < hand.size(); ++i){
     if (hand[i].get_suit(trump) == led_card.get_suit(trump)){
       hasSuit = true;
     }
   }
   if (hasSuit){
     Card max(TWO, notTrump);
     int index = 0;
     for (int i = 0; i < hand.size(); ++i){
       if (hand[i].get_suit(trump) == led_card.get_suit(trump)) {
         if (Card_less(max, hand[i], led_card, trump) ){
         max = hand[i];
         index = i;
       }
       }
     }
     hand.erase(hand.begin() + index);
     return max;
    }
    else {
     Card min(JACK, trump);
     int index;
     for (int i = 0; i < hand.size(); ++i){
       if (Card_less(hand[i], min, led_card, trump)){
         min = hand[i];
         index = i;
       }
     }
     hand.erase(hand.begin() + index);
     return min;
    }
   }
  // Maximum number of cards in a player's hand
   static const int MAX_HAND_SIZE = 5;
};


class HumanPlayer : public Player {
   private:
       string name;
       vector<Card> hand;
       void print_hand() const {
           for (size_t i=0; i < hand.size(); ++i) {
            cout << "Human player " << name << "'s hand: ";
            cout << "[" << i << "] " << hand[i] << "\n";
           }
           return;
       }


      
     public:
       HumanPlayer(const string& name)
         : name(name) {}
 
   const string& get_name() const override{
       return name;
   }


 //REQUIRES player has less than MAX_HAND_SIZE cards
 //EFFECTS  adds Card c to Player's hand
   void add_card(const Card &c) override{
       hand.push_back(c);
       sort(hand.begin(), hand.end());
       return;
   }


 //REQUIRES round is 1 or 2
 //MODIFIES order_up_suit
 //EFFECTS If Player wishes to order up a trump suit then return true and
 //  change order_up_suit to desired suit.  If Player wishes to pass, then do
 //  not modify order_up_suit and return false.
   bool make_trump(const Card &upcard, bool is_dealer,
                         int round, Suit &order_up_suit) const override {
      print_hand();
      cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";


      string decision;
      cin >> decision;


      if (decision != "pass") {
       order_up_suit = string_to_suit(decision);
       return true;
      }


      else {
       return false;
      }
   }


 //REQUIRES Player has at least one card
 //EFFECTS  Player adds one card to hand and removes one card from hand.
 void add_and_discard(const Card &upcard) override{
   add_card(upcard);
   print_hand();
   cout << "Discard upcard: [-1]\n";
   cout << "Human player " << name << ", please select a card to discard:\n";


   int discard;
   cin >> discard;


   hand.erase(hand.begin() + discard);


   return;


 }


 //REQUIRES Player has at least one card
 //EFFECTS  Leads one Card from Player's hand according to their strategy
 //  "Lead" means to play the first Card in a trick.  The card
 //  is removed the player's hand.
 Card lead_card(Suit trump) override{
   //play the highest non-trump card in hand
   print_hand();
   cout << "Human player " << name << ", please select a card:\n";


   int play;
   cin >> play;
   cout << play;
   
   hand.erase(hand.begin() + play);
   return hand[play];
 }


 //REQUIRES Player has at least one card
 //EFFECTS  Plays one Card from Player's hand according to their strategy.
 //  The card is removed from the player's hand.
 Card play_card(const Card &led_card, Suit trump) override{
   print_hand();
   cout << "Human player " << name << ", please select a card:\n";


   int play;
   cin >> play;

   hand.erase(hand.begin() + play);
   return hand[play];
}
  // Maximum number of cards in a player's hand
   static const int MAX_HAND_SIZE = 5;
};
Player* Player_factory(const std::string &name,
                       const std::string &strategy) {
 // We need to check the value of strategy and return
 // the corresponding player type.
 if (strategy == "Simple") {
   // The "new" keyword dynamically allocates an object.
   return new SimplePlayer(name);
 }
 else if (strategy == "Human") {
   return new HumanPlayer(name);
 }
 // Repeat for each other type of Player
 // Invalid strategy if we get here
 else{
 assert(false);
 }
 return nullptr;
}


std::ostream & operator<<(std::ostream &os, const Player &p) {
 os << p.get_name();
 return os;
}
