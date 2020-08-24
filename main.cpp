#include <iostream>
#include <Resources/Ref.h>
#include <Files/FileSystem.h>

#include "Resources/ResourceManager.h"
#include "Resources/TestResource.h"

int main() {

  {
    Ref<TestResource> resource = ResourceManager::getInstance()->getResource<TestResource>("test.mp3");
    {
      Ref<TestResource> secondResource = ResourceManager::getInstance()->getResource<TestResource>("test.mp3");
    }
  }

  File testFile = FileSystem::getInstance()->readFile("Resources:/test.txt");

  return 0;
}
