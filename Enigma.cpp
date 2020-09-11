#include "Enigma.h"

Enigma::Enigma(const char* notches, const std::string* rotorPermutations)
	: mNotches(notches), mRotorPermutations(rotorPermutations)
{
}

void Enigma::addRotors(int r1, int r2, int r3)
{
	mRotorsArray[0] = new Rotor(r1, mNotches[r1 - 1], mRotorPermutations[r1 - 1]);
	mRotorsArray[1] = new Rotor(r1, mNotches[r2 - 1], mRotorPermutations[r2 - 1]);
	mRotorsArray[2] = new Rotor(r1, mNotches[r2 - 1], mRotorPermutations[r3 - 1]);
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

std::string Enigma::invertKey(std::string key)
{
	std::string ret;
	for (int i = 0; i < 26; i++)
	{
		ret += char(key.find(char(i + 65)) + 65);
	}
	return ret;
}

void Enigma::setOffsetPositions(const char* positions)
{
	for (int i = 0; i < 3; i++)
	{
		mRotorsArray[i]->setCurrentSetting(positions[i]);
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

int Enigma::mod(int a, int b)
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

char Enigma::wire(int rotorIndex, const char letter, int mode)
{
	std::string permutation;
	char setting;
	switch (mode)
	{
		case 0:
		{
			permutation = mRotorsArray[rotorIndex]->getRotorPermutation();
			setting = mRotorsArray[rotorIndex]->getCurrentSetting();
			break;
		}

		case 1:
		{
			permutation = mReflectorPermutation;
			setting = 'A';
			break;
		}

		case 2:
		{
			permutation = invertKey(mRotorsArray[rotorIndex]->getRotorPermutation());
			setting = mRotorsArray[rotorIndex]->getCurrentSetting();
			break;
		}
	}

	const int offset = int(setting) - 65;
	const int l = letter - 65;
	//int y = (l + offset) % 26;
	int y = mod((l + offset), 26);
	//int gap = ((permutation[y] - 65) - y) % 26;
	int gap = mod(((permutation[y] - 65) - y), 26);
	std::cout << "index: " << rotorIndex << std::endl;
	std::cout << permutation << std::endl;
	
	
	std::cout << "gap: " << gap << " for: " << char(y + 65) << std::endl;
	//int ret = (l + gap) % 26;
	int ret = mod((l + gap), 26);
	std::cout << letter << " --> " << char(ret + 65) << ret << std::endl;
	
	return char(ret + 65);
}

std::string Enigma::begin()
{
	std::string encodedMessage;
	for (int i = 0; i < mInputMessage.size(); i++)
	{
		char a = wire(2, mInputMessage[i], 0);
		char b = wire(1, a, 0);
		char c = wire(0, b, 0);
		char d = wire(-1, c, 1);
		char e = wire(0, d, 2);
		char f = wire(1, e, 2);
		char g = wire(2, f, 2);
		encodedMessage += g;
		rotate();
	}
	return encodedMessage;
}