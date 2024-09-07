#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class Puzzle
{
protected:
    int puzzleId;
    string description;
    vector<string> solutions;

public:
    Puzzle(int id, const string &desc, const vector<string> &sols)
        : puzzleId(id), description(desc), solutions(sols) {}

    bool solve(const string &attempt) const
    {
        for (const auto &solution : solutions)
        {
            if (attempt == solution)
            {
                return true;
            }
        }
        return false;
    }

    virtual void displayHint() const
    {
        // Display a hint for the puzzle
    }

    string getDescription() const
    {
        return description;
    }

    // Additional methods for managing puzzle attributes
};

class NumericPuzzle : public Puzzle
{
private:
    int minValue;
    int maxValue;

public:
    NumericPuzzle(int id, const string &desc, const vector<string> &sols, int minVal, int maxVal)
        : Puzzle(id, desc, sols), minValue(minVal), maxValue(maxVal) {}

    // Additional methods specific to numeric puzzles
};

class WordPuzzle : public Puzzle
{
private:
    vector<string> validWords;

public:
    WordPuzzle(int id, const string &desc, const vector<string> &sols, const vector<string> &words)
        : Puzzle(id, desc, sols), validWords(words) {}

    // Additional methods specific to word puzzles
};
class BankAccount
{
private:
    string accholdername;
    string accountNumber;
    double balance;

public:
    BankAccount(const string &holdername, const string &accNo, double initialBalance)
        : accholdername(holdername), accountNumber(accNo), balance(initialBalance) {}

    double getBalance()
    {
        return balance;
    }

    void deposit(double amount)
    {
        balance += amount;
    }

    void withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
        }
        else
        {
            cout << "Insufficient funds in the bank account." << endl;
        }
    }
};
class Room
{
private:
    int roomId;
    string description;
    vector<Puzzle *> puzzles;

public:
    Room(int id, const string &desc)
        : roomId(id), description(desc) {}

    void addPuzzle(Puzzle *puzzle)
    {
        puzzles.push_back(puzzle);
    }

    int getPuzzleCount() const
    {
        return puzzles.size();
    }

    Puzzle *getPuzzle(int index) const
    {
        if (index >= 0 && index < puzzles.size())
        {
            return puzzles[index];
        }
        return nullptr;
    }

    void removePuzzle(int index)
    {
        if (index >= 0 && index < puzzles.size())
        {
            puzzles.erase(puzzles.begin() + index);
        }
    }

    int getRoomId()
    {
        return roomId;
    }

    string getDescription()
    {
        return description;
    }

    ~Room()
    {
        for (Puzzle *puzzle : puzzles)
        {
            delete puzzle;
        }
    }
};

class Player
{
private:
    int playerId;
    string name;
    int age;
    BankAccount *bankAccount;

public:
    Player(int id, const string &n, int a, BankAccount *ba)
        : playerId(id), name(n), age(a), bankAccount(ba) {}

    int getId()
    {
        return playerId;
    }

    string getName()
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }

    BankAccount *getBankAccount()
    {
        return bankAccount;
    }

    // Additional methods for managing player attributes and actions
};

class Payment
{
public:
    virtual bool processPayment() = 0;
};

class CreditCard : public Payment
{
private:
    string cardNumber;
    int cvv;
    string expiryDate;

public:
    CreditCard(const string &num, int cvv, const string &date)
        : cardNumber(num), cvv(cvv), expiryDate(date) {}

    bool processPayment() override
    {
        return true;
    }
};

class DebitCard : public Payment
{
private:
    string cardNumber;
    string pin;

public:
    DebitCard(const string &num, const string &pin)
        : cardNumber(num), pin(pin) {}

    bool processPayment() override
    {

        return true;
    }
};

class UPI : public Payment
{
private:
    string upiId;
    string name;

public:
    UPI(const string &id, const string &name)
        : upiId(id), name(name) {}

    bool processPayment() override
    {

        return true;
    }
};

class GameEngine
{
private:
    vector<Room *> rooms;
    Player *player;
    int currentRoomIndex;
    double entryFee;
    double prizeMoney;
    int maxWrongAttemptsRoom1; // Maximum allowed wrong attempts in Room 1

public:
    GameEngine(Player *p, double fee, double prize, int maxWrong)
        : player(p), currentRoomIndex(0), entryFee(fee), prizeMoney(prize), maxWrongAttemptsRoom1(maxWrong) {}

    void addRoom(Room *room)
    {
        rooms.push_back(room);
    }

    void promptUserCredentials()
    {
        string name;
        int age;
        string holdername;
        string bankAccountNum;
        double initialBalance;

        cout << "Enter your name: ";
        getline(cin, name);

        cout << "Enter your age: ";
        cin >> age;

        cin.ignore();

        cout << "bank account holder name:  ";
        getline(cin, holdername);

        cout << "Enter your bank account number: ";
        getline(cin, bankAccountNum);

        cout << "Enter initial bank balance: $";
        cin >> initialBalance;

        player = new Player(1, name, age, new BankAccount(holdername, bankAccountNum, initialBalance));
    }

    void promptPayment()
    {
        string paymentMethod;
        cout << "Choose a payment method (credit/debit/UPI): ";
        getline(cin, paymentMethod);

        if (paymentMethod == "credit")
        {
            string ccNo;
            int cvv;
            string exp;

            cout << "Enter credit card number: ";
            getline(cin, ccNo);

            cout << "Enter CVV: ";
            cin >> cvv;

            cin.ignore();

            cout << "Enter expiration date (MM/YY): ";
            getline(cin, exp);

            Payment *payment = new CreditCard(ccNo, cvv, exp);
            if (payment->processPayment())
            {
                cout << "Payment successful!" << endl;
            }
            else
            {
                cout << "Payment failed. Please try again." << endl;
                promptPayment();
            }
            delete payment;
        }
        else if (paymentMethod == "debit")
        {
            string accNo;
            string pin;

            cout << "Enter debit card number: ";
            getline(cin, accNo);

            cout << "Enter PIN: ";
            getline(cin, pin);

            Payment *payment = new DebitCard(accNo, pin);
            if (payment->processPayment())
            {
                cout << "Payment successful!" << endl;
            }
            else
            {
                cout << "Payment failed. Please try again." << endl;
                promptPayment();
            }
            delete payment;
        }
        else if (paymentMethod == "UPI")
        {
            string uid;
            string name;

            cout << "Enter UPI ID: ";
            getline(cin, uid);

            cout << "Enter name associated with UPI ID: ";
            getline(cin, name);

            Payment *payment = new UPI(uid, name);
            if (payment->processPayment())
            {
                cout << "Payment successful!" << endl;
            }
            else
            {
                cout << "Payment failed. Please try again." << endl;
                promptPayment();
            }
            delete payment;
        }
        else
        {
            // cout << "Invalid payment method. Please try again." << endl;
            promptPayment();
        }
    }

    void startGame()
    {
        cout << "Welcome, " << player->getName() << "!" << endl;

        if (player->getAge() < 18)
        {
            cout << "Sorry, players below 18 years old are not allowed to play." << endl;
            return;
        }

        promptPayment();
        player->getBankAccount()->withdraw(entryFee);

        cout << "Payment successful. You may now enter the game room." << endl;

        int wrongAttemptsRoom1 = 0;      // Counter for wrong attempts in Room 1
        int correctPuzzleCountRoom1 = 0; // Counter for correct puzzles solved in Room 1

        while (currentRoomIndex < rooms.size())
        {
            Room *currentRoom = rooms[currentRoomIndex];
            cout << "You are in room " << currentRoom->getRoomId() << endl;
            cout << currentRoom->getDescription() << endl;

            int puzzleCount = currentRoom->getPuzzleCount();
            if (puzzleCount == 0)
            {
                cout << "There are no puzzles in this room. Proceed to the next room." << endl;
                currentRoomIndex++;
                continue;
            }

            cout << "Choose a puzzle to solve (1-" << puzzleCount << "): ";
            int choice;
            cin >> choice;

            if (choice >= 1 && choice <= puzzleCount)
            {
                Puzzle *selectedPuzzle = currentRoom->getPuzzle(choice - 1);
                cout << "Question: " << selectedPuzzle->getDescription() << endl;

                string attempt;
                cout << "Enter your solution: ";
                cin.ignore();
                getline(cin, attempt);

                if (selectedPuzzle->solve(attempt))
                {
                    cout << "Congratulations! You solved the puzzle!" << endl;
                    player->getBankAccount()->deposit(50.0);
                    cout << "Bank Balance: $" << player->getBankAccount()->getBalance() << endl;
                    currentRoom->removePuzzle(choice - 1);
                    puzzleCount--;             // Update the puzzle count after removal
                    correctPuzzleCountRoom1++; // Increment correctPuzzleCountRoom1 on each correct attempt in Room 1
                }
                else
                {
                    cout << "Incorrect solution. Try again or ask for a hint." << endl;
                    player->getBankAccount()->withdraw(20.0);
                    cout << "Bank Balance: $" << player->getBankAccount()->getBalance() << endl;
                    selectedPuzzle->displayHint();
                    wrongAttemptsRoom1++; // Increment wrongAttemptsRoom1 on each incorrect attempt in Room 1
                    if (wrongAttemptsRoom1 > maxWrongAttemptsRoom1)
                    {
                        cout << "You have exceeded the maximum allowed wrong attempts in Room 1. You cannot proceed to the next room." << endl;
                        return; // Stop the game and prevent entry to Room 2
                    }
                }
            }
            else
            {
                cout << "Invalid choice. Please try again." << endl;
            }
        }

        // Check if the player can proceed to Room 2
        bool canProceedToRoom2 = correctPuzzleCountRoom1 == currentRoomIndex || wrongAttemptsRoom1 <= 1;

        if (canProceedToRoom2)
        {
            cout << "Congratulations! You have successfully completed Room 1." << endl;
            cout << "You may now proceed to Room 2." << endl;

            // Move to Room 2
            currentRoomIndex++;

            // Reset wrongAttemptsRoom1 to allow attempts in Room 2
            wrongAttemptsRoom1 = 0;

            while (currentRoomIndex < rooms.size())
            {
                // The game logic for Room 2 will be similar to Room 1
                // ...
                // You can add more puzzles and logic for Room 2 here
                // ...
            }
        }
        else
        {
            cout << "You failed to solve all the puzzles in Room 1 or exceeded the maximum allowed wrong attempts." << endl;
            cout << "Your prize money is forfeited." << endl;

            cout << "Final Bank Balance: $" << player->getBankAccount()->getBalance() << endl;
        }
    }
};

void displayEndMessage()
{
    cout << endl;
    cout << " Thank you for your participation." << endl
         << " We appreciate your contribution." << endl;
    cout << "Your participation has also contributed to the Plant Trees Approach as 70 percent of the entry fee will be used for planting and caring of trees." << endl;
    cout << "Hope you enjoyed your participation with us." << endl;
}

int main()
{
    double entryFee = 10.0;        // Set the entry fee
    double prizeMoney = 100.0;     // Set the prize money
    int maxWrongAttemptsRoom1 = 1; // Maximum allowed wrong attempts in Room 1

    GameEngine game(nullptr, entryFee, prizeMoney, maxWrongAttemptsRoom1);

    // Create Room 1 and add puzzles to it
    Room room1(1, "You are in a dimly lit room. There is a locked door in front of you.");
    vector<string> numericSolutionsRoom1{"6"};
    NumericPuzzle *puzzle1 = new NumericPuzzle(1, "Solve the equation: 2 + 2 * 2 =", numericSolutionsRoom1, 0, 10);
    vector<string> wordSolutionsRoom1{"read", "dear", "dare"};
    WordPuzzle *puzzle2 = new WordPuzzle(2, "Unscramble the letters to form a word: R E D A", wordSolutionsRoom1, {"read", "dear", "dare"});
    vector<string> numericSolutionsRoom1B{"8"};
    NumericPuzzle *puzzle3 = new NumericPuzzle(3, "Solve the equation: 2 * 2 * 2 =", numericSolutionsRoom1B, 0, 10);
    vector<string> wordSolutionsRoom1B{"mice", "emic", "cime"};
    WordPuzzle *puzzle4 = new WordPuzzle(4, "Rearrange the letters to form a word: M I C E", wordSolutionsRoom1B, {"mice", "emic", "cime"});

    // adding puzzle to the room1
    room1.addPuzzle(puzzle1);
    room1.addPuzzle(puzzle2);
    room1.addPuzzle(puzzle3);
    room1.addPuzzle(puzzle4);

    game.addRoom(&room1);

    Room room2(2, "You have entered Room 2. This room is filled with puzzles that are more challenging.");
    vector<string> numericSolutionsRoom2{"12"};
    NumericPuzzle *puzzle5 = new NumericPuzzle(5, "Solve the equation: 3 * 4 =", numericSolutionsRoom2, 0, 20);
    vector<string> wordSolutionsRoom2{"planet", "platen", "penalt", "aplent"};
    WordPuzzle *puzzle6 = new WordPuzzle(6, "Rearrange the letters to form a word: T A N L E P", wordSolutionsRoom2, {"planet", "platen", "penalt", "aplent"});
    vector<string> numericSolutionsRoom2B{"15"};
    NumericPuzzle *puzzle7 = new NumericPuzzle(7, "Solve the equation: 5 + 5 * 2 =", numericSolutionsRoom2B, 0, 20);
    vector<string> wordSolutionsRoom2B{"great", "grate", "targe", "retag"};
    WordPuzzle *puzzle8 = new WordPuzzle(8, "Rearrange the letters to form a word: G R E A T", wordSolutionsRoom2B, {"great", "grate", "targe", "retag"});

    // adding
    room2.addPuzzle(puzzle5);
    room2.addPuzzle(puzzle6);
    room2.addPuzzle(puzzle7);
    room2.addPuzzle(puzzle8);

    game.addRoom(&room2);
    game.promptUserCredentials();
    game.startGame();

    displayEndMessage();
    // Clean up memory
    delete puzzle1;
    delete puzzle2;
    delete puzzle3;
    delete puzzle4;
    delete puzzle5;
    delete puzzle6;
    delete puzzle7;
    delete puzzle8;

    return 0;
}