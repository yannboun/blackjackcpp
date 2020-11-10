#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;


class Card{
    public:
        string kind;
        string face;
        Card(string kind, string face) : kind{kind}, face{face} {};
    };

class Deck{
    public:
        vector<Card> cards{};
        vector<Card>::iterator current_card{cards.begin()};
        Deck(){
            for(auto k: kinds){
                for(auto f:face){
                    cards.push_back(Card(k,f));
                }
            }
                shuffle();
            }
        void shuffle(){
            srand(unsigned(time(NULL)));
            std::random_shuffle(std::begin(cards), std::end(cards));
            current_card = cards.begin();
            }
        void get_next_card(){
            current_card++;
            if(current_card>=cards.end()){shuffle();};
        }
    private:
        string kinds[4]{"H", "S", "C", "D"};
        string face[13]{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    };

class BlackJack{
    public:
        Deck deck;
        BlackJack(Deck &deck) : deck(deck) {};
        BlackJack(){
            Deck deck{};
            deck=deck;
            };
        void play(){
            initialize();
            char player_action{};
            draw_dealer();
            cout << "\nDealer has : " << dealer_hand << " (" << dealer_score << ")\n";
            draw_dealer();  //silently draw dealer second card
            draw_player();
            while(true){
                draw_player();
                cout << "Player has : " << player_hand << " (" << player_score << ")\n";
                if(player_score==21){
                        cout << "BlackJack ! You Win";
                        return;
                        }
                if(player_score>21){
                        cout << "Busted you Lose !";
                        return;
                        }
                do
                {
                    cout << "Hit (h) or Stand (s) ?" << endl;
                    cin >> player_action;
                } while( !cin.fail() && player_action!='h' && player_action!='s');
                if(player_action == 's'){break;}
            }
            cout << "Dealer has : " << dealer_hand << " (" << dealer_score << ")\n";
            while(dealer_score < 17){
                    draw_dealer();
                    cout << "Dealer has : " << dealer_hand << " (" << dealer_score << ")\n";
            }
            if(dealer_score > 21){cout << "Dealer Busts, you win"; return;}
            else if(player_score>dealer_score){cout << "You Win !"; return;}
            else if(player_score==dealer_score){cout << "Draw"; return;}
            else{cout << "You lose"; return;}

        }
    private:
        int dealer_score_1{};
        int dealer_score_2{};
        int dealer_score{};
        string dealer_hand{};
        int player_score_1{};
        int player_score_2{};
        int player_score{};
        string player_hand{""};
        void initialize(){
            dealer_score_1 = 0;
            dealer_score_2 = 0;
            dealer_score = 0;
            dealer_hand = "";
            player_score_1 = 0;
            player_score_2 = 0;
            player_score = 0;
            player_hand = "";
            }
        void draw_player(){
            player_score_1 += value_map[deck.current_card->face][0];
            player_score_2 += value_map[deck.current_card->face][1];
            player_hand += deck.current_card->face + deck.current_card->kind + " ";
            player_score = get_best_score(player_score_1,player_score_2);
            deck.get_next_card();
        }
        void draw_dealer(){
            dealer_score_1 += value_map[deck.current_card->face][0];
            dealer_score_2 += value_map[deck.current_card->face][1];
            dealer_hand += deck.current_card->face + deck.current_card->kind + " ";
            dealer_score = get_best_score(dealer_score_1,dealer_score_2);
            deck.get_next_card();
        }
        int get_best_score(int score1, int score2){
            //This condition does not need to be reflective because score2 >= score1
            if(score2>21){
                return score1;
            }
            else{
                return max(score1,score2);
            }
        }
        map<string, vector<int> > value_map {
                                            {"2", {2,2}},
                                            {"3", {3,3}},
                                            {"4", {4,4}},
                                            {"5", {5,5}},
                                            {"6", {6,6}},
                                            {"7", {7,7}},
                                            {"8", {8,8}},
                                            {"9", {9,9}},
                                            {"10",{10,10}},
                                            {"J", {10,10}},
                                            {"Q", {10,10}},
                                            {"K", {10,10}},
                                            {"A", {1,11}},
                                            };
    };


int main(){
    BlackJack bj{};
    bj.play();
    return 0;
}
