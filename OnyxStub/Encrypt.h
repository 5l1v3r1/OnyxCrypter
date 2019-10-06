#include <vector>

std::vector<char> decrypt(std::vector<char> input, std::vector<char> key)
{
	int block_count = 4;
	std::vector<char> output = input;

	for (int i = 0; i < input.size() / block_count; i++)
	{
		for (int j = i * block_count; j < i * block_count + block_count; j++)
		{
			if (j >= input.size()) break;
			output[j] = input[j] ^ key[j % key.size()];
		}
	}

	return output;
}