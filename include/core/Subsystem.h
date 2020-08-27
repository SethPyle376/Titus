//
// Created by seth on 8/25/20.
//

#ifndef TITUS_SUBSYSTEM_H
#define TITUS_SUBSYSTEM_H

#include <set>
#include <string>

template<class T>
class Subsystem {
protected:
    std::string type;
    std::set<T*> components;
public:
    void registerComponent(T* component) {
      components.insert(component);
    }

    void unregisterComponent(T* component) {
      components.erase(component);
    }

    virtual void update(float delta) = 0;
};

#endif //TITUS_SUBSYSTEM_H
