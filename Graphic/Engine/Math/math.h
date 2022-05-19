#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <fstream>

namespace glm
{
	inline float fade(float t)
	{
		return ((6 * t - 15) * t + 10) * t * t * t;
	}

	inline float lerp(float t, float a1, float a2)
	{
		return a1 + (a2 - a1) * t;
	}

	inline void shuffle(std::vector<int>& p)
	{
		for (int i = p.size() - 1; i > 0; i--)
		{
			int j = rand() % i;
			int tmp = p[i];
			p[i] = p[j];
			p[j] = tmp;
		}
	}

	inline std::vector<int> makePrtmutation()
	{
		std::vector<int> p;
		for (int i = 0; i < 256; i++) p.push_back(i);
		shuffle(p);
		for (int i = 0; i < 256; i++) p.push_back(p[i]);
		return p;
	}

	inline glm::vec2 getConstantVector(int v)
	{
		int h = v & 3;
		switch (h)
		{
		case 0:	return glm::vec2(1.0f, 1.0f);
		case 1:	return glm::vec2(-1.0f, 1.0f);
		case 2:	return glm::vec2(-1.0f, -1.0f);
		case 3:	return glm::vec2(1.0f, -1.0f);
		}
	}

	inline float noise2d_perlin(float x, float y, std::vector<int>& p)
	{
		int X = (int)x & 255;
		int Y = (int)y & 255;

		float xf = x - (int)x;
		float yf = y - (int)y;		

		glm::vec2 topRight = { xf - 1.0f, yf - 1.0f };
		glm::vec2 topLeft = { xf, yf - 1.0f };
		glm::vec2 botRight = { xf - 1.0f, yf };
		glm::vec2 botLeft = { xf, yf };

		int vTopRight = p[p[X + 1] + Y + 1];
		int vTopLeft = p[p[X] + Y + 1];
		int vBotRight = p[p[X + 1] + Y];
		int vBotLeft = p[p[X] + Y];

		float dotTopRight = glm::dot(topRight, getConstantVector(vTopRight));
		float dotTopLeft = glm::dot(topLeft, getConstantVector(vTopLeft));
		float dotBotRight = glm::dot(botRight, getConstantVector(vBotRight));
		float dotBotLeft = glm::dot(botLeft, getConstantVector(vBotLeft));

		float u = fade(xf);
		float v = fade(yf);

		float a = lerp(v, dotBotLeft, dotTopLeft);
		float b = lerp(v, dotBotRight, dotTopRight);
		float r = lerp(u, a, b);
		return r;
	}

	inline float noise2d_fbm(float x, float y, std::vector<int>& p, const int& octaves)
	{
		float value = 0.0f;
		float amplitude = 1.0f;
		
		for (int i = 0; i < octaves; i++)
		{
			value += amplitude * noise2d_perlin(x, y, p);
			amplitude *= 0.5;
			x *= 2.0f; y *= 2.0f;
		}

		return value;
	}

	inline void noise2d_fbm_map(std::vector<float>& map, const int& size, const float& frequency, const int& octaves)
	{
		std::vector<int> p = makePrtmutation();
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				map[i * size + j] = noise2d_fbm(i * frequency, j * frequency, p, octaves);
	}

	inline float noise2d_fractal(float x, float y)
	{
		return fract(sin(dot(vec2(x,y), vec2(12.9898f, 78.233f))) * 43758.5453123f);
	}

	inline vec2 noise2d_fractal_vec(vec2 p)
	{
		return fract(sin(vec2(dot(p, vec2(127.1f, 311.7f)), dot(p, vec2(269.5f, 183.3f)))) * 43758.5453f);
	}

	inline void noise2d_fractal_map(std::vector<float>& map, const int& size)
	{
		std::vector<int> p = makePrtmutation();
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				map[i * size + j] = noise2d_fractal(i, j);
	}

	inline void noise2d_fractal_map(std::vector<vec2>& map, const int& size)
	{
		std::vector<int> p = makePrtmutation();
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				map[i * size + j] = noise2d_fractal_vec(vec2(i, j));
	}

	inline void wright_noise(std::vector<float>& map, const int& size, const std::string& path)
	{
		std::ofstream fs;
		fs.open(path, std::ofstream::out | std::ofstream::trunc);
		fs << "P3\n" << size << " " << size << '\n' << 255 << '\n';
		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				int col = (map[x * size + y] + 1.0f) / 2.0f * 255;
				fs << col << ' ' << col << ' ' << col << '\n';
			}
		}
		fs.close();
	}
}

