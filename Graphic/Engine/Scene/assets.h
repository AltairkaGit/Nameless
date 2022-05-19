#pragma once
#include <vector>
#include "Core/base.h"


enum class LoadingState
{
	Unloaded = 0,
	Preparing,
	Prepared,
	Loading,
	Loaded,	
	Unloading,
};


class AssetManager;

class Asset
{
public:
	Asset(WeakRef<AssetManager> manager, uint32_t id)
		: m_Manager(manager), m_Id(id)
	{}
	virtual ~Asset() = default;

	uint32_t getId() const { return m_Id; }
	virtual uint32_t getSize() const = 0;

	virtual bool operator==(Asset&) = 0;
	virtual bool compare(Asset& other) { return this->operator==(other); }

protected:
	Asset() = default;

	WeakRef<AssetManager> m_Manager;
	uint32_t m_Id;
	uint32_t m_Size;
	LoadingState m_LoadingStage = LoadingState::Unloaded;

	//unloaded => prepared
	virtual void prepare() {}
	//prepred => unloaded
	virtual void unprepare() {}
	//

	//prepareded => loading
	virtual void preLoad() {}
	
	virtual void posLoad() {}

public:
	virtual void load() {}
	virtual void unload() {}

	
};

class AssetPool
{
public:
	AssetPool();
	~AssetPool();

private:
	std::vector<WeakRef<Asset>> m_Store;
};

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

private:
	AssetPool m_Pool;
};