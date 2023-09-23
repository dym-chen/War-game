#include <iostream>
#include <string>
#include <ctime>
using namespace std;

//bolding statement
std::ostream &bold_on(std::ostream &os)
{
    return os << "\e[1m";
}
std::ostream &bold_off(std::ostream &os)
{
    return os << "\e[0m";
}

//initialize the game
void gamePlay(string deck[], string shuffle[], int len) //create the shuffled deck
{
    int count = 0; //counter variable
    while (count < len)
    {
        int odd = (rand() % len); //produce random number between 0-52
        string val = deck[odd];   //store the value of the array
        if (val == "0")
        {
        } //replaces with zero in order to prevent re-draw
        else
        {
            shuffle[count] = deck[odd]; //add card to shuffle deck and replaces the card with 0
            deck[odd] = "0";
            count++;
        }
    }
}
void createHand(string deck[], int start, string hand[]) // splits the deck in two for the two players
{
    int count = 0;
    for (int i = start; i < 26 + start; i++)
    {
        hand[count] = deck[i];
        count++;
    }
}

//game functions
void getHand(string hand[], string player, int pos, string play[], int turn) //get the play hand for each player
{
    cout << bold_on << "Player " << player << ", Turn " << turn << "\n"
         << bold_off;
    cout << "Your four cards are: \n";
    string cards[4];                    //array for the availble cards
    int start = 0;                      //counter variable
    for (int i = pos; i < pos + 4; i++) //display and store the 4 available cards for each player
    {
        cout << start + 1 << ". " << hand[i] << "\n";
        cards[start] = hand[i];
        start++;
    }
    cout << "Select your order ex.(4 3 1 2): \n";
    int temp = 0;     //input variable
    int numArr[4];    //stores their decided play
    int x = 0;        //counter variable
    int input[4];     //to prevent retypes
    bool out = false; //boolean to prevent same input
    for (int i = 0; i < 4; i++)
    {
        input[i] = 0; //fill the array with zeroes in order to place numbers, check for loop at 75
    }
    while (x < 4)
    {
        out = 0;
        cin >> temp; //take input
        if ((temp < 0) || (temp > 4))
        { //checking for valid inputs, if possible take the values
            cout << "Please insert a proper input \n";
            continue;
        }
        for (int i = 0; i < 4; i++)
        {
            if (input[i] == temp)
            {
                cout << "You have already selected that card \n";
                out = true;
                break;
            }
        }
        if (out == true)
        {
            continue;
        }
        for (int i = 0; i < 4; i++)
        {
            if (input[i] == 0)
            {
                input[i] = temp;
                break;
            }
        }
        numArr[x] = temp - 1;
        x++;
    }
    for (int z = 0; z < 4; z++) //stores card in the return array
    {
        play[z] = cards[numArr[z]];
    }
    cout << "\n";
}
int position(string order[], string *hand, int pos) //return the int position of the value inside of the order array (determining the bigger value)
{
    int i = 0;
    while (i < 52)
    {
        if (order[i] == hand[pos])
        {
            break;
        }
        i++;
    }
    return i;
}

void runGame(string hand1[], string hand2[], string order[], string winner, int turn, string user1, string user2) //to play the game
{
    int pos1 = 0; //starting position in the deck for players, used in the getHang function, adds 4 at the end of each round, line 157
    int pos2 = 0;
    string play1[4];
    getHand(hand1, user1, pos1, play1, turn); //get the hand for each player
    string play2[4];
    getHand(hand2, user2, pos2, play2, turn);

    //discard pile starter
    int index1 = 0;      //determines how long the discard pile is
    int size1 = 26;      //total amount of cards each player has
    string discard1[52]; //array to store discard pile
    int index2 = 0;
    int size2 = 26;
    string discard2[52];
    for (int i = 0; i < 52; i++) //fill up each array with zeroes in order to be able to shuffle them on like 181, 196
    {
        discard1[i] = "0";
        discard2[i] = "0";
    }
    while (true)
    {
        int p1 = 0; //used to determine the number of wins each player won out of the four, used on line 158
        int p2 = 0;
        cout << "-----------------------------------" << endl;
        for (int i = 0; i < 4; i++) //compare the four cards, place won cards into the discard pile (increase index to keep position), and output message
        {
            int comp1 = position(order, play1, i);
            int comp2 = position(order, play2, i);
            if (comp1 > comp2)
            {
                cout << "Battle " << i + 1 << ", " << play1[i] << " is higher ranked than " << play2[i] << ", " << bold_on << user1 << " won the battle \n"
                     << bold_off;
                discard1[index1] = play1[i];
                discard1[index1 + 1] = play2[i];
                index1 += 2;
                p1++;
            }
            if (comp2 > comp1)
            {
                cout << "Battle " << i + 1 << ", " << play2[i] << " is higher ranked than " << play1[i] << ", " << bold_on << user2 << " won the battle \n"
                     << bold_off;
                discard2[index2] = play1[i];
                discard2[index2 + 1] = play2[i];
                index2 += 2;
                p2++;
            }
            if (comp1 == comp2)
            {
                cout << "Battle " << i + 1 << ", " << play1[i] << " and " << play2[i] << "are equally ranked. The battle ended in a draw. \n";
                discard1[index1] = play1[i];
                discard2[index2] = play2[i];
            }
        }
        pos1 += 4;
        pos2 += 4;
        turn++; //add turn
        cout << bold_on << user1 << bold_off << " won " << p1 << " battles, " << bold_on << user2 << bold_off << " won " << p2 << " battles. \n \n";
        cout << bold_on << user1 << bold_off << " has " << bold_on << size1 - pos1 << bold_off << " cards left in play deck, " << bold_on << index1 << bold_off << " cards in discard deck, for a total of " << bold_on << size1 - pos1 + index1 << bold_off << " cards \n";
        cout << bold_on << user2 << bold_off << " has " << bold_on << size2 - pos2 << bold_off << " cards left in play deck, " << bold_on << index2 << bold_off << " cards in discard deck, for a total of " << bold_on << size2 - pos2 + index2 << bold_off << " cards \n";
        //check if the game is done, end statement
        if ((size1 - pos1) + index1 < 4)
        {
            winner = user2;
            return;
        }
        if ((size2 - pos2) + index2 < 4)
        {
            winner = user1;
            return;
        }
        //create new arrays to hold the "new deck", new deck is composed of shuffled discard deck under remaining play cards
        string newDeck1[(size1 - pos1) + index1]; //remaining cards + discard pile length (see line 115)
        string newDeck2[(size2 - pos2) + index2];
        int bol1 = 0; //boolean to check if we need to shuffle
        int bol2 = 0;
        int count1 = 0; //used for inside next for loop as increment of 1
        int count2 = 0;
        if (size1 - pos1 < 4)
        {
            string shuffle1[index1]; //shuffle discard deck
            gamePlay(discard1, shuffle1, index1);
            bol1++;                                //increment up because we need to shuffle
            for (int i = size1 - pos1; i > 0; i--) //getting the remaining play cards inside the new pile
            {
                newDeck1[count1] = hand1[size1 - i];
                count1++;
            }
            for (int i = 0; i < index1; i++) //inserting shuffled discard pile after the remaining play cards
            {
                newDeck1[i + size1 - pos1] = shuffle1[i];
            }
        }
        if (size2 - pos2 < 4) //same thing for the player 2
        {
            string shuffle2[index2];
            gamePlay(discard2, shuffle2, index2);
            bol2++;
            for (int i = size2 - pos2; i > 0; i--)
            {
                newDeck2[count2] = hand2[size2 - i];
                count2++;
            }
            for (int i = 0; i < index2; i++)
            {
                newDeck2[i + (size2 - pos2)] = shuffle2[i];
            }
        }
        if ((bol1 == 1) && (bol2 == 0)) //playing next round if player 1 has to reshuffle
        {
            size1 = (size1 - pos1) + index1; //new deck size
            pos1 = 0;                        //reset all of the variables, same for other parts
            index1 = 0;
            cout << "----------------------------------- \n"
                 << endl;
            getHand(newDeck1, user1, pos1, play1, turn);
            getHand(hand2, user2, pos2, play2, turn);
        }
        if ((bol1 == 0) && (bol2 == 1)) //playing next round if player 2 has to reshuffle
        {
            size2 = (size2 - pos2) + index2;
            pos2 = 0;
            index2 = 0;
            cout << "----------------------------------- \n"
                 << endl;
            getHand(hand1, user1, pos1, play1, turn);
            getHand(newDeck2, user2, pos2, play2, turn);
        }
        if ((bol1 == 1) && (bol2 == 1)) //playing next round if both players have to reshuffles
        {
            size1 = (size1 - pos1) + index1;
            pos1 = 0;
            size2 = (size2 - pos2) + index2;
            pos2 = 0;
            index1 = 0;
            index2 = 0;
            cout << "----------------------------------- \n"
                 << endl;
            getHand(newDeck1, user1, pos1, play1, turn);
            getHand(newDeck2, user2, pos2, play2, turn);
        }
        if ((bol1 == 0) && (bol2 == 0)) //next round is none have to reshuffle
        {
            cout << "----------------------------------- \n"
                 << endl;
            getHand(hand1, user1, pos1, play1, turn);
            getHand(hand2, user2, pos2, play2, turn);
        }
    }
}

int main()
{
    string faces[13] = {"Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
    string suits[4] = {"spades", "hearts", "diamonds", "clubs"};

    string deck[52];
    string deck1[52];
    int count = 0;
    for (int i = 0; i < 13; i++)
    {
        for (int x = 0; x < 4; x++)
        {
            deck[count] = faces[i] + " of " + suits[x];
            deck1[count] = faces[i] + " of " + suits[x];
            count++;
        }
    }
    cout << "Hey Users! It's time to play" << bold_on << " War!\n"
         << bold_off << "\nInstructions: \n 1. The deck will be shuffled and divided equally amongst the both of you \n 2. You will each draw four cards from the tops of your decks then decide the order in which to play them \n 3. Higher value cards beat lower value cards \n (Order lowest to highest: Deuce, 1 Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace)\n If your faces match, it will be decided by suits (Order strongest to weakest: Clubs, Diamonds, Hearts, Spades)\n 4. The winner of each battle takes their card back and takes the card of their opponent\n 5. The rounds continue until one of you has less than four cards to play total (disgard will be shuffled in).\n\n";
    cout << "Player 1 Name: \n";
    string user1;
    cin >> user1;
    cout << "Welcome to the game " << bold_on << user1 << bold_off << "!!!" << endl;
    cout << "\nPlayer 2 Name: \n";
    string user2;
    cin >> user2;
    cout << "Welcome to the game " << bold_on << user2 << bold_off << "!!!\n"
         << endl;

    string shuffle[52];

    while (true)
    {
        gamePlay(deck, shuffle, 52);
        string hand1[26];
        createHand(shuffle, 0, hand1);
        string hand2[26];
        createHand(shuffle, 26, hand2);
        string winner;
        string replay;
        runGame(hand1, hand2, deck1, winner, 1, user1, user2);
        cout << "Player " << winner << " won the game. \n";
        cout << "Would you like to play again? y/n : ";
        while (true)
        {
            cin >> replay;
            if ((replay == "y") || replay == "n")
            {
                break;
            }
            else
            {
                cout << "Invalid input, please try again. \n";
            }
        }
        if (replay == "y")
        {
            cout << bold_on << "HERE WE GO AGAIN!!!! \n"
                 << bold_off;
            continue;
        }
        else
        {
            cout << "Thanks for playing :D";
            break;
        }
    }
    return 0;
}
