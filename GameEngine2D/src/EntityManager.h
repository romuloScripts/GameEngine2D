#pragma once

#include "Entity.h"
#include "Components/Component.h"
#include <vector>

class EntityManager
{

private:
	std::vector<Entity*> entities;
public:
	void ClearData();
	void Update(float deltaTime);
	void Render();
	bool HasNoEntities() const;
	unsigned int GetEntityCount() const;
	void DestroyInactiveEntities();
	void ListAllEntities() const;
	std::vector<Entity*> GetEntities() const;
	std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
	Entity& AddEntity(std::string entityName, LayerType layer);
	CollisionType CheckCollisions() const;
	Entity* GetEntityByName(std::string entityName) const;
};

