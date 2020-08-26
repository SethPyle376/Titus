//
// Created by seth on 8/25/20.
//

#ifndef TITUS_COMPONENT_H
#define TITUS_COMPONENT_H

#include <string>

class Component {
public:
    virtual std::string getType() = 0;
};

#endif //TITUS_COMPONENT_H
