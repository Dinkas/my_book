#include "LinkedList.hpp"
#include "AddressBook.hpp"
#include <iostream>

using namespace std;

template class LinkedListType<float>;
template class LinkedListType<AddressBook>;
template struct NodeType<AddressBook>;

template<class T>
LinkedListType<T>::LinkedListType()
{
    length = 0;
    listData = nullptr;
    currentItem = nullptr;
    int currentItemIndex = 0;
}

template<class T>
LinkedListType<T>::~LinkedListType()
{
    if (listData == nullptr)
        return;
    NodeType<T>* tmpptr = listData->next;
    while (listData != tmpptr)
    {
        tmpptr = tmpptr->next;
        delete tmpptr->back;
    }
    delete listData;
}

template<class T>
NodeType<T>* LinkedListType<T>::FindItem(T item, bool& found)
{
    found = false;
    if (listData == nullptr)
        return nullptr;

    NodeType<T>* location = listData->next;

    while (true)
    {
        if (location ->info == item)
        {
            found = true;
            return location;
        }

        else if (item < location->info)
            return location->back;

        else if (location == listData)
            return location->next;

        location = location ->next;
        //#DEBUG cout << "Finding " << item << endl;
    }
}

template<class T>
T LinkedListType<T>::SearchList(T item)
{
    bool found;
    NodeType<T>* location = LinkedListType::FindItem(item,found);
    if (found == false)
        throw ItemNotFoundException();
    else
        return location ->info;
}

template<class T>
void LinkedListType<T>::PutItem(T item)
{
    NodeType<T>* itemNode = new NodeType<T>;
    itemNode->info = item;
    if (listData == nullptr)
    {
        listData = itemNode;
        listData->next = listData;
        listData->back = listData;
        length++;
        //#DEBUG cout << "First item added" << endl;
    }
    else if (listData->info < item)
    {
        itemNode ->next = listData ->next;
        (listData->next)->back = itemNode;
        itemNode ->back = listData;
        listData ->next = itemNode;
        listData = itemNode;
        length++;
        //#DEBUG cout <<"Item added to last slot" << endl;
    }
    else
    {
        bool found;
        NodeType<T>* location = LinkedListType::FindItem(item,found);
        //#DEBUG cout << "Next smaller number:" << location->info;
        if (found == true)
            throw DuplicateItemException();
        else
        {
            itemNode ->next = location ->next;
            (location->next)->back = itemNode;
            itemNode ->back = location;
            location ->next = itemNode;
            length++;
            //#DEBUG cout << "Item added in middle" << endl;
        }
    }
    //#DEBUG cout << "Length: " << length << endl;
}

template<class T>
void LinkedListType<T>::DeleteItem(T item)
{
    bool found;
    NodeType<T>* location = LinkedListType::FindItem(item,found);
    if (found == false)
        throw ItemNotFoundException();

    else
    {
        if (location == listData)
            listData = location->back;
        (location->next)->back = location->back;
        (location->back)->next = location->next;
        delete location;
        length--;
        if (length == 0)
            listData = nullptr;
    }
}

template<class T>
int LinkedListType<T>::GetLength() const
{
    return length;
}

template<class T>
T LinkedListType<T>::GetFirstItem()
{
    if (listData == nullptr)
        throw EmptyListException();
    else
    {
        currentItem = listData->next;
        currentItemIndex = 1;
        //#DEBUG cout << "first item got" << endl;
        return (currentItem ->info);
    }
}

template<class T>
T LinkedListType<T>::GetNextItem()
{
    currentItem = currentItem->next;
    if (currentItemIndex == length)
        currentItemIndex = 0;
    currentItemIndex++;
    //#DEBUG cout << "next item got" << endl;
    return (currentItem->info);
}

template<class T>
T LinkedListType<T>::GetPreviousItem()
{
    currentItem = currentItem->back;
    currentItemIndex--;
    if (currentItemIndex == 0)
        currentItemIndex = length;
    return (currentItem->info);
}

template<class T>
int LinkedListType<T>::GetCurrentIndex()
{
    return currentItemIndex;
}
