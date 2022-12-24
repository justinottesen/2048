#include "Board.h"

Board::Board() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      board[i][j] = 0;
    }
  }
  score = 0;

  srand(time(NULL));
  add(2);
}

void Board::up() {
  bool merged_table[4][4]; // Tiles cant merge twice
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      merged_table[i][j] = false;
    }
  }
  bool change = false;
  for (int i = 1; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] == 0) continue;
      int k = i-1;
      while (k > 0 && board[k][j] == 0) k--;
      if (board[k][j] == 0) {
        board[k][j] = board[i][j];
        board[i][j] = 0;
        change = true;
      } else if (board[k][j] == board[i][j] && !merged_table[k][j]) {
        board[k][j] <<= 1;
        merged_table[k][j] = true;
        score += board[k][j];
        board[i][j] = 0;
        change = true;
      } else if (k != i-1) {
        board[k+1][j] = board[i][j];
        board[i][j] = 0;
        change = true;
      }
    }
  }
  if (change) add();
}

void Board::down() {
  bool merged_table[4][4]; // Tiles cant merge twice
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      merged_table[i][j] = false;
    }
  }
  bool change = false;
  for (int i = 2; i > -1; i--) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] == 0) continue;
      int k = i+1;
      while (k < 3 && board[k][j] == 0) k++;
      if (board[k][j] == 0) {
        board[k][j] = board[i][j];
        board[i][j] = 0;
        change = true;
      } else if (board[k][j] == board[i][j] && !merged_table[k][j]) {
        board[k][j] <<= 1;
        merged_table[k][j] = true;
        score += board[k][j] = 0;
        change = true;
      } else if (i != k+1) {
        board[k-1][j] = board[i][j];
        board[i][j] = 0;
        change = true;
      }
    }
  }
  if (change) add();
}

void Board::left() {
  bool merged_table[4][4]; // Tiles cant merge twice
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      merged_table[i][j] = false;
    }
  }
  bool change = false;
  for (int j = 1; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      if (board[i][j] == 0) continue;
      int k = j-1;
      while (k > 0 && board[i][k] == 0) k--;
      if (board[i][k] == 0) {
        board[i][k] = board[i][j];
        board[i][j] = 0;
        change = true;
      } else if (board[i][k] == board[i][j] && !merged_table[i][k]) {
        board[i][k] <<= 1;
        merged_table[i][k] = true;
        score += board[i][k];
        board[i][j] = 0;
        change = true;
      } else if (k != j-1) {
        board[i][k+1] = board[i][j];
        board[i][j] = 0;
        change = true;
      }
    }
  }
  if (change) add();
}

void Board::right() {
  bool merged_table[4][4]; // Tiles cant merge twice
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      merged_table[i][j] = false;
    }
  }
  bool change = false;
  for (int j = 2; j > -1; j--) {
    for (int i = 0; i < 4; i++) {
      if (board[i][j] == 0) continue;
      int k = j+1;
      while (k < 3 && board[i][k] == 0) k++;
      if (board[i][k] == 0) {
        board[i][k] = board[i][j];
        board[i][j] = 0;
        change = true;
      } else if (board[i][k] == board[i][j] && !merged_table[i][k]) {
        board[i][k] <<= 1;
        merged_table[i][k] = true;
        score += board[i][k];
        board[i][j] = 0;
        change = true;
      } else if (k != j+1) {
        board[i][k-1] = board[i][j];
        board[i][j] = 0;
        change = true;
      }
    }
  }
  if (change) add();
}

void Board::print(std::ostream& ostr) const {
  ostr << "SCORE: " << score;
  if (won()) ostr << "\t You won!";
  ostr << std::endl;
  ostr << "*************************************" << std::endl;
  for (int i = 0; i < 4; i++) {
    ostr << "*        *        *        *        *" << std::endl;
    for (int j = 0; j < 4; j++) {
      if (board[i][j] == 0) { ostr << "*        "; continue; }
      ostr << "* ";
      if (board[i][j] < 10) ostr << " ";
      if (board[i][j] < 1000) ostr << " ";
      if (board[i][j] < 100000) ostr << " ";
      ostr << board[i][j];
      if (board[i][j] < 100) ostr << " ";
      if (board[i][j] < 10000) ostr << " ";
      ostr << " ";
    }
    ostr << "*" << std::endl;
    ostr << "*        *        *        *        *" << std::endl;
    ostr << "*************************************" << std::endl;
  }
}

bool Board::checkStatus() const {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] == 0) return true;
    }
  }
  return false;
}

void Board::add(unsigned int num) {
  std::vector<std::pair<int, int>> open;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] == 0) open.push_back(std::make_pair(i, j));
    }
  }
  assert(open.size() >= num);
  std::random_shuffle(open.begin(), open.end());
  for (unsigned int n = 0; n < num; n++) {
    board[open[n].first][open[n].second] = (rand() % 2 + 1) << 1;
  }
}

bool Board::won() const {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] >= 2048) return true;
    }
  }
  return false;
}