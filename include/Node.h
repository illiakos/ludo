// Node.h
#ifndef NODE_H
#define NODE_H

#include "Event.h"
#include <memory>

struct Node {
    std::unique_ptr<Event> event;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node(std::unique_ptr<Event> ev) : event(std::move(ev)) {}
};

#endif
