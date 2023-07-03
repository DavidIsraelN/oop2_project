#pragma once
#include "ResourcesManager.h"
#include "StaticObject.h"

class Door : public StaticObject
{
public:
  Door(const sf::Vector2f& position, float width, float height)
  {
    m_sprite = sf::Sprite(ResourceManager::Resource().getObjTexture(ObjIndex::DOOR));
    const auto bounds = m_sprite.getLocalBounds();
    m_sprite.setScale(width / bounds.width, height / bounds.height);
    m_sprite.setPosition(position);
    m_sprite.setOrigin(bounds.width / 2, bounds.height / 2);
  }

private:

};

