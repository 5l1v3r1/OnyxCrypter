#include	<iostream>
#include	<Windows.h>
#include	<vector>
#include	<string>

//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string GetLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return std::string(); //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)& messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	//Free the buffer.
	LocalFree(messageBuffer);

	return message;
}

// Function to get the file as a vector
std::vector<char> get_file_data(const char* file_path)
{
	// DWORD to hold the file's size
	DWORD file_size;
	// DWORD to see how many bytes we have read
	DWORD bytes_read;
	// Vector to hold our file data
	std::vector<char> file_data;
	// Handle to the file we want to read
	// This will be used to read the file / get information from it
	HANDLE hFile = CreateFileA(file_path, GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	// Get the file size
	file_size = GetFileSize(hFile, NULL);
	// Resize the vector we hold the data in accordingly
	file_data.resize(file_size);
	// Read the file into the vector
	ReadFile(hFile, (LPVOID)(file_data.data()), file_size, &bytes_read, NULL);
	// Close the handle!!!
	CloseHandle(hFile);

	// Check if we were able to read something
	if (file_size != bytes_read)
	{
		std::cout << "Error reading the file data!" << std::endl;
		return file_data;
	}
	// I saw this in the example, I have no idea what it does.
	char choice;
	file_data.push_back(choice);
	return file_data;
}

bool modify_resources(LPCSTR szTargetPE, int id, LPBYTE lpBytes, DWORD dwSize)
{
	// Handle to the resources section of our stub
	HANDLE hFile = BeginUpdateResourceA(szTargetPE, FALSE);
	// Attempt to update the resources and store the result in a bool
	bool update_succes = UpdateResourceA(hFile, MAKEINTRESOURCEA(10), MAKEINTRESOURCEA(69), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lpBytes, dwSize);
	// Close the handle / end updating the resources so we can use them again.
	EndUpdateResourceA(hFile, FALSE);
	return update_succes;
}

int main()
{
	// Path to file to be transfered to our resources.
	char file_path[MAX_PATH];
	// Stub file to carry our executable.
	const char* stub_path = "./OnyxStub.exe";
	std::cout << "File to be encrypted: ";
	std::cin >> file_path;

	// Get the file bytes in a vector
	std::vector<char> file_data = get_file_data(file_path);

	// If we actually want to do it we could now encrypt our file_data vector before inserting it into the stub's resources
	// I did not bother to since this is a test and encryption / decryption will be added once I do actually get an understanding
	// Of how this all works.

	// Modify the resources of the stub.
	if (modify_resources(stub_path, 10, (BYTE*)file_data.data(), file_data.size()))
	{
		std::cout << "Succes!" << std::endl;
	}
	else
	{
		std::cout << "Error!" << std::endl;
		printf(GetLastErrorAsString().c_str());
	}
}