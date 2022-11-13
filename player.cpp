#pragma once

#include "board.cpp"

class Player {
private:
    string name;

public:
    Player(string name) {
        this->name = name;
    }

    virtual Board::Move getMove(Board::BoardType board) {
        Board::Move move;
        move.x = NULL;
        move.y = NULL;
        return move;
    };

protected:
    string getName() {
        return name;
    }
};

class ComputerPlayer : public Player {
public:
    Board::Move getMove(Board::BoardType board) {
        cout << "Ruch komputera, Gracz: " << getName() << endl;
        Board::Move move;
        do {
            move.x = rand() % 3;
            move.y = rand() % 3;
        } while (board[move.x][move.y] != EMPTY_FIELD);
        return move;
    }
    ComputerPlayer(string name) : Player(name) {}
};

class HumanPlayer : public Player {
public:
    bool checkData(Board::Move move) {
        return (0 <= move.x && move.x <= 2) && (0 <= move.y && move.y <= 2);
    }

    Board::Move getMove(Board::BoardType board) {
        cout << "Ruch czlowieka, Gracz: " << getName() << endl;
        cout << " Podaj wspolrzedne dla gracza: " << endl;
        Board::Move move;
        cin >> move.x >> move.y;
        while (!checkData(move) && board[move.x][move.y] != EMPTY_FIELD) {
            cout << " Podaj wspolrzedne dla gracza: " << endl;
            cin >> move.x >> move.y;
        }
        return move;
    }
    HumanPlayer(string name) : Player(name) {}
};