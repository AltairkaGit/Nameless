#include "dataStream.h"

void DataStream::openToRead(const std::string& path)
{
	m_Stream.open(path, std::ios::in);
}

void DataStream::openToWright(const std::string& path)
{
	m_Stream.open(path, std::ios::out);
}

void DataStream::close()
{
	m_Stream.close();
}

Byte* DataStream::read(uint32_t offset, uint32_t count)
{
	if (!m_Stream.is_open()) return 0;
	m_Stream.seekg(offset);
	if (m_Stream.eof()) return 0;
	char* data = new char[count];
	m_Stream.read(data, count);
	return reinterpret_cast<Byte*>(data);
}

void DataStream::write(uint32_t offset, uint32_t count, Byte* data)
{
	if (!m_Stream.is_open()) return;
	m_Stream.seekg(offset);
	m_Stream.write(reinterpret_cast<char*>(data), count);
}