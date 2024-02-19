#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ProjectFunc.h"
#include <stdbool.h>

void yearlyMinMax(record *values, date *dates, int year, int j, float *max, float *min)
{
    if (dates[j].year == year)
    {
        if (values[j].MarketHigh > *max)
            *max = values[j].MarketHigh;
        if (values[j].MarketLow < *min)
            *min = values[j].MarketLow;
    }
}

void quarterlyMinMax(record *values, date *dates, int year, int j, float *min1, float *max1, float *min2, float *max2, float *min3, float *max3, float *min4, float *max4)
{
    if (dates[j].year == year)
    {
        for (int i = 1; i <= 12; i++)
        {
            int k = 0;
            if (i == dates[j].month && i <= 3)
            {
                while (k <= 31)
                {
                    if (k <= dates[j].day)
                    {
                        if (values[j].MarketHigh > *max1)
                            *max1 = values[j].MarketHigh;
                        if (values[j].MarketLow < *min1)
                            *min1 = values[j].MarketLow;
                    }
                    k++;
                }
            }

            if (i == dates[j].month && i > 3 && i <= 6)
            {
                while (k <= 31)
                {
                    if (k <= dates[j].day)
                    {
                        if (values[j].MarketHigh > *max2)
                            *max2 = values[j].MarketHigh;
                        if (values[j].MarketLow < *min2)
                            *min2 = values[j].MarketLow;
                    }
                    k++;
                }
            }

            if (i == dates[j].month && i > 6 && i <= 9)
            {
                while (k <= 31)
                {
                    if (k <= dates[j].day)
                    {
                        if (values[j].MarketHigh > *max3)
                            *max3 = values[j].MarketHigh;
                        if (values[j].MarketLow < *min3)
                            *min3 = values[j].MarketLow;
                    }
                    k++;
                }
            }

            if (i == dates[j].month && i > 9 && i <= 12)
            {
                while (k <= 31)
                {
                    if (k <= dates[j].day)
                    {
                        if (values[j].MarketHigh > *max4)
                            *max4 = values[j].MarketHigh;
                        if (values[j].MarketLow < *min4)
                            *min4 = values[j].MarketLow;
                    }
                    k++;
                }
            }
        }
    }
}

void monthlyMinMax(record *values, date *dates, int year, int month, int j, float *min, float *max)
{
    int k = 0;
    if (dates[j].year == year)
    {
        if (dates[j].month == month)
        {
            while (k <= 31)
            {
                if (k <= dates[j].day)
                {
                    if (values[j].MarketHigh > *max)
                        *max = values[j].MarketHigh;
                    if (values[j].MarketLow < *min)
                        *min = values[j].MarketLow;
                }
                k++;
            }
        }
    }
}

float percentageOpenClose(record *values, int i)
{
    float difference, percentage;

    difference = values[i].MarketClose - values[i].MarketOpen;
    percentage = (difference / values[i].MarketOpen) * 100;

    return percentage;
}

float yearlyPercentageOpenClose(record *values, float open, int i, int year, date *dates)
{
    // Yearly average of the percentages increase/decrease.
    float percentage;
    if (dates[i].year == year)
    {
        return percentage = ((values[i].MarketClose - open) / open) * 100;
    }
}

float monthlyPercentageOpenClose(record *values, int month, float open, int i, int year, date *dates)
{
    float percentage;
    if (dates[i].year == year)
    {
        if (dates[i].month == month)
        {
            return percentage = ((values[i].MarketClose - open) / open) * 100;
        }
    }
}

float quarterlyPercentageOpenClose(record *values, date *dates, int year, int j, float *open1, float *open2, float *open3, float *open4, float *percentage1, float *percentage2, float *percentage3, float *percentage4)
{
    if (dates[j].year == year)
    {
        for (int i = 1; i <= 12; i++)
        {
            int k = 0;
            if (i == dates[j].month && i <= 3)
            {
                while (k <= 31)
                {

                    if (k <= dates[j].day)
                    {
                        *percentage1 = ((values[j].MarketClose - *open1) / *open1) * 100;
                    }
                    k++;
                }
            }

            if (i == dates[j].month && i > 3 && i <= 6)
            {
                while (k <= 31)
                {
                    if (k <= dates[j].day)
                    {
                        *percentage2 = ((values[j].MarketClose - *open2) / *open2) * 100;
                    }
                    k++;
                }
            }

            if (i == dates[j].month && i > 6 && i <= 9)
            {
                while (k <= 31)
                {
                    if (k <= dates[j].day)
                    {
                        *percentage3 = ((values[j].MarketClose - *open3) / *open3) * 100;
                    }
                    k++;
                }
            }

            if (i == dates[j].month && i > 9 && i <= 12)
            {
                while (k <= 31)
                {
                    if (k <= dates[j].day)
                    {
                        *percentage4 = ((values[j].MarketClose - *open4) / *open4) * 100;
                    }
                    k++;
                }
            }
        }
    }
}

void monthlySums(record *values, date *dates, int year, int month, int j, float *close, float *open, float *low, float *high, float *volume, int *nbDays)
{
    int k = 0;

    if (dates[j].year == year)
    {
        if (dates[j].month == month)
        {
            if (k <= dates[j].day)
            {
                *open += values[j].MarketOpen;
                *close += values[j].MarketClose;
                *low += values[j].MarketLow;
                *high += values[j].MarketHigh;
                *volume += values[j].Volume;
                *nbDays += 1;
            }
            k++;
        }
    }
}

void monthlyAverage(float *close, float *open, float *low, float *high, float *volume, int nbDays)
{
    *close = (*close) / nbDays;
    *open = (*open) / nbDays;
    *low = (*low) / nbDays;
    *high = (*high) / nbDays;
    *volume = (*volume) / nbDays;
}

void yearlySums(record *values, date *dates, int year, int j, float *close, float *open, float *low, float *high, float *volume, int *nbDays)
{

    if (dates[j].year == year)
    {
        *open += values[j].MarketOpen;
        *close += values[j].MarketClose;
        *low += values[j].MarketLow;
        *high += values[j].MarketHigh;
        *volume += values[j].Volume;
        *nbDays += 1;
    }
}

float yearlyAverage(int nbDays, float *close, float *open, float *low, float *high, float *volume)
{
    *close = (*close) / nbDays;
    *open = (*open) / nbDays;
    *low = (*low) / nbDays;
    *high = (*high) / nbDays;
    *volume = (*volume) / nbDays;
}

float quarterlySums(record *values, date *dates, int year, int j, float *close1, float *open1, float *low1, float *high1, float *volume1, int *nbDays1, float *close2, float *open2, float *low2, float *high2, float *volume2, int *nbDays2, float *close3, float *open3, float *low3, float *high3, float *volume3, int *nbDays3, float *close4, float *open4, float *low4, float *high4, float *volume4, int *nbDays4)
{
    if (dates[j].year == year)
    {
        for (int i = 1; i <= 12; i++)
        {
            int k = 0;
            if (i == dates[j].month && i <= 3)
            {
                while (k <= 31)
                {
                    if (k <= dates[j].day)
                    {
                        *open1 += values[j].MarketOpen;
                        *close1 += values[j].MarketClose;
                        *low1 += values[j].MarketLow;
                        *high1 += values[j].MarketHigh;
                        *volume1 += values[j].Volume;
                        *nbDays1 += 1;
                    }
                    k++;
                }
            }

            if (i == dates[j].month && i > 3 && i <= 6)
            {
                while (k <= 31)
                {
                    if (k <= dates[j].day)
                    {
                        *open2 += values[j].MarketOpen;
                        *close2 += values[j].MarketClose;
                        *low2 += values[j].MarketLow;
                        *high2 += values[j].MarketHigh;
                        *volume2 += values[j].Volume;
                        *nbDays2 += 1;
                    }
                    k++;
                }
            }

            if (i == dates[j].month && i > 6 && i <= 9)
            {
                while (k <= 31)
                {
                    if (k <= dates[j].day)
                    {
                        *open3 += values[j].MarketOpen;
                        *close3 += values[j].MarketClose;
                        *low3 += values[j].MarketLow;
                        *high3 += values[j].MarketHigh;
                        *volume3 += values[j].Volume;
                        *nbDays3 += 1;
                    }
                    k++;
                }
            }

            if (i == dates[j].month && i > 9 && i <= 12)
            {
                while (k <= 31)
                {
                    if (k <= dates[j].day)
                    {
                        *open4 += values[j].MarketOpen;
                        *close4 += values[j].MarketClose;
                        *low4 += values[j].MarketLow;
                        *high4 += values[j].MarketHigh;
                        *volume4 += values[j].Volume;
                        *nbDays4 += 1;
                    }
                    k++;
                }
            }
        }
    }
}

float quarterlyAverage(float *close1, float *open1, float *low1, float *high1, float *volume1, int nbDays1, float *close2, float *open2, float *low2, float *high2, float *volume2, int nbDays2, float *close3, float *open3, float *low3, float *high3, float *volume3, int nbDays3, float *close4, float *open4, float *low4, float *high4, float *volume4, int nbDays4)
{
    *close1 = (*close1) / nbDays1;
    *open1 = (*open1) / nbDays1;
    *low1 = (*low1) / nbDays1;
    *high1 = (*high1) / nbDays1;
    *volume1 = (*volume1) / nbDays1;

    *close2 = (*close2) / nbDays2;
    *open2 = (*open2) / nbDays2;
    *low2 = (*low2) / nbDays2;
    *high2 = (*high2) / nbDays2;
    *volume2 = (*volume2) / nbDays2;

    *close3 = (*close3) / nbDays3;
    *open3 = (*open3) / nbDays3;
    *low3 = (*low3) / nbDays3;
    *high3 = (*high3) / nbDays3;
    *volume3 = (*volume3) / nbDays3;

    *close4 = (*close4) / nbDays4;
    *open4 = (*open4) / nbDays4;
    *low4 = (*low4) / nbDays4;
    *high4 = (*high4) / nbDays4;
    *volume4 = (*volume4) / nbDays4;
}

float allSums(record *values, int j, float *close, float *open, float *low, float *high, float *volume, int *nbDays)
{
    *open += values[j].MarketOpen;
    *close += values[j].MarketClose;
    *low += values[j].MarketLow;
    *high += values[j].MarketHigh;
    *volume += values[j].Volume;
    *nbDays += 1;
}

float Average(float *close, float *open, float *low, float *high, float *volume, int nbDays)
{
    *close = (*close) / nbDays;
    *open = (*open) / nbDays;
    *low = (*low) / nbDays;
    *high = (*high) / nbDays;
    *volume = (*volume) / nbDays;
}

void reportPercentageQuarterly(char symbol, int year, float *percentage, FILE *file)
{
    char title[10];
    char IncDec[] = "decrease";
    char IncDec1[] = "decrease";
    char IncDec2[] = "decrease";
    char IncDec3[] = "decrease";
    titleAlways(symbol, title);

    if (percentage[0] > 0)
        strcpy(IncDec, "increase");
    if (percentage[1] > 0)
        strcpy(IncDec1, "increase");
    if (percentage[2] > 0)
        strcpy(IncDec2, "increase");
    if (percentage[3] > 0)
        strcpy(IncDec3, "increase");

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks during the year %d\nQuarter 1 had a percentage %s of %.2f%% \n"
           "Quarter 2 had a percentage %s of %.2f%% \n"
           "Quarter 3 had a percentage %s of %.2f%% \n"
           "Quarter 4 had a percentage %s of %.2f%% \n",
           title, year, IncDec, percentage[0], IncDec1, percentage[1], IncDec2, percentage[2], IncDec3, percentage[3]);

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks during the year %d\nQuarter 1 had a percentage %s of %.2f%% \n"
                  "Quarter 2 had a percentage %s of %.2f%% \n"
                  "Quarter 3 had a percentage %s of %.2f%% \n"
                  "Quarter 4 had a percentage %s of %.2f%% \n",
            title, year, IncDec, percentage[0], IncDec1, percentage[1], IncDec2, percentage[2], IncDec3, percentage[3]);
}

void reportPercentageQuarter(char symbol, int year, float percentage, int q, FILE *file)
{
    char title[10];
    char IncDec[] = "decrease";
    titleAlways(symbol, title);

    if (percentage > 0)
        strcpy(IncDec, "increase");
    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks during the year %d and Quarter %d had a percentage %s of %.2f%% \n",
           title, year, q, IncDec, percentage);

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks during the year %d and Quarter %d had a percentage %s of %.2f%% \n",
            title, year, q, IncDec, percentage);
}

void comparePercent(float percent1, float percent2, char symbol1, char symbol2, int DayYearMonthQuarter, int year, int day, int month, int quarter, FILE *file)
{

    char title[10], title1[10];
    titleAlways(symbol1, title);
    titleAlways(symbol2, title1);
    float newPercent = 0;
    char string[10];
    monthAlways(month, string);

    char flag1 = (percent1) > (percent2) ? '1' : '2';

    switch (flag1)
    {
    case '1':

        newPercent = percent1 - percent2;
        printf("%s has a higher percentage between open and close than %s\n", title, title1);

        fprintf(file, "\n\n---------------------------------------------------------------------\n");
        fprintf(file, "%s has a higher percentage between open and close than %s\n", title, title1);

        if (DayYearMonthQuarter == 0)
        { // year
            printf("\nDuring the year %d %s percentage was %.2f%% and %s percentage between open and close was %.2f%%, there was a difference of %.2f%%\n", year, title, percent1, title1, percent2, newPercent);

            fprintf(file, "\nDuring the year %d %s percentage was %.2f%% and %s percentage between open and close was %.2f%%, there was a difference of %.2f%%\n", year, title, percent1, title1, percent2, newPercent);
        }
        if (DayYearMonthQuarter == 1)
        { // quarter
            printf("\nDuring the year %d and in quarter %d %s percentage between open and close was %.2f%% and %s percentage was %.2f%%, there was a difference of %.2f%%\n", year, quarter, title, percent1, title1, percent2, newPercent);

            fprintf(file, "\nDuring the year %d and in quarter %d %s percentage between open and close was %.2f%% and %s percentage was %.2f%%, there was a difference of %.2f%%\n", year, quarter, title, percent1, title1, percent2, newPercent);
        }
        if (DayYearMonthQuarter == 2)
        { // month
            printf("\nDuring the year %d and the %s month %s percentage between open and close was %.2f%% and %s percentage was %.2f%%, there was a difference of %.2f%%\n", year, string, title, percent1, title1, percent2, newPercent);

            fprintf(file, "\nDuring the year %d and the %s month %s percentage between open and close was %.2f%% and %s percentage was %.2f%%, there was a difference of %.2f%%\n", year, string, title, percent1, title1, percent2, newPercent);
        }
        if (DayYearMonthQuarter == 3)
        { // day
            printf("\nDuring the year %d and the %s month on the %d day %s percentage between open and close was %.2f%% and %s percentage was %.2f%%, there was a difference of %.2f%%\n", year, string, day, title, percent1, title1, percent2, newPercent);

            fprintf(file, "\nDuring the year %d and the %s month on the %d day %s percentage between open and close was %.2f%% and %s percentage was %.2f%%, there was a difference of %.2f%%\n", year, string, day, title, percent1, title1, percent2, newPercent);
        }

        break;
    case '2':
        newPercent = percent2 - percent1;
        printf("%s has a higher percentage between open and close than %s\n", title1, title);

        fprintf(file, "\n\n---------------------------------------------------------------------\n");
        fprintf(file, "%s has a higher percentage between open and close than %s\n", title1, title);

        if (DayYearMonthQuarter == 0)
        { // year
            printf("\nDuring the year %d %s percentage was %.2f%% and %s percentage between open and close was %.2f%%, there was a difference of %.2f%%\n\n", year, title1, percent2, title, percent1, newPercent);

            fprintf(file, "\nDuring the year %d %s percentage was %.2f%% and %s percentage between open and close was %.2f%%, there was a difference of %.2f%%\n\n", year, title1, percent2, title, percent1, newPercent);
        }
        if (DayYearMonthQuarter == 1)
        { // quarter
            printf("\nDuring the year %d and in quarter %d %s percentage between open and close was %.2f%% and %s percentage was %.2f%%, there was a difference of %.2f%%\n\n", year, quarter, title1, percent2, title, percent1, newPercent);

            fprintf(file, "\nDuring the year %d and in quarter %d %s percentage between open and close was %.2f%% and %s percentage was %.2f%%, there was a difference of %.2f%%\n\n", year, quarter, title1, percent2, title, percent1, newPercent);
        }
        if (DayYearMonthQuarter == 2)
        { // month
            printf("\nDuring the year %d and the %s month %s percentage between open and close was %.2f%% and %s percentage was %.2f%%, there was a difference of %.2f%%\n\n", year, string, title1, percent2, title, percent1, newPercent);

            fprintf(file, "\nDuring the year %d and the %s month %s percentage between open and close was %.2f%% and %s percentage was %.2f%%, there was a difference of %.2f%%\n\n", year, string, title1, percent2, title, percent1, newPercent);
        }
        if (DayYearMonthQuarter == 3)
        { // day
            printf("During the year %d and the %s month on the %d day %s percentage between open and close was %.2f%% and %s percentage was %.2f%%, there was a difference of %.2f%%\n\n", year, string, day, title1, percent2, title, percent1, newPercent);

            fprintf(file, "During the year %d and the %s month on the %d day %s percentage between open and close was %.2f%% and %s percentage was %.2f%%, there was a difference of %.2f%%\n\n", year, string, day, title1, percent2, title, percent1, newPercent);
        }
        break;
    default:

        break;
    }
}

void reportMonthlyAverage(char symbols, int year, int month, float open, float close, float high, float low, int volume, FILE *file)
{
    char monthString[10];
    char title[10];
    monthAlways(month, monthString);

    titleAlways(symbols, title);

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks had overall averages in the year %d during the %s month consisting of the following:\nThe stocks had Open: $%.2f, Close: $%.2f.\n"
           "The stocks reached an average high of $%.2f"
           " and a low of $%.2f.\nIt's average trade volume consisted of %d.\n\n",
           title, year, monthString, open, close, high, low, volume);
    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks had overall averages in the year %d during the %s month consisting of the following:\nThe stocks had Open: $%.2f, Close: $%.2f.\n"
                  "The stocks reached an average high of $%.2f"
                  " and a low of $%.2f.\nIt's average trade volume consisted of %d.\n\n",
            title, year, monthString, open, close, high, low, volume);
}

void reportYearlyAverage(char symbols, int year, float open, float close, float high, float low, int volume, FILE *file)
{

    char title[10];

    titleAlways(symbols, title);

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks had overall averages in the year %d consisting of the following:\nThe stocks had Open: $%.2f, Close: $%.2f.\n"
           "The stocks reached an average high of $%.2f"
           " and a low of $%.2f.\nIt's average trade volume consisted of %d.\n\n",
           title, year, open, close, high, low, volume);

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks had overall averages in the year %d consisting of the following:\nThe stocks had Open: $%.2f, Close: $%.2f.\n"
                  "The stocks reached an average high of $%.2f"
                  " and a low of $%.2f.\nIt's average trade volume consisted of %d.\n\n",
            title, year, open, close, high, low, volume);
}

void reportQuarterAverage(char symbols, int year, float open, float close, float high, float low, float volume, int quart, FILE *file)
{

    char title[10];

    titleAlways(symbols, title);

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks had overall averages in the year %d and quarter %d consisting of the following:\nThe stocks had Open: $%.2f, Close: $%.2f.\n"
           "The stocks reached an average high of $%.2f"
           " and a low of $%.2f.\nIt's average trade volume consisted of %.2f.\n\n",
           title, year, quart, open, close, high, low, volume);

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks had overall averages in the year %d and quarter %d consisting of the following:\nThe stocks had Open: $%.2f, Close: $%.2f.\n"
                  "The stocks reached an average high of $%.2f"
                  " and a low of $%.2f.\nIt's average trade volume consisted of %.2f.\n\n",
            title, year, quart, open, close, high, low, volume);
}

void reportQuarterlyAverage(float *open, float *close, float *high, float *low, float *volume, char symbols, int year, FILE *file)
{
    char title[10];

    titleAlways(symbols, title);

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks had overall averages during the year %d consisting of:\n"
           "Quarter 1: \nThe stocks had Open: $%.2f, Close: $%.2f.\n"
           "The stocks reached an average high of $%.2f"
           " and a low of $%.2f.\nIt's average trade volume consisted of %.2f.\n"
           "Quarter 2: \nThe stocks had Open: $%.2f, Close: $%.2f.\n"
           "The stocks reached an average high of $%.2f"
           " and a low of $%.2f.\nIt's average trade volume consisted of %.2f.\n"
           "Quarter 3: \nThe stocks had Open: $%.2f, Close: $%.2f.\n"
           "The stocks reached an average high of $%.2f"
           " and a low of $%.2f.\nIt's average trade volume consisted of %.2f.\n"
           "Quarter 4: \nThe stocks had Open: $%.2f, Close: $%.2f.\n"
           "The stocks reached an average high of $%.2f"
           " and a low of $%.2f.\nIt's average trade volume consisted of %.2f.\n\n",
           title, year, open[0], close[0], high[0], low[0], volume[1], open[1], close[1], high[1], low[1], volume[1],
           open[2], close[2], high[2], low[2], volume[2], open[3], close[3], high[3], low[3], volume[3]);

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks had overall averages during the year %d consisting of:\n"
                  "Quarter 1: \nThe stocks had Open: $%.2f, Close: $%.2f.\n"
                  "The stocks reached an average high of $%.2f"
                  " and a low of $%.2f.\nIt's average trade volume consisted of %.2f.\n"
                  "Quarter 2: \nThe stocks had Open: $%.2f, Close: $%.2f.\n"
                  "The stocks reached an average high of $%.2f"
                  " and a low of $%.2f.\nIt's average trade volume consisted of %.2f.\n"
                  "Quarter 3: \nThe stocks had Open: $%.2f, Close: $%.2f.\n"
                  "The stocks reached an average high of $%.2f"
                  " and a low of $%.2f.\nIt's average trade volume consisted of %.2f.\n"
                  "Quarter 4: \nThe stocks had Open: $%.2f, Close: $%.2f.\n"
                  "The stocks reached an average high of $%.2f"
                  " and a low of $%.2f.\nIt's average trade volume consisted of %.2f.\n\n",
            title, year, open[0], close[0], high[0], low[0], volume[1], open[1], close[1], high[1], low[1], volume[1],
            open[2], close[2], high[2], low[2], volume[2], open[3], close[3], high[3], low[3], volume[3]);
}

void reportAverage(char symbols, float open, float close, float high, float low, int volume, FILE *file)
{

    char title[10];

    titleAlways(symbols, title);

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks had overall averages consisting of the following:\nThe stocks had Open: $%.2f, Close: $%.2f.\n"
           "The stocks reached an average high of $%.2f"
           " and a low of $%.2f.\nIt's average trade volume consisted of %d.\n\n",
           title, open, close, high, low, volume);
    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks had overall averages consisting of the following:\nThe stocks had Open: $%.2f, Close: $%.2f.\n"
                  "The stocks reached an average high of $%.2f"
                  " and a low of $%.2f.\nIt's average trade volume consisted of %d.\n\n",
            title, open, close, high, low, volume);
}

void reportGivenDay(record *values, int i, FILE *file)
{
    char symbols = values[i].Symbol[0];
    char title[10];

    titleAlways(symbols, title);

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks on %s opened at $%.2f and closed at $%.2f.\nThe stocks reached a high of $%.2f"
           " and a low of $%.2f.\nIt's total trade volume consisted of %d.\n\n",
           title, values[i].Date,
           values[i].MarketOpen, values[i].MarketClose, values[i].MarketHigh, values[i].MarketLow, values[i].Volume);

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks on %s opened at $%.2f and closed at $%.2f.\nThe stocks reached a high of $%.2f"
                  " and a low of $%.2f.\nIt's total trade volume consisted of %d.\n\n",
            title, values[i].Date,
            values[i].MarketOpen, values[i].MarketClose, values[i].MarketHigh, values[i].MarketLow, values[i].Volume);
}

void reportHighLowYearly(float max, float min, char symbol, int date, FILE *file)
{
    char title[10];

    titleAlways(symbol, title);

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks during the year %d had a maximum high of $%.2f and a low of $%.2f\n\n",
           title, date, max, min);

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks during the year %d had a maximum high of $%.2f and a low of $%.2f\n\n",
            title, date, max, min);
}

void reportPercentageYear(char symbol, int year, float percentage, FILE *file)
{
    char title[10];
    char IncDec[] = "decrease";

    titleAlways(symbol, title);
    if (percentage > 0)
        strcpy(IncDec, "increase");

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks during the year %d had a percentage %s of %.2f%% \n\n",
           title, year, IncDec, percentage);

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks during the year %d had a percentage %s of %.2f%% \n\n",
            title, year, IncDec, percentage);
}

void reportPercentageMonth(char symbol, int year, float percentage, int month, FILE *file)
{
    char title[10];
    char monthString[10];
    char IncDec[] = "decrease";
    monthAlways(month, monthString);
    titleAlways(symbol, title);
    if (percentage > 0)
        strcpy(IncDec, "increase");

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks during the year %d and the %s month had a percentage %s of %.2f%% \n\n",
           title, year, monthString, IncDec, percentage);

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks during the year %d and the %s month had a percentage %s of %.2f%% \n\n",
            title, year, monthString, IncDec, percentage);
}

void reportHighLowOneQuarter(int quarter, float max, float min, char symbol, int date, FILE *file)
{
    char title[10];

    titleAlways(symbol, title);

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks during quarter %d of the year %d: had a high of $%.2f and a low of $%.2f.\n\n",
           title, quarter, date, max, min);

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks during quarter %d of the year %d: had a high of $%.2f and a low of $%.2f.\n\n",
            title, quarter, date, max, min);
}

void reportHighLowQuarterly(float *max, float *min, char symbol, int date, FILE *file)
{
    char title[10];

    titleAlways(symbol, title);

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks during the year %d:\nQuarter 1 had a high of $%.2f and a low of $%.2f.\n"
           "Quarter 2 had a high of $%.2f and a low of $%.2f.\nQuarter 3 had a "
           "high of $%.2f and a low of $%.2f.\nQuarter 4 had a high of $%.2f and a low of $%.2f.\n\n",
           title, date, max[0], min[0], max[1], min[1], max[2], min[2], max[3], min[3]);

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks during the year %d:\nQuarter 1 had a high of $%.2f and a low of $%.2f.\n"
                  "Quarter 2 had a high of $%.2f and a low of $%.2f.\nQuarter 3 had a "
                  "high of $%.2f and a low of $%.2f.\nQuarter 4 had a high of $%.2f and a low of $%.2f.\n\n",
            title, date, max[0], min[0], max[1], min[1], max[2], min[2], max[3], min[3]);
}

void reportHighLowMonthly(float max, float min, char symbol, int year, int month, FILE *file)
{
    char title[10];
    char monthString[10];

    titleAlways(symbol, title);

    monthAlways(month, monthString);

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks in the %s month of the year %d had a high of $%.2f and a low of $%.2f.\n\n",
           title, monthString, year, max, min);

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks in the %s month of the year %d had a high of $%.2f and a low of $%.2f.\n\n",
            title, monthString, year, max, min);
}

void reportPercentageOpenClose(record *values, int i, float percentage, FILE *file)
{
    char symbol = values[i].Symbol[0];
    char title[10];
    char IncDec[] = "decrease";

    titleAlways(symbol, title);

    if (percentage > 0)
        strcpy(IncDec, "increase");

    printf("\n\n-------------------------------REPORT-------------------------------\n%s "
           "stocks on %s had an open price of %.2f, a close price of %.2f, with a percentage %s of %.2f %%\n\n",
           title, values[i].Date, values[i].MarketOpen, values[i].MarketClose, IncDec, fabs(percentage));

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\n%s "
                  "stocks on %s had an open price of %.2f, a close price of %.2f, with a percentage %s of %.2f %%\n\n",
            title, values[i].Date, values[i].MarketOpen, values[i].MarketClose, IncDec, fabs(percentage));
}

void titleAlways(char sym, char *title)
{
    switch (sym)
    {
    case 'F':
        strcpy(title, "Facebook");
        break;
    case 'T':
        strcpy(title, "Twitter");
        break;
    case 'P':
        strcpy(title, "Pinterest");
        break;
    case 'S':
        strcpy(title, "Snapchat");
        break;
    case 'E':
        strcpy(title, "Etsy");
        break;
    default:
        break;
    }
}

void monthAlways(int month, char *monthString)
{
    switch (month)
    {
    case 1:
        strcpy(monthString, "first");
        break;
    case 2:
        strcpy(monthString, "second");
        break;
    case 3:
        strcpy(monthString, "third");
        break;
    case 4:
        strcpy(monthString, "fourth");
        break;
    case 5:
        strcpy(monthString, "fifth");
        break;
    case 6:
        strcpy(monthString, "sixth");
        break;
    case 7:
        strcpy(monthString, "seventh");
        break;
    case 8:
        strcpy(monthString, "eigth");
        break;
    case 9:
        strcpy(monthString, "ninth");
        break;
    case 10:
        strcpy(monthString, "tenth");
        break;
    case 11:
        strcpy(monthString, "eleventh");
        break;
    case 12:
        strcpy(monthString, "twelvth");
        break;
    default:
        break;
    }
}

void printValues(record values[], int i)
{
    printf("Date -> %s\nSymbol -> %s\nMarket Close -> %.2f\nHigh -> %.2f\nLow -> %.2f\nMarket Open -> %.2f\nVolume -> %d \n", values[i].Date, values[i].Symbol, values[i].MarketClose, values[i].MarketHigh, values[i].MarketLow, values[i].MarketOpen, values[i].Volume);
}

void help()
{
    printf("\nHELP FOR USAGE OF THE COMMAND LINE FOR ANALYSIS AND FUNCTIONS:\n\n");
    printf(".\\Project.exe (MONTH/DAY/YEAR) SYMBOL \t\t\t||\tTo find all data on a given day for a given company.\n\n");

    printf(".\\Project.exe YEAR MONTH SYMBOL -m \t\t\t||\tTo find the high and low of a given month in a specific year for a given company.\n\n");
    printf(".\\Project.exe YEAR SYMBOL -q \t\t\t\t||\tTo find the high and low of all quarters in a specific year for a given company.\n\n");
    printf(".\\Project.exe YEAR SYMBOL -qX \t\t\t\t||\tTo find the high and low of a given quarter in a specific year for a given company, \t\t\t\t\t\t\t\t\t\tX being 1,2,3 or 4 specifying the quarter requested.\n\n");
    printf(".\\Project.exe YEAR SYMBOL \t\t\t\t||\tTo find the high and low of a given year for a given company.\n\n");

    printf(".\\Project.exe (MONTH/DAY/YEAR) SYMBOL -p \t\t||\tTo find the percentage difference between open and close on a specific day for a \t\t\t\t\t\t\t\t\t\tgiven company.\n\n");
    printf(".\\Project.exe YEAR MONTH SYMBOL -p \t\t\t||\tTo find the percentage difference between open and close of a specific month for a \t\t\t\t\t\t\t\t\t\tgiven company.\n\n");
    printf(".\\Project.exe YEAR SYMBOL -pa \t\t\t\t||\tTo find the percentage difference between open and close for all for quarters for a \t\t\t\t\t\t\t\t\t\tgiven company.\n\n");
    printf(".\\Project.exe  YEAR SYMBOL -paX \t\t\t||\tTo find the percentage difference between open and close for a specific quarter for a \t\t\t\t\t\t\t\t\t\tgiven company, X being 1,2,3 or 4 specifying the quarter requested.\n\n");
    printf(".\\Project.exe YEAR SYMBOL -p \t\t\t\t||\tTo find the percentage difference between open and close for a specific year for a \t\t\t\t\t\t\t\t\t\tgiven company.\n\n");

    printf(".\\Project.exe YEAR MONTH SYMBOL -a \t\t\t||\tTo find the averages of all data for a specific month for a given company.\n\n");
    printf(".\\Project.exe YEAR SYMBOL --a \t\t\t\t||\tTo find the averages of all data for all quarters for a given company.\n\n");
    printf(".\\Project.exe YEAR SYMBOL --aX \t\t\t\t||\tTo find the averages of all data for a specific quarter for a \t\t\t\t\t\t\t\t\t\t\t\t\t\tgiven company, X being 1,2,3 or 4 specifying the quarter requested.\n\n");
    printf(".\\Project.exe YEAR SYMBOL -a \t\t\t\t||\tTo find the averages of all data for a specific year for a given company.\n\n");
    printf(".\\Project.exe SYMBOL -a \t\t\t\t||\tTo find the averages of all data for a given company.\n\n");

    printf(".\\Project.exe -comp YEAR SYMBOL1 SYMBOL2 -cy \t\t||\tTo compare the open close percent difference between two companies for a given year.\n\n");
    printf(".\\Project.exe -comp (MONTH/DAY/YEAR) SYMBOL1 SYMBOL2 \t||\tTo compare the open close percent difference between two companies for a given day.\n\n");

    printf(".\\Project.exe (MONTH/DAY/YEAR) (MONTH/DAY/YEAR) SYMBOL\n NumberOfStocks \t\t\t\t\t||\tTo Find the Loss or Gain when purchasing and selling stocks, First Date is the buy date and\n\t\t\t\t\t\t\t\tthe second date is the sell date.\n\n");
}

void menu()
{
    printf("Please select a number from the following list:\n");
    printf("1. To find all data on a given day for a given company\n"
           "2. To find the high and low of a given year for a given company\n"
           "3. To find the high and low of a given quarter\n"
           "4. To find the high and low of all quarters in a specific year for a given company\n"
           "5. To find the high and low of a given month in a specific year\n"
           "6. To find the percentage difference between open and close on a given day\n"
           "7. To find the percent difference between first open and last close in a year\n"
           "8. To find the percent difference between first open and last close in a month\n"
           "9. To find the percent difference between first open and last close in all quarters\n"
           "10. To find the percent difference between first open and last close for a specific quarter\n"
           "11. To find averages for all data in a year\n"
           "12. To find averages for all data in all quarters\n"
           "13. To find average for all data in a given quarter\n"
           "14. To find averages for all data in a month\n"
           "15. To find averages for all data for a company using all data\n"
           "16. To compare two companies percentage differnece for a specific year\n"
           "17. To compare two companies percentage differnece for a specific day\n"
           "Enter 0 to exit Program.\n");
}

void userChoice(int n, record *values, date *dates, int i, FILE *file)
{
    char date[10], dateExtra[4];
    char symbol[4], symbol2[4];
    float min, max;
    char quart[2];
    int q;
    float minq[4] = {0, 0, 0, 0};
    float maxq[4] = {0, 0, 0, 0};
    float open, minm, maxm;
    int day, month;
    float closeAvg, openAvg, lowAvg, highAvg, volumeAvg;
    float closeAv[4], openAv[4], lowAv[4], highAv[4], volumeAv[4];
    int nbDay[4] = {0, 0, 0, 0};
    int nbDays = 0;
    float openPrice[4], openPercerntage[4];
    float percentYear1 = 0, percentYear2 = 0;
    float open1, open2;
    int flagq1, flagq2, flagq3, flagq4;
    flagq1 = flagq2 = flagq3 = flagq4 = 0;
    char symbol1[5];


    switch (n)
    {
    case 1:
        printf("please enter the full date MONTH/DAY/YEAR\n");
        scanf("%s", &date);
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        for (int j = 0; j <= i; j++)
        {
            if (!strcmp(date, values[j].Date))
            {
                if (!strcmp(symbol, values[j].Symbol))
                {
                    reportGivenDay(values, j, file);
                }
                else
                {
                    printf("ERROR THE SYMBOL %s IS NOT A COMPANY SYMBOL", symbol);
                    break;
                }
            }
        }
        break;
    case 2:
        printf("please enter the YEAR\n");
        scanf("%s", &date);
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
            {
                if (!strcmp(symbol, values[a].Symbol))
                {
                    min = values[a].MarketLow;
                    max = values[a].MarketHigh;
                    break;
                }
            }
        }
        for (int j = 0; j <= i; j++)
        {
            yearlyMinMax(values, dates, atoi(date), j, &max, &min);
        }

        reportHighLowYearly(max, min, symbol[0], atoi(date), file);
        break;
    case 3:
        printf("please enter the YEAR\n");
        scanf("%s", &date);
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        printf("please enter the desired quarter from q1 - q4:\n");
        scanf("%s", quart);
        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
            {
                if (!strcmp(symbol, values[a].Symbol))
                {
                    if (dates[a].month >= 1 && dates[a].month <= 3)
                    {
                        if (!strcmp(quart, "q1"))
                        {
                            minq[0] = values[a].MarketLow;
                            maxq[0] = values[a].MarketHigh;
                            q = 1;
                            break;
                        }
                    }

                    if (dates[a].month >= 4 && dates[a].month <= 6)
                    {
                        if (!strcmp(quart, "q2"))
                        {
                            minq[1] = values[a].MarketLow;
                            maxq[1] = values[a].MarketHigh;
                            q = 2;
                            break;
                        }
                    }

                    if (dates[a].month >= 7 && dates[a].month <= 9)
                    {
                        if (!strcmp(quart, "q3"))
                        {
                            minq[2] = values[a].MarketLow;
                            maxq[2] = values[a].MarketHigh;
                            q = 3;
                            break;
                        }
                    }

                    if (dates[a].month >= 10 && dates[a].month <= 12)
                    {
                        if (!strcmp(quart, "q4"))
                        {
                            minq[3] = values[a].MarketLow;
                            maxq[3] = values[a].MarketHigh;
                            q = 4;
                            break;
                        }
                    }
                }
            }
        }
        for (int j = 0; j <= i; j++)
        {
            quarterlyMinMax(values, dates, atoi(date), j, &minq[0], &maxq[0], &minq[1], &maxq[1], &minq[2], &maxq[2], &minq[3], &maxq[3]);
        }
        reportHighLowOneQuarter(q, maxq[q - 1], minq[q - 1], symbol[0], atoi(date), file);
        break;
    case 4:

        printf("please enter the YEAR\n");
        scanf("%s", &date);
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
            {
                if (!strcmp(symbol, values[a].Symbol))
                {
                    if (dates[a].month >= 1 && dates[a].month <= 3)
                    {
                        if (flagq1 == 0)
                        {
                            minq[0] = values[a].MarketLow;
                            maxq[0] = values[a].MarketHigh;
                        }
                        flagq1 = 1;
                        q = 1;
                    }

                    if (dates[a].month >= 4 && dates[a].month <= 6)
                    {
                        if (flagq2 == 0)
                        {
                            minq[1] = values[a].MarketLow;
                            maxq[1] = values[a].MarketHigh;
                        }
                        flagq2 = 1;
                        q = 2;
                    }

                    if (dates[a].month >= 7 && dates[a].month <= 9)
                    {
                        if (flagq3 == 0)
                        {
                            minq[2] = values[a].MarketLow;
                            maxq[2] = values[a].MarketHigh;
                        }
                        flagq3 = 1;
                        q = 3;
                    }

                    if (dates[a].month >= 10 && dates[a].month <= 12)
                    {
                        if (flagq4 == 0)
                        {
                            minq[3] = values[a].MarketLow;
                            maxq[3] = values[a].MarketHigh;
                        }
                        flagq4 = 1;
                        q = 4;

                        break;
                    }
                }
            }
        }
        for (int j = 0; j <= i; j++)
        {

            quarterlyMinMax(values, dates, atoi(date), j, &minq[0], &maxq[0], &minq[1], &maxq[1], &minq[2], &maxq[2], &minq[3], &maxq[3]);
        }
        reportHighLowQuarterly(maxq, minq, symbol[0], atoi(date), file);
        break;
    case 5:
        printf("please enter the YEAR\n");
        scanf("%s", &date);
        printf("please enter the MONTH\n");
        scanf("%s", &dateExtra);
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
            {
                if (atoi(dateExtra) == dates[a].month)
                {
                    if (!strcmp(symbol, values[a].Symbol))
                    {

                        minm = values[a].MarketLow;
                        maxm = values[a].MarketHigh;
                        break;
                    }
                }
            }
        }
        for (int j = 0; j <= i; j++)
        {
            monthlyMinMax(values, dates, atoi(date), atoi(dateExtra), j, &minm, &maxm);
        }
        reportHighLowMonthly(maxm, minm, symbol[0], atoi(date), atoi(dateExtra), file);
        break;
    case 6:
        printf("please enter the MONTH/DAY/YEAR\n");
        scanf("%s", &date);
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        for (int j = 0; j <= i; j++)
        {

            if (!strcmp(date, values[j].Date))
            {
                if (!strcmp(symbol, values[j].Symbol))
                {
                    reportPercentageOpenClose(values, j, percentageOpenClose(values, j), file);
                }
            }
        }
        break;

    case 7:
        printf("please enter the YEAR\n");
        scanf("%s", &date);
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
            {
                if (!strcmp(symbol, values[a].Symbol))
                {
                    open = values[a].MarketOpen;
                    break;
                }
            }
        }
        float percentYear;

        for (int j = 0; j <= i; j++)
        {
            if (atoi(date) == dates[j].year)
            {
                if (!strcmp(symbol, values[j].Symbol))
                {
                    percentYear = yearlyPercentageOpenClose(values, open, j, atoi(date), dates);
                }
            }
        }

        reportPercentageYear(symbol[0], atoi(date), percentYear, file);
        break;
    case 8:
        printf("please enter the YEAR\n");
        scanf("%s", &date);
        printf("please enter the MONTH\n");
        scanf("%s", &dateExtra);
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        float percentMonth;
        int day1;
        for (int j = 0; j <= i; j++)
        {
            if (atoi(date) == dates[j].year)
            {
                if (atoi(dateExtra) == dates[j].month)
                {
                    if (!strcmp(symbol, values[j].Symbol))
                    {
                        open = values[j].MarketOpen;
                        break;
                    }
                }
            }
        }

        for (int j = 0; j <= i; j++)
        {
            if (atoi(date) == dates[j].year)
            {
                if (atoi(dateExtra) == dates[j].month)
                {
                    if (!strcmp(symbol, values[j].Symbol))
                    {
                        percentMonth = monthlyPercentageOpenClose(values, atoi(dateExtra), open, j, atoi(date), dates);
                    }
                }
            }
        }
        printf("%f, %f\n", open, percentMonth);
        reportPercentageMonth(symbol[0], atoi(date), percentMonth, atoi(dateExtra), file);
        break;
    case 9:
        printf("please enter the YEAR\n");
        scanf("%s", &date);

        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);

        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
            {
                if (!strcmp(symbol, values[a].Symbol))
                {
                    if (dates[a].month >= 1 && dates[a].month <= 3)
                    {
                        if (flagq1 == 0)
                        {
                            openPrice[0] = values[a].MarketOpen;
                        }
                        flagq1 = 1;
                    }

                    if (dates[a].month >= 4 && dates[a].month <= 6)
                    {
                        if (flagq2 == 0)
                        {
                            openPrice[1] = values[a].MarketOpen;
                        }
                        flagq2 = 1;
                    }

                    if (dates[a].month >= 7 && dates[a].month <= 9)
                    {
                        if (flagq3 == 0)
                        {
                            openPrice[2] = values[a].MarketOpen;
                        }
                        flagq3 = 1;
                    }

                    if (dates[a].month >= 10 && dates[a].month <= 12)
                    {
                        if (flagq4 == 0)
                        {
                            openPrice[3] = values[a].MarketOpen;
                        }
                        flagq4 = 1;
                        break;
                    }
                }
            }
        }
        for (int j = 0; j <= i; j++)
        {
            if (atoi(date) == dates[j].year)
            {
                if (!strcmp(symbol, values[j].Symbol))
                {

                    quarterlyPercentageOpenClose(values, dates, atoi(date), j, &openPrice[0], &openPrice[1], &openPrice[2], &openPrice[3], &openPercerntage[0], &openPercerntage[1], &openPercerntage[2], &openPercerntage[3]);
                }
            }
        }
        reportPercentageQuarterly(symbol[0], atoi(date), openPercerntage, file);
        break;
    case 10:
        printf("please enter the YEAR\n");
        scanf("%s", &date);
        printf("please enter the quarter\n");
        scanf("%s", &dateExtra);
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);

        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
            {
                if (!strcmp(symbol, values[a].Symbol))
                {
                    if (dates[a].month >= 1 && dates[a].month <= 3)
                    {
                        if (flagq1 == 0)
                        {
                            openPrice[0] = values[a].MarketOpen;
                        }
                        flagq1 = 1;
                    }

                    if (dates[a].month >= 4 && dates[a].month <= 6)
                    {
                        if (flagq2 == 0)
                        {
                            openPrice[1] = values[a].MarketOpen;
                        }
                        flagq2 = 1;
                    }

                    if (dates[a].month >= 7 && dates[a].month <= 9)
                    {
                        if (flagq3 == 0)
                        {
                            openPrice[2] = values[a].MarketOpen;
                        }
                        flagq3 = 1;
                    }

                    if (dates[a].month >= 10 && dates[a].month <= 12)
                    {
                        if (flagq4 == 0)
                        {
                            openPrice[3] = values[a].MarketOpen;
                        }
                        flagq4 = 1;
                        break;
                    }
                }
            }
        }
        for (int j = 0; j <= i; j++)
        {
            if (atoi(date) == dates[j].year)
            {
                if (!strcmp(symbol, values[j].Symbol))
                {

                    quarterlyPercentageOpenClose(values, dates, atoi(date), j, &openPrice[0], &openPrice[1], &openPrice[2], &openPrice[3], &openPercerntage[0], &openPercerntage[1], &openPercerntage[2], &openPercerntage[3]);
                }
            }
        }
        if (!strcmp(dateExtra, "1"))
            reportPercentageQuarter(symbol[0], atoi(date), openPercerntage[0], 1, file);
        if (!strcmp(dateExtra, "2"))
            reportPercentageQuarter(symbol[0], atoi(date), openPercerntage[1], 2, file);
        if (!strcmp(dateExtra, "3"))
            reportPercentageQuarter(symbol[0], atoi(date), openPercerntage[2], 3, file);
        if (!strcmp(dateExtra, "4"))
            reportPercentageQuarter(symbol[0], atoi(date), openPercerntage[3], 4, file);

        break;
    case 11:
        printf("please enter the YEAR\n");
        scanf("%s", &date);
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        for (int j = 0; j <= i; j++)
        {
            if (atoi(date) == dates[j].year)
            {
                if (!strcmp(symbol, values[j].Symbol))
                {
                    closeAvg = values[j].MarketClose;
                    openAvg = values[j].MarketHigh;
                    lowAvg = values[j].MarketLow;
                    highAvg = values[j].MarketHigh;
                    volumeAvg = values[j].Volume;
                    break;
                }
            }
        }
        for (int j = 0; j <= i; j++)
        {
            if (atoi(date) == dates[j].year)
            {
                if (!strcmp(symbol, values[j].Symbol))
                {

                    if (j == 0)
                    {
                        j++;
                    }
                    yearlySums(values, dates, atoi(date), j, &closeAvg, &openAvg, &lowAvg, &highAvg, &volumeAvg, &nbDays);
                }
            }
        }
        yearlyAverage(nbDays, &closeAvg, &openAvg, &lowAvg, &highAvg, &volumeAvg);
        reportYearlyAverage(symbol[0], atoi(date), openAvg, closeAvg, highAvg, lowAvg, volumeAvg, file);

        break;
    case 12:
        printf("please enter the YEAR\n");
        scanf("%s", &date);

        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
            {
                if (!strcmp(symbol, values[a].Symbol))
                {

                    if (dates[a].month >= 1 && dates[a].month <= 3)
                    {
                        if (flagq1 == 0)
                        {
                            closeAv[0] = values[a].MarketClose;
                            openAv[0] = values[a].MarketHigh;
                            lowAv[0] = values[a].MarketLow;
                            highAv[0] = values[a].MarketHigh;
                            volumeAv[0] = values[a].Volume;
                        }
                        flagq1 = 1;
                    }

                    if (dates[a].month >= 4 && dates[a].month <= 6)
                    {
                        if (flagq2 == 0)
                        {
                            closeAv[1] = values[a].MarketClose;
                            openAv[1] = values[a].MarketHigh;
                            lowAv[1] = values[a].MarketLow;
                            highAv[1] = values[a].MarketHigh;
                            volumeAv[1] = values[a].Volume;
                        }
                        flagq2 = 1;
                    }

                    if (dates[a].month >= 7 && dates[a].month <= 9)
                    {
                        if (flagq3 == 0)
                        {
                            closeAv[2] = values[a].MarketClose;
                            openAv[2] = values[a].MarketHigh;
                            lowAv[2] = values[a].MarketLow;
                            highAv[2] = values[a].MarketHigh;
                            volumeAv[2] = values[a].Volume;
                        }
                        flagq3 = 1;
                    }
                }

                if (dates[a].month >= 10 && dates[a].month <= 12)
                {
                    if (flagq4 == 0)
                    {
                        closeAv[3] = values[a].MarketClose;
                        openAv[3] = values[a].MarketHigh;
                        lowAv[3] = values[a].MarketLow;
                        highAv[3] = values[a].MarketHigh;
                        volumeAv[3] = values[a].Volume;
                    }
                    flagq4 = 1;
                    break;
                }
            }
        }
        for (int j = 0; j <= i; j++)
        {
            if (atoi(date) == dates[j].year)
            {
                if (!strcmp(symbol, values[j].Symbol))
                {

                    if (j == 0)
                    {
                        j++;
                    }

                    quarterlySums(values, dates, atoi(date), j, &closeAv[0], &openAv[0], &lowAv[0], &highAv[0], &volumeAv[0], &nbDay[0], &closeAv[1], &openAv[1], &lowAv[1], &highAv[1], &volumeAv[1], &nbDay[1], &closeAv[2], &openAv[2], &lowAv[2], &highAv[2], &volumeAv[2], &nbDay[2], &closeAv[3], &openAv[3], &lowAv[3], &highAv[3], &volumeAv[3], &nbDay[3]);
                }
            }
        }
        quarterlyAverage(&closeAv[0], &openAv[0], &lowAv[0], &highAv[0], &volumeAv[0], nbDay[0], &closeAv[1], &openAv[1], &lowAv[1], &highAv[1], &volumeAv[1], nbDay[1], &closeAv[2], &openAv[2], &lowAv[2], &highAv[2], &volumeAv[2], nbDay[2], &closeAv[3], &openAv[3], &lowAv[3], &highAv[3], &volumeAv[3], nbDay[3]);

        reportQuarterlyAverage(openAv, closeAv, highAv, lowAv, volumeAv, symbol[0], atoi(date), file);

        break;
    case 13:
        printf("please enter the YEAR\n");
        scanf("%s", &date);
        printf("please enter the quarter desired, between 1 and 4\n");
        scanf("%s", &dateExtra);
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
            {
                if (!strcmp(symbol, values[a].Symbol))
                {

                    if (dates[a].month >= 1 && dates[a].month <= 3)
                    {
                        if (flagq1 == 0)
                        {
                            closeAv[0] = values[a].MarketClose;
                            openAv[0] = values[a].MarketHigh;
                            lowAv[0] = values[a].MarketLow;
                            highAv[0] = values[a].MarketHigh;
                            volumeAv[0] = values[a].Volume;
                        }
                        flagq1 = 1;
                    }

                    if (dates[a].month >= 4 && dates[a].month <= 6)
                    {
                        if (flagq2 == 0)
                        {
                            closeAv[1] = values[a].MarketClose;
                            openAv[1] = values[a].MarketHigh;
                            lowAv[1] = values[a].MarketLow;
                            highAv[1] = values[a].MarketHigh;
                            volumeAv[1] = values[a].Volume;
                        }
                        flagq2 = 1;
                    }

                    if (dates[a].month >= 7 && dates[a].month <= 9)
                    {
                        if (flagq3 == 0)
                        {
                            closeAv[2] = values[a].MarketClose;
                            openAv[2] = values[a].MarketHigh;
                            lowAv[2] = values[a].MarketLow;
                            highAv[2] = values[a].MarketHigh;
                            volumeAv[2] = values[a].Volume;
                        }
                        flagq3 = 1;
                    }
                }

                if (dates[a].month >= 10 && dates[a].month <= 12)
                {
                    if (flagq4 == 0)
                    {
                        closeAv[3] = values[a].MarketClose;
                        openAv[3] = values[a].MarketHigh;
                        lowAv[3] = values[a].MarketLow;
                        highAv[3] = values[a].MarketHigh;
                        volumeAv[3] = values[a].Volume;
                    }
                    flagq4 = 1;
                    break;
                }
            }
        }
        for (int j = 0; j <= i; j++)
        {
            if (atoi(date) == dates[j].year)
            {
                if (!strcmp(symbol, values[j].Symbol))
                {

                    if (j == 0)
                    {
                        j++;
                    }

                    quarterlySums(values, dates, atoi(date), j, &closeAv[0], &openAv[0], &lowAv[0], &highAv[0], &volumeAv[0], &nbDay[0], &closeAv[1], &openAv[1], &lowAv[1], &highAv[1], &volumeAv[1], &nbDay[1], &closeAv[2], &openAv[2], &lowAv[2], &highAv[2], &volumeAv[2], &nbDay[2], &closeAv[3], &openAv[3], &lowAv[3], &highAv[3], &volumeAv[3], &nbDay[3]);
                }
            }
        }
        quarterlyAverage(&closeAv[0], &openAv[0], &lowAv[0], &highAv[0], &volumeAv[0], nbDay[0], &closeAv[1], &openAv[1], &lowAv[1], &highAv[1], &volumeAv[1], nbDay[1], &closeAv[2], &openAv[2], &lowAv[2], &highAv[2], &volumeAv[2], nbDay[2], &closeAv[3], &openAv[3], &lowAv[3], &highAv[3], &volumeAv[3], nbDay[3]);
        if (!strcmp(dateExtra, "1"))
            reportQuarterAverage(symbol[0], atoi(date), openAv[0], closeAv[0], highAv[0], lowAv[0], volumeAv[0], 1, file);
        if (!strcmp(dateExtra, "2"))
            reportQuarterAverage(symbol[0], atoi(date), openAv[1], closeAv[1], highAv[1], lowAv[1], volumeAv[1], 2, file);
        if (!strcmp(dateExtra, "3"))
            reportQuarterAverage(symbol[0], atoi(date), openAv[2], closeAv[2], highAv[2], lowAv[2], volumeAv[2], 3, file);
        if (!strcmp(dateExtra, "4"))
            reportQuarterAverage(symbol[0], atoi(date), openAv[3], closeAv[3], highAv[3], lowAv[3], volumeAv[3], 4, file);

        break;
    case 14:
        printf("please enter the YEAR\n");
        scanf("%s", &date);
        printf("please enter the month desired,\n");
        scanf("%s", &dateExtra);
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
            {
                if (atoi(dateExtra) == dates[a].month)
                {
                    closeAvg = values[a].MarketClose;
                    openAvg = values[a].MarketHigh;
                    lowAvg = values[a].MarketLow;
                    highAvg = values[a].MarketHigh;
                    volumeAvg = values[a].Volume;
                    break;
                }
            }
        }

        for (int j = 0; j <= i; j++)
        {
            if (atoi(date) == dates[j].year)
            {
                if (atoi(dateExtra) == dates[j].month)
                {
                    if (!strcmp(symbol, values[j].Symbol))
                    {

                        if (j == 0)
                        {
                            j++;
                        }

                        monthlySums(values, dates, atoi(date), atoi(dateExtra), j, &closeAvg, &openAvg, &lowAvg, &highAvg, &volumeAvg, &nbDays);
                    }
                }
            }
        }
        monthlyAverage(&closeAvg, &openAvg, &lowAvg, &highAvg, &volumeAvg, nbDays);

        reportMonthlyAverage(symbol[0], atoi(date), atoi(dateExtra), openAvg, closeAvg, highAvg, lowAvg, volumeAvg, file);
        break;
    case 15:
        printf("please enter the symbol for the company desired\n");
        scanf("%s", &symbol);
        for (int a = 0; a <= i; a++)
        {
            if (!strcmp(symbol, values[a].Symbol))
            {
                closeAvg = values[a].MarketClose;
                openAvg = values[a].MarketHigh;
                lowAvg = values[a].MarketLow;
                highAvg = values[a].MarketHigh;
                volumeAvg = values[a].Volume;
                break;
            }
        }
        for (int j = 0; j <= i; j++)
        {
            if (!strcmp(symbol, values[j].Symbol))
            {
                allSums(values, j, &closeAvg, &openAvg, &lowAvg, &highAvg, &volumeAvg, &nbDays);
            }
        }
        Average(&closeAvg, &openAvg, &lowAvg, &highAvg, &volumeAvg, nbDays);
        reportAverage(symbol[0], openAvg, closeAvg, highAvg, lowAvg, volumeAvg, file);
        break;
    case 16:
        printf("please enter the YEAR\n");
        scanf("%s", &date);
        printf("please enter the symbol for the first company desired\n");
        scanf("%s", &symbol);
        printf("please enter the symbol for the second company desired\n");
        scanf("%s", &symbol2);

        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
            {
                if (!strcmp(symbol, values[a].Symbol))
                {
                    open1 = values[a].MarketOpen;
                    break;
                }
            }
        }
        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
            {
                if (!strcmp(symbol2, values[a].Symbol))
                {

                    open2 = values[a].MarketOpen;
                    break;
                }
            }
        }
        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
                if (!strcmp(symbol, values[a].Symbol))

                    percentYear1 = yearlyPercentageOpenClose(values, open1, a, atoi(date), dates);
        }
        for (int a = 0; a <= i; a++)
        {
            if (atoi(date) == dates[a].year)
                if (!strcmp(symbol2, values[a].Symbol))

                    percentYear2 = yearlyPercentageOpenClose(values, open2, a, atoi(date), dates);
        }

        comparePercent(percentYear1, percentYear2, symbol[0], symbol2[0], 0, atoi(date), 0, 0, 0, file);
        break;

    case 17:
        printf("please enter Month/Day/Year\n");
        scanf("%s", &date);
        printf("please enter the symbol for the first company desired\n");
        scanf("%s", &symbol1);

        printf("please enter the symbol for the second company desired\n");
        scanf("%s", &symbol2);

        for (int a = 0; a <= i; a++)
        {
            if (!strcmp(date, values[a].Date))
            {
                if (!strcmp(symbol1, values[a].Symbol))
                {
                    percentYear1 = percentageOpenClose(values, a);
                    break;
                }
            }
        }
        int b;
        for (b = 0; b <= i; b++)
        {
            if (!strcmp(date, values[b].Date))
                if (!strcmp(symbol2, values[b].Symbol))
                {
                    percentYear2 = percentageOpenClose(values, b);
                    break;
                }
        }
        char code[10];
        strcpy(code, date);
        char *MonthFinal = strtok(code, "/");
        char *dayFinal = strtok(NULL, "/");
        char *YearFinal = strtok(NULL, "");
        comparePercent(percentYear1, percentYear2, symbol1[0], symbol2[0], 3, atoi(YearFinal), atoi(dayFinal), atoi(MonthFinal), 0, file);

        break;
        
    default:
        break;
    }
}

void GainLoss(float buyPrice, float sellPrice, int nbOfStocks, float *PriceBuy, float *PriceSell, float *difference)
{
    *PriceBuy = buyPrice * nbOfStocks;
    *PriceSell = sellPrice * nbOfStocks;
    *difference = (*PriceSell) - (*PriceBuy);
}

void reportGainLoss(char symbol, char *date2, float openBuy, float openSell, float gain, char *date, int stocks, FILE *file)
{

    char title[10];
    char gainLoss[] = "loss";

    titleAlways(symbol, title);

    if (gain > 0)
        strcpy(gainLoss, "gain");

    printf("\n\n-------------------------------REPORT-------------------------------\nOn %s -buy date- %s "
           "stocks had an open price of %.2f, and on %s -sell date- %s stocks had an open price of %.2f,\nif a puchase is made with number of stocks equal to %d and they are sold on the sell date you will end with a %s of %.2f $\n\n",
           date, title, openBuy, date2, title, openSell, stocks, gainLoss, fabs(gain));

    fprintf(file, "\n\n-------------------------------REPORT-------------------------------\nOn %s -buy date- %s stocks had an open price of %.2f, and on %s -sell date- %s stocks had an open price of %.2f,\nif a puchase is made with number of stocks equal to %d and they are sold on the sell date you will end with a %s of %.2f $\n\n", date, title, openBuy, date2, title, openSell, stocks, gainLoss, fabs(gain));
}