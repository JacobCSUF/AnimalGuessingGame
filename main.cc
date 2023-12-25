#include <iostream>

#include "animal_tree.h"

int main() {
  
  
  Animal_Tree tree("Lizard", "Does it have 4 limbs");

  bool ok = true;

  tree.load_data();
  while (ok) {
   std::cout << "Enter any key to play or enter "no" to quit"
    std::string str;
    std::cin >> str;

    if (str == "no") {
      ok = false;
    }
    tree.question();
  }

  std::ofstream jimmy{"data.txt"};

  int newline_ind = 0;
  for (auto text : tree.data) {
    jimmy << text << " ";
    if (text == "NEW_LINE_IND") {
      newline_ind += 1;
    } else if (newline_ind == 1) {
      newline_ind += 1;
    } else if (newline_ind == 2) {
      jimmy << '\n';
      newline_ind = 0;
    }
  }
}