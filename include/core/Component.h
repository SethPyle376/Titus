//
// Created by seth on 8/25/20.
//

#ifndef TITUS_COMPONENT_H
#define TITUS_COMPONENT_H

#include <string>

#include "scene/Node.h"

class Component {
private:
    Node* parentNode = nullptr;
public:
    virtual ~Component() {
      if (parentNode != nullptr) {
        parentNode->removeComponent(this);
      }
    }

    bool hadParentNode() {
      return parentNode != nullptr;
    }

    Node* getParentNode() {
      return parentNode;
    }

    void setParentNode(Node* node) {
      this->parentNode = node;
    }

    void removeParentNode() {
      this->parentNode = nullptr;
    }
};

#endif //TITUS_COMPONENT_H
