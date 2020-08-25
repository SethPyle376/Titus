#include <iostream>
#include <resources/Ref.h>
#include <files/FileSystem.h>

#include "resources/ResourceManager.h"
#include "resources/TestResource.h"

int main() {

  {
    Ref<TestResource> resource = ResourceManager::getInstance()->getResource<TestResource>("resources:/test.mp3");
    {
      Ref<TestResource> secondResource = ResourceManager::getInstance()->getResource<TestResource>("resources:/test.mp3");
    }
  }

  File testFile = FileSystem::getInstance()->readFile("resources:/test.txt");

  std::string testString = FileSystem::getInstance()->readFileToString("resources:/test.txt");

  std::cout << "TEST STRING: " << testString << std::endl;

  return 0;
}
