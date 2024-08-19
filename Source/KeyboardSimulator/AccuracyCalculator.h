// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
namespace AccuracyCalculator
{
    int CalculateLevenshteinDistance(FString Original, FString Copy);

    float CalculateAccuracy(int LevenshteinDistance, int MaxLength);

    float CalculateAverageAccuracy(float CurrentAccuracy, float NewAccuracy, int CommissionCount);
}
