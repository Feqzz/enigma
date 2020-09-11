#include <string>
class Rotor
{
public:
	Rotor(int index, char notch, std::string permutation);
	void setCurrentSetting(char setting);
	void setRingSetting(char setting);
	char getNotch() const;
	std::string getRotorPermutation() const;
	char getCurrentSetting() const;
	char getRingSetting() const;
	void incrementSetting();
private:
	const char mNotch;
	char mCurrentSetting;
	char mRingSetting;
	const std::string mRotorPermutation;
};