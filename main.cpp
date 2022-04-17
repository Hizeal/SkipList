#include <iostream>
#include <string>
#include "skliplists.h"


int main(){
    SkipList<int,std::string> skiplist(6);
    skiplist.insert_element(1,"test1");
    skiplist.insert_element(2,"test2");
    skiplist.insert_element(3,"test3");
    skiplist.insert_element(4,"test4");
    skiplist.insert_element(5,"test5");
    skiplist.insert_element(6,"test6");

    std::cout << "skiplist.size(): "<<skiplist.size() << std::endl;
    
    skiplist.search_element(1);
    skiplist.search_element(2);

    skiplist.delete_element(4);

    std::cout << "skiplist.size(): "<<skiplist.size() << std::endl;    
}