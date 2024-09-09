/*
* We can't include defined functions without static
* include just copy and pastes code so we get linker collision
* 
* Made files static so definitions are contained to each file
* NOTE: This affects builds: compiler will not see binary changes in include
* files past initial compilations w/ include statement present
* Only fix is to remove includes, get a clean compilation, & bring back includes
*/
#include "./FileStuff.cpp"
#include "./BitShifting.cpp"

#include "./LinkedList.cpp"
#include <thread>
#include <chrono>
#include <queue>

using namespace std::chrono_literals;
int main () {

    FileCreation();
    FileExecutor();
    {
        LinkedList::LinkedList linked_list = LinkedList::LinkedList();

        linked_list.addNode('a');
        linked_list.addNode('b');
        linked_list.addNode('c');

        linked_list.popNode();
        linked_list.popNode();

        linked_list.addNode('d');
        linked_list.addNode('e');
    }
    //////////////////////////////////////////
    // Preformance Test for Linked List /////
    /////////////////////////////////////////

    LinkedList::LinkedList linked_list = LinkedList::LinkedList();
    std::cout << "\nStarting LinkedList\n";
    

    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10'000'000; ++i) {
        linked_list.addNode('a');
    }


    std::chrono::time_point<std::chrono::high_resolution_clock> m_end_time = std::chrono::high_resolution_clock::now();

    // Ref: https://stackoverflow.com/questions/7889136/stdchrono-and-cout
    // Ref: https://www.youtube.com/watch?v=YG4jexlSAjc&ab_channel=TheCherno
    std::cout << "Time elapsed: " << (float)(std::chrono::duration_cast<std::chrono::milliseconds>(m_end_time - m_start_time).count()) / 100 << " seconds\n"; //idfk, its for testing, not design practice 

    std::cout <<"Starting Queue\n";
    std::queue<char> m_queue;
    m_start_time = std::chrono::high_resolution_clock::now(); //If i really cared id make this a function, better yet a wrapper function
    for (int i = 0; i < 10'000'000; ++i) {
        m_queue.push('a');
     }

    m_end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Time elapsed: " << (float)(std::chrono::duration_cast<std::chrono::milliseconds>(m_end_time - m_start_time).count()) / 100 << " seconds\n"; //idfk, its for testing, not design practice 


    // Welp...found out LL is wayyyyyyyyyy faster 
    // Further Reading: https://stackoverflow.com/questions/41102465/why-does-stdqueue-use-stddequeue-as-underlying-default-container (Seems kinda BS to me)
    // #2: https://stackoverflow.com/questions/51266104/c-default-implementation-of-stack-and-queue - Sounds like main reason is reusage, idk man and idc, testing for this use case proves otherwise

    //////////////////////////////////////////////
    // Preformance Test for Linked List #2  /////
    ////////////////////////////////////////////
    std::cout << "\nStarting Linked List with deletions \n";
    LinkedList::LinkedList m_linked_list_2 = LinkedList::LinkedList();
    m_start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 5'000'000; ++i) { 
        m_linked_list_2.addNode('a');
    }
    for (int i = 0; i < 3'000'000; ++i) {
        m_linked_list_2.popNode();
    }
    for (int i = 0; i < 5'000'000; ++i) {
        m_linked_list_2.addNode('b');
    }
    for (int i = 0; i < 6'000'000; ++i) {
        m_linked_list_2.popNode();
    }
    m_end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Time elapsed: " << (float)(std::chrono::duration_cast<std::chrono::milliseconds>(m_end_time - m_start_time).count()) / 100 << " seconds\n"; 
    //////////////////////////////////////////////////////////////
    std::cout << "Starting Queue with deletions \n";
    std::queue<char> m_queue_2;
    m_start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 5'000'000; ++i) {
        m_queue_2.push('a');
    }
    for (int i = 0; i < 3'000'000; ++i) {
        m_queue_2.pop();
    }
    for (int i = 0; i < 5'000'000; ++i) {
        m_queue_2.push('b');
    }
    for (int i = 0; i < 6'000'000; ++i) {
        m_queue_2.pop();
    }
    m_end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Time elapsed: " << (float)(std::chrono::duration_cast<std::chrono::milliseconds>(m_end_time - m_start_time).count()) / 100 << " seconds\n";


    // Gawd Daymeeeee!!! This is even worse!!!! LL outpreforms by >= 2x EVERY TIME!!

    //Main Takeaway:
    // 1. NOTHING MATTERS BELOW 1'000'000. Small numbers are so insignificant, preformance gains are near non-existent
    // 2. Use the right tools for the job. DSA is EXTREMELY IMPORTANT for large data sets. consider O(n), malloc calls, & instruction calls in general
    return 0;
}