
#include "Equation.h"

#include <random>

UEquation::UEquation()
	: MaxDegree(4)
{
	for (int i = 0; i <= MaxDegree; i++)
		Equation.Add(i);

	MakeRandomEquation();
}

void UEquation::MakeRandomEquation()
{
	bool Sign;

	CurrentDegree = rand() % (MaxDegree + 1);

	for (int i = 0; i <= CurrentDegree; i++)
	{
		Sign = static_cast<bool>(rand() % 2);
		Equation[i] = i ? rand() % (10 / i) : rand() % 10;

		if (Sign)
			Equation[i] *= -1;

		UE_LOG(LogClass, Warning, TEXT("%d Degree: %f"), i, Equation[i]);
	}
}

TArray<float> UEquation::GetRoot()
{
	TArray<float> Roots;
	float x0 = 0.0f;
	float xp = x0;
	float div;

	int i;
	const int MAX_TRY = 100;

	for (i = 0; i < MAX_TRY; i++)
	{
		x0 = xp;
		div = GetDifferntiation(x0);

		if (FMath::Abs(div) <= 0.0f)
			break;

		xp = x0 - GetYValue(x0) / div;

		if (FMath::Abs(x0 - xp) <= 0.0f)
			break;
	}

	UE_LOG(LogClass, Warning, TEXT("root: %f"), xp);
	Roots.Add(xp);

	return Roots;
}

float UEquation::GetYValue(float XValue) const
{
	float YValue = 0.0f;
	float TermValue;
	int i, j;

	for (i = 0; i <= CurrentDegree; i++)
	{
		for (j = 0, TermValue = 1.0f; j < i; j++)
			TermValue *= XValue;

		TermValue *= Equation[i];
		YValue += TermValue;
	}

	return YValue;
}

float UEquation::GetDifferntiation(float XValue) const
{
	float YValue = 0.0f;
	float TermValue;
	int i, j;

	for (i = 1; i <= CurrentDegree; i++)
	{
		for (j = 0, TermValue = 1.0f; j < i - 1; j++)
			TermValue *= XValue;

		TermValue *= (Equation[i] * i);
		YValue += TermValue;
	}

	return YValue;
}