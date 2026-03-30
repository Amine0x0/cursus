#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return (1);
	}

	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	if (filename.empty())
	{
		std::cerr << "Error: filename cannot be empty" << std::endl;
		return (1);
	}

	if (s1.empty())
	{
		std::cerr << "Error: search string (s1) cannot be empty" << std::endl;
		return (1);
	}

	std::ifstream infile(filename.c_str());
	if (!infile.is_open())
	{
		std::cerr << "Error: could not open file '" << filename << "'" << std::endl;
		return (1);
	}

	std::string content;
	std::string line;
	while (std::getline(infile, line))
	{
		if (infile.fail() && !infile.eof())
		{
			std::cerr << "Error: failed to read from file" << std::endl;
			return (1);
		}
		content += line;
		content += '\n';
	}
	infile.close();

	if (content.empty())
	{
		std::cerr << "Error: file is empty" << std::endl;
		return (1);
	}

	if (!content.empty() && content[content.length() - 1] == '\n')
	{
		content.erase(content.length() - 1);
	}

	size_t pos = 0;
	while ((pos = content.find(s1, pos)) != std::string::npos)
	{
		std::string before = content.substr(0, pos);
		std::string after = content.substr(pos + s1.length());
		content = before + s2 + after;
		pos += s2.length();
	}

	std::string output_filename = filename + ".replace";

	std::ofstream outfile(output_filename.c_str());
	if (!outfile.is_open())
	{
		std::cerr << "Error: could not create output file '" << output_filename << "'" << std::endl;
		return (1);
	}

	outfile << content;
	if (outfile.fail())
	{
		std::cerr << "Error: failed to write to output file" << std::endl;
		return (1);
	}
	outfile.close();

	std::cout << "Successfully created '" << output_filename << "'" << std::endl;
	return (0);
}