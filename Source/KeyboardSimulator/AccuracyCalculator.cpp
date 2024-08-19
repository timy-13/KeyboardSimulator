// Fill out your copyright notice in the Description page of Project Settings.


#include "AccuracyCalculator.h"
#include "Kismet/KismetMathLibrary.h"

namespace AccuracyCalculator
{
    int CalculateLevenshteinDistance(FString Original, FString Copy)
    {
        float MaxLength = FMath::Max(Original.Len(), Copy.Len());

        if (Original.IsEmpty() || Copy.IsEmpty())
        {
            return MaxLength;
        }

        int substitution = CalculateLevenshteinDistance(Original.RightChop(1), Copy.RightChop(1));

        if (Original[0] == Copy[0])
        {
            return substitution;
        }
        
        int insertion = CalculateLevenshteinDistance(Original.RightChop(1), Copy);
        int deletion = CalculateLevenshteinDistance(Original, Copy.RightChop(1));

        return FMath::Min3(substitution, insertion, deletion);
    }

    float CalculateAccuracy(int LevenshteinDistance, int MaxLength)
    {
        return (MaxLength - LevenshteinDistance) / MaxLength;
    }

    float CalculateAverageAccuracy(float CurrentAccuracy, float NewAccuracy, int CommissionCount)
    {
        return (CurrentAccuracy*(CommissionCount-1) + NewAccuracy) / CommissionCount;
    }
}