/*
#pragma once
#include "Objects/Object.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

enum class ObjectType
{
  PLAYER = 'P',
  WALL = '#',
  DOOR = 'D',
  BALL = 'B'
};

class Factory
{
public:
  static Factory& instance()
  {
    static auto instance = Factory();
    return instance;
  }

  using FuncType = std::unique_ptr<Object>(*)(const sf::Vector2f&);
  bool registerType(ObjectType type, FuncType func)
  {
    m_map.emplace(type, func);
    return true;
  }

  std::unique_ptr<Object> create(ObjectType type, sf::Vector2f position) const
  {
    return m_map.at(type)(position);
  }

private:
  Factory() = default;
  Factory(const Factory&) = delete;
  void operator=(const Factory&) = delete;

  std::unordered_map<ObjectType, FuncType> m_map;
};
*/
