#ifndef Game_h
#define Game_h

#include "Artemis.h"
#include "Engine/Rendering/Window.h"
#include "World/Actor.h"
#include "World/Level.h"
#include <map>
#include <thread>
#include <vector>

namespace Kepler {

typedef std::vector<EntitySystem *> tESIter;

class Game {
public:
  float currentTime = 0;

private:
  Window *window;
  World &world;
  Level *level;
  SystemManager *sm;
  EntityManager *em;
  std::vector<EntitySystem *> systems;
  std::map<std::string, Actor *> actors;
  bool isRunning = true;

public:
  Game(World &world, Level *level, SystemManager *sm, EntityManager *em);
  void Launch();
  void Run() {
    using namespace std::chrono_literals;
    using clock = std::chrono::high_resolution_clock;
    auto oldTime = clock::now();
    while (!window->ShouldClose()) {
      window->RenderBegin();
      {
        auto newTime = clock::now();
        std::chrono::microseconds deltamicroseconds =
            std::chrono::duration_cast  //
            <std::chrono::microseconds> //
            (newTime - oldTime);
        float deltaTime = deltamicroseconds.count() / 1000000.0;
        oldTime = newTime;
        world.LoopStart();
        world.SetDelta(deltaTime);
        for (auto i : systems) {
          i->Process();
        }
      }
      window->RenderEnd();
      window->PollEvents();
      std::this_thread::sleep_for(1ms);
    }
  }
  template <class L> static void Create(std::vector<EntitySystem *> systems) {
    World world;
    SystemManager *sm = world.GetSystemManager();
    EntityManager *em = world.GetEntityManager();
    Level *level = new L(em);
    Game game(world, level, sm, em);
    // Add systems
    game.systems = systems;
    for (auto i : systems) {
      sm->SetSystem(i);
    }
    game.Launch();
    game.Run();
  }
  template <class L> static void Create() {
    std::vector<EntitySystem *> systems;
    Create<L>(systems);
  }
  Game *AddActor(Actor *actor);
  Actor *GetActor(std::string name);
  // Stop the game
  void Stop() { isRunning = false; }
  Window *GetWindow() { return window; }
};

} // namespace Kepler

#endif
