//
// Created by seth on 8/25/20.
//

#include "scene/Node.h"

Node::Node() {
  this->localTransform = glm::mat4(1.0f);
}

Node::Node(const glm::mat4& transform) {
  this->localTransform = transform;
}

Node::Node(Node *parent) {
  this->parent = parent;
  parent->notifyChildCreation(this);
  this->localTransform = parent->localTransform;
}

Node::Node(Node *parent, const glm::mat4 &transform) {
  this->parent = parent;
  parent->notifyChildCreation(this);
  this->localTransform = parent->localTransform * transform;
}

Node::~Node() {
  if (parent != nullptr) {
    parent->notifyChildDeath(this);
  }
  std::set<Node*> tempChildrenList = children;
  for (Node* child : tempChildrenList) {
    delete child;
  }
}

void Node::notifyChildCreation(Node *child) {
  this->children.insert(child);
}

void Node::notifyChildDeath(Node *child) {
  auto it = this->children.find(child);
  children.erase(it);
  return;
}