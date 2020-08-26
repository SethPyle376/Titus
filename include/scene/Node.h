//
// Created by seth on 8/25/20.
//

#ifndef TITUS_NODE_H
#define TITUS_NODE_H

#include <vector>
#include <set>

#include "glm/glm.hpp"

class Node {
private:
  Node* parent = nullptr;
  std::set<Node*> children;
  glm::mat4 localTransform;

  void notifyChildCreation(Node* child);
  void notifyChildDeath(Node* child);
public:
  Node();
  explicit Node(const glm::mat4& transform);
  explicit Node(Node* parent);
  Node(Node* parent, const glm::mat4& transform);
  ~Node();
};

#endif //TITUS_NODE_H
