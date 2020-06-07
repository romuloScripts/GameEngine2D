#include "EntityManager.h"
#include <iostream>
#include "ColliderComponent.h"
#include "Collision.h"

void EntityManager::ClearData()
{
	for (auto& entity : entities)
	{
		entity->Destroy();
	}
}

void EntityManager::Update(float deltaTime)
{
	for (auto& entity : entities)
	{
		entity->Update(deltaTime);
	}
	DestroyInactiveEntities();
}

void EntityManager::DestroyInactiveEntities() 
{
	for (int i = 0; i < entities.size(); i++) {
		if (!entities[i]->IsActive()) {
			entities.erase(entities.begin() + i);
		}
	}
}

void EntityManager::Render()
{
	for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
		for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber))) {
			entity->Render();
		}
	}
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const 
{
	std::vector<Entity*> selectedEntities;
	for (auto& entity : entities) {
		if (entity->layer == layer) {
			selectedEntities.emplace_back(entity);
		}
	}
	return selectedEntities;
}

bool EntityManager::HasNoEntities() const
{
	return entities.size() == 0;
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) 
{
	Entity *entity = new Entity(*this, entityName, layer);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
	return entities;
}

unsigned int EntityManager::GetEntityCount() const
{
	return entities.size();
}

Entity* EntityManager::GetEntityByName(std::string entityName) const {
	for (auto* entity : entities) {
		if (entity->name.compare(entityName) == 0) {
			return entity;
		}
	}
	return NULL;
}

CollisionType EntityManager::CheckCollisions() const 
{
	for (int i = 0; i < entities.size() - 1; i++) {
		auto& thisEntity = entities[i];
		if (thisEntity->HasComponent<ColliderComponent>()) {
			ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
			for (int j = i + 1; j < entities.size(); j++) {
				auto& thatEntity = entities[j];
				if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>()) {
					ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
					if (Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider)) {
						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("ENEMY") == 0) {
							return PLAYER_ENEMY_COLLISION;
						}
						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("PROJECTILE") == 0) {
							return PLAYER_PROJECTILE_COLLISION;
						}
						if (thisCollider->colliderTag.compare("ENEMY") == 0 && thatCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0) {
							return ENEMY_PROJECTILE_COLLISION;
						}
						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("LEVEL_COMPLETE") == 0) {
							return PLAYER_LEVEL_COMPLETE_COLLISION;
						}
					}
				}
			}
		}
	}
	return NO_COLLISION;
}

void EntityManager::ListAllEntities() const 
{
	unsigned int i = 0;
	for (auto& entity : entities) {
		std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
		entity->ListAllComponents();
		i++;
	}
}
