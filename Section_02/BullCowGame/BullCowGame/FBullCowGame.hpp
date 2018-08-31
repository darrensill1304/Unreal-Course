//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Darren Sill on 15/10/2017.
//  Copyright © 2017 darren.sill. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>
#endif /* FBullCowGame_hpp */
#pragma once

using FString = std::string;
using int32 = int;

struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus {
    InvalidStatus,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
    
public:
    
    FBullCowGame(); // Constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset(); // TODO: Return a more rich value
    
    // counts bulls and cows and increases try number, assuming valid guess
    FBullCowCount SubmitValidGuess(FString);
    
private:
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
    bool bIsGameWon;
    
    bool isIsogram(FString) const;
    bool isLowercase(FString) const;
};
