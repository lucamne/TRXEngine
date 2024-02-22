#include "IOManager.h"

#include <fstream>

namespace TRXEngine {
	bool IOManager::readFileToBuffer(std::string fp, std::vector<unsigned char>& buffer)
	{
		// read file in as binary
		std::ifstream file(fp, std::ios::binary);
		if (file.fail())
		{
			perror(fp.c_str());
			return false;
		}

		// seek to the end of the file
		file.seekg(0, std::ios::end);

		// get file size
		int file_size{ static_cast<int>(file.tellg()) };
		// seek back to beginning
		file.seekg(0, std::ios::beg);
		// reduce file size by any header bytes that may be present
		file_size -= static_cast<int>(file.tellg());

		buffer.resize(file_size);
		file.read((char*)&(buffer[0]), file_size);
		return true;
	}
}