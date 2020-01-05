/**
  * Created by Chris Vanderloo on 1/4/2020
  */

#include <iostream>
#include <vector>

#define BOARDSIZE 9

using namespace std;

class Board;

class Player {
public:
  // returns 0-8
  virtual int getMove(Board b) = 0;
  virtual ~Player() {};
};

class Board {
private:
  vector<int> board;
  Player *player1, *player2;
public:
  void initBoard() {
    for (int i=0; i<BOARDSIZE; i++)
      board.push_back(0);
  }

  Board() {
    initBoard();
  }

  Board(Board& b) {
    for (int i=0; i<BOARDSIZE; i++)
      board.push_back(b.board[i]);
  }

  Board(Player player1, Player player2) {
    player1 = _player1;
    player2 = _player2;
    initBoard();
  }

  vector<int> getBoard() {
    return board;
  }

  bool makeMove(int move) {
    if (!isValidMove(move)) return false;
  }

  bool isValidMove(int move) {
    return move >= 0 && move < 9 && board[move] == 0; 
  }

  void print() {
    for (int i=0; i<3; i++) {
      for (int j=0; j<3; j++) {
        printf(" %d |", board[i*3+j]);
      }
      printf("\e[1D\e[0K\n---+---+---\n");
    }
    printf("\e[1A\e[0K");
  }
};

class User : public Player {
  int getMove(Board b) {
    while (true) {
      int move;
      cout << "Tile: ";
      cin >> move;
      if (b.isValidMove(move)) return move;
      cout << endl << "Invalid move\e[2A";
    }
  }
};

class CPU: public Player {
  int getMove(Board b) {

  }
};

int main() {
  printf("\e[2J\e[2;0HNumber of players: ");
  int selection;
  cin >> selection;
  if (selection > 2 || selection < 0) {
    cout << "Invalid choice" << endl;
    return -1;
  }

  Player *player1, *player2;

  if (selection == 0) {
    player1 = new CPU();
    player2 = new CPU();
  } else if (selection == 1) {
    player1 = new User();
    player2 = new CPU();
  } else {
    player1 = new User();
    player2 = new User();
  }

  Board main(player1, player2);
  main.print();

  delete player1;
  delete player2;
}