#include <iostream>
#include <fstream>
#include <string>
#include "Pack.hpp"
#include "Player.hpp"
using namespace std;


class Game {
 public:
   // Game();
   void play(vector<Player*> players, int pointstoWin, string shuffleType) {
     int hand = 0;
     while (t1GamePoints < pointstoWin && t2GamePoints < pointstoWin){
       cout << "Hand " << hand << endl;
       cout << players[dealerIndex]->get_name() << " deals" << endl;
       shuffle(shuffleType, pack);
       deal(upcard, players, dealerIndex);
       make_trump(orderUpTeam, players, dealerIndex, upcard);
       tricks(orderedupSuit, players, leader, dealerIndex, t1trickPoints, t2trickPoints);
       scoring(players, t1trickPoints, t2trickPoints, t1GamePoints, t2GamePoints, pointstoWin);
       hand++;
       dealerIndex = (dealerIndex + 1) % 4;
       leader = (leader + 1) % 4;
       t1trickPoints = 0;
       t2trickPoints = 0;
     }
     if (t1GamePoints > t2GamePoints){
       cout << *players[0] << " and " << *players[2] << " win!" << endl;
     }
     else {
       cout << *players[1] << " and " << *players[3] << " win!" << endl;
     }
     endgame(players);
   }


 private:
   vector<Player*> players;
   int orderUpTeam;
   Suit orderedupSuit;
   Card upcard;
   int t1trickPoints;
   int t2trickPoints;
   int t1GamePoints;
   int t2GamePoints;
   int dealerIndex = 0;
   int leader = (dealerIndex + 1) % 4; //left to dealer leads
   Pack pack;
   void shuffle(string shuffleType, Pack& pack) {
     if (shuffleType == "shuffle"){
       pack.shuffle();
     }
     else {
       pack.reset();
     }
     return;
   }


   void deal(Card& upcard, vector<Player*> players, int dealerIndex) {
     for (int i = 0; i < 4; i = i + 2){
       for (int j = 0; j < 3; ++j){
         Card dealt = pack.deal_one();
         players[(dealerIndex + 1 + i) % 4]->add_card(dealt);
       }
       for (int k = 0; k < 2; ++k){
         Card dealt = pack.deal_one();
         players[(dealerIndex + 2 + i) % 4]->add_card(dealt);
       }
     }
     for (int i = 0; i < 4; i = i + 2){
       for (int j = 0; j < 2; ++j){
         Card dealt = pack.deal_one();
         players[(dealerIndex + 1 + i) % 4]->add_card(dealt);
       }
       for (int k = 0; k < 3; ++k){
         Card dealt = pack.deal_one();
         players[(dealerIndex + 2 + i) % 4]->add_card(dealt);
       }
     }
     upcard = pack.deal_one();
     cout << upcard.get_rank() << " of " << upcard.get_suit() << " turned up" << endl;
   }


   void make_trump(int& orderupTeam, vector<Player*> players, int dealerIndex, Card& upcard){
     int round = 1;
     bool orderedUp = false;
     bool dealer = false;
     for (int i = 0; i < 4; ++i) {
       if (i == dealerIndex){
         dealer = true;
       }
       orderedUp = players[(dealerIndex + i + 1) % 4]->make_trump(upcard, dealer, round, orderedupSuit);
       if (orderedUp == true){
         cout << players[(dealerIndex + i + 1) % 4]->get_name() << " orders up " << orderedupSuit << endl;
         orderupTeam = (dealerIndex + i + 1) % 2;
         cout << endl;
         players[dealerIndex]->add_and_discard(upcard);
         return;
       }
       else {
         cout << players[(dealerIndex + i + 1) % 4]->get_name() << " passes" << endl;
       }
     }
     round++;
     dealer = false;
     for (int i = 0; i < 4; ++i) {
       if (i == dealerIndex){
         dealer = true;
       }
       orderedUp = players[(dealerIndex + i + 1) % 4]->make_trump(upcard, dealer, round, orderedupSuit);
       if (orderedUp == true){
         cout << players[(dealerIndex + i + 1) % 4]->get_name() << " orders up " << orderedupSuit << endl;
         orderUpTeam = (dealerIndex + i + 1) % 2;
         cout << endl;
         return;
       }
       else {
         cout << players[(dealerIndex + i + 1) % 4]->get_name() << " passes" << endl;
       }
     }
   }
   void tricks(Suit& orderedUpSuit, vector<Player*> players, int leader, int dealerIndex, int& t1trickPoints, int& t2trickPoints) {
     Card max;
     Card played;
     Card lead;
     int leaderIndex;
     for (int i = 0; i < 5; ++i){ //5 tricks
       for (int j = 0; j < 4; ++j){ //every player
         if (j == 0) { //leader
           max = players[(leader + j) % 4]->lead_card(orderedUpSuit);
           lead = max;
           cout << lead.get_rank() << " of " << lead.get_suit() << " led by " << players[(leader + j) % 4]->get_name() << endl;
           leaderIndex = (leader + j) % 4;
         }
         else { //players
           played = players[(leader + j) % 4]->play_card(lead, orderedUpSuit);
           cout << played.get_rank() << " of " << played.get_suit() << " played by " << players[(leader + j) % 4]->get_name() << endl;
           if (Card_less(max, played, lead, orderedUpSuit)) {
             max = played;
             leaderIndex = (leader + j) % 4;
           }
         }
       }
       leader = leaderIndex;
       cout << players[leader]->get_name() << " takes the trick" << endl << endl;
       if (leader % 2 == 0){
         t1trickPoints++;
       }
       else {
         t2trickPoints++;
       }
     }
   }
    
  
   void scoring(vector<Player*> players, int& t1trickPoints, int& t2trickPoints, int& t1GamePoints, int& t2GamePoints, int pointstoWin){
     int winner = 0;
     int winningteam = 0; //team 1 = 1, team 2 = 2
     if (t1trickPoints > t2trickPoints){
       winner = t1trickPoints;
       winningteam = 1;
       cout << players[0]->get_name() << " and " << players[2]->get_name() << " win the hand" << endl;
     }
     else {
       winner = t2trickPoints;
       winningteam = 2;
       cout << players[1]->get_name() << " and " << players[3]->get_name() << " win the hand" << endl;
     }
     if (winningteam == orderUpTeam + 1){ //did orderup
       if (winner < 5){
         if (winningteam == 1){
           t1GamePoints++;
         }
         else {
           t2GamePoints++;
         }
       }
       else {
         if (winningteam == 1){
           t1GamePoints = t1GamePoints + 2;
         }
         else {
           t2GamePoints = t2GamePoints + 2;
         }
         cout << "march!" << endl;
       }
     }
   else { //team did not orderup
     if (winningteam == 1){
       t1GamePoints = t1GamePoints + 2;
     }
     else {
       t2GamePoints = t2GamePoints + 2;
     }
     cout << "euchred!" << endl;
   }
  
   cout << players[0]->get_name() << " and " << players[2]->get_name() << " have " << t1GamePoints << " points" << endl;
   cout << players[1]->get_name() << " and " << players[3]->get_name() << " have " << t2GamePoints << " points" << endl;
   cout << endl;
 }


 void endgame(vector<Player*> players) {
   for (size_t i = 0; i < players.size(); ++i){
     delete players[i];
   }
 }
};




int main(int argc, char *argv[]) {
 int points = atoi(argv[3]);
 string input = argv[1];
 ifstream fin(input);


 string typeP1 = argv[5];
 string typeP2 = argv[7];
 string typeP3 = argv[9];
 string typeP4 = argv[11];
 vector <Player*> players;


 for (int i = 4; i < 12; i += 2) {
   string name = argv[i];
   string type = argv[i + 1];
   players.push_back(Player_factory(name, type));
 }
  string shuffleType = argv[2];
  if (!(argc == 12 && (points >= 1 && points <= 100) && (shuffleType == "shuffle" || shuffleType == "noshuffle") &&
 (typeP1 == "Simple" || typeP1 == "Human") && (typeP2 == "Simple" || typeP2 == "Human") &&
 (typeP3 == "Simple" || typeP3 == "Human") && (typeP4 == "Simple" || typeP4 == "Human"))){
   cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
    << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
    << "NAME4 TYPE4" << endl;
    return 1;
 }
 if (!fin.is_open()) {
   cout << "Error opening " << input << endl;
   return 1;
 }


 Game game;
 // print executable
 for (int i = 0; i < 12; ++i) {
   cout << argv[i] << " ";
 }
 cout << endl;
 game.play(players, points, shuffleType);
}
