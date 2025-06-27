#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

string board[9];
string turn = "X";
bool vsComputer = false;
int xWins = 0, oWins = 0, draws = 0;
int winCombos[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
    {0, 4, 8}, {2, 4, 6}
};

void populateEmptyBoard() {
    for (int i = 0; i < 9; i++) {
        board[i] = to_string(i + 1);
    }
}

void printBoard() {
    cout << "/---|---|---\\\n";
    cout << "| " << board[0] << " | " << board[1] << " | " << board[2] << " |\n";
    cout << "|-----------|\n";
    cout << "| " << board[3] << " | " << board[4] << " | " << board[5] << " |\n";
    cout << "|-----------|\n";
    cout << "| " << board[6] << " | " << board[7] << " | " << board[8] << " |\n";
    cout << "/---|---|---\\\n";
}

void showScoreboard() {
    cout << "\n📊 Scoreboard:\n";
    cout << "X Wins: " << xWins << "\n";
    cout << "O Wins: " << oWins << "\n";
    cout << "Draws : " << draws << "\n";
}

int getValidInput(int min, int max) {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cout << "❌ Invalid input. Please enter a number:\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (input >= min && input <= max) {
            return input;
        } else {
            cout << "⚠ Enter a number between " << min << " and " << max << ":\n";
        }
    }
}

void computerMove() {
    int move;
    srand(time(0));
    while (true) {
        move = rand() % 9;
        if (board[move] == to_string(move + 1)) {
            board[move] = turn;
            break;
        }
    }
}

string checkWinner() {
    for (auto &combo : winCombos) {
        string a = board[combo[0]];
        string b = board[combo[1]];
        string c = board[combo[2]];
        if (a == b && b == c) {
            board[combo[0]] += "🎉";
            board[combo[1]] += "🎉";
            board[combo[2]] += "🎉";
            return a.substr(0, 1);
        }
    }

    for (int i = 0; i < 9; i++) {
        if (board[i] == to_string(i + 1)) return "";
    }

    return "draw";
}

bool askReplay() {
    string answer;
    while (true) {
        cout << "\n🔁 Play again? (Y/N):\n";
        cin >> answer;
        for (auto &c : answer) c = toupper(c);
        if (answer == "Y") return true;
        if (answer == "N") return false;
        cout << "❌ Invalid input. Please enter Y or N.\n";
    }
}

void playGame() {
    string winner = "";
    turn = "X";
    populateEmptyBoard();

    cout << "\n🎲 New Game Started!\n";
    cout << "Select Game Mode:\n";
    cout << "1. User vs User\n";
    cout << "2. User vs Computer\n";

    int mode = getValidInput(1, 2);
    vsComputer = (mode == 2);

    printBoard();
    cout << "X goes first.\n";

    while (winner == "") {
        if (turn == "X" || !vsComputer) {
            cout << turn << "'s turn; enter a slot number (1-9):\n";
            int move = getValidInput(1, 9);
            if (board[move - 1] != to_string(move)) {
                cout << "❗ Slot already taken; try another.\n";
                continue;
            }
            board[move - 1] = turn;
        } else {
            cout << "Computer's turn:\n";
            computerMove();
        }

        printBoard();
        winner = checkWinner();

        if (winner == "") {
            turn = (turn == "X") ? "O" : "X";
        }
    }

    if (winner == "draw") {
        cout << "🤝 It's a draw!\n";
        draws++;
    } else {
        cout << "🎉 Congratulations! " << winner << " wins! 🎉\n";
        if (winner == "X") xWins++;
        else oWins++;
    }
}

int main() {
    do {
        playGame();
        showScoreboard();
    } while (askReplay());

    cout << "🏁 Final Score:\n";
    showScoreboard();
    cout << "Thanks for playing! 👋\n";

    return 0;
}
