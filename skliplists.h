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
Node<K,V>::Node(K k,V v,int level){ //跳表节点
    this->key = k;
    this->val = v;
    this->node_level = level;//节点层数

    this->forward = new Node<K,V>* [level+1];//前进指针

    memset(forward, 0 , sizeof(Node<K,V>*)*(level+1)); 
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

        Node<K,V>* _header; //头节点
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
    while(rand() % 2) k+=1;
    return k < max_level?k:max_level;
}

template<typename K,typename V>
int SkipList<K,V>::insert_element(K key,V value){  //跳表的插入操作
    mtx.lock();


    Node<K,V>* current = this->_header;
    Node<K,V>* update[max_level+1];
    
    memset(update,0,sizeof(Node<K,V>*)*(max_level+1));

    
    for(int i = _skipList_level - 1;i >= 0 ;i--){
        while(current->forward[i] != nullptr && current->forward[i]->get_key() < key){
            current = current->forward[i];
        }
        update[i]=current;
    }

    current = current->forward[0];

    if(current != nullptr && current->get_key() == key){
        std::cout << "the key " << key << " exists"<<endl;
        mtx.unlock();
        return 1;
    }

    if(current == nullptr || current->get_key() != key){
        int random_level = get_random_level();
        Node<K,V> inserted_node = create_node(key,value,random_level);

        if(random_level > _skipList_level){
            for(int i = _skipList_level+1 ;i < random_level;i++){
                update[i] = _header;
            }
            _skipList_level = random_level;
        }

        for(int i = 0; i <= _skipList_level; i++){
            inserted_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = inserted_node;
        }

        std::cout << "Successfully insert key "<< key << "the value " << value <<endl;
        ++_element_count;        
    }

    mtx.unlock();
    return 0;
}

template<typename K,typename V>
bool SkipList<K,V>::search_element(K key){

}

template<typename K,typename V>
bool SkipList<K,V>::delete_element(K key){
    mtx.lock();

    Node<K,V>* current = this->_header;

    Node<K,V>* update[max_level+1];
    memset(update,0,sizeof(Node<K,V>*)*(max_level+1));

    for(int i=_skipList_level-1;i>=0;i--){
        while(current->forward[i] != nullptr && current[i]->forward[i]->get_key() < key){
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if(current != nullptr && current->get_key() == key){
        for(int i=0;i<=_skipList_level;i++){
            if(update[i]->forward[i] != current) break;

            update[i]->forward[i] = current->forward[i];
        }

        while(_skipList_level > 0 && _header->forward[_skipList_level]){
            _skipList_level--;
        }
        std<<cout << "Successfully delete key "<<key<<endl;
        --_element_count;
        return true;
    }
    return false;
    mtx.unlock();
    
}


