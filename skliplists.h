#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <mutex>

std::mutex mtx;

template<typename K,typename V>
class Node{
    public:
        Node() {}
        ~Node();

        Node(K k,V v,int);

        K get_key() const;

        V get_value() const;

        void set_value(V);

        Node<K,V>** forward; //双重指针,在函数外部定义一个指针p，在函数内给指针赋值，函数结束后对指针p生效，那么我们就需要二级指针。

        int node_level;
    
    private:
        K key;
        V value;
};


template<typename K,typename V>
Node<K,V>::Node(K k,V v,int level){
    this->key = k;
    this->val = v;
    this->node_level = level;

    this->forward = new Node<K,V>*[level+1];

    memset(forward, 0 , sizeof(Node<K,V>**(level+1))); 
}


template<typename K,typename V>
Node<K,V>::~Node(){
    delete []forward;
}


template<typename K,typename V>
K Node<K,V>::get_key() const{
    return this->key;
}

template<typename K,typename V>
V Node<K,V>::get_value() const{
    return this->value;
}

template<typename K,typename V>
void Node<K,V>::set_value(V value){
    this->value = value;
}


template<typename K,typename V>
class SkipList{
    public:
        SkipList(int);
        ~SkipList();

        Node<K,V>* create_node(K,V,int);
        int insert_element(K,V);
        bool search_element(K);
        int get_random_level();
        bool delete_element(K);
        int size();
    
    private:
        int max_level;
        int _skipList_level;
        int _element_count;

        Node<K,V>* _header;
};

template<typename K,typename V>
SkipList<K,V>::SkipList(int level){
    this->max_level = level;
    this->_skipList_level = 0;
    this->_element_count = 0;

    K k;
    V v;
    this->_header = new Node<K,V>(k,v,max_level);
};

template<typename K,typename V>
SkipList<K,V>::~SkipList(){
    delete _header;
}

template<typename K,typename V>
Node<K,V>* SkipList<K,V>::create_node(K k,V v,int level){
    Node<K,V>* n = new Node<K,V>(k,v,level);
    return n;
}

template<typename K,typename V>
int SkipList<K,V>::size(){
    return _element_count;
}

template<typename K,typename V>
int SkipList<K,V>::get_random_level(){
    int k=1;
    while(rand() % 2) k++;
    return k < max_level?k:max_level;
}

template<typename K,typename V>
int SkipList<K,V>::insert_element(K k,V v){

}

template<typename K,typename V>
bool SkipList<K,V>::search_element(K k){

}

template<typename K,typename V>
bool SkipList<K,V>::delete_element(K k){
    
}


