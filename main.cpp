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
    
    return 0;
}