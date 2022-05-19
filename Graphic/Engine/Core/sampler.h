#pragma once
#include "base.h"

enum class SamplerAnisotropy
{
	X1 = 0, X2, X4, X8, X16,
};

enum class Filtering
{
	Nearest = 0, Billinear,
};

enum class Wrapping
{
	Repeat = 0, Clamp,
};

class TextureSampler
{
public:
	virtual ~TextureSampler() = default;

	virtual void bind(uint32_t slot) const = 0;

	virtual uint32_t getMagFilter() const = 0;
	virtual uint32_t getMinFilter() const = 0;

	virtual uint32_t getWrapS() const = 0;
	virtual uint32_t getWrapT() const = 0;

	virtual float_t getMaxAnisotropyExt() const = 0;

	static OwnRef<TextureSampler> create(Filtering filtering = Filtering::Billinear, 
		Wrapping wrapping = Wrapping::Repeat, SamplerAnisotropy anisotropyExt = SamplerAnisotropy::X16);
};
