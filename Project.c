#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ProjectFunc.h"

int main(int argc, char **argv)
{

    FILE *fp = fopen("social-media-stocks-2012-2022.csv", "r"); // open the data set file in read mode
    FILE *accessData = fopen("data.txt", "a");

    if (!fp)
    {
        fprintf(stderr, "ERROR!! FILE IS NOT AVAILABLE"); // if file doesnt exist, return -1 and display error
        return -1;
    }

    char line[1024];

    int row_count = 0;

    record *values = (record *)malloc(sizeof(record)); // create storage for the data to be read from file
    date *dates = (date *)malloc(sizeof(date));        // create storage for the date to be read from file
    char dateTest[25];
    int i = 0;
    char *field;
    float min, max, minm, maxm; // initiliaze a minimum, maximum, minimum month, and maximum month for funtions
    float minq[4], maxq[4];     // initiliaze a minimum and maximum array for all four quarters
    char symb;                  // initiliaze a symb character to always store the value in it
    int year, month;            //
    char sym[5];                //
    float percentage;           //

    int flagy = 0; // flag variable used for deciding what report function to use:
    int flagm = 0; // flag variable used for deciding what report function to use:

    int flagq, flagq1, flagq2, flagq3, flagq4; // flag variable used for deciding what report function to use:
    flagq = flagq1 = flagq2 = flagq3 = flagq4 = 0;

    int flagPq, flagPq1, flagPq2, flagPq3, flagPq4; // flag variable used for deciding what report function to use:
    flagPq = flagPq1 = flagPq2 = flagPq3 = flagPq4 = 0;

    int flagMP, flagyp; // flag variable used for deciding what report function to use: monthly %
    flagMP = flagyp = 0;

    int flagAvg, flagAvgM, flagAvgY, nbDays;
    flagAvg = flagAvgM = flagAvgY = nbDays = 0;

    int flagAvgq, flagAvgq1, flagAvgq2, flagAvgq3, flagAvgq4; // flag variable used for deciding what report function to use:
    flagAvgq = flagAvgq1 = flagAvgq2 = flagAvgq3 = flagAvgq4 = 0;
    int quart;

    float open;      // variable to store the first open of the month/year to be used in percentage
    int day, month1; // variable to store dates while increasing them during percent function

    float percentYear, percentMonth; // variable to store percentage open close for a given year
    percentYear = percentMonth = 0;

    float closeAvg, openAvg, lowAvg, highAvg, volumeAvg;
    float closeAv[4], openAv[4], lowAv[4], highAv[4], volumeAv[4];
    int nbDay[4] = {0, 0, 0, 0};

    float openPrice[4], openPercerntage[4];
    int user = 0;
    int n = 1, nstrings = 0;

    while (1)
    {
        field = fgets(line, sizeof(line), fp); // read one line at a time from the file fp into field

        if (nstrings == n)
        {
            n *= 2;
            values = (record *)realloc(values, n * sizeof(record));
            dates = (date *)realloc(dates, n * sizeof(date));
            // checking if number of string that is incremented when we finish reading each line into our structure equal to n which is 1 at first
            // which means we allocated size of the structure to the values we have and then this n will be doubled each time we reach the allocated limit n
            // then we will realocate by n * sizeof(structure)
        }

        row_count++;

        if (field == NULL)
            break;

        if (row_count == 1) // skip the first row which is the field names
            continue;

        field = strtok(line, ",");        // taking the first value from the line where the delimiter is ',' and put it in field
        strcpy(values[i].Date, field);    // copying the value stored in field into values[i].date since field is a temporary variable
        strcpy(dateTest, values[i].Date); // copying the value from values[i].date into datatest for further use

        field = strtok(NULL, ","); // taking the next value with a delimiter ',', after we tokenized the first value and then we put this one in field once again
        strcpy(values[i].Symbol, field);

        field = strtok(NULL, ",");
        values[i].MarketClose = atof(field); // atof of field (ascii to float) because we are reading the field as a string

        field = strtok(NULL, ",");
        values[i].MarketHigh = atof(field);

        field = strtok(NULL, ",");
        values[i].MarketLow = atof(field);

        field = strtok(NULL, ",");
        values[i].MarketOpen = atof(field);

        field = strtok(NULL, "\n"); // taking the next value into field but now with a delimited of '\n' since the first line of values finish with an enter
        values[i].Volume = atoi(field);

        field = strtok(dateTest, "/"); // tokenizing the date with a delimiter '/' to take each part of the date MM/DD/YYYY -> MM
        dates[i].month = atoi(field);

        field = strtok(NULL, "/"); // MM/DD/YYYY -> DD
        dates[i].day = atoi(field);

        field = strtok(NULL, "");
        dates[i].year = atoi(field); // MM/DD/YYYY -> YYYY with atoi of field (ascii to integer) because we are reading the field as a string

        i++;        // increamenting to take the number of rows in the whole file
        ++nstrings; // increamenting the size of the line we took to know the realocation
    }
    fclose(fp);

    if (argc < 2)
    {
        fprintf(stderr, "USAGE: %s <%d>\n\nFor help\nUSAGE: %s --help\n", argv[0], argc, argv[0]);
    }

    if (argc == 2)
    {
        if (!strcmp("--help", argv[1]))
            help(argv[0]);
        else if (!strcmp("--UserChoice", argv[1]))
        {
            do
            {
                menu(); // open a menu with all the available function
                scanf("%d", &user);
                userChoice(user, values, dates, i, accessData);
                // it allows the user to choose which function they want to execute from the functions shown in the menu
            } while (user != 0);
        }
        else
            fprintf(stderr, "USAGE: %s <%d>\n", argv[0], argc);
    }

    if (argc == 3)
    {
        for (int a = 0; a <= i; a++)
        {
            if (atoi(argv[1]) == dates[a].year)
            {
                if (!strcmp(argv[2], values[a].Symbol))
                {
                    min = values[a].MarketLow;
                    max = values[a].MarketHigh;
                    break;
                    // taking the values of min and max of a given year and symbol
                }
            }

            if (!strcmp(argv[1], values[a].Symbol))
            {
                if (!strcmp(argv[2], "-a"))
                {
                    closeAvg = values[a].MarketClose;
                    openAvg = values[a].MarketHigh;
                    lowAvg = values[a].MarketLow;
                    highAvg = values[a].MarketHigh;
                    volumeAvg = values[a].Volume;
                    break;
                    // it will take the first occurance of the close open low high and volume values where we have the same year and symbol
                }
            }
        }

        for (int j = 0; j <= i; j++)
        {

            if (!strcmp(argv[1], values[j].Date))
            {

                if (!strcmp(argv[2], values[j].Symbol))
                {
                    printValues(values, j);
                    reportGivenDay(values, j, accessData);
                    // print the report of values of a given date a symbol
                }
                else
                {
                    printf("ERROR THE SYMBOL %s IS NOT A COMPANY SYMBOL", argv[2]);
                    break;
                }
            }

            if (atoi(argv[1]) == dates[j].year)
            {
                if (!strcmp(argv[2], values[j].Symbol))
                {
                    flagy = 1; // taking a flag to print when we are outside the loop
                    yearlyMinMax(values, dates, atoi(argv[1]), j, &max, &min);
                    // compute the yearly min max of a given year and a symbol
                }
            }

            if (!strcmp(argv[1], values[j].Symbol))
            {
                if (!strcmp(argv[2], "-a"))
                {
                    flagAvg = 1;
                    allSums(values, j, &closeAvg, &openAvg, &lowAvg, &highAvg, &volumeAvg, &nbDays);
                    // compute the sums of the values a given symbol for further use
                }
            }
        }

        if (flagAvg == 1)
        {
            strcpy(sym, argv[1]);
            symb = sym[0];
            Average(&closeAvg, &openAvg, &lowAvg, &highAvg, &volumeAvg, nbDays);            // compute the average using the values from allsums
            reportAverage(symb, openAvg, closeAvg, highAvg, lowAvg, volumeAvg, accessData); // printing the report of the average taking the values returned by reference from the average function
        }

        // yearly
        if (flagy == 1)
        {
            strcpy(sym, argv[2]);
            symb = sym[0];
            year = atoi(argv[1]);
            reportHighLowYearly(max, min, symb, year, accessData); // report of the yearly min max taking the values returned by the yearlyminmax function
        }
    }

    if (argc == 4)
    {
        strcpy(sym, argv[2]); // copying what is in argv[2] the variable sym
        symb = sym[0];        // taking the first character from sym into symb
        year = atoi(argv[1]); // converting argv[1] to an integer and storing it in the variable year
        for (int a = 0; a <= i; a++)
        {
            if (atoi(argv[1]) == dates[a].year)
            {
                if (!strcmp(argv[2], values[a].Symbol))
                {
                    if (!strcmp(argv[3], "-q") || !strcmp(argv[3], "-q1") || !strcmp(argv[3], "-q2") || !strcmp(argv[3], "-q3") || !strcmp(argv[3], "-q4"))
                    {
                        // checking the year, the symbol and what the user want to get, in here -q is for quarterly and -qX is for a specific quarter
                        // if this criterias are true we read the first occurence of the min and max (high and low) values into an array minq[4] maxq[4]
                        if (dates[a].month >= 1 && dates[a].month <= 3)
                        {
                            if (flagq1 == 0)
                            {
                                minq[0] = values[a].MarketLow;
                                maxq[0] = values[a].MarketHigh;
                            }
                            flagq1 = 1;
                        }

                        if (dates[a].month >= 4 && dates[a].month <= 6)
                        {
                            if (flagq2 == 0)
                            {
                                minq[1] = values[a].MarketLow;
                                maxq[1] = values[a].MarketHigh;
                            }
                            flagq2 = 1;
                        }

                        if (dates[a].month >= 7 && dates[a].month <= 9)
                        {
                            if (flagq3 == 0)
                            {
                                minq[2] = values[a].MarketLow;
                                maxq[2] = values[a].MarketHigh;
                            }
                            flagq3 = 1;
                        }

                        if (dates[a].month >= 10 && dates[a].month <= 12)
                        {
                            if (flagq4 == 0)
                            {
                                minq[3] = values[a].MarketLow;
                                maxq[3] = values[a].MarketHigh;
                            }
                            flagq4 = 1;
                            break; // break out of the loop when we reach the first min max occurence of the 4th quarter
                        }
                    }

                    if (!strcmp(argv[3], "--a") || !strcmp(argv[3], "--a1") || !strcmp(argv[3], "--a2") || !strcmp(argv[3], "--a3") || !strcmp(argv[3], "--a4"))
                    {
                        if (dates[a].month >= 1 && dates[a].month <= 3)
                        {
                            // taking the first occurence of each of these variable in each quarter to use them in the quarterly and quareter average
                            if (flagAvgq1 == 0)
                            {
                                closeAv[0] = values[a].MarketClose;
                                openAv[0] = values[a].MarketHigh;
                                lowAv[0] = values[a].MarketLow;
                                highAv[0] = values[a].MarketHigh;
                                volumeAv[0] = values[a].Volume;
                            }
                            flagAvgq1 = 1;
                        }

                        if (dates[a].month >= 4 && dates[a].month <= 6)
                        {
                            if (flagAvgq2 == 0)
                            {
                                closeAv[1] = values[a].MarketClose;
                                openAv[1] = values[a].MarketHigh;
                                lowAv[1] = values[a].MarketLow;
                                highAv[1] = values[a].MarketHigh;
                                volumeAv[1] = values[a].Volume;
                            }
                            flagAvgq2 = 1;
                        }

                        if (dates[a].month >= 7 && dates[a].month <= 9)
                        {
                            if (flagAvgq3 == 0)
                            {
                                closeAv[2] = values[a].MarketClose;
                                openAv[2] = values[a].MarketHigh;
                                lowAv[2] = values[a].MarketLow;
                                highAv[2] = values[a].MarketHigh;
                                volumeAv[2] = values[a].Volume;
                            }
                            flagAvgq3 = 1;
                        }

                        if (dates[a].month >= 10 && dates[a].month <= 12)
                        {
                            if (flagAvgq4 == 0)
                            {
                                closeAv[3] = values[a].MarketClose;
                                openAv[3] = values[a].MarketHigh;
                                lowAv[3] = values[a].MarketLow;
                                highAv[3] = values[a].MarketHigh;
                                volumeAv[3] = values[a].Volume;
                            }
                            flagAvgq4 = 1;
                            break;
                        }
                    }
                    if (!strcmp(argv[3], "-pq") || !strcmp(argv[3], "-pq1") || !strcmp(argv[3], "-pq2") || !strcmp(argv[3], "-pq3") || !strcmp(argv[3], "-pq4"))
                    {
                        // taking the first occurence of the openPrice  when the user gives a year, a symbol and an option of -pq or -pqX
                        if (dates[a].month >= 1 && dates[a].month <= 3)
                        {
                            if (flagPq1 == 0)
                            {
                                openPrice[0] = values[a].MarketOpen;
                            }
                            flagPq1 = 1;
                        }

                        if (dates[a].month >= 4 && dates[a].month <= 6)
                        {
                            if (flagPq2 == 0)
                            {
                                openPrice[1] = values[a].MarketOpen;
                            }
                            flagPq2 = 1;
                        }

                        if (dates[a].month >= 7 && dates[a].month <= 9)
                        {
                            if (flagPq3 == 0)
                            {
                                openPrice[2] = values[a].MarketOpen;
                            }
                            flagPq3 = 1;
                        }

                        if (dates[a].month >= 10 && dates[a].month <= 12)
                        {
                            if (flagPq4 == 0)
                            {
                                openPrice[3] = values[a].MarketOpen;
                            }
                            flagPq4 = 1;
                            break;
                        }
                    }
                }
            }
        }

        for (int a = 0; a <= i; a++)
        {
            if (atoi(argv[1]) == dates[a].year)
            {
                if (!strcmp(argv[2], values[a].Symbol))
                {
                    if (!strcmp(argv[3], "-p"))
                    {
                        flagyp = 1;
                        open = values[a].MarketOpen;
                        break;
                    }
                    if (!strcmp(argv[3], "-a"))
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
        }

        for (int j = 0; j <= i; j++)
        {
            if (atoi(argv[1]) == dates[j].year)
            {
                if (!strcmp(argv[2], values[j].Symbol))
                {
                    if (!strcmp(argv[3], "-p"))
                    {
                        percentYear = yearlyPercentageOpenClose(values, open, j, atoi(argv[1]), dates);
                        // computer the yearlypercentage of a company during a given year
                    }

                    if (!strcmp(argv[3], "-a"))
                    {
                        if (j == 0)
                        {
                            j++;
                        }
                        flagAvgY = 1;
                        yearlySums(values, dates, atoi(argv[1]), j, &closeAvg, &openAvg, &lowAvg, &highAvg, &volumeAvg, &nbDays);
                        // compute the sums of the values in a year of a given symbol for further use
                    }
                    if (!strcmp(argv[3], "--a") || !strcmp(argv[3], "--a1") || !strcmp(argv[3], "--a2") || !strcmp(argv[3], "--a3") || !strcmp(argv[3], "--a4"))
                    {
                        if (j == 0)
                        {
                            j++;
                        }
                        flagAvgq = 1;
                        quarterlySums(values, dates, atoi(argv[1]), j, &closeAv[0], &openAv[0], &lowAv[0], &highAv[0], &volumeAv[0], &nbDay[0], &closeAv[1], &openAv[1], &lowAv[1], &highAv[1], &volumeAv[1], &nbDay[1], &closeAv[2], &openAv[2], &lowAv[2], &highAv[2], &volumeAv[2], &nbDay[2], &closeAv[3], &openAv[3], &lowAv[3], &highAv[3], &volumeAv[3], &nbDay[3]);
                        // compute the sums of the values of the quarters in a year of a given symbol for further use
                    }
                }
            }
        }

        for (int j = 0; j <= i; j++)
        {
            if (atoi(argv[1]) == dates[j].year)
            {
                if (!strcmp(argv[2], values[j].Symbol))
                {
                    if (!strcmp(argv[3], "-q") || !strcmp(argv[3], "-q1") || !strcmp(argv[3], "-q2") || !strcmp(argv[3], "-q3") || !strcmp(argv[3], "-q4"))
                    {
                        if (!strcmp(argv[3], "-q"))
                            flagq = 1;

                        quarterlyMinMax(values, dates, atoi(argv[1]), j, &minq[0], &maxq[0], &minq[1], &maxq[1], &minq[2], &maxq[2], &minq[3], &maxq[3]);
                        // Computes the highest and lowest price of a given company for each quarter of a given year
                    }
                    if (!strcmp(argv[3], "-pq") || !strcmp(argv[3], "-pq1") || !strcmp(argv[3], "-pq2") || !strcmp(argv[3], "-pq3") || !strcmp(argv[3], "-pq4"))
                    {
                        if (!strcmp(argv[3], "-pq"))
                            flagPq = 1;
                        quarterlyPercentageOpenClose(values, dates, atoi(argv[1]), j, &openPrice[0], &openPrice[1], &openPrice[2], &openPrice[3], &openPercerntage[0], &openPercerntage[1], &openPercerntage[2], &openPercerntage[3]);
                        // Computes the percentage between the open prices and the close prices for each quarter of a given year
                    }
                }
            }
            if (!strcmp(argv[1], values[j].Date))
            {
                if (!strcmp(argv[2], values[j].Symbol))
                {
                    if (!strcmp(argv[3], "-p"))
                    {
                        percentage = percentageOpenClose(values, j);
                        reportPercentageOpenClose(values, j, percentage, accessData);
                        // Computes the percentage between the open prices and the close prices of a given day
                    }
                }
            }
        }

        if (flagPq == 1)
        {
            reportPercentageQuarterly(symb, year, openPercerntage, accessData);
        }

        if (!strcmp(argv[3], "-pq1"))
        {
            reportPercentageQuarter(symb, year, openPercerntage[0], 1, accessData);
        }
        if (!strcmp(argv[3], "-pq2"))
        {
            reportPercentageQuarter(symb, year, openPercerntage[1], 2, accessData);
        }
        if (!strcmp(argv[3], "-pq3"))
        {
            reportPercentageQuarter(symb, year, openPercerntage[2], 3, accessData);
        }
        if (!strcmp(argv[3], "-pq4"))
        {
            reportPercentageQuarter(symb, year, openPercerntage[3], 4, accessData);
        }

        if (flagyp == 1)
        {
            reportPercentageYear(sym[0], atoi(argv[1]), percentYear, accessData);
        }

        if (flagAvgq == 1)
        {

            quarterlyAverage(&closeAv[0], &openAv[0], &lowAv[0], &highAv[0], &volumeAv[0], nbDay[0], &closeAv[1], &openAv[1], &lowAv[1], &highAv[1], &volumeAv[1], nbDay[1], &closeAv[2], &openAv[2], &lowAv[2], &highAv[2], &volumeAv[2], nbDay[2], &closeAv[3], &openAv[3], &lowAv[3], &highAv[3], &volumeAv[3], nbDay[3]);
            // compute the average of all the prices and volume in a given year for all 4 quarters

            if (!strcmp(argv[3], "--a"))
            {
                reportQuarterlyAverage(openAv, closeAv, highAv, lowAv, volumeAv, symb, year, accessData);
            }
            else if (!strcmp(argv[3], "--a1"))
            {
                quart = 1;

                reportQuarterAverage(symb, year, openAv[0], closeAv[0], highAv[0], lowAv[0], volumeAv[0], quart, accessData);
            }
            else if (!strcmp(argv[3], "--a2"))
            {
                quart = 2;
                reportQuarterAverage(symb, year, openAv[1], closeAv[1], highAv[1], lowAv[1], volumeAv[1], quart, accessData);
            }
            else if (!strcmp(argv[3], "--a3"))
            {
                quart = 3;
                reportQuarterAverage(symb, year, openAv[2], closeAv[2], highAv[2], lowAv[2], volumeAv[2], quart, accessData);
            }
            else if (!strcmp(argv[3], "--a4"))
            {
                quart = 4;
                reportQuarterAverage(symb, year, openAv[3], closeAv[3], highAv[3], lowAv[3], volumeAv[3], quart, accessData);
            }
        }

        if (flagAvgY == 1)
        {
            // compute the average of all the prices and volume in a given year
            yearlyAverage(nbDays, &closeAvg, &openAvg, &lowAvg, &highAvg, &volumeAvg);
            reportYearlyAverage(symb, year, openAvg, closeAvg, highAvg, lowAvg, volumeAvg, accessData);
        }

        int q;
        if (flagq == 1)
        {
            reportHighLowQuarterly(maxq, minq, symb, year, accessData);
        }

        if (!strcmp(argv[3], "-q1"))
        {
            q = 1;
            reportHighLowOneQuarter(q, maxq[0], minq[0], symb, year, accessData);
        }
        if (!strcmp(argv[3], "-q2"))
        {
            q = 2;
            reportHighLowOneQuarter(q, maxq[1], minq[1], symb, year, accessData);
        }
        if (!strcmp(argv[3], "-q3"))
        {
            q = 3;
            reportHighLowOneQuarter(q, maxq[2], minq[2], symb, year, accessData);
        }
        if (!strcmp(argv[3], "-q4"))
        {
            q = 4;
            reportHighLowOneQuarter(q, maxq[3], minq[3], symb, year, accessData);
        }
    }

    if (argc == 5)
    {
        for (int a = 0; a <= i; a++)
        {
            if (atoi(argv[1]) == dates[a].year)
            {
                if (atoi(argv[2]) == dates[a].month)
                {
                    if (!strcmp(argv[3], values[a].Symbol))
                    {
                        if (!strcmp(argv[4], "-m"))
                        {
                            minm = values[a].MarketLow;
                            maxm = values[a].MarketHigh;
                            break;
                        }

                        if (!strcmp(argv[4], "-p"))
                        {
                            open = values[a].MarketOpen;
                            break;
                        }

                        if (!strcmp(argv[4], "-a"))
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
            }
        }

        for (int j = 0; j <= i; j++)
        {
            if (atoi(argv[1]) == dates[j].year)
            {
                if (atoi(argv[2]) == dates[j].month)
                {
                    if (!strcmp(argv[3], values[j].Symbol))
                    {
                        if (!strcmp(argv[4], "-p"))
                        {
                            flagMP = 1;
                            percentMonth = monthlyPercentageOpenClose(values, atoi(argv[2]), open, j, atoi(argv[1]), dates);
                            // store the computed percentage difference between open and close for a given month in a given year
                        }
                        if (!strcmp(argv[4], "-a"))
                        {
                            if (j == 0)
                            {
                                j++;
                            }
                            flagAvgM = 1;
                            monthlySums(values, dates, atoi(argv[1]), atoi(argv[2]), j, &closeAvg, &openAvg, &lowAvg, &highAvg, &volumeAvg, &nbDays);
                            // compute all the sums of prices and volume of a company of a given month is a given year
                        }
                    }
                }
            }
        }

        if (flagAvgM == 1)
        {
            strcpy(sym, argv[3]);
            symb = sym[0];
            year = atoi(argv[1]);
            month = atoi(argv[2]);
            monthlyAverage(&closeAvg, &openAvg, &lowAvg, &highAvg, &volumeAvg, nbDays);
            // compute the monthly average of the values taken from the monthlysums function and return them by reference
            reportMonthlyAverage(symb, year, month, openAvg, closeAvg, highAvg, lowAvg, volumeAvg, accessData);
        }

        if (flagMP == 1)
        {
            strcpy(sym, argv[3]);
            symb = sym[0];
            reportPercentageMonth(symb, atoi(argv[1]), percentMonth, atoi(argv[2]), accessData);
        }

        for (int j = 0; j <= i; j++)
        {
            if (atoi(argv[1]) == dates[j].year)
            {
                if (atoi(argv[2]) == dates[j].month)
                {
                    if (!strcmp(argv[3], values[j].Symbol))
                    {
                        if (!strcmp(argv[4], "-m"))
                        {
                            flagm = 1;
                            monthlyMinMax(values, dates, atoi(argv[1]), atoi(argv[2]), j, &minm, &maxm);
                        }
                    }
                }
            }
        }

        strcpy(sym, argv[3]);
        symb = sym[0];
        year = atoi(argv[1]);
        month = atoi(argv[2]);

        if (flagm == 1)
        {
            reportHighLowMonthly(maxm, minm, symb, year, month, accessData);
        }

        float openPriceBuy, openPriceSell, priceBuy, priceSell, gainLossDifference;
        int flagGL = 0;
        for (int j = 0; j <= i; j++)
        {
            if (!strcmp(argv[1], values[j].Date))
            {
                if (!strcmp(argv[3], values[j].Symbol))
                {
                    flagGL = 1;
                    openPriceBuy = values[j].MarketOpen;
                    // store the open market price in the first given date
                }
            }
            if (!strcmp(argv[2], values[j].Date))
            {
                if (!strcmp(argv[3], values[j].Symbol))
                {
                    openPriceSell = values[j].MarketOpen;
                    // store the open market price in the second given date
                }
            }
        }

        if (flagGL == 1)
        {
            GainLoss(openPriceBuy, openPriceSell, atoi(argv[4]), &priceBuy, &priceSell, &gainLossDifference);
            // computes the price of the given stocks number at the buying day and selling day plus the gain and loss difference between them
            reportGainLoss(symb, argv[2], openPriceBuy, openPriceSell, gainLossDifference, argv[1], atoi(argv[4]), accessData);
        }
    }

    float percentYear1, percentYear2;
    float open1, open2;
    char symbol1, symbol2;
    float openPrice1[4], openPercerntage1[4];
    float openPrice2[4], openPercerntage2[4];
    char code[10];
    char code1;
    strcpy(sym, argv[3]);
    symbol1 = sym[0];
    strcpy(sym, argv[4]);
    symbol2 = sym[0];
    int flagOpen1, flagOpen2, flagOpen3, flagOpen4;
    flagOpen1 = flagOpen2 = flagOpen3 = flagOpen4 = 0;

    if (argc >= 2 && !strcmp(argv[1], "-comp"))
    {
        if (argc == 6)
        {
            for (int a = 0; a <= i; a++)
            {
                if (atoi(argv[2]) == dates[a].year)
                {
                    if (!strcmp(argv[3], values[a].Symbol))
                    {
                        if (!strcmp(argv[5], "-cy"))
                        {
                            // stores the first occurence of the open price in the given year for the given company
                            open1 = values[a].MarketOpen;
                            break;
                        }
                    }
                }
            }
            for (int a = 0; a <= i; a++)
            {
                if (atoi(argv[2]) == dates[a].year)
                {
                    if (!strcmp(argv[4], values[a].Symbol))
                    {
                        if (!strcmp(argv[5], "-cy"))
                        {
                            // stores the first occurence of the open price in the given year for the given company
                            open2 = values[a].MarketOpen;
                            break;
                        }
                    }
                }
            }

            for (int a = 0; a <= i; a++)
            {
                if (atoi(argv[2]) == dates[a].year)
                    if (!strcmp(argv[3], values[a].Symbol))
                        if (!strcmp(argv[5], "-cy"))
                            percentYear1 = yearlyPercentageOpenClose(values, open1, a, atoi(argv[2]), dates);
                // percentage of the first company in the given year
            }
            for (int a = 0; a <= i; a++)
            {
                if (atoi(argv[2]) == dates[a].year)
                    if (!strcmp(argv[4], values[a].Symbol))
                        if (!strcmp(argv[5], "-cy"))
                            percentYear2 = yearlyPercentageOpenClose(values, open2, a, atoi(argv[2]), dates);
                // percentage of the second company in the given year
            }

            if (!strcmp(argv[5], "-cy"))
            {
                comparePercent(percentYear1, percentYear2, symbol1, symbol2, 0, atoi(argv[2]), 0, 0, 0, accessData);
                // compute the percentage difference between 2 companies in a given year
            }
            for (int a = 0; a <= i; a++)
            {
                if (!strcmp(argv[2], values[a].Date))
                    if (!strcmp(argv[3], values[a].Symbol))
                        if (!strcmp(argv[5], "-cd"))
                        {
                            // percentage of the first company in the given date
                            percentYear1 = percentageOpenClose(values, a);
                            break;
                        }
            }
            int b;
            for (b = 0; b <= i; b++)
            {
                if (!strcmp(argv[2], values[b].Date))
                    if (!strcmp(argv[4], values[b].Symbol))
                        if (!strcmp(argv[5], "-cd"))
                        {
                            // percentage of the second company in the given date
                            percentYear2 = percentageOpenClose(values, b);
                            break;
                        }
            }

            strcpy(code, argv[2]);
            char *MonthFinal = strtok(code, "/");
            char *dayFinal = strtok(NULL, "/");
            char *YearFinal = strtok(NULL, "");
            if (!strcmp(argv[5], "-cd"))
            {
                comparePercent(percentYear1, percentYear2, symbol1, symbol2, 3, atoi(YearFinal), atoi(dayFinal), atoi(MonthFinal), 0, accessData);
                // compute the percentage difference between 2 companies in a given date
            }
        }
    }

    free(values);
    free(dates);
    fclose(accessData);
    return 0;
}
