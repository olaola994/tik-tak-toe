#pragma once

#include <iostream>
#include <chrono>

using namespace std;

#define PLAYER_ONE 'X'
#define PLAYER_TWO 'O'
#define EMPTY_FIELD ' '

class Board {
public:
    typedef char BoardType[3][3];

    struct Move {
        int x;
        int y;
    };

    BoardType board;

    enum GameResult { NoResult, Draw, PlayerOne, PlayerTwo, Interrupted };

    Board() {
        //srand(time(NULL));

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = EMPTY_FIELD;
            }
        }
    }
    void displayBoardHelp() {
        cout << endl;
        cout << "POMOC DO GRY" << endl;
        cout << "Wspolrzedne pol na planszy" << endl;
        cout << endl;
        cout << "    0   1   2 " << endl;
        cout << " 0    |   |   " << endl;
        cout << "   ---+---+---" << endl;
        cout << " 1    |   |   " << endl;
        cout << "   ---+---+---" << endl;
        cout << " 2    |   |   " << endl;
        cout << endl;
    }

    void display() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << " " << board[i][j];
                if (j != 2) cout << " | ";
            }
            cout << endl;
            if (i != 2) cout << "---+----+---" << endl;
        }
        cout << endl;
    }


    bool isBoardFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY_FIELD) return false;
            }
        }
        return true;
    }

    bool isBoardEmpty() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != EMPTY_FIELD) return false;
            }
        }
        return true;
    }

    bool setMoveOnBoard(Move move, char player) {
        if (board[move.x][move.y] == EMPTY_FIELD) {
            board[move.x][move.y] = player;
            return true;
        }
        else {
            return false;
        }
    }

    BoardType* getBoardState() {
        return &board;
    }

    GameResult getGameResult(char winner) {
        switch (winner) {
            case PLAYER_ONE:
                return PlayerOne;
            case PLAYER_TWO:
                return PlayerTwo;
            default:
                return Draw;
        }
    }

    GameResult isGameOver() {
        int i = 0;
        if (isBoardFull()) return Draw;
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY_FIELD) return getGameResult(board[i][0]); // sprawdzanie wiersza
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY_FIELD) return getGameResult(board[0][i]); // sprawdzanie kolumny
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY_FIELD) return getGameResult(board[0][0]); // przekatna glowna
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY_FIELD) return getGameResult(board[0][2]); // przekatna poboczna


        return NoResult;
    }
};
