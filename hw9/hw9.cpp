//
//  main.cpp
//  hw9
//
//  Created by Patricia Antlitz on 4/20/23.
//
/***********************************************
Author: <Patricia Antlitz>
Date: <04/20/2023>
Purpose: <Create a guess a number game using OOP>
Sources of Help: <>
Time Spent: <4hrs>
***********************************************/
/*
Computing III -- COMP.2010 Honor Statement
The practice of good ethical behavior is essential for maintaining
good order in the classroom, providing an enriching learning
experience for students, and as training as a practicing computing
professional upon graduation. This practice is manifested in the
University’s Academic Integrity policy. Students are expected to
strictly avoid academic dishonesty and adhere to the Academic
Integrity policy as outlined in the course catalog. Violations will
be dealt with as outlined therein.
All programming assignments in this class are to be done by the
student alone. No outside help is permitted except the instructor and
approved tutors.
I certify that the work submitted with this assignment is mine and was
generated in a manner consistent with this document, the course
academic policy on the course website on Blackboard, and the UMass
Lowell academic code.
Date: 04/20/2023
Name: Patricia Antlitz
*/

#include <iostream>         //  I/O
#include <cstdlib>          //  for the random number
#include <ctime>            //  random number seed
using namespace std;

bool checkForWin(int guess, int answer)
{
    if (answer == guess)
    {
        cout << "      You're right! You win!" << endl;
        return true;
    }
    else if (answer < guess)
        cout << "      Your guess is too high." << endl;
    else
        cout << "      Your guess is too low." << endl;
    return false;
}

class Player {
public:
    virtual int getGuess() = 0;
    virtual void setGuess(int aGuess) = 0;
};

class HumanPlayer : public Player {
public:
    void setGuess(int aGuess){}
    //numbers guessed cannot be larger than 30 or zero or less
    int getGuess()
    {
        cin >> guess;
        while(cin)
        {
            if(guess > 30)
            {
                cout << "The number cannot be greater than 30. Please enter again: " << endl;
                cin >> guess;
    
            }
            else if(guess <= 0)
            {
                cout << "The number cannot be 0 or less. Please enter again: " << endl;
                cin >> guess;

            }
            else {
                break;
            }
        }
        return guess;
    }
    
private:
    int guess;
};

class ComputerPlayer : public Player {
public:
    //number is set by what is passed either by the user or by the random number
    void setGuess(int aGuess){ guess = aGuess; }
    
    int getGuess(){
        cout << guess << " ---> Computer Guess" << endl;
        return guess;
    }
    
private:
    int guess;
};

void play(Player& player1, Player& player2);

//I prefer to keep the main function as small as I can, only with the extremely necessary calls
int main(int argc, const char * argv[])
{
    srand(static_cast<unsigned>(time(NULL)));
    // human versus human
    HumanPlayer playerOne;
    HumanPlayer playerTwo;
    ComputerPlayer computerOne;
    ComputerPlayer computerTwo;
    
    cout << "Human vs. Human" << endl;
    play(playerOne, playerTwo);
    cout << " ----------------------------------------------------------------------------------------- " << endl;
    // human versus computer
    cout << endl << "Human vs. Computer" << endl;
    //if()
    play(playerOne, computerOne);
    cout << " ----------------------------------------------------------------------------------------- " << endl;
    // computer versus computer
    cout << endl << "Computer vs. Computer" << endl;
    play(computerOne, computerTwo);
    
    return 0;
}

void play(Player& player1, Player& player2)
{
    //first number to be used by the computer
    int guess = (rand() % 30) + 1;
    //number picked to be guessed
    int answer = (rand() % 30) + 1;
    int guessNum = 0;
    bool win = false;
    
    //this will be the very first round between two humans
    cout << "Player 1's turn to guess: ";
    //setting the guess using the random number
    player1.setGuess(guess);
    //guessNum is used as a value
    guessNum = player1.getGuess();
    //check if winner
    win = checkForWin(guessNum, answer);

    //player 2
    cout << endl << "Player 2's turn to guess: ";
    player2.setGuess(guess);
    guessNum = player2.getGuess();
    win = checkForWin(guessNum, answer);
    //if the game is not won in the first round, enter loop
    while (!win)
    {
//        cout << " this is the answer: " << answer << endl;
        //if the number to be guessed is greater than the guessed number
        if(answer > guessNum)
        {
            //we want to lower the range, so it will go from the guessed number to 30 as the max
            //if the number picked by the system is 25, and the guessed number is 30, this should limit the random number range to a number from
            int set = answer + rand() % (30-answer);
            int set2 = answer + rand() % (30-answer);

            //sets the new numbers for player 1
            cout << "Player 1's turn to guess: ";
            player1.setGuess(set);
            guessNum = player1.getGuess();
            win = checkForWin(guessNum, answer);
            
            if (win) {
                return;
            }
            //for player 2
            cout << endl << "Player 2's turn to guess: ";
            player2.setGuess(set2);
            guessNum = player2.getGuess();
            win = checkForWin(guessNum, answer);
        }
        else if(answer < guessNum)
        {
            //range from 1 to whatever the number is
            int set = 1 + (rand() % answer);
            int set2 = 1 + (rand() % answer);

            cout << "Player 1's turn to guess: ";
            player1.setGuess(set);
            guessNum = player1.getGuess();
            win = checkForWin(guessNum, answer);
            
            if (win) {
                return;
            }
            
            cout << endl << "Player 2's turn to guess: ";
            player2.setGuess(set2);
            guessNum = player2.getGuess();
            win = checkForWin(guessNum, answer);
        }
    }
}

