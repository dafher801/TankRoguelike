
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

	// 이 함수는 (생성된 방정식 = 0) 의 근이 아니라 
	// (생성된 방정식 = 벽의 위치 좌표) 의 근을 구합니다.
	// 근이 1개가 아닐 것을 대비해서 배열형식으로 반환합니다.
	TArray<float> GetRoot();

	float GetYValue(float XValue) const;

	float GetDifferntiation(float XValue) const;

private:

	TArray<float> Equation;

	int MaxDegree;
	int CurrentDegree;
};
