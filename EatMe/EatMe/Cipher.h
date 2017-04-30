#pragma once

#include <iostream>
#include <string>

class VerrnamCipher
{
	static std::string KEY;

public:
	static std::string encrypt(std::string text)
	{
		std::string ct = "";

		char pos = 0;
		for (unsigned int i = 0; i < text.length(); ++i)
		{
			ct += text[i] ^ KEY[i % KEY.length()];
		}
		return ct;
	}

	static std::string decrypt(std::string text)
	{
		std::string pt = "";
		int pos = 0;
		for (unsigned int i = 0; i < text.length(); ++i)
		{
			pt += text[i] ^ KEY[i % KEY.length()];
		}
		return pt;
	}
};

std::string VerrnamCipher::KEY = "gP52bafLJF354t9SvijnDt4i3;qty1gtq3tA.garq3zgalhfKasopaq[b8fneYq1qtar0dfh5qp,rouafd13k6y3bfIJEHa0TLGA";
