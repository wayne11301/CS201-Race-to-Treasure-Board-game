/*
This is the header file goes alone with hw6.cpp. The purpose of this program is to practice multiple file programming and object oriented programming.
*/

#pragma once
#include <iostream>
#include <string>
using namespace std;

//table class is the board of the game
class Table {
public:
    string table[8][7] = { {"O","O","O","O","O","O","O"},{"O","O","O","O","O","O","O"},{"O","O","O","O","O","O","O"},
{"O","O","O","O","O","O","O"},{"O","O","O","O","O","O","O"},{"O","O","O","O","O","O","O"},
{"O","O","O","O","O","O","O"},{"O","O","O","O","O","O","O"} };

    //constructor
    Table() {
        table[0][0] = "N";
    }

    //getter
    string gettable(int i, int j) {
        return table[i][j];
    }
    
    //board display function
    void displayboard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 7; j++) {
                cout << table[i][j];
            }
            cout << endl;
        }
    }
    //placing keys and snacks
    void placekeys(int* keypos) {
        
        for (int i = 0; i < 5; i++) {
            int row = *(keypos + i) / 6;
            int column = *(keypos + i) % 6;
            table[row + 1][column] = "K";
            if (i == 4) table[row + 1][column] = "S";
        }
    }

    //generally used for finding the next position
    int rownum(string str) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 7; j++) {
                if (table[i][j] == str) return i;
            }
        }
    }

    //generally used for finding the next position
    int colnum(string str) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 7; j++) {
                if (table[i][j] == str) return j;
            }
        }
    }

    //table update function
    void tableupdate(int direction, int row, int column) {
        table[row][column] = "P";
        if (direction == 1) {
            column++;
        }
        else if (direction == 2) {
            row++;
        }
        else if (direction == 3) {
            column--;
        }
        else if (direction == 4) {
            row--;
        }
        table[row][column] = "N";
        return;
    }

    //a quick way to do changes to table
    void tableadjust(int i, int j, string letter) {
        table[i][j] = letter;
    }

    //check the number of keys player have gathered
    int keyscheck() {
        int count = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 7; j++) {
                if (table[i][j] == "K") count++;
            }
        }
        return 4 - count;
    }
    //check the number of snack player have gathered
    int snackcheck() {
        int count = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 7; j++) {
                if (table[i][j] == "S") count++;
            }
        }
        return 1 - count;
    }
};

class Cards {
public:
    //Icards is straight forward card, Lcard is turn card, Ogcard is ogre card, roadcardsum is all the road cards that have drawn
    int Icard, Lcard, Ogcard, roadcardsum;
    //constructor
    Cards() {
        Icard = 15, Lcard = 15, Ogcard = 10, roadcardsum = Icard+Lcard;
    }
    //draw card function
    string drawcard() {
        int cardnumber = rand() % (Icard + Lcard + Ogcard);
        string cardtype;
        if (cardnumber < Icard) {
            cardtype = "I";
            Icard--;
        }
        else if (cardnumber < (Icard + Lcard)) {
            cardtype = "L";
            Lcard--;
        }
        else {
            cardtype = "G";
            Ogcard--;
        }

        return cardtype;
    }
    //card number getter
    int getcardnumber(string cardtype) {
        if (cardtype == "I") {
            return Icard;
        }else if (cardtype == "L") {
            return Lcard;
        }
        else if(cardtype == "G"){

        }
        else {
            return Icard + Lcard + Ogcard;
        }
    }
    int roadcard() {
        return roadcardsum;
    }

};

class Die {
public:
    int* key = new int[5];
    //generate positions for keys and snack 
    Die() {
        bool overlapcheck;
        do {
            overlapcheck = true; //if there are overlaping position, redraw
            for (int i = 0; i < 5; i++) {
                *(key + i) = rand() % 36;  //total of 36 possible positions for keys and snack
            }
            for (int i = 0; i < 5; i++) { //overlap checker
                for (int j = i + 1; j < 5; j++) {
                    if (*(key + i) == *(key + j)) overlapcheck = false;
                }
            }
        } while (overlapcheck == false);
    }
    //getter
    int* getkey() {
        return key;
    }

};