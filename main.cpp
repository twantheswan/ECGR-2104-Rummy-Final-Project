// Antoine Sieredzki
// 5/3/16


#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <chrono>
#include <unistd.h>

using namespace std;
class Card
{
private:
    string suit;
    int cards;
    int cardVal;
    int deletecard;
public:
    Card();
    void getSuit();
    void getCardVal();
    void setCard( int in_suit, int in_val);
    void showhand(vector<Card> player);
    friend ostream& operator <<( ostream& os,  Card& obj);
    //Card& operator =(Card otherin);
    Card(const Card &otherin);
    void meld(Card& playercard,Card& playercard1, Card& playercard2);
    void run(Card& playercard,Card& playercard1, Card& playercard2);
    void pass(Card& playercard);
    void deletethecard(Card& card, char& yn);
    
};
void cpucpu(vector<Card> deck);
void drawCardp1(vector<Card>& deck, vector<Card>& player1);
void showhand(vector<Card> player);
void gamestart(vector<Card> deck);
void pickcards(vector<Card>& deck, vector<Card>& player1);
void checkdelete(vector<Card>& player);





int main()
{
    srand(unsigned(time(NULL))); //begins the random timer to shuffle the cards
    
    vector<Card> deck;
    for(int i=0; i < 4 ; ++i) {
        for(int j=1; j< 14; ++j) {
            Card obj;
            obj.setCard( i, j);
            deck.push_back(obj);
        }
    }
    std::random_shuffle(deck.begin(), deck.end() );
    gamestart(deck);
    //cout << deck[1]; //output value check
    
    
    return 0;
}


////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
Card::Card(){
    suit="";
    cards=0;
    cardVal=0;
    deletecard=0;
}
Card::Card(const Card &otherin){
    this->suit=otherin.suit;
    this->cardVal=otherin.cardVal;
    this->cards=0;
}


ostream& operator <<(ostream& os,  Card& obj){
    os << obj.cardVal << " of " << obj.suit << endl;
    return os;
}





////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////




void cpucpu(vector<Card> deck){
    cout << "Drawing Cards..." << endl << endl;
    vector<Card> player1, player2;
    player1=deck;
    deck.erase(deck.begin(), deck.begin()+9);
    player2=deck;
    player1.erase(player1.begin()+10,player1.end());
    player2.erase(player2.begin()+10,player2.end());
    deck.erase(deck.begin(), deck.begin()+9);
    cout << "Player 1 cards:" << endl;
    for(int i = 0; i < 10; i++){
        usleep(500000);
        cout << player1[i];
    }
    usleep(1000000);
    cout<< endl << "Player 2 cards:\n";
    usleep(500000);
    for(int i = 0; i < 10; i++){
        usleep(500000);
        cout<< player2[i];
    }
    
    cout << endl << "10 cards have been drawn to each player. \nThere are now " << deck.size() << " cards remaining" << endl;
    
    
    
    for(int i = 0; i < 1; i++){
    usleep(1000000);
        cout << "Player 1 turn..." << endl;
        drawCardp1(deck, player1);
        showhand(player1);
        pickcards(deck, player1);
        checkdelete(player1);
        cout << "There are now " << deck.size() << " cards remaining" << endl;
        usleep(1000000);
        cout << "Player 2 turn..." << endl;
        usleep(500000);
        drawCardp1(deck, player2);
        showhand(player2);
        pickcards(deck, player2);
        checkdelete(player2);
        if(deck.size()==0){
            cout << "Game over. No winner" << endl;
        }
        if(player1.size()==0){
            cout << "Player 1 wins!!" << endl;
        }
        if(player2.size()==0){
            cout << "Player 2 wins!!" << endl;
        }
        int input12=1;
        cout << "Next turn? (1=yes, 2=quit game)." << endl;
        cin >> input12;
        if(input12 == 2){
            i=1;
            cout << "Quitting game..." << endl;
        }
        else{
            i=i-1;
            cout << "There are now " << deck.size() << " cards remaining" << endl;
        }
        
    
    }
    usleep(500000);
}





////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


//This does not need to be written, void cpucpu is the only gamemode we need.


void cpuplayer(vector<Card> deck){
    cout << "Game mode not complete yet." << endl;
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////








void gamestart(vector<Card> deck){
    
    
    int input;
    
    cout << "Welcome to Rummy!\n" << "Do you want player v.s. player or computer v.s. player? (type 1 or 2)" << endl;
    cin >> input;
    
    if(input==1){
        cout << "player v.s. player selected" << endl;
        cpucpu(deck);
    }
    
    if(input==2){
        cout << "computer v.s. player selected" << endl;
        cpuplayer(deck);
    }
    if(input != 1 && input != 2){
        cout << "Incorrect input. Please try again" << endl;
        
    }
    
}

////////////////////////////////////////////////////////////////////////////////////
void checkdelete(vector<Card>& player){
    for(int i = 0; i <player.size(); i++){
        Card check;
        char yn = 'n';
        check = player[i];
        check.deletethecard(check, yn);
        if(yn == 'y'){
            usleep(500000);
            cout << player[i] << " discarded" << endl;
            player.erase(player.begin()+i);
            i=i-1;
        }
    }
    
}

void Card::deletethecard(Card& card, char& yn){
    if(card.deletecard == 1){
        yn = 'y';
    }
    else{
        yn='n';
    }
}

void Card::pass(Card &playercard){
    playercard.deletecard = 0;
}

void Card::meld(Card &playercard, Card &playercard1, Card &playercard2){
    if(playercard.cardVal == playercard1.cardVal && playercard1.cardVal == playercard2.cardVal){
        cout << "Meld possible" << endl;
        playercard.deletecard = 1;
        playercard1.deletecard = 1;
        playercard2.deletecard =1;
    }
    else{
        cout << "Numbers do not match. Turn skipped" << endl;
    }
}

void Card::run(Card& playercard,Card& playercard1, Card& playercard2){
    if(playercard.suit == playercard1.suit && playercard1.suit == playercard2.suit){
        cout << "Run possible" << endl;
        playercard.deletecard = 1;
        playercard1.deletecard = 1;
        playercard2.deletecard =1;
    }
    else{
        cout << "Suits do not match. Turn skipped" << endl;
    }
    
}

void  drawCardp1(vector<Card>& deck, vector<Card>& player1){
    cout << "Drawing Card..." << endl << endl;
    
        player1.push_back(deck[0]);
        
    
    deck.erase(deck.begin(), deck.begin()+1);
    usleep(1000000);
    
    
}


void showhand(vector<Card> player){
    cout << "Here are the cards in your hand: " << endl;
    for(int i = 0; i <player.size(); i++){
        cout << i << ": " ;
        usleep(250000);
        cout << player[i];
        usleep(250000);
    }
    cout << endl;
    usleep(1000000);
}

void pickcards(vector<Card>& deck, vector<Card>& player1){
    int input;
    cout << "Pick the cards that you wish to run or meld." << endl;
    usleep(500000);
    cout << "A run is when three cards are of the same suit" << endl;
    usleep(500000);
    cout << "A meld is a set of three of the same numbers" << endl;
    cout << "What do you wish to do? (1=run, 2=meld, 3=pass)" << endl;
    cin >> input;
    if(input == 1){
        int cardselect =14,cardselect1 =14,cardselect2 =14;
        cout << "Run selected. Which 3 cards do you pick?" << endl;
        cin >> cardselect;
        cin >> cardselect1;
        cin >> cardselect2;
        if(cardselect ==14 || cardselect1==14||cardselect2==14){
            cout << "Incorrect amount of cards inputted" << endl;
            exit(0);
        }
        else{
            Card run;
            run.run(player1[cardselect], player1[cardselect1], player1[cardselect2]);
        }
    }
    if(input == 2){
        int cardselect =14,cardselect1 =14,cardselect2 =14;
        cout << "Meld selected. Which 3 cards do you pick?" << endl;
        cin >> cardselect;
        cin >> cardselect1;
        cin >> cardselect2;
        if(cardselect ==14 || cardselect1==14||cardselect2==14){
            cout << "Incorrect amount of cards inputted" << endl;
            exit(0);
        }
        else{
            Card meld;
            meld.meld(player1[cardselect], player1[cardselect1], player1[cardselect2]);
        }
    }
    if(input==3){
        cout << "Pass selected... Next player turn." << endl;
        usleep(500000);
        Card pass;
        pass.pass(player1[player1.size()-1]);
    }
}

////////////////////////////////////////////////////////////////////////////////////


void Card::setCard(int in_suit, int in_val){
    if(in_suit==0){
        suit = "Hearts";
    }
    if(in_suit==1){
        suit ="Spades";
    }
    if(in_suit==2){
        suit ="Clubs";
    }
    if(in_suit==3){
        suit ="Diamonds";
    }
    
    cardVal=in_val;
    deletecard = 0;
    
}





