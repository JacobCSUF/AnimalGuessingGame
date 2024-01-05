#include <iostream>

#include "animal_tree.h"

int main() {
  Animal_Tree tree("Lizard", "Does it have 4 limbs");

  tree.load_data();
  while (true) {
    std::cout << "Enter any key to play or type (n) if your done: \n \n";
    std::string str;
    std::cin >> str;

    if (str == "n") {
      break;
    }
    tree.question();
  }

  std::cout << "Would you like to save any new animals/questions added this "
               "game for the next time it is run? ";
  std::cout << "Type (y) if yes: ";
  std::string load_data;
  std::cin >> load_data;
  if (load_data == "y") {
    tree.put_new_questions_in_data_base();
  }
}