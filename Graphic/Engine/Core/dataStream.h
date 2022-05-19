#pragma once
#include "base.h"
#include <iostream>
#include <fstream>

class DataStream
{
public:
	DataStream() = default;
	~DataStream() = default;

	void openToRead(const std::string& path);
	void openToWright(const std::string& path);
	void close();

	Byte* read(uint32_t offset, uint32_t count);
	void write(uint32_t offset, uint32_t count, Byte* data);
private:
	std::fstream m_Stream;
};
