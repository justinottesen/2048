#include "Board.h"

#include <iostream>
#include <cctype>

int main() {
  std::cout << std::endl;
  Board b;
  
  char input = 0;
  while (b.checkStatus() && input != 'Q') {
    b.print(std::cout);
    std::cin >> input;
    input = toupper(input);
    switch (input) {
      case 'W': b.up(); break;
      case 'A': b.left(); break;
      case 'S': b.down(); break;
      case 'D': b.right(); break;
      case 'Q': exit(0); break;
      default:
        std::cout << "INVALID INPUT: USE WASD KEYS" << std::endl;
        continue;
    }
  }

  return 0;
}