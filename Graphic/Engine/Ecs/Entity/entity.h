#pragma once
#include "Math/math.h"
#include "entt.hpp"
#include "scene.h"

class Entity
{
public:
	Entity() = default;
	Entity(entt::entity handle, Scene* scene);

	template<class T, class... Args>
	T& addComponent(Args&&... args)
	{
		T& component = m_Scene->m_Registry.emplace(m_EntityHandle, std::forward<Args>(args)...);
		m_Scene->onComponentAdded<T>(*this, component);
		return component;
	}

	template<class T>
	T& getComponent()
	{
		return m_Scene->m_Registry.get<T>(m_EntityHandle);
	}

	template<class T>
	bool hasComponent()
	{
		return m_Scene->m_Registry.has<T>(m_EntityHandle);
	}

	template<class T>
	bool removeComponent()
	{
		return m_Scene->m_Registry.remove<T>(m_EntityHandle);
	}

	operator bool() const
	{
		return m_EntityHandle != entt::null;
	}

	operator entt::entity() const
	{
		return m_EntityHandle;
	}

	operator uint32_t() const
	{
		return (uint32_t)m_EntityHandle;
	}

	bool operator==(const Entity& other) const
	{
		return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
	}

	bool operator!=(const Entity& other) const
	{
		return m_EntityHandle != other.m_EntityHandle || m_Scene != other.m_Scene;
	}

private:
	entt::entity m_EntityHandle{ entt::null };
	Scene* m_Scene = nullptr;

};