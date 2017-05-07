#include <iostream>
#include <cstdlib>  
#include <ctime>
#include <cstring>

using namespace std;

/**
 * These are the variables that store the player's names.
 */
string playerNameA, playerNameB;

/**
 * This tracks the wins that will be showed at the end when the players are
 * done playing.
 */
int playerAWins = 0, playerBWins = 0;

/**
 * This sets up the baord. 
 */
char board[7][6];

/**
 * winner - this tracks if the game has been won or not so we can tell if we
 *          need to continue asking for moves.
 * 
 * playerATurn - this is a value that just switches to track who's turn it is
 * 
 * firstRunNames - since we don't need to ask for names every single time, once 
 *                  we ask for them the first time, we'll change this to false
 *                  so we don't keep resetting the names.
 * 
 * stopPlaying - this boolean will tell us if we need to stop playing the game
 *               all together and just go ahead and display the wins of each
 *               user.
 */
bool winner=false, playerAturn, firstRunNames = true, stopPlaying = false;

/**
 * This gives the appearance that there's only one thing on the screen at a 
 * time by printing 100 empty lines.
 */
void clearScreen() {
    for(int i = 0; i < 100; ++i) { 
        cout << endl;
    }
}

/**
 * A function to display the entire Connect 4 board in the console.
 */
void displayBoard (){
    clearScreen();
    cout << " 1 2 3 4 5 6 7" << endl;
    
    for (int row=0; row < 6; ++row) { //for loop for row of 1 to 6, provides divider "|"
      cout << "|";
      for (int col=0; col < 7; ++col) { //for loop for column 1 to 7
        cout << board[col][row] << "|"; // "x|"
      }
      
      cout << endl;
    }
}

/**
 * This sets up the game. It clears the board (empty spaces), get's player names
 * if needed, and decides who goes first.
 */
void setupGame() {
    srand(time(0));
    int randomStart;
    
    if(firstRunNames) {
        // get player a's name
        cout << "Enter your name player A"<< endl;
        cin >> playerNameA; 
        
        // get player b's name
        cout << "Enter your name player B" << endl;
        cin >> playerNameB;
        
        firstRunNames = false;
    }
    
    randomStart=(rand () % 101);
    
    //select what player goes first
    if (randomStart > 50) {
        playerAturn = false;
    }
    else {
        playerAturn = true;
    }
    
    // set all the board to spaces
    for(int col = 0; col < 7; col++) {
        for(int row = 0; row < 6; row++) {
            board[col][row] = ' ';
        }
    }
}

/**
 * Based on the mark (X or O) passed in, we'll add a win to that user.
 */
void addWin(char mark) {
    if(mark == 'X') {
        playerAWins++;
    } else {
        playerBWins++;
    }
}

/**
 * Check to see if a user has won the game based on the colum they chose.
 */
void check(int column, int row, char mark) {
    int count=0;
    
    //horizontal check
    for(int col=0; col < 7; ++col) {
        if(board[col][row] != ' '){
            if(board[col][row] == mark) {
                ++count;
            }
            else {
                count=0;
            }
        }
        else {
            count=0;
        }
        
        if(count >= 4){
            winner=true;
            displayBoard();
            cout << ((mark == 'X') ? playerNameA : playerNameB) << " is the winner." << endl;
            addWin(mark);
            break;
        }
    }
    
    count = 0;
    
    //vertical check
    for(int row1=0; row1 < 6; ++row1) {
        if(board[column][row1] != ' '){
            if(board[column][row1] == mark) {
                ++count;
            }
            else {
                count=0;
            }
        }
        else {
            count=0;
        }
        
        if(count >= 4){
            winner=true;
            displayBoard();
            cout << ((mark == 'X') ? playerNameA : playerNameB) << " is the winner." << endl;
            addWin(mark);
            break;
        }
    }
    
    /**
     * This is the funciton for the Diagonal check.
     * Uses for loop to check in a stair-case like fashion. Up one, over one,etc. 
     * and vice versa. 
     */
    
    int v = 0, h = 0;
    
    count = 1;
    for(v = column - 1, h = row - 1; (board[v][h] == mark) && v > -1 && h > -1; count++, h--, v--); // up and left
    for(v = column + 1, h = row + 1; (board[v][h] == mark) && v < 7 && h < 6; count++, h++, v++); // down and right
    
    if(count >= 4) {
        winner=true;
        displayBoard();
        cout << ((mark == 'X') ? playerNameA : playerNameB) << " is the winner." << endl;
        addWin(mark);
        return;
    }
    
    
    count = 1;
    for(v = column - 1, h = row + 1; (board[v][h] == mark) && v > -1 && h < 6; count++, v--, h++); // up and right
    for(v = column + 1, h = row - 1; (board[v][h] == mark) && v < 7 && h > -1; count++, v++, h--); // down and left
    
    if(count >= 4) {
        winner=true;
        displayBoard();
        cout << ((mark == 'X') ? playerNameA : playerNameB) << " is the winner." << endl;
        addWin(mark);
        return;
    }
}

/**
 * The main function.
 */
int main() {
    while(!stopPlaying) {
        setupGame();
        
        //Checks the players turn and places the simple X or O in the chosen location
        while(!winner) {
            displayBoard();
            cout << (playerAturn ? playerNameA : playerNameB) << ", it's your turn." << endl;
            cout << "Please input a column number (1-7)" << endl;
            int column;
            cin >> column;
            
            for(int row=5; row >= 0; --row) {
                if(board[column - 1][row] ==' ') {
                    board[column -1][row] = (playerAturn ? 'X' : 'O');
                    check(column - 1, row, (playerAturn ? 'X' : 'O'));
                    break;
                }
            }
            
            playerAturn = !playerAturn;
        }
        
        //Asks the user if they would like to pay again
        cout << "Do you want to play again?" << endl;
        string answer;
        
        cin >> answer;
        
        if(answer == "no" || answer == "n" || answer == "N" || answer == "No") {
            stopPlaying = true;
            
            clearScreen();
            //unique feature, highscore board, keep track of wins. 
            cout << " Total Wins" << endl;
            cout << "-------------" << endl;
            cout << playerNameA << ": " << playerAWins << " Wins" << endl;
            cout << playerNameB << ": " << playerBWins << " Wins" << endl;
        } else {
            winner = false;
        }
    }
    
    return 0;
}