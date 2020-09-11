#include "Rotor.h"
#include <iostream>
#include <string>

class Enigma
{
public:
	Enigma(const char* notches, const std::string* rotorPermutations);
	void rotate();
	std::string begin();
	void addRotors(int r1, int r2, int r3);
	void setOffsetPositions(const char* positions);
	void setInputMessage(std::string str);
	void setReflectorPermutation(std::string str);
	
private:
	Rotor* mRotorsArray[3];
	const char* mNotches;
	const std::string* mRotorPermutations;
	std::string mReflectorPermutation;
	std::string mInputMessage;
	std::string invertKey(std::string key);
	char wire(int rotor, const char letter, int mode);
	int mod(int a, int b);
};