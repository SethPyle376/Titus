#include <iostream>

#define VOLK_IMPLEMENTATION
#include "volk.h"

#include "resources/Ref.h"
#include "files/FileSystem.h"
#include "scene/Node.h"

#include "resources/ResourceManager.h"
#include "resources/TestResource.h"

#include "core/Config.h"
#include "core/testing/TestSubsystem.h"

#include "rendering/RenderSubsystem.h"
#include "rendering/vulkan/resources/VulkanMaterial.h"

int main() {
  Config::load("resources:/testConfig.json");
  std::cout << Config::globalConfig["testElement"].get<std::string>() << std::endl;
  std::cout << Config::globalConfig["testParent"]["testChild"].get<std::string>() << std::endl;

  File testFile = FileSystem::getInstance()->readFile("resources:/test.txt");

  std::string testString = FileSystem::getInstance()->readFileToString("resources:/test.txt");

  std::cout << "TEST STRING: " << testString << std::endl;


  Node* testNode = new Node();

  Node* testNode2 = new Node(testNode);
  Node* testNode3 = new Node(testNode);
  Node* testNode4 = new Node(testNode2);

  auto* testComponent = new TestComponent();

  testNode2->addComponent(testComponent);

  TestSubsystem::getInstance()->update(123);

  RenderComponent testRenderComponent;
  UiComponent testUiComponent;

  RenderSubsystem::getInstance()->update(123);

  auto* testMaterial = ResourceManager::getInstance()->getResource<VulkanMaterial>("resources:/testMaterial.json");
  delete testMaterial;

  return 0;
}
