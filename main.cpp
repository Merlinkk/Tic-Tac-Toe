#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// layout example
string stage[3][3] = {{"11","12","13"},{"21","22","23"},{"31","32","33"}};

// Output that is going to be displayed to the players
char output[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};

// using boolean true and false to switch player turns between 'X' and 'O'
bool turn = true;

// player input of the cell they wish to mark 
string choice;

bool gameWon = false;

// render example layout for directions
void display_stage(){
    // render example layout for directions
    cout<<endl;
    cout<<"\t\t\tPLAYER - 1 [X]\t PLAYER - 2 [O]\n\n";
    cout<<"\t\t\t\t     |     |     \n";
    cout<<"\t\t\t\t "<<stage[0][0]<<"  | "<<stage[0][1]<<"  |  "<<stage[0][2]<<" \n";
    cout<<"\t\t\t\t_____|_____|_____\n";
    cout<<"\t\t\t\t     |     |     \n";
    cout<<"\t\t\t\t "<<stage[1][0]<<"  | "<<stage[1][1]<<"  |  "<<stage[1][2]<<" \n";
    cout<<"\t\t\t\t_____|_____|_____\n";
    cout<<"\t\t\t\t     |     |     \n";
    cout<<"\t\t\t\t "<<stage[2][0]<<"  | "<<stage[2][1]<<"  |  "<<stage[2][2]<<" \n";
    cout<<"\t\t\t\t     |     |     \n";
}

// render output layout with real-time-changes
void display_output(){
    // render output layout with real-time-changes
    cout<<endl;
    cout<<"\t\t\tPLAYER - 1 [X]\t PLAYER - 2 [O]\n\n";
    cout<<"\t\t\t\t     |     |     \n";
    cout<<"\t\t\t\t  "<<output[0][0]<<"  | "<<output[0][1]<<"   |  "<<output[0][2]<<" \n";
    cout<<"\t\t\t\t_____|_____|_____\n";
    cout<<"\t\t\t\t     |     |     \n";
    cout<<"\t\t\t\t  "<<output[1][0]<<"  | "<<output[1][1]<<"   |  "<<output[1][2]<<" \n";
    cout<<"\t\t\t\t_____|_____|_____\n";
    cout<<"\t\t\t\t     |     |     \n";
    cout<<"\t\t\t\t  "<<output[2][0]<<"  | "<<output[2][1]<<"   |  "<<output[2][2]<<" \n";
    cout<<"\t\t\t\t     |     |     \n";
}

// render rules
void display_rules(){
    cout<<endl;
    cout<<"\t\t\t-The game operates in a 3x3 matrix / 2d array. Players enter the number associated with the cell when their turn comes. eg: '12' \n";
    cout<<"\t\t\t-Players take turn and mark the cell of their choice with their respective designated character be it 'X' or 'O' \n";
    cout<<"\t\t\t-The game starts with 'X' being first followed by 'O'\n";
    cout<<"\t\t\t-The game ends when any one player be it 'X' or 'O' makes a pattern vertically, horizontally or diagonally.\n";
    cout<<"\t\t\t-The first one to do so will trigger the gameover and win\n";
}

// render intro- introducing the player to the game
void display_intro(){
    cout<<endl;
    cout<<"\t\t\tWelcome to TIC TAC TOE game.\n";
    cout<<"\t\t\tThis is a tic tac toe game written in C++\n";
    cout<<"\t\t\tLet us go over some rules first, but first lets us look \n\t\t\tat the layout of the game\n";
    display_stage();
    display_rules();
    // cout<<"\t\t\t--If you want to display the rules again then enter (99) or if you want to display the layout again enter (98)";
    cout<<endl<<"\n";
}

// checks if there are any matching patterns and declares winner 
bool checkWinner(char player) {
    for (int i = 0; i < 3; ++i) {
        // check vertiical and horizontal
        if ((output[i][0] == player && output[i][1] == player && output[i][2] == player) || // Check rows
            (output[0][i] == player && output[1][i] == player && output[2][i] == player)) { // Check columns
            gameWon = true;
            return true;
        }
    }

    // Check diagonals
    if ((output[0][0] == player && output[1][1] == player && output[2][2] == player) ||
        (output[0][2] == player && output[1][1] == player && output[2][0] == player)) {
        gameWon = true;
        return true;
    }

    return false;
}

// check if position is available or occupied
bool ifOccupied(int row,int column){
    if (output[row][column] != ' '){
        return true;
    }else{
        return false;
    }
}

// string display asking player for their choice
void askChoice(){
    if(!turn){
        cout<<endl;
        cout<<"\t\tPLAYER - 1 [X]:";
        }
        else{
        cout<<"\t\tPLAYER - 2 [O]:";
    }
}

// choice / input validation
void checkChoice(string choice, int& row, int& column) {
    if ((choice != "11") && (choice != "12") && (choice != "13") &&
        (choice != "21") && (choice != "22") && (choice != "23") &&
        (choice != "31") && (choice != "32") && (choice != "33")) {
        cout << "\n\n\t\t\t\tInvalid Input\n\n";
        askChoice();
        cin >> choice;
        row = choice[0] - '1';
        column = choice[1] - '1';
        checkChoice(choice, row, column); // Recheck the new choice 
    } else if (ifOccupied(row, column)) {
        cout << "\n\n\t\t\t\tPosition Already Taken\n\n";
        askChoice();
        cin >> choice;
        row = choice[0] - '1'; // converts it into int equivalent along with -1
        column = choice[1] - '1';
        checkChoice(choice, row, column); // Recheck the new choice
    }
}

// to reset the 2d array for new game
void reset(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            output[i][j] = ' ';
        }
    }
}


// main game code
void game(){
    // reset for new game
    turn = true;
    gameWon = false;
    choice = "";
    reset();
    // game will run for nine iterations and if there is no winner until the end it will declare a draw
    for(int i=0;i<9;i++){
        int row,column;
        if(turn){
            cout<<endl;
            cout<<"\t\tPLAYER - 1 [X]:";
            turn = false;
        }else{
            cout<<"\t\tPLAYER - 2 [O]:";
            turn=true;
        }
        cin>>choice;
        row = choice[0] - '1';
        column = choice[1] -'1';
        
        checkChoice(choice,row,column);
        
        if(!turn){
            if(ifOccupied(row,column)){
            askChoice();
            cin>>choice;
            row = choice[0] - '1';
            column = choice[1] -'1';
            }else{
                output[row][column] = 'X';
            }
            display_output();
            if(checkWinner('X')){
                cout<<"\n\n\t\t\t\t'X' Wins";
                break;
            }
        }else{
            if(ifOccupied(row,column)){
            askChoice();
            cin>>choice;
            row = choice[0] - '1';
            column = choice[1] -'1';
            }else{
                output[row][column] = 'O';
            }
            display_output();
            if(checkWinner('O')){
                cout<<"\n\n\t\t\t\t'O' Wins";
                break;
            }
        }        
    }
    if(!gameWon){
        cout<<"\n\n\t\t\t\tDRAW";
        cout<<"\n\n\t\t\t\ttry again?(type anything eg: 'yes' then press enter {no to exit})";
        cin>>choice;
        if(choice == "no"){
            return;
        }
        game();
    }else{
        cout<<"\n\n\t\t\t\ttry again?(type anything eg: 'yes' then press enter{no to exit})";
        cin>>choice;
        if(choice == "no"){
            return;
        }
        game();
    }

    
    
}



int main(){
    // display introduction for the player
    display_intro();

    // run game
    game();

    return 0;
}
