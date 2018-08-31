//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Darren Sill on 15/10/2017.
//  Copyright © 2017 darren.sill. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() {
    Reset();
}

void FBullCowGame::Reset() {
    constexpr int32 MAX_TRIES = 8;
    const FString HIDDEN_WORD = "planet";
    
    MyHiddenWord = HIDDEN_WORD;
    MyMaxTries = MAX_TRIES;
    MyCurrentTry = 1;
    bIsGameWon = false;
    
    return;
}

// Getters
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetHiddenWordLength() const { return (int32)MyHiddenWord.length(); }

// Other Methods
bool FBullCowGame::IsGameWon() const{ return bIsGameWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    
    if (!isIsogram(Guess)) { // if guess isnt isogram
        
        return EGuessStatus::Not_Isogram;
        
    } else if (!isLowercase(Guess)) { // if guess isnt lowercase
        
        return EGuessStatus::Not_Lowercase;
        
    } else if (Guess.length() != GetHiddenWordLength()) { // if the guess length != hidden word length
        
        return EGuessStatus::Wrong_Length;
        
    } else {
        
        return EGuessStatus::OK;
        
    }
}

// Receives valid guess, increments turn and returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
    
    MyCurrentTry ++;
    
    // set up return variable
    FBullCowCount bcc;
    
    int32 WordLength = (int32)MyHiddenWord.length(); // assume same length as guess
    
    // loop through all letters in guess
    for (int32 iGuessChar = 0; iGuessChar < WordLength; iGuessChar++){
    // for each..
        for (int32 iHWChar = 0; iHWChar < WordLength; iHWChar++) {
        // compare letters against hidden word
            // if they match
            if (Guess[iGuessChar] == MyHiddenWord[iHWChar]){
                if ( iGuessChar == iHWChar ){
                    // increment bulls if in the same place
                    bcc.Bulls ++;
                } else {
                    // increment cows if not
                    bcc.Cows ++;
                }
            }
        }
    }
    
    if (bcc.Bulls == WordLength) {
        bIsGameWon = true;
    } else {
        bIsGameWon = false;
    }
    
    return bcc;
}

bool FBullCowGame::isIsogram(FString word) const {
    
    // treat 0 and 1 letter words as isograms
    if (word.length() <= 1) { return true; }
    
    // set up map
    TMap<char, bool> LetterSeen;
    
    // loop through all letter
    for(auto letter : word) {
        letter = tolower(letter);
        //if letter in map
        if (LetterSeen[letter]) {
            // we do NOT have an isogram -> return false
            return false;
        } else {
            // add the letter to the map
            LetterSeen[letter] = true;
        }
        
        
    }
    
    return true; // for example, in cases where /0 is entered
}

bool FBullCowGame::isLowercase(FString word) const {
    for (auto letter : word) {
        // If not a lowercase letter, return false
        if (!islower(letter)) {
            return false;
        }
    }
    return true;
}






