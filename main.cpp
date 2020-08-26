#include <iostream>
#include <resources/Ref.h>
#include <files/FileSystem.h>
#include <scene/Node.h>

#include "resources/ResourceManager.h"
#include "resources/TestResource.h"

#include "core/testing/TestSubsystem.h"

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


  Node* testNode = new Node();

  Node* testNode2 = new Node(testNode);
  Node* testNode3 = new Node(testNode);
  Node* testNode4 = new Node(testNode2);

  auto* testSubsystem = new TestSubsystem();
  auto* testComponent = new TestComponent();
  testSubsystem->registerComponent(testComponent);

  testNode4->addComponent(testComponent);

  testSubsystem->update(420);

  return 0;
}
