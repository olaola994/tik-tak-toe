#pragma once

#include<sstream>
#include <iostream>

#include "game.cpp"
#include "board.cpp"
#include "player.cpp"


using namespace std;

int main() {

    Player* player1 = NULL;
    Player* player2 = NULL;
    Game* game = NULL;
    int option = -1;

    while (true) {
        while (true) {
            cout << "Witaj w grze kolko i krzyzyk!" << endl;
            cout << "Wybierz tryb gry: " << endl
                 << "1. Czlowiek i komputer" << endl
                 << "2. Czlowiek i czlowiek" << endl
                 << "3. Komputer i komputer" << endl;

            if (cin >> option);
            else {
                cout << "Blad, popraw dane: " << endl;
                cin.clear();
                cin.ignore(80, '\n');
                continue;
            }

            switch (option) {
                case 1:
                    player1 = new HumanPlayer("player1");
                    player2 = new ComputerPlayer("player2");
                    break;
                case 2:
                    player1 = new HumanPlayer("player1");
                    player2 = new HumanPlayer("player2");
                    break;
                case 3:
                    player1 = new ComputerPlayer("player1");
                    player2 = new ComputerPlayer("player2");
                    break;
                default:
                    cout << "Blad, popraw dane: " << endl;
                    continue;
            }
            break;
        }

        game = new Game(player1, player2);

        game->startGame();
        if (game->doYouWantRepeatGame()) continue;
        cout << endl << "Koniec gry." << endl;
        break;
    }

    delete game;

    return 0;
}
