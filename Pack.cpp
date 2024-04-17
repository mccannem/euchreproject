#include "Pack.hpp"
#include <cassert>


 // EFFECTS: Initializes the Pack to be in the following standard order:
 //          the cards of the lowest suit arranged from lowest rank to
 //          highest rank, followed by the cards of the next lowest suit
 //          in order from lowest to highest rank, and so on.
 // NOTE: The standard order is the same as that in pack.in.
 // NOTE: Do NOT use pack.in in your implementation of this function
 // NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(){
   int index = 0;
   for (int dealSuit = SPADES; dealSuit <= DIAMONDS; ++dealSuit){
       for(int dealRank = NINE; dealRank <= ACE; ++dealRank){
           cards[index++] = Card(static_cast<Rank>(dealRank), static_cast<Suit>(dealSuit));
       }
   }
   next = 0;
   //causing segmentation error
}


 // REQUIRES: pack_input contains a representation of a Pack in the
 //           format required by the project specification
 // MODIFIES: pack_input
 // EFFECTS: Initializes Pack by reading from pack_input.
 // NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(std::istream& pack_input){
   for (int i = 0; i < PACK_SIZE; ++i){
       pack_input >> cards[i];
   }
   next = 0;
}


 // REQUIRES: cards remain in the Pack
 // EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one(){
 return cards[next++];
}


 // EFFECTS: Resets next index to first card in the Pack
void Pack::reset(){
   next = 0;
}


 // EFFECTS: Shuffles the Pack and resets the next index. This
 //          performs an in shuffle seven times. See
 //          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle(){
   //make a copy of card array
   Card copy[PACK_SIZE];
   for (int i = 0; i < 7; ++i){
     for (int i = 0; i < PACK_SIZE; ++i){
       copy[i] = cards[i];
     }
     for (int i = 0; i < PACK_SIZE / 2; ++i){
         cards[2 * i] = copy[(PACK_SIZE/2) + i];
         cards[2 * i + 1] = copy[i];
     }
   }
   reset();
}


 // EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const{
   return next >= PACK_SIZE;
}


/*private:
 static const int PACK_SIZE = 24;
 std::array<Card, PACK_SIZE> cards;
 int next; //index of next card to be dealt
};


#endif // PACK_HPP */
