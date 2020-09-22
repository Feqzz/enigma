#include <iostream>
#include "Enigma.h"
#include <algorithm>
#include <vector>
#include <algorithm>

void printUsage()
{
	std::cout << "Usage: ./enigma <text> <rotors> <rotor settings> <ring settings> <reflector> <plugboard setting 1> .. <plugboard setting N>" << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc < 6)
	{
		printUsage();
		exit(1);
	}

	char settingArr[3]; 
	char ringSettingArr[3];
	int rotorsArr[3];
	std::vector<std::string> plugBoard = {};

	std::string inputMessage = argv[1];
	const std::string rotorsStr = argv[2];
	const std::string rotorSettingsStr = argv[3];
	const std::string ringSettingsStr = argv[4];
	const int reflectorType = (int)(std::string(argv[5])[0] - 65);

	for (int i = 0; i < 3; i++)
	{
		settingArr[i] = rotorSettingsStr[i];
		ringSettingArr[i] = ringSettingsStr[i];
		rotorsArr[i] = (int)rotorsStr[i] - 48;
	}

	for (int i = 6; i < argc; i++)
	{
		const std::string pb = argv[i];
		plugBoard.push_back(pb);
	}

	const char notches[5] = {'Q','E','V','J','Z'};
	const std::string rotorPermutations[5] =
	{
		"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
	  	"AJDKSIRUXBLHWTMCQGZNPYFVOE",
	  	"BDFHJLCPRTXVZNYEIWGAKMUSQO",
	  	"ESOVPZJAYQUIRHXLNFTGKDCMWB",
	  	"VZBRGITYUPSDNHLXAWMJQOFECK"
	};

	const std::string reflectors[3] =
	{
		"EJMZALYXVBWFCRQUONTSPIKHGD",
		"YRUHQSLDPXNGOKMIEBFZCWVJAT",
		"FVPJIAOYEDRZXWGCTKUQSBNMHL"
	};

	//Tranforms the string to only uppercase. Otherwise it will not function, as I have designed the code
	//to work with uppercases only.
	std::transform(inputMessage.begin(), inputMessage.end(), inputMessage.begin(), ::toupper);

	Enigma en = Enigma(notches, rotorPermutations);
	en.addRotors(rotorsArr);
	en.setOffsetPositions(settingArr, ringSettingArr);
	en.configurePlugboard(plugBoard);
	en.setInputMessage(inputMessage);
	en.setReflectorPermutation(reflectors[reflectorType]);

	std::string encodedMessage = en.begin();
	std::cout << "encoded: " << encodedMessage << std::endl;
	return 0;
}