#include "Rotor.h"
#include <iostream>
#include <string>
#include <vector>

class Enigma
{
public:
	Enigma(const char* notches, const std::string* rotorPermutations);
	void rotate(int i);
	std::string begin();
	void addRotors(int r1, int r2, int r3);
	void setOffsetPositions(const char* positions, const char* ringPositions);
	void setInputMessage(std::string str);
	void setReflectorPermutation(std::string str);
	void configurePlugboard(std::vector<std::string> vec);
	
private:
	char wire(int rotor, const char letter, int mode);
	int mod(int a, int b) const;
	int getRingedCharacter(std::string str, int ring, int letter) const;
	std::string invertKey(std::string key) const;

	Rotor* mRotorsArray[3];
	const char* mNotches;
	const std::string* mRotorPermutations;
	std::string mReflectorPermutation;
	std::string mInputMessage;
	char mModifiedAlphabet[26];
	
};