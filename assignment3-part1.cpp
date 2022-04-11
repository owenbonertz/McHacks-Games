#include <exception>
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <algorithm> 

using namespace std;

enum rank{ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
enum type{Clubs, Diamonds, Hearts, Spades};

class Card{

    public:
    
    //enums used for card attributes
    enum rank{ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
    enum type{Clubs, Diamonds, Hearts, Spades};
    
    rank r;
    type t;

    //basic constructor
    Card(Card::rank ranky, Card::type suit){
        
        this->r = ranky;
        this->t = suit;
    }
    
    //constructor used by deck.populate()
    Card(int x, int y){
        
        // we must cast the arguments (ints) into enums
        rank val = static_cast<rank>(x);
        type uhHuh = static_cast<type>(y);
        this->r = val;
        this->t = uhHuh;
    }

    int getvalue(){
        //if we have a face card, it's always value of 10
        if(this->r >= 11){
            return 10;
        }
        else{
            return this->r;
        }
    }

    void displayCard(){
        char symbol;
        char royalty;

        // this switch statement reads the suit of the card and assigns a char accordingly
        switch(this->t){
            case 0:
                symbol = 'C';
                break;
            case 1:
                symbol = 'D';
                break;
            case 2:
                symbol = 'H';
                break;
            case 3:
                symbol = 'S';
                break;
        }

        //if we have a face card, then we must assign a char to match the type of royalty
        if(this->r >= 11){
            //char royalty [2];
            switch(this->r){
                case 11:
                    royalty = 'J';
                    break;
                case 12:
                    royalty = 'Q';
                    break;
                case 13:
                    royalty = 'K';
                    break;
            }
            // this is only triggered if it's a face card
            cout<<royalty<<symbol<<" ";
        }
        else{
            // this is triggered in all other instances
            // if the rank is not a face card, we can just print the value straight up
            cout<<this->r<<symbol<<" ";
        }

    }

};

class Hand{

    public:
    // i chose to use a vector because it can be easily manipulated in size
    // and it has many built in methods
    vector<Card> currentHand;

    void add(Card nextCard){
        //.push_back puts the card at the end of the vector, which is ultimately what I wante
        // so that the hand gets printed/ counted sequentially 
        this->currentHand.push_back(nextCard);
    }

    void clear(){
        // pretty self-explanatory
        this->currentHand.clear();
    }

    int getTotal(){
        int total = 0;
        // iterate through the vector card by card
        for(int i = 0; i < this->currentHand.size(); i++){
            Card yup = this->currentHand[i];
            // this logic accounts for the ace 1vs11 decision

            //first if statement checks if it's an ace 
            if(yup.r == 1){
                //if the running count is 10 or less, and the card being checked is the last in the hand, then we want it to be an 11
                if(total <= 10 && (i == (this->currentHand.size() -1))) {
                    total += 11;
                }
                // otherwise (middle of the hand, or total is already so high we would bust)
                // we count ace as 1
                else{
                    total += 1;
                }
            }
            // if it's not an ace, this part is pretty simple
            else{
                int currentValue = yup.getvalue();
                total += currentValue;
            }
        }
        return total;
    }
};

class Deck: public Hand{

    public:


    void Populate(){
        // nested for loop creates 4 of each number IE: one Club, Diamond, Spade, Heart
        // then we append the card to the back of the deck
        for(int i= 0; i< 4; i++){
            for(int j=1; j<14; j++){
                Card newCard = Card(j,i);
                this->add(newCard);
            }
        }
    }

    void shuffle(){
        // random_shuffle is included with <algorithms>
        // requires start and end point as arguments
        random_shuffle(this->currentHand.begin(), this->currentHand.end());
    }

    Hand deal(Hand gimme){
        //this first shuffle changes the deck with every deal, when I added it
        // it kept my programming from giving me the same sequence of hands everytime I ran it
        this->shuffle();
        // we need a int variable for the size of the deck because it changes with each (-1)
        int sizo = this->currentHand.size();
        //rand is is in <cstlib>
        int random = rand() % sizo;
        Card rando = this->currentHand[random];
        gimme.add(rando);
        // the arguments for this function delete a specific card at random indices past the beginning
        this->currentHand.erase(this->currentHand.begin() + random);
        return gimme;
    }
};

class AbstractPlayer{

    public:
    
    // decided to not inherit hand but make it a class attribute
    // as it made my deal function more straight forward
    Hand holdEm;
    
    // declare this as a pure virtual method
    virtual bool isDrawing() = 0;

    bool isBusted(){
        // pretty straightforward
        Hand mine = this->holdEm;
        //calls Hand.getTotal();
        int total = mine.getTotal();
        if (total > 21){
            return true;
        }
        else{
            return false;
        }
    }
};

class HumanPlayer: public AbstractPlayer{

    public:
    
    bool isDrawing(){
        // print the current state of the hand
        Hand mio = this->holdEm;
        cout<<"Player: ";
        for(int i = 0; i < mio.currentHand.size(); i++){
            Card printMe = mio.currentHand[i];
            printMe.displayCard();
            cout<<" ";
        }
        cout<<"["<<mio.getTotal()<<"]"<<"\n";
        
        //crucially, this prevents the player from being prompted again if they have busted
        // this was an essential addition for the logic of my BlackjackGame.play() method
        if(mio.getTotal() > 21){
            return false;
        }
       
       // take input on if we want another card
        char yOrN;
        cout<<"Do you want to draw? (y/n): ";
        cin>> yOrN;
        

        //sanity check
        while(yOrN != 'y' && yOrN != 'n'){
            cout<<"Invalid Input, try again\n";
            cout<<"Do you want to draw? (y/n): ";
            cin>> yOrN;
            
        }
        
        if(yOrN == 'y'){
            return true;
        }
        else if (yOrN == 'n'){
            return false;
        }
        // this is here mainly because the compiler complained that you could reach
        // the end of the function wihtout a return, I'm not sure how you would actually get
        // to this chunk of code though
        else{
            return false;
        }
    }

    void announce(int x){
    
        int state = x;
        // this switch statement takes one of 5 int arguments and spits out one of the 5 
        // possible victory strings
        switch (state)
        {
        case 1:
            cout<<"Player wins\n";
            break;
        
        case 2:
            cout<<"Player busts\n";
            cout<<"Casino Wins\n";
            break;

        case 3:
            cout<<"Push: No one wins.\n";
            break;
            
        case 4:
            cout<<"Casino wins\n";
            break;
            
        case 5:
            cout<<"Casino Busts\n";
            cout<<"Player Wins\n";
        
        default:
            break;
        }
    }
};

class ComputerPlayer: public AbstractPlayer{
    
    public:
    
    //int winPercentage;

    bool isDrawing(){
    
        // beginning for-loop is the same as HumanPlayer
        cout<<"Casino: ";
        Hand moi = this->holdEm;
        for(int i = 0; i < moi.currentHand.size(); i++){
            Card printMe = moi.currentHand[i];
            printMe.displayCard();
            cout<<" ";
        }
        cout<<"["<<moi.getTotal()<<"]"<<"\n";

        int total = moi.getTotal();

        // this is how the computer is instructed to stop drawing if it's total is greater than 16
        if(total <= 16){
            return true;
        }
        else{
            return false;
        }
    }
};

class BlackJackGame{

    public:
    Deck m_deck;
    ComputerPlayer m_casino;

    BlackJackGame(){

        //we create a new deck at the beginning of each game, rather than using the same one
        Deck decky = Deck();
        decky.Populate();
        decky.shuffle();
        this->m_deck = decky;
        this->m_casino = ComputerPlayer();
    }

    void play(){

        
        Deck decked = this->m_deck;
        ComputerPlayer bellagio = this->m_casino;
        HumanPlayer playa = HumanPlayer();
        
        //opening shuffle and distribution of two cards to player and one to dealer
        bellagio.holdEm = decked.deal(bellagio.holdEm);
        bool houseDraw = bellagio.isDrawing();
        
        decked.shuffle();
        
        playa.holdEm = decked.deal(playa.holdEm);
        decked.shuffle();
        playa.holdEm = decked.deal(playa.holdEm);
        bool doubleDown = playa.isDrawing();
        
        // this while loop represents the player drawing their hand
        while(doubleDown == true && playa.isBusted() == false){
            decked.shuffle();
            playa.holdEm = decked.deal(playa.holdEm);
            doubleDown = playa.isDrawing();
        }
        
        // this runs if the player busts while drawing
        if(playa.isBusted() == true){
            // this gives a slight edge to the casino because if the player busts,
            // then the casino does not have to risk playing their hand, this is how 
            // real casinos give an edge to the dealer. I ran the program 100 times
            // and got 60 wins for the casino and 40 wins for the player. I imagine if I expanded
            // the sample size it would sit around 55%, as it was in a real casino
            playa.announce(2);
            return;
        }
        
        
        // this runs if the player stops drawing before getting to 21
        else if(doubleDown == false && playa.isBusted() == false){
            // this represents the house drawing cards
            while(houseDraw == true && bellagio.isBusted() == false){
                decked.shuffle();               
                bellagio.holdEm = decked.deal(bellagio.holdEm);
                houseDraw = bellagio.isDrawing();
            }
            
            //this represents if the computer busts
            if(bellagio.isBusted() == true){
                playa.announce(5);
                
            }
            // this represents if the computer stops drawing and we must compare
            else if(houseDraw == false && bellagio.isBusted() == false){
                
                int playaCount = playa.holdEm.getTotal();
                int houseTotal = bellagio.holdEm.getTotal();
                
                // if the player wins after both have stopped drawing
                if(playaCount > houseTotal){
                    playa.announce(1);
                    return;
                }
                
                // if the house wins after both have stopped drawing
                else if(houseTotal > playaCount){
                    playa.announce(4);
                    return;
                }
                
                //push
                else if(playaCount == houseTotal){
                    playa.announce(3);
                    return;
                }
            }
        }
    }
};
int main()
{
    cout << "\tWelcome to the Comp322 Blackjack game!" << endl << endl;
     BlackJackGame game;
     // The main loop of the game
     bool playAgain = true;
     char answer = 'y';
     while (playAgain)
     {
         game.play();
         // Check whether the player would like to play another round
         cout << "Would you like another round? (y/n): ";
         cin >> answer;
         cout << endl << endl;
         playAgain = (answer == 'y' ? true : false);
}
     cout <<"Gave over!";
return 0;
    
}   