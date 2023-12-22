#include <iostream>
#include "animal_tree.h"


int main(){





    Animal_Tree tree("dog", "Does it have 4 legs");

   bool ok = true;

while (ok){
    
    std::cout << "DO U WANT TO PLAY ";
    std::string str;
    std::cin >> str;
    if (str == "yes"){
        ok = false;
    }
    tree.question();

}

std::ofstream jimmy{"data.txt"};
for (auto text : tree.data){
    jimmy << text << " ";
    if (text == "NEW_LINE_IND"){
    jimmy << '\n';
    }

}






  
}