#include "Rotor.h"

Rotor::Rotor(int index, char notch, std::string permutation)
	: mNotch(notch), mRotorPermutation(permutation)
{
}

char Rotor::getNotch() const
{
	return mNotch;
}

std::string Rotor::getRotorPermutation() const
{
	return mRotorPermutation;
}

char Rotor::getCurrentSetting() const
{
	return mCurrentSetting;
}

void Rotor::setCurrentSetting(char setting)
{
	mCurrentSetting = setting;
}

void Rotor::incrementSetting()
{
	mCurrentSetting = int(mCurrentSetting) + 1;
}