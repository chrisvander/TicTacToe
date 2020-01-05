/**
  * Created by Chris Vanderloo on 1/4/2020
  */

#include <iostream>
#include <vector>

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
  int currentPlayer;
public:
  void initBoard() {
    currentPlayer = 1;
    for (int i=0; i<9; i++)
      board.push_back(0);
  }

  Board() {
    initBoard();
  }

  Board(Board& b) {
    currentPlayer = 1;
    for (int i=0; i<9; i++)
      board.push_back(b.board[i]);
  }

  Board(Player *_player1, Player *_player2) {
    player1 = _player1;
    player2 = _player2;
    initBoard();
  }

  vector<int> getBoard() {
    return board;
  }

  void nextMove() {
    if (currentPlayer == 1) makeMove(player1->getMove(*this));
    else makeMove(player2->getMove(*this));
    currentPlayer = currentPlayer % 2 + 1;
  }

  bool makeMove(int move) {
    if (!isValidMove(move)) return false;
    board[move] = currentPlayer;
  }

  bool isValidMove(int move) {
    return move >= 0 && move < 9 && board[move] == 0; 
  }

  // returns 0 if no one has won
  // 1 for player 1
  // 2 for player 2
  int hasWon() {
    int a[2] = { 1, 2 };
    for (int p : a) {
      int conditions[8][3] = 
        { {0,1,2},
          {3,4,5},
          {6,7,8},
          {0,3,6},
          {1,4,7},
          {2,5,8},
          {2,4,6},
          {0,4,8} };
      for (auto &condition : conditions) {
        bool won = true;
        for(auto &part : condition) {
          won = won && board[part] == p;
        }
        if (won) return p;
      }
    }
    return 0;
  }

  void print() {
    printf("\n");
    for (int i=0; i<3; i++) {
      for (int j=0; j<3; j++) {
        int state = board[i*3+j];
        printf(" %c |", state == 0 ? ' ' : state == 1 ? 'X' : 'O');
      }
      printf("\e[1D\e[0K\n---+---+---\n");
    }
    printf("\e[1A\e[0K\n");
  }
};

class User : public Player {
  int getMove(Board b) {
    while (true) {
      int move;
      cout << "Tile: ";
      cin >> move;
      if (b.isValidMove(move-1)) return move-1;
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
  int winningPlayer = 0;
  while (true) {
    main.print();

    winningPlayer = main.hasWon();
    if (winningPlayer != 0) break;

    main.nextMove();
  }

  printf("Player %d won!", winningPlayer);

  delete player1;
  delete player2;
}