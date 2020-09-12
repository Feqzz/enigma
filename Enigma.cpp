#include "Enigma.h"

Enigma::Enigma(const char* notches, const std::string* rotorPermutations)
	: mNotches(notches), mRotorPermutations(rotorPermutations)
{
	for (int i = 0; i < 26; i++)
	{
		mModifiedAlphabet[i] = char(i + 65);
	}
}

void Enigma::addRotors(int r1, int r2, int r3)
{
	mRotorsArray[0] = new Rotor(r1, mNotches[r1 - 1], mRotorPermutations[r1 - 1]);
	mRotorsArray[1] = new Rotor(r2, mNotches[r2 - 1], mRotorPermutations[r2 - 1]);
	mRotorsArray[2] = new Rotor(r3, mNotches[r3 - 1], mRotorPermutations[r3 - 1]);
}

void Enigma::configurePlugboard(std::vector<std::string> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		char x = vec[i][0];
		char y = vec[i][1];
		mModifiedAlphabet[int(x - 65)] = y;
		mModifiedAlphabet[int(y - 65)] = x;
	}
}

void Enigma::rotate(int i)
{
	if (mRotorsArray[1]->getCurrentSetting() == mRotorsArray[1]->getNotch())
	{
		//std::cout << "NOTCH " << 1 << mRotorsArray[1]->getNotch() << " " << i << std::endl;
		mRotorsArray[1]->incrementSetting();
		mRotorsArray[0]->incrementSetting();
	}

	if (mRotorsArray[2]->getCurrentSetting() == mRotorsArray[2]->getNotch())
	{
		//std::cout << "NOTCH " << 2 << mRotorsArray[2]->getNotch() << " " << i << std::endl;
		mRotorsArray[1]->incrementSetting();
	}

	mRotorsArray[2]->incrementSetting();
	//std::cout << mRotorsArray[2]->getCurrentSetting();
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
	char ringSetting;
	switch (mode)
	{
		case 0:
		{
			permutation = mRotorsArray[rotorIndex]->getRotorPermutation();
			setting = mRotorsArray[rotorIndex]->getCurrentSetting();
			ringSetting = mRotorsArray[rotorIndex]->getRingSetting();
			break;
		}

		case 1:
		{
			permutation = mReflectorPermutation;
			setting = 'A';
			ringSetting = 'A';
			break;
		}

		case 2:
		{
			permutation = invertKey(mRotorsArray[rotorIndex]->getRotorPermutation());
			setting = mRotorsArray[rotorIndex]->getCurrentSetting();
			ringSetting = mRotorsArray[rotorIndex]->getRingSetting();
			//ringSetting = 'A';
			break;
		}
	}

	const int offset = int(setting) - 65;
	int ringOffset = int(ringSetting) - 65;

	int l = letter - 65;

	

	//int y = (l + offset) % 26;
	const int y = mod((l + offset), 26);

	int yyy = getRingPermutation(permutation, ringOffset, y);

	std::cout << "new: " << yyy;

	//permutation = setRingPermutation(permutation, ringOffset, l);
	//int gap = ((permutation[y] - 65) - y) % 26;
	//const int gap = mod(((permutation[y] - 65) - y), 26);

	const int gap = mod((getRingPermutation(permutation, ringOffset, y) - y), 26);



	std::cout << " old: " << permutation[y] - 65 << std::endl;
	
	//std::cout << "index: " << rotorIndex << std::endl;
	//std::cout << permutation << std::endl;
	//std::cout << "ring offset: " << ringOffset << std::endl;

	//std::string ok = setRingPermutation(permutation, ringOffset, l);
	
	
	//std::cout << "gap: " << gap << " for: " << char(y + 65) << std::endl;
	//int ret = (l + gap) % 26;
	const int ret = mod((l + gap), 26);
	
	//char xd = permutation[mod((permutation.find(char(ret + 65))), 26)];

	//std::cout << "letter" << xd << std::endl;

	//std::cout << letter << " --> " << xd << " " << char(ret + 65) << std::endl;
	//std::cout << letter << " --> " << char(ret + 65) << std::endl;
	
	return char(ret + 65);
	//return xd;
}

std::string Enigma::setRingPermutation(std::string str, int ring, int letter)
{
	std::string ret = str;

	for (int i = 0; i < 26; i++)
	{
		int gap = mod(((str[i] - 65) - i), 26);
		ret[mod((i + ring), 26)] = char(65 + mod((i + ring + gap), 26));
	}
	return ret;
}

int Enigma::getRingPermutation(std::string str, int ring, int letter)
{
	int gap = mod(((str[mod((letter - ring), 26)] - 65) - letter + ring), 26);
	//std::cout << "GAP: " << gap << std::endl;
	int ret = mod((letter + gap), 26);
	return ret;
}

std::string Enigma::begin()
{
	std::string encodedMessage;
	for (int i = 0; i < mInputMessage.size(); i++)
	{
		rotate(i);
		char a = wire(2, mModifiedAlphabet[mInputMessage[i] - 65] , 0);
		char b = wire(1, a, 0);
		char c = wire(0, b, 0);
		char d = wire(-1, c, 1);
		char e = wire(0, d, 2);
		char f = wire(1, e, 2);
		char g = wire(2, f, 2);

		if (((i % 5) == 0) && i > 0)
		{
			encodedMessage += " ";
		}

		encodedMessage += mModifiedAlphabet[g - 65];
	}
	return encodedMessage;
}