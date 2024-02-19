#ifndef PROJECTFUNC_H_INCLUDED
#define PROJECTFUNC_H_INCLUDED

typedef struct record
{
    char Date[25];
    char Symbol[25];
    float MarketClose;
    float MarketHigh;
    float MarketLow;
    float MarketOpen;
    int Volume;
} record;

typedef struct date
{
    int day;
    int month;
    int year;
} date;

void printValues(record values[], int i);
void reportGivenDay(record *values, int i, FILE *file);

float percentageOpenClose(record *values, int i);
void reportPercentageOpenClose(record *values, int i, float percentage, FILE *file);

void monthlyMinMax(record *values, date *dates, int year, int month, int j, float *min, float *max);
void reportHighLowMonthly(float max, float min, char symbol, int year, int month, FILE *file);
void monthlySums(record *values, date *dates, int year, int month, int j, float *close, float *open, float *low, float *high, float *volume, int *nbDays);
void monthlyAverage(float *close, float *open, float *low, float *high, float *volume, int nbDays);
void reportMonthlyAverage(char symbols, int year, int month, float open, float close, float high, float low, int volume, FILE *file);
float monthlyPercentageOpenClose(record *values, int month, float open, int i, int year, date *dates);
void reportPercentageMonth(char symbol, int year, float percentage, int month, FILE *file);

void yearlyMinMax(record *values, date *dates, int year, int j, float *max, float *min);
void reportHighLowYearly(float max, float min, char symbol, int date, FILE *file);
float yearlyPercentageOpenClose(record *values, float open, int i, int year, date *dates);
void reportPercentageYear(char symbol, int year, float percentage, FILE *file);
void yearlySums(record *values, date *dates, int year, int j, float *close, float *open, float *low, float *high, float *volume, int *nbDays);
float yearlyAverage(int nbDays, float *close, float *open, float *low, float *high, float *volume);
void reportYearlyAverage(char symbols, int year, float open, float close, float high, float low, int volume, FILE *file);

void quarterlyMinMax(record *values, date *dates, int year, int j, float *min1, float *max1, float *min2, float *max2, float *min3, float *max3, float *min4, float *max4);
void reportHighLowQuarterly(float *max, float *min, char symbol, int date, FILE *file);
void reportHighLowOneQuarter(int quarter, float max, float min, char symbol, int date, FILE *file);
float quarterlySums(record *values, date *dates, int year, int j, float *close1, float *open1, float *low1, float *high1, float *volume1, int *nbDays1, float *close2, float *open2, float *low2, float *high2, float *volume2, int *nbDays2, float *close3, float *open3, float *low3, float *high3, float *volume3, int *nbDays3, float *close4, float *open4, float *low4, float *high4, float *volume4, int *nbDays4);
float quarterlyAverage(float *close1, float *open1, float *low1, float *high1, float *volume1, int nbDays1, float *close2, float *open2, float *low2, float *high2, float *volume2, int nbDays2, float *close3, float *open3, float *low3, float *high3, float *volume3, int nbDays3, float *close4, float *open4, float *low4, float *high4, float *volume4, int nbDays4);
void reportQuarterlyAverage(float *open, float *close, float *high, float *low, float *volume, char symbols, int year, FILE *file);
void reportQuarterAverage(char symbols, int year, float open, float close, float high, float low, float volume, int quart, FILE *file);
float quarterlyPercentageOpenClose(record *values, date *dates, int year, int i, float *open1, float *open2, float *open3, float *open4, float *percentage1, float *percentage2, float *percentage3, float *percentage4);
void reportPercentageQuarterly(char symbol, int year, float *percentage, FILE *file);
void reportPercentageQuarter(char symbol, int year, float percentage, int q, FILE *file);

float allSums(record *values, int j, float *close, float *open, float *low, float *high, float *volume, int *nbDays);
float Average(float *close, float *open, float *low, float *high, float *volume, int nbDays);
void reportAverage(char symbols, float open, float close, float high, float low, int volume, FILE *file);

void comparePercent(float percent1, float percent2, char symbol1, char symbol2, int DayYearMonthQuarter, int year, int day, int month, int quarter, FILE *file);

void GainLoss(float buyPrice, float sellPrice, int nbOfStocks, float *PriceBuy, float *PriceSell, float *difference);
void reportGainLoss(char symbol, char *date2, float openBuy, float openSell, float gain, char *date, int stocks, FILE *file);

void titleAlways(char sym, char *title);
void monthAlways(int month, char *monthString);
void help();
void userChoice(int n, record *values, date *dates, int i, FILE *file);
void menu();
#endif

// Stocks buy and sell
// Stocks buy and sell report

// log file
