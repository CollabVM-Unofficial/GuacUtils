#ifndef __GUAC_UTILS_HPP__
#define __GUAC_UTILS_HPP__

// made by totallyNotAUser
// it is for c++, not c
// because .hpp = header for c++

#include <string>
#include <vector>

std::vector<std::string> guac_decode(std::string encoded_str)
{
	// ported from totallyNotABot
	std::vector<std::string> ret;
	std::string _msg = msg;

	for (int i = 0; i < _msg.length();)
	{
		// Decode the length part
		int lenEnd = _msg.find('.');
		if (lenEnd == std::string::npos)
			break;
		int len = std::stoi(_msg.substr(i, lenEnd));
		// Decode the text part
		i += lenEnd + 1; // Put i after the .
		std::string text = _msg.substr(i, len);
		ret.push_back(text);
		i += len; // Put i on the ,/;
		if (_msg[i] == ';')
		{
			break;
		}
		else if (_msg[i] == ',')
		{
			i++;
		}
		//else throw new FormatException($"Expexcted ',' or ';', but got {_msg[i]}");
		_msg = _msg.substr(i);
		i = 0;
	}
	return ret;
}

std::string guac_encode(std::vector<std::string> not_encoded)
{
	std::string ret;
	for (const std::string &part : not_encoded)
	{
		ret.append(std::to_string(part.length())).append(".").append(part).append(","); // appends <length>.<part>,
	}
	ret.erase(ret.length() - 1); // erase the last ,
	ret.append(";");			 // finish the guac message with ;
	return ret;
}

#endif // __GUAC_UTILS_HPP__