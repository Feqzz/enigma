#include <iostream>
#include "Enigma.h"
#include <algorithm>
#include <vector>

//const std::string REFLECTOR_PERMUTATION = "YRUHQSLDPXNGOKMIEBFZCWVJAT"; //"IXUHFEZDAOMTKQJWNSRLCYPBVG";

//fast rotor, middle rotor and a slow rotor inversed
// 26
// lampboard, rotors, reflector


int main(int argc, char *argv[])
{
	char settingArr[3] = {'A', 'A', 'A'};
	char ringSettingArr[3] = {'A', 'A', 'A'};

	const char notches[5] = {'Q','E','V','J','Z'};
	const std::string rotorPermutations[5] =
	{
		"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
	  	"AJDKSIRUXBLHWTMCQGZNPYFVOE",
	  	"BDFHJLCPRTXVZNYEIWGAKMUSQO",
	  	"ESOVPZJAYQUIRHXLNFTGKDCMWB",
	  	"VZBRGITYUPSDNHLXAWMJQOFECK"
	};

	std::vector<std::string> plugBoard = {"BQ", "CR", "DI", "EJ", "KW", "MT", "OS", "PX", "UZ", "GH"};

	Enigma en = Enigma(notches, rotorPermutations);
	en.addRotors(1, 3, 1);
	en.setOffsetPositions(settingArr, ringSettingArr);
	en.configurePlugboard(plugBoard);
	en.setInputMessage("OOIJAWDIJWDYURIOEJRGOIFDGYHDRGIJEF");
	//en.setReflectorPermutation("IXUHFEZDAOMTKQJWNSRLCYPBVG");
	en.setReflectorPermutation("YRUHQSLDPXNGOKMIEBFZCWVJAT");

	std::string encodedMessage = en.begin();

	//en.setOffsetPositions(settingArr, ringSettingArr);
	//en.setInputMessage(encodedMessage);
	//std::string decodedMessage = en.begin();
	std::cout << "encoded: " << encodedMessage << std::endl;
	//std::cout << "decoded: " << decodedMessage << std::endl;

	return 0;
}