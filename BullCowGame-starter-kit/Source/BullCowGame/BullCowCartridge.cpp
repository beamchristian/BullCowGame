// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);

    GetValidWords(Words);
    
    SetupGame();

    PrintLine(TEXT("The number of possible words is %i."), Words.Num());
    PrintLine(TEXT("The number of valid words is: %i"), GetValidWords(Words).Num());
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug Line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
   if (bGameOver)
   {
       ClearScreen();
       SetupGame();
   }
   else // Checking PlayerGuess
   {
        ProcessGuess(Input); 
   }
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the Player
    PrintLine(TEXT("Welcome to Bull Cows!"));

    HiddenWord = TEXT("cakes"); 
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type in your guess and \nPress enter to continue..."));  // Prompt Player for Guess
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again!"));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
        {
            PrintLine(TEXT("You Win!"));
            EndGame();
            return;
        }

        // check if Isogram
        if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("No repeating letters, guess again!"));
            return;
        }
        
        if (Guess.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
            PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining."), Lives);
            return;          
        }

        // Remove life
        PrintLine(TEXT("Lost a life!"));
        --Lives;

        if (Lives <= 0)  
        {
            ClearScreen();
            PrintLine(TEXT("You have no lives left!"));
            PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
            EndGame();
            return;
        }
        // Show the player Bulls and Cows
        PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}
bool UBullCowCartridge::IsIsogram(FString Word) const
{

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
       for (int32 Comparison = Index +1; Comparison < Word.Len(); Comparison++) 
       {
           if (Word[Index] == Word[Comparison])
           {
               return false;
           }
       }
       
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
TArray<FString> ValidWords;

    for (int32 Index = 0; Index < WordList.Num(); Index++)
    {
        if (WordList[Index].Len() >= 4 && WordList[Index].Len() <= 8)
        {
            if (IsIsogram(WordList[Index])) 
            {
                ValidWords.Emplace(WordList[Index]);
            }
        }
    }
    return ValidWords;
}

