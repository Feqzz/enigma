#include "Enigma.h"

Enigma::Enigma(const char* notches, const std::string* rotorPermutations)
	: mNotches(notches), mRotorPermutations(rotorPermutations)
{
	//Fills up the modified alphabet
	for (int i = 0; i < 26; i++)
	{
		mModifiedAlphabet[i] = char(i + 65);
	}
}

void Enigma::addRotors(int arr[3])
{
	for (int i = 0; i < 3; i++)
	{
		mRotorsArray[i] = new Rotor(arr[i], mNotches[arr[i] - 1], mRotorPermutations[arr[i] - 1]);
	}
}

void Enigma::configurePlugboard(std::vector<std::string> vec)
{
	//The input can look like "AB", then the A and B swaps places in the modified alphabet.
	for (int i = 0; i < vec.size(); i++)
	{
		char x = vec[i][0];
		char y = vec[i][1];
		mModifiedAlphabet[int(x - 65)] = y;
		mModifiedAlphabet[int(y - 65)] = x;
	}
}

void Enigma::rotate()
{
	if (mRotorsArray[1]->getCurrentSetting() == mRotorsArray[1]->getNotch())
	{
		mRotorsArray[1]->incrementSetting();
		mRotorsArray[0]->incrementSetting();
	}

	if (mRotorsArray[2]->getCurrentSetting() == mRotorsArray[2]->getNotch())
	{
		mRotorsArray[1]->incrementSetting();
	}

	mRotorsArray[2]->incrementSetting();
}

std::string Enigma::invertKey(const std::string key) const
{
	std::string ret;
	for (int i = 0; i < 26; i++)
	{
		ret += char(key.find(char(i + 65)) + 65);
	}
	return ret;
}

void Enigma::setOffsetPositions(const char* positions, const char* ringPositions)
{
	for (int i = 0; i < 3; i++)
	{
		mRotorsArray[i]->setCurrentSetting(positions[i]);
		mRotorsArray[i]->setRingSetting(ringPositions[i]);
	}
}

void Enigma::setInputMessage(std::string str)
{
	mInputMessage = str;
}

void Enigma::setReflectorPermutation(std::string str)
{
	mReflectorPermutation = str;
}

int Enigma::mod(const int a, const int b) const
{
	if (a == 0)
	{
		return 0;
	}

	if ((a > 0) == (b > 0))
	{
		return a % b;
	}
	else
	{
		return (a % b) + b;
	}
}

char Enigma::wire(const int rotorIndex, const char letter, const int mode)
{
	std::string permutation;
	char rotorSetting;
	char ringSetting;
	switch (mode)
	{
		case 0:
		{
			permutation = mRotorsArray[rotorIndex]->getRotorPermutation();
			rotorSetting = mRotorsArray[rotorIndex]->getCurrentSetting();
			ringSetting = mRotorsArray[rotorIndex]->getRingSetting();
			break;
		}

		case 1:
		{
			//When reflecting, there should be no rotor and ring settings.
			permutation = mReflectorPermutation;
			rotorSetting = 'A';
			ringSetting = 'A';
			break;
		}

		case 2:
		{
			//On the way back, the permutation is inverted.
			permutation = invertKey(mRotorsArray[rotorIndex]->getRotorPermutation());
			rotorSetting = mRotorsArray[rotorIndex]->getCurrentSetting();
			ringSetting = mRotorsArray[rotorIndex]->getRingSetting();
			break;
		}
	}

	//From ASCII to the letter's position in the alphabet.
	const int rotorOffset = int(rotorSetting) - 65;
	const int ringOffset = int(ringSetting) - 65;
	const int let = letter - 65;

	const int letterWithRotorOffset = mod((let + rotorOffset), 26);

	const int letterWithRingOffset = getRingedCharacter(permutation, ringOffset, letterWithRotorOffset);

	const int gap = mod((letterWithRingOffset - letterWithRotorOffset), 26);

	//returns the letter with the calculated gap and adds it back to ASCII format.
	const int ret = mod((let + gap), 26) + 65;
	
	return char(ret);
}

int Enigma::getRingedCharacter(const std::string permutation, const int ring, const int letter) const
{
	const int newLetter = permutation[mod((letter - ring), 26)] - 65;
	const int gap = mod((newLetter - letter + ring), 26);
	return mod((letter + gap), 26);
}

std::string Enigma::begin()
{
	std::string encodedMessage;
	for (int i = 0; i < mInputMessage.size(); i++)
	{
		rotate();
		char currentCharacter = mModifiedAlphabet[mInputMessage[i] - 65];

		for (int j = 2; j >= 0; j--)
		{
			currentCharacter = wire(j, currentCharacter, 0);
		}

		//The reflector
		currentCharacter = wire(-1, currentCharacter, 1);

		for (int j = 0; j < 3; j++)
		{
			currentCharacter = wire(j, currentCharacter, 2);
		}

		if (((i % 5) == 0) && i > 0)
		{
			encodedMessage += " ";
		}

		encodedMessage += mModifiedAlphabet[currentCharacter - 65];
	}
	return encodedMessage;
}