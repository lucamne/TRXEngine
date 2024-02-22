#pragma once

#include <vector>
#include <string>

namespace TRXEngine

{
	/*Static IO manager class to load and manage files*/
	class IOManager
	{
	public:
		/*Given file path, reads file to buffer*/
		static bool readFileToBuffer(std::string fp, std::vector<unsigned char>& buffer);
	};

}