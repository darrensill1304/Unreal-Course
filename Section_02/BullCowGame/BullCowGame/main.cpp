//
//  main.cpp
//  BullCowGame
//
//  Created by Darren Sill on 12/10/2017.
//  Copyright © 2017 darren.sill. All rights reserved.
//


/*
This is the console excecutable, that makes use of the Bull Cow game.
This acts as the "view" in the MVC pattern, and is responsible for all
user interaction. For game logic, see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main() {
    
    do {
        PrintIntro();
        PlayGame();
    } while (AskPlayAgain());
    
    return 0;
}

void PrintIntro() {
    
    // Introduce the Game
    std::cout << "\n\nWelcome to Bulls and Cows!" << std::endl;
    std::cout << std::endl;
    std::cout << "             }____{             ___ " << std::endl;
    std::cout << "             (o  o)            (o o) " << std::endl;
    std::cout << "     /--------\\  /              \\ /-----------\\ " << std::endl;
    std::cout << "    / | BULL  | O                O |   COW  |  \\ " << std::endl;
    std::cout << "   *  |-,-----|          VS        |--------|   *" << std::endl;
    std::cout << "      ^       ^                    ^        ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?" << std::endl;
    std::cout << std::endl;
    
    return;
}

void PlayGame() {
    
    BCGame.Reset();
    
    int32 MaxTries = BCGame.GetMaxTries();
    
    // Loop for number of turns while asking for a guess
    // while game is not won and there are still tries remaining
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        
        FText Guess = GetValidGuess(); //TODO: Make loop checking valid guesses
        
        // Submit Valid Guess to the game
        FBullCowCount bcc = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls = " << bcc.Bulls << std::endl;
        std::cout << "Cows = " << bcc.Cows << "\n\n";
    }
    
    PrintGameSummary();
    return;
}

FText GetValidGuess() {
    
    EGuessStatus status = EGuessStatus::InvalidStatus;
    FText Guess = "";
    do {
        
        int32 CurrentTry = BCGame.GetCurrentTry();
        
        std::cout << "Try " << CurrentTry << ": Enter Guess: ";
        
        getline(std::cin,Guess);
        
        status = BCGame.CheckGuessValidity(Guess);
        
        switch (status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Plesae enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter a guess all in lowercase.\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word with no repeat letters.\n";
                break;
            case EGuessStatus::OK:
                break;
            default:
                break;
        }
        std::cout << std::endl;
    } while (status != EGuessStatus::OK);
    
    return Guess;
}

bool AskPlayAgain() {
    std::cout << "Do you want to play again? (y/n)\n" << std::endl;
    FText Response = "";
    getline(std::cin, Response);
    
    return (Response[0] == 'Y') || (Response[0] == 'y');
    
    
}

void PrintGameSummary() {
    if (BCGame.IsGameWon()) {
        std::cout << "Well Done - You Win!\n\n";
    } else {
        std::cout << "Better Luck Next Time\n";
    }
}

