#include	<iostream>
#include	<Windows.h>
#include	<vector>
#include	<string>
#include	<fstream>
#include	"Encrypt.h"

std::vector<char> get_file_data(const char* file_path)
{
	std::ifstream ifs(file_path, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	return result;
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
	const char* stub_path = "./OnyxStub.exe";

	std::cout << "File to be encrypted: ";
	std::cin >> file_path;

	std::vector<char> file_data = get_file_data(file_path);
	std::vector<char> key = { 'd','u','c','k' };
	file_data = encrypt(file_data, key);

	if (modify_resources(stub_path, 10, (BYTE*)file_data.data(), file_data.size()))
	{
		std::cout << "Succes!" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Error!" << std::endl;
		return 1;
	}
}