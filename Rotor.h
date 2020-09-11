#include <string>
class Rotor
{
public:
	Rotor(int index, char notch, std::string permutation);
	void setCurrentSetting(char setting);
	char getNotch() const;
	std::string getRotorPermutation() const;
	char getCurrentSetting() const;
	void incrementSetting();
private:
	const char mNotch;
	char mCurrentSetting;
	const std::string mRotorPermutation;
};