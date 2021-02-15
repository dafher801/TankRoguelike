
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Array.h"
#include "Equation.generated.h"

UCLASS()
class TANKROGUELIKE_API UEquation : public UObject
{
	GENERATED_BODY()
	
public:

	UEquation();

	void MakeRandomEquation();

	// �� �Լ��� (������ ������ = 0) �� ���� �ƴ϶� 
	// (������ ������ = ���� ��ġ ��ǥ) �� ���� ���մϴ�.
	// ���� 1���� �ƴ� ���� ����ؼ� �迭�������� ��ȯ�մϴ�.
	TArray<float> GetRoot();

	float GetYValue(float XValue) const;

	float GetDifferntiation(float XValue) const;

private:

	TArray<float> Equation;

	int MaxDegree;
	int CurrentDegree;
};
