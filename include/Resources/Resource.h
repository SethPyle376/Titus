//
// Created by seth on 8/23/20.
//

#ifndef TITUS_RESOURCE_H
#define TITUS_RESOURCE_H

#include <string>

class Resource {
public:
    virtual ~Resource() {}
    std::string path;
    virtual void init(std::string) = 0;
    virtual void destroy() = 0;
};

#endif //TITUS_RESOURCE_H
