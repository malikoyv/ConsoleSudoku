#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cmath>
using namespace std;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void set_cursor(int x, int y);
void printArr(int sudoku[][9]);
bool validateMove(int num, int sudoku[][9], int row, int col);
bool checkForWin(int sudoku[][9]);

int main() {
    int sudoku[9][9] = {
            {0, 0, 0, 3, 0, 7, 4, 0, 0},
            {9, 0, 0, 0, 0, 4, 0, 0, 9},
            {3, 7, 0, 0, 0, 0, 0, 6, 0},
            {8, 2, 0, 9, 0, 0, 6, 0, 0},
            {0, 0, 1, 2, 0, 0, 9, 0, 4},
            {0, 4, 0, 0, 3, 8, 0, 5, 0},
            {2, 0, 8, 6, 9, 0, 7, 0, 0},
            {0, 9, 0, 0, 0, 0, 0, 0, 0},
            {7, 5, 0, 0, 0, 0, 0, 0, 6},
    };
    int x = 1, y = 1, loseCounter = 0;
    system("chcp 437"); // configuration to use some specific ASCII symbols
    system("CLS"); // clear a console;
    printArr(sudoku);

    while (true) {
        char c;
        set_cursor(x, y);
        switch (c = getch()) {
            case KEY_UP:
                if (y > 1) y -= 2;
                break;
            case KEY_DOWN:
                if (y <= 15) y += 2;
                break;
            case KEY_LEFT:
                if (y >= 1) x -= 2;
                break;
            case KEY_RIGHT:
                if (x <= 15) x += 2;
                break;
            default:
                if (isdigit(c)) {
                    c = char(c);
                    int row_index = (y - 1) / 2;
                    int col_index = (x - 1) / 2;

                    if (sudoku[row_index][col_index] == 0) {
                        if (validateMove(c - 48, sudoku, row_index, col_index)) {
                            cout << c;
                            sudoku[row_index][col_index] = c - 48; // Convert a number from ASCII to normal
                        } else {
                            set_cursor(1, 20); // Writing a message below the table
                            cout << "Fault!";
                            loseCounter++;
                            Sleep(2000); // sleeping
                            set_cursor(1, 20);
                            cout << "                    "; // Clear the message
                        }
                        if (loseCounter == 3){      // Losing after 3 faults
                            set_cursor(1, 20);
                            cout << "You lose :(";
                            Sleep(5000);
                            exit(0);
                        }
                    }
                }

        }
        if (checkForWin(sudoku)){
            for (int a = 0; a < 29; a++) cout << "You win!" << endl;
        }

    }
    return 0;
}

void set_cursor(int x, int y) // cursor set up
{
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition ( handle , coordinates );
}

void printArr(int sudoku[][9]){ // Printing a table using ASCII
    for (int i = 0; i <= 18; i++){
        for (int j = 0; j <= 18; j++){
            if (i % 6 == 0) {
                if (i == 0 && j == 0) cout << char(201);
                else if (i == 0 && j == 18) cout << char(187);
                else if (i == 18 && j == 0) cout << char(200);
                else if (i == 18 && j == 18) cout << char(188);
                else if ((i == 6 && j == 0) || (i == 12 && j == 0)) cout << char(204);
                else if (i == 6 && j == 18 || i == 12 && j == 18) cout << char(185);
                else if ((i == 0 && j == 6) || (i==0 && j == 12)) cout << char(203);
                else if (i == 0 && j%2 == 0) cout << char(209);
                else if (i == 18 && j%6 == 0) cout << char(202);
                else if (i == 18 && j%2 == 0) cout << char(207);
                else if (i%6 == 0 && j%6==0) cout << char(206);
                else if (i == 6 && j%2==0 || i == 12 && j%2 ==0) cout << char(216);
                else cout << char(205);
            }
            else if (i%2 == 0 && j == 0) cout << char(199);
            else if (i%2 == 0 && j == 18) cout << char(182);
            else if (i%2 == 0 && j%6 == 0) cout << char(215);
            else if (j%6 == 0) cout << char(186);
            else if (i%2 == 0 && j%2 == 0) cout << char(197);
            else if (i%2 == 0 && i%3!= 0) cout << char(196);
            else if (j % 2 == 0 && j%3!= 0) cout << char(179);
            else {
                if (sudoku[(i-1)/2][(j-1) / 2] == 0) cout << ' ';
                else cout << sudoku[(i-1)/2][(j-1) / 2];
            }
        }
        cout << endl;
    }
}

bool validateMove(int num, int sudoku[][9], int row, int col) {
    for (int i = 0; i < 9; i++) {
        if (i != col && sudoku[row][i] == num) {
            return false; // Repetition in row
        }
        if (i != row && sudoku[i][col] == num) {
            return false; // Repetition in column
        }
    }

    int startRow = 3 * (row / 3); // Algorithm to find out in which square we are at that moment
    int startCol = 3 * (col / 3);

    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if ((i != row || j != col) && sudoku[i][j] == num) {
                return false; // Repetition in 3x3 square
            }
        }
    }

    return true;
}

bool checkForWin(int sudoku[][9]){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (sudoku[i][j] != 0) return true;
            else return false;
        }
    }
}

