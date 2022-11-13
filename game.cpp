
#pragma once

#include <Windows.h>
#include <iostream>
#include <chrono>
#include <fstream>

#include "board.cpp"
#include "player.cpp"

using namespace std;

class Game {
private:
    Board* board;

    Player* playerX;
    Player* playerO;

    Board::GameResult gameResult;

    long startGameTime;
    long finishGameTime;

    char logFileName[20] = "game_summary.log";

    long getTimeNow() {
        return time(NULL);
    }

public:

    Game() {
        board = new Board();

        playerX = new HumanPlayer("Player1");
        playerO = new ComputerPlayer("Player2");

        gameResult = Board::NoResult;
    }

    Game(Player* playerX, Player* playerO) {
        board = new Board();

        this->playerX = playerX;
        this->playerO = playerO;

        gameResult = Board::NoResult;
    }

    ~Game() {
        delete board;
        delete playerX;
        delete playerO;
    }

    void startGame() {
        startGameTime = getTimeNow();

        showGameInfo();

        board->displayBoardHelp();

        while (true) {
            Board::Move playerOneMove = playerX->getMove(*board->getBoardState());
            board->setMoveOnBoard(playerOneMove, PLAYER_ONE);
            board->display();

            gameResult = board->isGameOver();
            if (gameResult != Board::NoResult) break;

            sleep(2000);

            Board::Move playerTwoMove = playerO->getMove(*board->getBoardState());
            board->setMoveOnBoard(playerTwoMove, PLAYER_TWO);
            board->display();

            gameResult = board->isGameOver();
            if (gameResult != Board::NoResult) break;
        }
        displayGameSummary(gameResult);

        finishGameTime = getTimeNow();
        long delta = finishGameTime - startGameTime;
        cout << "Czas trwania gry: " << delta << " sekundy" << endl;
        saveGameSummary(delta);
    }

    void addPlayers(Player* playerX, Player* playerO) {
        this->playerX = playerX;
        this->playerO = playerO;
    }

    void showGameInfo() {
        cout << "Version: 0.01" << endl;
        cout << "Author:  Aleksandra Filipowicz" << endl;
        cout << "\'Tic Tac Toe'\ Game" << endl;
    }


    bool doYouWantRepeatGame() {
        cout << "Czy chcesz zagrac jeszcze raz? (tak, nie): " << endl;
        string wybor;
        cin >> wybor;

        if (wybor == "tak") return true;
        else return false;
    }

    void displayGameSummary(Board::GameResult result) {
        switch (result) {
            case Board::Draw:
                cout << "Remis" << endl;
                break;
            case Board::PlayerOne:
                cout << "Wygrywa X" << endl;
                break;
            case Board::PlayerTwo:
                cout << "Wygrywa O" << endl;
        }
        cout << "Koniec gry." << endl;
    }

    void saveGameSummary(long time) {
        fstream fstr;
        fstr.open(logFileName, ios::app);
        if (fstr.is_open()) {
            cout << "Zapisano wyniki gry w pliku " << logFileName << endl;
            fstr << "Podsumwanie gry: " << endl;
            if (gameResult == Board::Draw) fstr <<  "W grze remis. Czas gry: " << time << " s"<< endl;
            if (gameResult == Board::PlayerOne) fstr << "W grze wygrał X. Czas gry: " << time << " s" << endl;
            if (gameResult == Board::PlayerTwo)  fstr << "W grze wygrał O. Czas gry: " << time << " s" << endl;
        }
        else {
            cout << "Nie udalo sie utworzyc pliku " << endl;
        }
        fstr.close();
    }
};

template <typename T>
T getGreater(T a, T b) {
    if (a > b) return a;
    return b;
}
