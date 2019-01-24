#include "Engine/Artemis.h"
#include "Engine/Game.h"
#include "Engine/Systems/DebugSystem.h"
#include "Math/Vectors/Vec2.h"
#include "MyLevel.h"
#include <iostream>
#include <vector>

void TestPromise();
void TestQuaternion();

int main() {
  TestPromise();
  TestQuaternion();
  std::vector<Kepler::EntitySystem *> systems;
  systems.push_back(new Kepler::DebugSystem());
  Kepler::Game::Create<MyLevel>(systems);
  return 0;
}
