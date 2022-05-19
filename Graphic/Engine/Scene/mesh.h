#pragma once
#include <cinttypes>

class Mesh
{
public:
	Mesh(uint32_t primitive, uint32_t material);

	Mesh(const Mesh&) = delete;
	Mesh operator=(Mesh&) = delete;	

	const uint32_t getPrimitive() const { return m_Primitive; }
	const uint32_t getMaterial() const { return m_Material; }
private:
	/** Handles in managers
	*/
	uint32_t m_Primitive;
	uint32_t m_Material;
};

