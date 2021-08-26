/****************************************************************************************************
*** File Name:      sleep_debt_calculator.js
*** Description:    Program to prompt a user to guess the product and sum of three numbers
*** Author:         Trevor Carson
*** Date:           2021-08-21
*****************************************************************************************************/

#include <iostream>
#include <ctime>

// Method to print introduction
void PrintIntroduction() {
    std::cout << "\nWith the first snowfall signifying the end of the growing season you decide to take your yearly winter vacation back into space. 'See you in a couple months, earth!' You say cheerfully as you park your truck and hop into your space rocket. ";
    std::cout << "You kick up your feet after blasting off into space. 'Time for another adventure' you say while noticing a small glowing object floating just off in the distance. You quickly head over to the object in the hopes of discovering some lost relic of the past. ";
    std::cout << "As you get closer you notice the object looks like a high tech safe, the likes of which you have never seen before.\n";
    std::cout << "\nYou pull the box into your airlock and notice a 3 digit combination. 'What a find!', you yell in anticipation.\n";
}

void PrintVictory() {
    std::cout << "\nA small cute alien creature emerges from the box. After a brief moment you notice the creature is not small or cute at all, it has nearly quadrupled in size. The strange creature eats a hole in the side of your ship and you both get sucked out into the cold dark vastness of space. 'Ahhhhh!', you scream, only to realize no one in space can hear you.\n";
}

void PrintDefeat() {
    std::cout << "\n'Curse this damned box!', you mutter under your breath as you hurl the mysterious object back out the airlock, back into the depths of space.\n";
}

// Method to start the game
bool PlayGame(int LevelDifficulty, int TotalGuess) {
    srand(time(NULL)); // Seeds random based on the time of day

    int CodeA = rand() % 3 + LevelDifficulty; // Variable to hold the first parameter
    int CodeB = rand() % 3 + LevelDifficulty; // Variable to hold the second parameter
    int CodeC = rand() % 3 + LevelDifficulty; // Variable to hold the third parameter
    int CodeSum = CodeA + CodeB + CodeC; // Variable to store the sum of a, b, and c
    int CodeProduct = CodeA * CodeB * CodeC; // Variable to store the product of a, b, and c

    std::cout << "\n    _____________";
    std::cout << "\n   // GUESSES   \\\\";
    std::cout << "\n  //  LEFT:" << TotalGuess << "     \\\\";
    std::cout << "\n //               \\\\";
    std::cout << "\n//     SUM:" << CodeSum << "      \\\\";
    std::cout << "\n||  PRODUCT:" << CodeProduct <<"     ||";
    std::cout << "\n\\\\                 //";
    std::cout << "\n \\\\    ~#-#-#~    //";
    std::cout << "\n  \\\\    ~~~~~    //";
    std::cout << "\n   \\\\___________//";
    std::cout << "\n -------------------";
    std::cout << "\n: ";

    int GuessA, GuessB, GuessC; // Variables to hold user entered numbers
    std::cin >> GuessA;
    std::cin >> GuessB;
    std::cin >> GuessC;
    std::cout << std::endl;
       
    int GuessSum = GuessA + GuessB + GuessC; // Variable to store the sum of user entered numbers
    int GuessProduct = GuessA * GuessB * GuessC; // Variable to store the product of user entered numbers

    if (GuessSum == CodeSum && GuessProduct == CodeProduct && TotalGuess >= 1) {
        switch (LevelDifficulty) {
                case 1:
                    std::cout << "\nThe lock clicks open as you take a deep sigh of relief. Your anticipation begins to build only to discover there is another lock inside. 'What madness is this?', you mutter under your breath.\n";
                    break;
                case 2:
                    std::cout << "\nYou have successfully opened the second lock only to reveal there is more to the mystery. 'How deep can this mystery go?', you whisper to yourself.\n";
                    break;
                case 3:
                    std::cout << "\nThe mysterious box reveals there is even more to the mystery. 'What could be inside?' you exclaim.\n";
                    break;
                case 4:
                    std::cout << "\nYour excitement builds as you realize you are on the last lock. You stare at the mysterious box wondering if it was ever intended to be opened.\n";
                    break;
                default:
                    // code block
                    break;
            }
        return true; // Return true to signify level was completed
    } else {
        if (TotalGuess >= 2) {
            std::cout << "\n'BZZZZT...', The object makes a loud buzz as the combination shuffles around.\n";
            return false; // Return false to signify level was not completed
        } else {
            std::cout << "You Lose!";
            return false; // Return false to signify level was not completed
        }
    }
}

// Main method
int main() {
    int LevelDifficulty = 1;    // Integer to hold level difficulty multiplier
    int TotalGuess = 9;        // Integer to hold the total amount of guesses
    int const MaxLevel = 5;     // Constant integer to hold the max game level

    PrintIntroduction();

    while (LevelDifficulty <= MaxLevel && TotalGuess >= 1) {    
        bool bLevelComplete = PlayGame(LevelDifficulty, TotalGuess);
        std::cin.clear(); // Clears any errors
        std::cin.ignore(); // Discards the buffer
        
        if (bLevelComplete) {
            LevelDifficulty++;
            TotalGuess--;
        } else {
            TotalGuess--;
        }
    }
    return 0; // Standerd errorless return value
}
