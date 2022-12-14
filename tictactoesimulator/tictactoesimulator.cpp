// This is the code for a tictactoes simulator in c++ (Sound files may be needed) 

// tictactoe c++ edition.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


// C++ tictactoe game 

/*
Programmer: Nevin Ndonwi
Date completed: 6/6/2021
Duration of project: about a week (5 days)



a 2d array is unable to be passed between functions in c++, as a result vectors were used instead

*/
#include<iostream>

//the ability to use vectors, they can be sent and returned from functions, arrays can't do that in C++
#include<vector> 

//string
#include<string> 

// ability to file files 
#include <fstream>




//plays sounds
#include <Windows.h>
#include <mmsystem.h>;



using namespace std;



//psuedodeclared function that prints tictactoe board
//void playtheme();

//void endtheme();


void printboard(vector<string> row1, vector<string> row2, vector<string> row3);

//gets the name of player1
string player1name();

// gets the name of player2
string player2name();

//player 1's turn
string player1turn(vector<string> row1, vector<string> row2, vector<string> row3);


//player 2's turn
string player2turn(vector<string> row1, vector<string> row2, vector<string> row3, string turn1);


//checks the board for possible inputs so that the players know what they can do 
string checkboard(vector<string> row1, vector<string> row2, vector<string> row3);

//checks if player1 wins
bool win1(vector<string> row1, vector<string> row2, vector<string> row3);

//checks if player2 wins
bool win2(vector<string> row1, vector<string> row2, vector<string> row3);

// checks if a tie has occured 
bool checkTie(vector<string> row1, vector<string> row2, vector<string> row3);






int main()

//plays general music theme (heartgold game corner theme)
{
    PlaySound(TEXT("playthemee.wav"), NULL, SND_FILENAME | SND_ASYNC);




    string name1 = player1name();
    string name2 = player2name();


    cout << "\n" << name1 + "(Player 1)  will input a number and 'X' (without quotes) will be displayed at that spot\n";

    cout << "\n" << name2 + "(Player 2) will input  will input a number and 'O' (without quotes) will be displayed at that spot\n";

    // a tictactoe board with 3 rows and 3 columns.
    vector<string> row1 = { "0", "1", "2" };
    vector<string> row2 = { "3", "4" , "5" };
    vector<string> row3 = { "6", "7", "8" };

    printboard(row1, row2, row3);



    //checks if a tie has occured
    bool tie = false;


    bool oof = false;
    bool winn1 = false;
    bool winn2 = false;
    string turn1;
    string turn2;


    string winner = "";
    string loser = "";

    //the while loop where the tictactoe showdown takes place
    while (oof == false) {


        //obtains the space number player 1 wants to put their 'X' on
        turn1 = player1turn(row1, row2, row3);

        // puts X on the space number
        if (turn1 == "0") {
            row1[0] = "X";
        }
        else if (turn1 == "1") {
            row1[1] = "X";
        }
        else if (turn1 == "2") {
            row1[2] = "X";
        }
        else if (turn1 == "3") {
            row2[0] = "X";
        }
        else if (turn1 == "4") {
            row2[1] = "X";
        }
        else if (turn1 == "5") {
            row2[2] = "X";
        }
        else if (turn1 == "6") {
            row3[0] = "X";
        }
        else if (turn1 == "7") {
            row3[1] = "X";
        }
        else if (turn1 == "8") {
            row3[2] = "X";
        }


        //prints the new updated board
        cout << "\n \n Here is what the board looks like now \n \n";
        printboard(row1, row2, row3);

        //checks if player 1 wins
        winn1 = win1(row1, row2, row3);

        if (winn1 == true) {

            winner = name1;
            loser = name2;
            break;
        }


        //checks if there are spaces left incase a tie occurs 

        tie = checkTie(row1, row2, row3); //(true if there are no spaces left, false if spaces are still present)

        if (tie == true) {

            break;
        }





        // player 2's turn
        //obtains the space number player 2 wants to put their 'O' on
        turn2 = player2turn(row1, row2, row3, turn1);



        //Puts player 2's 'O' on the space they input
        if (turn2 == "0") {
            row1[0] = "O";
        }
        else if (turn2 == "1") {
            row1[1] = "O";
        }
        else if (turn2 == "2") {
            row1[2] = "O";
        }
        else if (turn2 == "3") {
            row2[0] = "O";
        }
        else if (turn2 == "4") {
            row2[1] = "O";
        }
        else if (turn2 == "5") {
            row2[2] = "O";
        }
        else if (turn2 == "6") {
            row3[0] = "O";
        }
        else if (turn2 == "7") {
            row3[1] = "O";
        }
        else if (turn2 == "8") {
            row3[2] = "O";
        }



        //Prints what the board looks like now
        cout << "\n \n Here is what the board looks like now \n \n";
        printboard(row1, row2, row3);


        //checks if player 2 wins
        winn2 = win2(row1, row2, row3);

        if (winn2 == true) {
            winner = name2;
            loser = name1;
            break;
        }
    }


    // stops song 
    PlaySound(NULL, 0, 0);




    //end of while loop

    //creates files of winners and losers
    ofstream filecreator;

    filecreator.open("winners.txt", ios::app); // ios::app makes it so that your name is added and not erasing prior file contents

    filecreator << "\n" + winner + "  defeated " + loser + "\n";

    filecreator.close();



    //if someone wins 
    cout << "\n CONGRADULATIONS, \n" + winner + " has been filed as a victor over " + loser + "\n";

    //plays other theme
       // plays end theme (heartgold reture theme) 
    PlaySound(TEXT("endthemee.wav"), NULL, SND_FILENAME | SND_SYNC); // plays sound synchrounously (pauses program to do so)



    printboard(row1, row2, row3);


    return 0;
}








// prints tictactoe board
void printboard(vector<string> row1, vector<string> row2, vector<string> row3) {



    // output the board 
    //row 1
    for (int i = 0; i < 3; i++)
    {
        cout << "[ " << row1[i] << " ]";

    }
    cout << "\n";
    //row 2
    for (int i = 0; i < 3; i++)
    {
        cout << "[ " << row2[i] << " ]";

    }
    cout << "\n";
    //row 3
    for (int i = 0; i < 3; i++)
    {
        cout << "[ " << row3[i] << " ]";

    }

    cout << "\n";
    cout << "\n";

    return;
}







//gets player1turn
string player1turn(vector<string> row1, vector<string> row2, vector<string> row3) {

    string output = "";


    //checks the board for possible moves
    string possible = checkboard(row1, row2, row3);

    //only outputs numbers and not Xs or Os
    for (int y = 0; y < possible.length(); y++) {

        if (possible[y] != 'X' && possible[y] != 'O') {
            output += possible[y];

        }



    }

    // what the player can input
    cout << "These are inputs player 1 can input: " + output;

    //initializing the variable that will hold player 1's turn input
    char player1move = 'n';



    //checks if player 1's input is legitimate and if the space on the board is available
    bool legit = false;

    while (legit == false) {

        cout << "\nInput a number player1: ";

        cin >> player1move;

        for (int x = 0; x < output.length(); x++) {

            if (output[x] == player1move) {
                legit = true;



            }



        }

        if (legit == false) {

            cout << "\nYour previous input was not within the ones provided, please try again player 1\n";

        }


    }
    cout << "\nA legitimate input has been registered by player 1\n";





    //converts player1move from character to string so the function returns a value 
    string x(1, player1move);

    return x;
}









//gets player2turn
string player2turn(vector<string> row1, vector<string> row2, vector<string> row3, string turn1) {



    // displays player 2's potential inputs
    string possible = checkboard(row1, row2, row3);



    string output = "";


    //only outputs numbers and not Xs or Os
    for (int y = 0; y < possible.length(); y++) {

        if (possible[y] != 'X' && possible[y] != 'O') {
            output += possible[y];

        }



    }



    cout << "These are inputs player 2 can input: " + output;













    //variable that will hold player 2's turn input
    char player2move = 'h';

    cout << "\nInput a number player2: ";
    cin >> player2move;

    //converts player2move from character to string so that it can be compared to string value
    string x(1, player2move);


    // while loop that checks if player 2's input is the same as player 1's input
    while (x == turn1) {

        cout << "\nYour previous input was the same as player 1, please modify it \n";
        cout << output;
        cout << "\nInput a number player2: ";
        cin >> x;

    }

    //character variable holding player 2's turn input 
    char player2 = x[0];



    //checks if player 2's turn is able to be placed on the tictactoe board
    bool legit = false;

    while (legit == false) {

        for (int x = 0; x < output.length(); x++) {

            if (output[x] == player2) {
                legit = true;



            }



        }

        //if the input doesn't work
        if (legit == false) {

            cout << "\nYour previous input was not within the ones provided, please try again player 2\n";

            cout << output;
            cout << "\nInput a number player2: ";
            cin >> player2;

        }


    }
    cout << "\nA legitimate input has been registered by player 2\n";


    //returns player 2's input as a string variable
    return x;



}






//checks what the player is allowed to input
string checkboard(vector<string> row1, vector<string> row2, vector<string> row3) {
    // string where legitimate inputs is stored
    string legitinputs;


    //checks row 1 for any available spaces
    for (int i = 0; i < 3; i++)
    {
        if ((row1[i] != "x") && (row1[i] != "o")) {

            // the numbers aere added to the legitinputs string variable 
            legitinputs = legitinputs + " " + row1[i];
        }


    }

    //checks row 2 for any available spaces
     //row 2
    for (int i = 0; i < 3; i++)
    {
        if ((row2[i] != "x") && (row2[i] != "o")) {

            //spaces added to legitinputs variable
            legitinputs = legitinputs + " " + row2[i];
        }
    }

    //checks row 3 for any available spaces
    for (int i = 0; i < 3; i++)
    {
        if ((row3[i] != "x") && (row3[i] != "o")) {

            //spaces added to legitinputs variable
            legitinputs = legitinputs + " " + row3[i];
        }

    }


    return legitinputs;
}






// gets player 1 name 
string player1name() {

    string player1;

    cout << "Player 1, Please input your name!!\n";
    cin >> player1;

    cout << "Player 1's name " + player1 + " has been registered \n";
    return player1;
}




// gets player 2 name  
string player2name() {

    string player2;

    cout << "Player 2, Please input your name!!\n";
    cin >> player2;
    cout << "Player 2's name " + player2 + " has been registered \n";
    return player2;
}




//check if player 1 is the winner
bool win1(vector<string> row1, vector<string> row2, vector<string> row3) {


    bool h = false; // false if player 1 is not the winner 
     //checks the board horizontally (row 1)

    if (row1[0] == "X") {

        if (row1[0] == row1[1]) {

            if (row1[1] == row1[2]) {

                cout << "Player 1 has won!!!";
                return true;
            }

        }

    }
    //checks the board horizontally (row 2)

    if (row2[0] == "X") {

        if (row2[0] == row2[1]) {

            if (row2[1] == row2[2]) {

                cout << "Player 1 has won!!!";
                return true;
            }

        }

    }

    //checks the board horizontally (row 3)

    if (row3[0] == "X") {

        if (row3[0] == row3[1]) {

            if (row3[1] == row3[2]) {

                cout << "Player 1 has won!!!";
                return true;
            }

        }

    }

    //checks the board vertically (column 1)

    if (row1[0] == "X") {

        if (row1[0] == row2[0]) {

            if (row2[0] == row3[0]) {

                cout << "Player 1 has won!!!";
                return true;
            }

        }

    }

    //checks the board vertically (column 2)

    if (row1[1] == "X") {

        if (row1[1] == row2[1]) {

            if (row2[1] == row3[1]) {

                cout << "Player 1 has won!!!";
                return true;
            }

        }

    }


    //checks the board vertically (column 3)

    if (row1[2] == "X") {

        if (row1[2] == row2[2]) {

            if (row2[2] == row3[2]) {

                cout << "Player 1 has won!!!";
                return true;
            }

        }

    }

    // checks the board diagonally (left to right)

    if (row1[0] == "X") {

        if (row1[0] == row2[1]) {

            if (row2[1] == row3[2]) {

                cout << "Player 1 has won!!!";
                return true;
            }

        }

    }




    // checks the board diagonally (right to left)
    if (row1[2] == "X") {

        if (row1[2] == row2[1]) {

            if (row2[1] == row3[0]) {

                cout << "Player 1 has won!!!";
                return true;
            }

        }

    }



    //true if player 1 is the winner, false if otherwise
    return h;


}



//check if player 2 is the winner
bool win2(vector<string> row1, vector<string> row2, vector<string> row3) {

    bool h = false; // false if player 2 is not the winner 

     //checks the board horizontally (row 1)

    if (row1[0] == "O") {

        if (row1[0] == row1[1]) {

            if (row1[1] == row1[2]) {

                cout << "Player 2 has won!!!";
                return true;
            }

        }

    }
    //checks the board horizontally (row 2)

    if (row2[0] == "O") {

        if (row2[0] == row2[1]) {

            if (row2[1] == row2[2]) {

                cout << "Player 2 has won!!!";
                return true;
            }

        }

    }

    //checks the board horizontally (row 3)

    if (row3[0] == "O") {

        if (row3[0] == row3[1]) {

            if (row3[1] == row3[2]) {

                cout << "Player 2 has won!!!";
                return true;
            }

        }

    }

    //checks the board vertically (column 1)

    if (row1[0] == "O") {

        if (row1[0] == row2[0]) {

            if (row2[0] == row3[0]) {

                cout << "Player 2 has won!!!";
                return true;
            }

        }

    }

    //checks the board vertically (column 2)

    if (row1[1] == "O") {

        if (row1[1] == row2[1]) {

            if (row2[1] == row3[1]) {

                cout << "Player 2 has won!!!";
                return true;
            }

        }

    }


    //checks the board vertically (column 3)

    if (row1[2] == "O") {

        if (row1[2] == row2[2]) {

            if (row2[2] == row3[2]) {

                cout << "Player 2 has won!!!";
                return true;
            }

        }

    }

    // checks the board diagonally (left to right)

    if (row1[0] == "O") {

        if (row1[0] == row2[1]) {

            if (row2[1] == row3[2]) {

                cout << "Player 2 has won!!!";
                return true;
            }

        }

    }




    // checks the board diagonally (right to left)
    if (row1[2] == "O") {

        if (row1[2] == row2[1]) {

            if (row2[1] == row3[0]) {

                cout << "Player 2 has won!!!";
                return true;
            }

        }

    }



    //true if player 2 is the winner, false if otherwise
    return h;


}

// checks if a tie has occured 
bool checkTie(vector<string> row1, vector<string> row2, vector<string> row3) {

    //if there are spaces left this variable is false. 
    bool spaces = true;


    // search row 1
    for (int i = 0; i < 3; i++)
    {

        //checks if a space is not an X or an O
        if ((row1[i] != "X") && (row1[i] != "O")) {
            spaces = false;
            break;
        }

    }

    // search row 2
    for (int i = 0; i < 3; i++)
    {

        //checks if a space is not an X or an O
        if ((row2[i] != "X") && (row2[i] != "O")) {
            spaces = false;
            break;
        }

    }

    //search row 3
    for (int i = 0; i < 3; i++)
    {

        //checks if a space is not an X or an O
        if ((row3[i] != "X") && (row3[i] != "O")) {
            spaces = false;
            break;
        }

    }

    if (spaces == true) {

        cout << "\n\n A TIE HAS OCCURED, THIS GAME IS COMPLETE \n\n";
    }
    return spaces; //true if there are zero spaces left, false if there are still spaces left
}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file