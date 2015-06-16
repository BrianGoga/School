#ifndef MASK_CPP
#define MASK_CPP
#include "Gauss.cpp"

class Mask
{
public:
	Mask();
	~Mask();

	void buildGauss(float);
	void buildGaussFirstDeriv(float);

	int getDimention() const;
	const float& at(int) const;

private:
	int Dimention;
	float* Data;
};

Mask::Mask()
{
	Dimention = 0;
	Data = NULL;
}

Mask::~Mask()
{
	Dimention = 0;
	delete[] Data;
	Data = NULL;
}

void Mask::buildGauss(float Sig)
{
	Dimention = int(5 * Sig);

	if(Data != NULL)
		delete[] Data;

	Data = Gauss(Sig, Dimention);
}

void Mask::buildGaussFirstDeriv(float Sig)
{
	Dimention = int(5 * Sig);

	if(Data != NULL)
		delete[] Data;

	Data = Gauss_Deriv1(Sig, Dimention);
}

int Mask::getDimention() const
{
	return Dimention;
}

const float& Mask::at(int index) const
{
	return Data[index];
}

#endif