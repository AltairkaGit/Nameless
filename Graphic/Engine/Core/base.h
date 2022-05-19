#pragma once
#include <memory>
#include <iostream>

typedef unsigned char Byte;

template<class T>
using OwnRef = std::shared_ptr<T>;
template<class T, class... Args>
constexpr OwnRef<T> createOwnRef(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<class T>
using Scope = std::unique_ptr<T>;
template<class T, class... Args>
constexpr Scope<T> createScope(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<class T>
using WeakRef = std::weak_ptr<T>;
