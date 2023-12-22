#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Node{
    
    public:

        Node(std::string value){
            value_ = value;
        }
    
        friend class Animal_Tree;

    private:

        std::string value_;
        std::shared_ptr<Node> left_child_ = nullptr;
        std::shared_ptr<Node> right_child_ = nullptr;
        bool animal = false;
};



class Animal_Tree {

    public: 
   
    Animal_Tree(std::string animal, std::string question){
       root_ = std::make_shared<Node>(question);
       root_->left_child_ = std::make_shared<Node>(animal);
       size_ = 1;
       root_->left_child_->animal = true;
    }

    
    
    
    
    void load_data(){
        std::ifstream database{ "data.txt" };

        std::shared_ptr curr = root_;


    }
    
    
    
    
    
    
    
    void add(std::string animal, std::string question, std::shared_ptr<Node> node, std::string direction){

        if (direction == "left"){
            node->right_child_= std::make_shared<Node>(node->value_);
            node->value_ = question;
            node->left_child_ = std::make_shared<Node>(animal);
            node->right_child_->animal = true;
            node->left_child_->animal = true;
            node->animal = false;
            }

        else if (direction == "right"){
            node->right_child_ = std::make_shared<Node>(question);
            node->right_child_->left_child_ = std::make_shared<Node>(animal);
            node->right_child_->left_child_->animal = true;
            }
     }




   void question(){
        std::cout << "*******************************************************" << '\n';
        std::cout << "Think of an animal and I will try to guess it" << '\n';
        std::cout << "*******************************************************" << '\n';
        bool traverse = true;
        std::shared_ptr curr = root_;
       
        std::vector<bool> path;
      
     
        int counter = 0;


        while(traverse)
            {
           
           if(curr->animal == true){
            std::cout << "Is the animal a " << curr->value_ << "? (y) for yes, (n) for no" << '\n';
           
            std::string answer;
            std::cin >> answer;

             if (answer == "y"){
           std::cout << "IT WAS FUN GUESSING" << '\n';
            return;
            }
            else
            {
                    std::cout << "This animal has not been added yet. What animal were you thinking of? " <<'\n';
                    std::string new_animal;
                    std::cin >> new_animal;
                    std::cout << "Enter a question that resembles the animal" << '\n';
                    std::string new_quest;
                    std::cin >> new_quest;
                   

                    //INPUTING DATA ON DATABASE
                 
                  data.push_back(new_animal);
                  data.push_back(new_quest);
                  
                    
                    for(auto move : path){
                         
                        if (move == false){
                    data.push_back("right");
                        }
                        else {
                    data.push_back("left");
                        }
                    }
                    
                    data.push_back("NEW_LINE_IND");
                   
                    

                    add(new_animal, new_quest, curr, "left");
                    return;
                    }

                
            }

            else {

            std::cout << curr->value_ << "? (y) for yes, (n) for no" << '\n';
            std::string answer;
            std::cin >> answer;

            if (answer == "y"){
                curr = curr->left_child_;
                path.push_back(true);
               

            }
            else if(answer == "n"){
                 if (curr->right_child_ == nullptr){
                    std::cout << "This animal has not been added yet. What animal were you thinking of? " <<'\n';
                    std::string new_animal;
                    std::cin >> new_animal;
                    std::cout << "Enter a question that resembles the animal" << '\n';
                    std::string new_quest;
                    std::cin >> new_quest;
                    path.push_back(false);

                    //release path into database
                  data.push_back(new_animal);
                  data.push_back(new_quest);
                  
                    
                    for(auto move : path){
                         
                        if (move == false){
                    data.push_back("right");
                        }
                        else {
                    data.push_back("left");
                        }
                    }
                    data.push_back("NEW_LINE_IND");


                    std::string direction = "right";
                    if (curr->animal == true){
                        direction = "left";
                    }
                    
                    add(new_animal, new_quest, curr, direction);
                    return;
                    }
                    curr = curr->right_child_;
                    path.push_back(false);
                    }
                    }
            }














          
                
               
                    
   }
    //prints all nodes in tree
    void print_tree(std::shared_ptr<Node> root) {
        if (!root){
            return;
        }
        std::cout << root->value_ << '\n';

         if (root->left_child_){
        print_tree(root->left_child_);
         }
        if (root->right_child_){
        print_tree(root_->right_child_);
        }
    }


        //returns root node
        std::shared_ptr<Node> root(){
            return root_;
        }


     
   
   
   std::vector<std::string> data;
    private:

        std::shared_ptr<Node> root_ = nullptr;
        size_t size_ = 0;
        
        


};