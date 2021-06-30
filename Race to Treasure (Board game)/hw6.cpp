/*
This program simulate the board game "Race To The Treasure"

Important note:
1. No 3 ways road cards in this program. Only straight forward cards and turn cards.
2. Increase the number of road cards to 30, straight forward cards 15 and turn cards 15.
3. If players have drew all the road cards and still not reach the end point, the game will end.
4. O<- represent a empty board position 
5. P<- represent the road have built
6. N<- represent the next road position
7. K<- represent keys
8. S<- represent snacks
9. The direction that the player is turning is base on the relative position of the previous road, NOT TRUE NORTH!!
example1: if the road is pointing "down" and player enter "1" for "turning right", the next road will be going "left" in the aspect of true north!!
example2: if the road is pointing "right" and player enter "2" for "turning left", the next road will be goint "up" in the aspect of true north!!

Known Bugs:
1. Players can overwrite the path thats already there.
2. If players purposely turn into a wall, the system will return error message but the direction system will mess up for the next input.
*/

#include <iostream>
#include <string>
#include <time.h>
#include "Header.h"

using namespace std;

//return card name function
string cardname(string card) {
    if (card == "I") {
        return "straight forward";
    }
    else if (card == "L") {
        return "turn";
    }
    else {
        return "ogre";
    }
}

//check whether the direction input is correct or not
bool directioncheck(int direction, int row, int column) {
    //win case
    if (row == 7 && column == 5 && direction == 1) return true;
    
    if (direction == 1) {
        column++;
        if (column > 5) {
            cout << "error input, try again";
            return false;
        }
    }
    else if (direction == 2) {
        row++;
        if (row > 7) {
            cout << "error input, try again";
            return false;
        }
    }
    else if (direction == 3) {
        column--;
        if (column < 0) {
            cout << "error input, try again";
            return false;
        }
    }
    else if (direction == 4) {
        row--;
        if (row < 0) {
            cout << "error input, try again";
            return false;
        }
    }

    return true;

}

int main()
{
    srand(time(NULL));
    Die keypos;
    bool end = false, checker = false,snackused=false;
    int org = 0, row = 0, column = 0, keynum = 0, snacknum = 0,direction=1;

    //initialize table
    Table table;
    //place keys and snack
    table.placekeys(keypos.getkey());
    //initialize the card deck
    Cards deck;

    cout << "Welcome to Race to the Treasure Game simulator! Please follow the instructions below" << endl;

    do {
        //drawcard function call
        string card = deck.drawcard();
        //get the string of the card
        string cardstr = cardname(card);
        cout << "You draw a " << cardstr << " card"<<endl;
        //find the next position
        int ro = table.rownum("N");
        int co = table.colnum("N");
        if (table.gettable(0,0) == "N") { //first road card
            if (card == "L" || card == "I") {
                cout << "This is your first road card, what direction do you want place next?(right or down)" << endl;
                cout << "1. right. 2. down" << endl;
                do {
                    cin >> direction;
                    if (direction == 1) {
                        column++;
                        checker = true;
                    }
                    else if (direction == 2) {
                        row++;
                        checker = true;
                    }
                    else {
                        cout << "error input, try again" << endl;
                        checker = false;
                    }
                } while (checker != true);
                table.tableadjust(row, column,"N");
                table.tableadjust(0, 0, "P");
                table.displayboard();
                continue;
            }
        }

        if (card == "I") {
            bool check = directioncheck(direction, ro, co); //check if the direction is valid
            if (check == true) {
                table.tableupdate(direction, ro, co); //update table
            }
            else {
                continue; //skip if direction is not valid
            }
        }
        else if (card == "L") {
            int predirection = direction;
            cout << "Which way do you want to turn? 1. right 2. left: "<<endl;
            cin >> direction;
            //direction rotate with the respect of the previous road card   
            if (predirection == 1) {
                if (direction == 1) {
                    direction=2;
                }
                else {
                    direction=4;
                }
            }
            else if (predirection == 2) {
                if (direction == 1) {
                    direction=3;
                }
                else {
                    direction=1;
                }
            }
            else if (predirection == 3) {
                if (direction == 1) {
                    direction=4;
                }
                else {
                    direction=2;
                }
            }
            else if (direction == 4) {
                if (direction == 1) {
                    direction=1;
                }
                else {
                    direction=3;
                }
            }
            else {
                cout << "error direction"<<endl;
                continue;
            }


            bool check = directioncheck(direction, ro, co); //direction check
            if (check == true) {
                table.tableupdate(direction, ro, co); //update
            }
            else {
                continue;
            }
        }
        else {
            if (org == 7) end = true;
            table.tableadjust(org,6, "G"); //ogre card placement 
            org++;
        }
        keynum = table.keyscheck();
        snacknum = table.snackcheck();
        //for getting snacks, need to use immediately 
        if (snackused == false && snacknum == 1 && org > 0) {
            table.tableadjust(org,6,"O");
            org--;
            snackused = true;
        }
        cout << "You have collected " << keynum << " keys now!" << endl;
        table.displayboard();
        if (table.gettable(7,6) != "O"|| deck.roadcard()==0) end = true; //end game condition
    } while (end != true);

    cout << endl << "Game Over!" << endl;
    table.displayboard();
    if (table.gettable(7, 6) == "G") cout << "Ogre win!";
    else if (deck.roadcard() == 0) cout << "You have no road card left";
    else if (keynum < 3) cout << "Even though you reached the end... but you do not have enough keys!";
    else cout << "You win!!";

}
