#include <iostream>
#include "Enigma.h"
#include <algorithm>

const std::string REFLECTOR_PERMUTATION = "YRUHQSLDPXNGOKMIEBFZCWVJAT"; //"IXUHFEZDAOMTKQJWNSRLCYPBVG";

//fast rotor, middle rotor and a slow rotor inversed
// 26
// lampboard, rotors, reflector
/*

char rotate(char offset2, const char letter, const std::string permutation)
{
	int offset = int(offset2) - 65;
	//std::cout << offset << std::endl;
	int l = letter - 65;
	//std::cout << letter << std::endl;
	int y = (l + offset) % 26;

	int gap = (permutation[y] - 65) - y;
	
	//std::cout << "gap: " << gap << " for: " << char(y + 65) << std::endl;
	int ret = (l + gap) % 26;
	//std::cout << letter << " --> " << char(ret + 65) << std::endl;
	
	return char(ret + 65);
}

void rotate2(char *arr, Rotor *rotorsArr)
{
	if (arr[1] == rotorsArr[1].getNotch())
	{
		arr[1] = int(arr[1]) + 1;
		arr[0] = int(arr[0]) + 1;
	}

	if (arr[2] == rotorsArr[2].getNotch())
	{
		arr[1] = int(arr[1]) + 1;
	}

	arr[2] = int(arr[2]) + 1;
}

void printSettingsArray(char *arr)
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

std::string invertKey(std::string key)
{
	std::string ret;
	for (int i = 0; i < 26; i++)
	{
		ret += char(key.find(char(i + 65)) + 65);
	}
	return ret;
}

void decrypt(char *settingArr, Rotor *rotorsArr, char letter)
{
	char a = rotate('A', letter, REFLECTOR_PERMUTATION);
	char b = rotate(settingArr[0], a, invertKey(rotorsArr[0].getRotorPermutation()));
	char c = rotate(settingArr[1], b, invertKey(rotorsArr[1].getRotorPermutation()));
	char d = rotate(settingArr[2], c, invertKey(rotorsArr[2].getRotorPermutation()));
	std::cout << d << std::endl;
}

void encrypt(char *settingArr, Rotor *rotorsArr, char letter)
{
	//std::cout << letter << std::endl;
	char a = rotate(settingArr[2], letter, rotorsArr[2].getRotorPermutation());
	char b = rotate(settingArr[1], a, rotorsArr[1].getRotorPermutation());
	char c = rotate(settingArr[0], b, rotorsArr[0].getRotorPermutation());
	//std::cout << c << std::endl;
	decrypt(settingArr, rotorsArr, c);
	rotate2(settingArr, rotorsArr);
}
*/

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		//std::cout << argv[1] << std::endl;
	}

	//Rotor rotorsArr[3] = {Rotor(3), Rotor(2), Rotor(1)}; // 1, 2, 3
	char settingArr[3] = {'A', 'A', 'A'};

	char currentLetter = 'Q';
	char offset = 'A';

	//std::string "Hello";

	//encrypt(settingArr, rotorsArr, 'E');
	//encrypt(settingArr, rotorsArr, 'F');

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
	en.addRotors(1, 2, 3);
	en.setOffsetPositions(settingArr);
	en.setInputMessage("JEGHETERSTIAN");
	//en.setReflectorPermutation("IXUHFEZDAOMTKQJWNSRLCYPBVG");
	en.setReflectorPermutation("YRUHQSLDPXNGOKMIEBFZCWVJAT");

	std::string encodedMessage = en.begin();

	en.setOffsetPositions(settingArr);
	en.setInputMessage(encodedMessage);
	std::string decodedMessage = en.begin();
	std::cout << encodedMessage << std::endl;
	std::cout << decodedMessage << std::endl;

	return 0;
}