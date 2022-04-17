#include <iostream>
#include <pthread.h>
#include <chrono>
#include <time.h>
#include "../skliplists.h"

#define NUM_THREADS 5
#define TEST_COUNTS 100000

SkipList<int,std::string> skiplist(18);

void* insertElem(void* threadid){
    long tid;
    tid = (long)threadid;

    std::cout<<tid<<std::endl;
    int epochs = TEST_COUNTS / NUM_THREADS;

    for(int i=tid*epochs,count = 0;count<epochs;i++){
        count++;
        skiplist.insert_element(rand() % TEST_COUNTS,"");
    }
    pthread_exit(NULL);
}

int main(){
    srand(time(NULL));
    {
        pthread_t PTHREAD_NUMS[NUM_THREADS];

        int rc;
        int i;

        auto start = std::chrono::high_resolution_clock::now();

        for(i=0;i<NUM_THREADS;i++){
            std::cout<< "main(): creating thread."<<i<<std::endl;
            rc = pthread_create(&PTHREAD_NUMS[i],NULL,insertElem,(void*)i);
            if(rc){
                std::cout<<"Error:unable to create Thread"<<std::endl;
                exit(-1);
            }
        }

        void* ret;
        for(i = 0;i<NUM_THREADS;i++){
            if(pthread_join(PTHREAD_NUMS[i],&ret) != 0){
                perror("pthread_create() error");
                exit(0);
            }
        }

        auto last = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> Dur = last-start;

        std::cout<<"insert elapsed: " << Dur.count() <<std::endl;

    }

    pthread_exit(NULL);
}