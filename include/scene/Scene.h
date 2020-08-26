//
// Created by seth on 8/25/20.
//

#ifndef TITUS_SCENE_H
#define TITUS_SCENE_H

#include "Node.h"

class Scene {
private:
    Node* root;
public:
    explicit Scene(Node* root) {
      this->root = root;
    }
};

#endif //TITUS_SCENE_H
