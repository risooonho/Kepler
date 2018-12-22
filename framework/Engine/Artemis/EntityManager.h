#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H


#include "ImmutableBag.h"
#include "Component.h"
#include "ComponentTypeManager.h"


namespace Kepler {
  
  class Entity;
  class World;
  class EntityManager {
    
  public:
    EntityManager(World& world);
    ~EntityManager();
    Entity & create();
    void remove(Entity &e);
    void RemoveComponentsOfEntity(Entity & e);
    bool isActive(int entityId);
    void AddComponent(Entity &e, Component * c);
    void Refresh(Entity &e);
    
    void removeAllEntities();
    
    void RemoveComponent(Entity & e, ComponentType & type);
    
    template<typename c>
    void RemoveComponent(Entity & e) {
      RemoveComponent(e,ComponentTypeManager::getTypeFor<c>());
    }
    
    Component * getComponent(Entity & e, ComponentType & type);
    
    template<typename c>
    Component * getComponent(Entity & e) {
      ComponentType type = ComponentTypeManager::getTypeFor<c>();
      return getComponent(e,type);
    }
    
    Entity& getEntity(int entityId);
    int getEntityCount();
    long getTotalCreated();
    long getTotalRemoved();
    
    Bag<Component*>& getComponents(Entity & e);
    
    
  private:
    World * world;
    Bag<Entity*> activeEntities;
    Bag<Entity*> removedAndAvailable;
    int nextAvailableId;
    int count;
    long uniqueEntityId;
    long totalCreated;
    long totalRemoved;
    
    Bag<Bag<Component*>*> componentsByType;
    Bag<Component*> entityComponents;
    
  };
};
#endif // $(Guard token)
