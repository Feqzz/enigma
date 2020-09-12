#include <iostream>
#include "Enigma.h"
#include <algorithm>
#include <vector>

int main(int argc, char *argv[])
{
	char settingArr[3] = {'A', 'A', 'A'};
	char ringSettingArr[3] = {'F', 'B', 'C'};
	std::vector<std::string> plugBoard = {};

	const char notches[5] = {'Q','E','V','J','Z'};
	const std::string rotorPermutations[5] =
	{
		"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
	  	"AJDKSIRUXBLHWTMCQGZNPYFVOE",
	  	"BDFHJLCPRTXVZNYEIWGAKMUSQO",
	  	"ESOVPZJAYQUIRHXLNFTGKDCMWB",
	  	"VZBRGITYUPSDNHLXAWMJQOFECK"
	};

	Enigma en = Enigma(notches, rotorPermutations);
	en.addRotors(3, 2, 1);
	en.setOffsetPositions(settingArr, ringSettingArr);
	en.configurePlugboard(plugBoard);
	en.setInputMessage("AAA");
	en.setReflectorPermutation("YRUHQSLDPXNGOKMIEBFZCWVJAT");

	std::string encodedMessage = en.begin();
	std::cout << "encoded: " << encodedMessage << std::endl;
	return 0;
}