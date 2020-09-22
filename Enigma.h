#include "Rotor.h"
#include <iostream>
#include <string>
#include <vector>

class Enigma
{
public:
	Enigma(const char* notches, const std::string* rotorPermutations);
	std::string begin();
	void addRotors(int arr[3]);
	void setOffsetPositions(const char* positions, const char* ringPositions);
	void setInputMessage(std::string str);
	void setReflectorPermutation(std::string str);
	void configurePlugboard(std::vector<std::string> vec);
	
private:
	void rotate();
	char wire(const int rotor, const char letter, const int mode);
	int mod(const int a, const int b) const;
	int getRingedCharacter(const std::string permutation, const int ring, const int letter) const;
	std::string invertKey(const std::string key) const;

	Rotor* mRotorsArray[3];
	const char* mNotches;
	const std::string* mRotorPermutations;
	std::string mReflectorPermutation;
	std::string mInputMessage;
	char mModifiedAlphabet[26];
};