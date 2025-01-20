#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP


//using namespace std;

template<class T>
struct NodeType
{
    T info;
    NodeType<T>* next;
    NodeType<T>* back;
};

// Error thrown if a duplicated item is added to the list
class DuplicateItemException
{};

// Error thrown if item is searched for in the list but not found
class ItemNotFoundException
{};

// Error thrown if actions are attempted on an empty list
class EmptyListException
{};


template<class T>
class LinkedListType
{
public:
    LinkedListType();
    ~LinkedListType();
    T SearchList(T item);
    void PutItem(T item);
    void DeleteItem(T item);
    int GetLength() const;
    T GetFirstItem();
    T GetNextItem();
    T GetPreviousItem();
    int GetCurrentIndex();

private:
    NodeType<T>* FindItem(T item, bool& found);
    int length;
    NodeType<T>* listData;
    NodeType<T>* currentItem;
    int currentItemIndex; //Keeps track of number/total records to enable browsing.
};

#endif // LINKEDLIST_HPP
