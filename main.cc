#include <iostream>

#include "animal_tree.h"

int main() {
  
  
  Animal_Tree tree("Lizard", "Does it have 4 limbs");

  bool ok = true;

  tree.load_data();
  while (ok) {
   std::cout << "Enter any key to play or type no if your done";
    std::string str;
    std::cin >> str;

    if (str == "nope") {
      ok = false;
    }
    tree.question();
  }

 tree.put_new_questions_in_data_base();
}