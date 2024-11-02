// EventList.h
#ifndef EVENTLIST_H
#define EVENTLIST_H

#include "Node.h"
#include <memory>

class EventList {
public:
  EventList() : head(nullptr), tail(nullptr) {}

  void pushFront(std::unique_ptr<Event> event) {
    Node *newNode = new Node(std::move(event));
    if (!head) {
      head = tail = newNode;
    } else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
  }

  void pushBack(std::unique_ptr<Event> event) {
    Node *newNode = new Node(std::move(event));
    if (!tail) {
      head = tail = newNode;
    } else {
      newNode->prev = tail;
      tail->next = newNode;
      tail = newNode;
    }
  }

  // Remove the front node and return it for processing
  std::unique_ptr<Event> popFront() {
    if (!head)
      return nullptr;
    Node *oldHead = head;
    std::unique_ptr<Event> event = std::move(oldHead->event);
    head = head->next;
    if (head)
      head->prev = nullptr;
    else
      tail = nullptr; // list is now empty
    delete oldHead;
    return event;
  }

  // Move the current player node from the front to the back
  void rotateTurn() {
    if (!head || !head->next)
      return; // Only one element
    Node *oldHead = head;
    head = head->next;
    head->prev = nullptr;

    // Move old head to the back
    tail->next = oldHead;
    oldHead->prev = tail;
    oldHead->next = nullptr;
    tail = oldHead;
  }

  bool empty() const { return head == nullptr; }

private:
  Node *head;
  Node *tail;
};

#endif
