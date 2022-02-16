// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Welcoming the Player
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the 4 letter word!")); // Magic Number Remove!
    PrintLine(TEXT("Press enter to continue..."));

    // Setting Up Game
    HiddenWord = (TEXT("cake")); // Set the HiddenWord

    // Set Lives

    // Prompt Player for Guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    // Checking PlayerGuess
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You Win!"));
    }
    else
    {
        PrintLine(TEXT("You Lose!"));
    }
    // check if Isogram
    // Prompt to Guess Again
    // Check right number of characters
    // Prompt to Guess Again

    // Remove life

    // Check If Lives > 0
    // If Yes GuessAgain
    // Show lives left
    // If No Show GameOver and HiddenWord?
    // Prompt to play again, Press Enter To Play Again?
    // Check User Input
    // PlayAgain or Quit
}