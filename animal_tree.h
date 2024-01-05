#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Node {
 public:
  Node(std::string value) { value_ = value; }

  friend class Animal_Tree;

 private:
  std::string value_;
  std::shared_ptr<Node> left_child_ = nullptr;
  std::shared_ptr<Node> right_child_ = nullptr;
  bool animal = false;
};



class Animal_Tree {
 public:
  // Initializes tree with a question and an animal
  Animal_Tree(std::string animal, std::string question) {
    root_ = std::make_shared<Node>(question);
    root_->left_child_ = std::make_shared<Node>(animal);
    root_->left_child_->animal = true;
  }

  // Loads the animal tree with information from a text file
  // The location of each question/animal is determined by its
  // "left" and "right" sequence on the database
  void load_data() {
    std::ifstream path_desript{"data.txt"};
    std::string info;

    // Push back all the information on the database to be used in determining
    // where each question/animal node goes
    while (path_desript.good()) {
      path_desript >> info;
      data_in_.push_back(info);
    }

    // If the node goes right or left traverse there
    std::shared_ptr<Node> curr = root_;
    for (int i = 0; i < data_in_.size(); i++) {
      if ((data_in_.at(i) == "right") && (curr->right_child_ != nullptr)) {
        curr = curr->right_child_;
      }

      if ((data_in_.at(i) == "left") && (curr->left_child_ != nullptr)) {
        curr = curr->left_child_;
      }

      // "New_LINE_IND" indicates that the the curr node
      // reached the location where the question/animal should be
      // and that they can now be added to the tree

      if (data_in_.at(i) == "NEW_LINE_IND") {
        if (curr->left_child_ != nullptr) {
          add(data_in_.at(i + 1), data_in_.at(i + 2), curr, "right");
        } else {
          add(data_in_.at(i + 1), data_in_.at(i + 2), curr, "left");
        }
 curr = root_;
      }
    }
  }

  
  
  // Save any new questions/animals it learned during current session onto text
  // file for future session
  void put_new_questions_in_data_base() {
    std::ofstream text_file{"data.txt"};
    int newline_ind = 0;
    for (auto text : data_in_) {
      text_file << text << " ";
      if (text == "NEW_LINE_IND") {
        newline_ind += 1;
      } else if (newline_ind == 1) {
        newline_ind += 1;
      } else if (newline_ind == 2) {
        text_file << '\n';
        newline_ind = 0;
      }
    }
  }

  
  
  // Main function of the tree which asks users to think of an animal
  void question() {
    std::cout << "***********************************************" << '\n';
    std::cout << "Think of an animal and I will try to guess it" << '\n';
    std::cout << "***********************************************" << '\n'
              << '\n';
    std::shared_ptr<Node> curr = root_;
    std::vector<bool> path;
    while (true) {
      
      // If the current node is an animal ask the user if they are thinking of
      // whatever the animal on the node it
      if (curr->animal == true) {
        std::cout << "Is the animal a " << curr->value_
                  << "? (y) for yes, (n) for no" << '\n';
        std::string answer;
        std::cin >> answer;

        // If the animal is correct end the current game
        if (answer == "y") {
          std::cout << "I KNEW IT. THANKS FOR PLAYING!" << '\n';
          return;

          // If the animal isn't correct input the new animal and question in
          // the game and on the database
        } else if (answer == "n") {
          insert_new_animal(path, "no", curr);
          return;
        }
      }

      // If the current node is a question ask whether the question is yes or no
      // for whatever animal the person is thinking of
      else {
        std::cout << curr->value_ << "? (y) for yes, (n) for no" << '\n';
        std::string answer;
        std::cin >> answer;

        // If the answer is yes traverse to the left child and idicate that the
        // path is left on the database by pushing back true
        if (answer == "y") {
          curr = curr->left_child_;
          path.push_back(true);

          // If the answer is no and there is no question/animal on the right
          // child ask the user to input their animal and a question to go along
          // with it or traverse to the right child if there is a
          // question/animal
        } else if (answer == "n") {
          if (curr->right_child_ == nullptr) {
            insert_new_animal(path, "yes", curr);

            return;
          }

          curr = curr->right_child_;
          path.push_back(false);
        }
      }
    }
  }




 private:
  std::shared_ptr<Node> root_ = nullptr;
  std::vector<std::string> data_in_;

 
 
  // helper functions

  // inserts path of yes/no questions to animal in a vector
  void insert_new_animal(std::vector<bool> path, std::string right,
                         std::shared_ptr<Node> node) {
    std::cout << "This animal has not been added yet. What animal were "
                 "you thinking of? "
              << '\n';
    std::string animal;
    std::cin >> animal;
    std::cout << "Enter a question that resembles the animal" << '\n';
    std::string question;
    std::cin >> question;

    std::string direction = "left";

    if (right == "yes") {
      path.push_back(false);

      if (node->animal != true) {
        direction = "right";
      }
    }

    for (auto move : path) {
      if (move == false) {
        data_in_.push_back("right");
      } else {
        data_in_.push_back("left");
      }
    }

    data_in_.push_back("NEW_LINE_IND");
    data_in_.push_back(animal);
    data_in_.push_back(question);

    add(animal, question, node, direction);
    std::cout << "Animal and question added to game" << '\n' << '\n';
  }

  
  
  // Adds an animal and a question to the tree
  void add(std::string animal, std::string question, std::shared_ptr<Node> node,
           std::string direction) {
    if (direction == "left") {
      node->right_child_ = std::make_shared<Node>(node->value_);
      node->value_ = question;
      node->left_child_ = std::make_shared<Node>(animal);
      node->right_child_->animal = true;
      node->left_child_->animal = true;
      node->animal = false;
    }

    else if (direction == "right") {
      node->right_child_ = std::make_shared<Node>(question);
      node->right_child_->left_child_ = std::make_shared<Node>(animal);
      node->right_child_->left_child_->animal = true;
    }
  }
};