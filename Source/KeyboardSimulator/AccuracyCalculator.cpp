// Fill out your copyright notice in the Description page of Project Settings.


#include "AccuracyCalculator.h"
#include "Kismet/KismetMathLibrary.h"

namespace AccuracyCalculator
{
    int CalculateLevenshteinDistance(FString Original, FString Copy)
    {
        // Construct a matrix of Levenshtein distances for all the possible combinations of prefixes
        // The previous and current rows of the matrix being constructed
        TArray<int> PreviousRow;
        TArray<int> CurrentRow;

        PreviousRow.Init(0, Copy.Len()+1);
        CurrentRow.Init(0, Copy.Len()+1);

        // Initialize the first row of the matrix
        // Distances to insert characters to create Original.
        for (int i = 0; i <= Copy.Len(); ++i)
        {
            PreviousRow[i] = i;
        }

        for (int i = 0; i < Original.Len(); ++i)
        {
            // Initialize the first element of the CurrentRow (initializing first column of matrix)
            // Distances to delete characters from Original to create Copy
            CurrentRow[0] = i + 1;

            // Fill in remaining values by taking minimum of deletion, insertion, substitution
            for (int j = 0; j < Copy.Len(); ++j)
            {
                int deletion = PreviousRow[j + 1] + 1;
                int insertion = CurrentRow[j] + 1;

                int substitution;
                if (Original[i] == Copy[j])
                {
                    substitution = PreviousRow[j];
                }
                else
                {
                    substitution = PreviousRow[j] + 1;
                }

                CurrentRow[j + 1] = FMath::Min3(deletion, insertion, substitution);
            }
            Swap(PreviousRow, CurrentRow);
        }

        return PreviousRow[Copy.Len()];
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