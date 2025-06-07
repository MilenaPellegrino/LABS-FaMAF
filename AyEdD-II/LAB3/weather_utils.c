#include<stdlib.h>
#include<stdio.h>
#include "array_helpers.h"

int min(int a, int b){
    return a < b ? a : b;
}

int max(int a, int b){
    return a > b ? a : b;
}
int low_min_temp(WeatherTable wheatable){
    int mins = wheatable[0][0][0]._min_temp;
    for(unsigned i=0; i<YEARS; i++){
        for(unsigned j = 0; j< MONTHS; j++){
            for(unsigned k = 0; k<DAYS; k++){
                int min_act = wheatable[i][j][k]._min_temp;
                mins = min(mins, min_act);
            }
        }
        
    }
    return mins;
}

int max_temp_year(WeatherTable a, int year){
    int maxs = a[0][0][0]._max_temp;
    for(unsigned int i =0; i<MONTHS; i++){
        for(unsigned j=0; i<DAYS; j++){
            int max_act = a[year][i][j]._max_temp;
            maxs = max(maxs, max_act);
        }
    }
    return maxs;
}

void procedimiento(WeatherTable a, int output[YEARS]) {
    for (unsigned int year = 0; year < YEARS; year++) {
        output[year] =  max_temp_year(a, year); // la mayor temperatura máxima del año 'year' + 1980
    }
}

month_t month_high_rain(WeatherTable arr, int year){
    unsigned int month_high = 1;
    month_t month_res = january;
    for(unsigned int i =0; i<MONTHS; i++){
        for(unsigned int j=0; j<DAYS; j++){
            if(arr[year][i][j]._rainfall > month_high){
                month_high = i;
            }
        }
    }
    month_res = month_high - 1;
    return month_res;
}
void month_more_rain(WeatherTable arr, month_t output[YEARS]){
    for(unsigned int year = 0; year<YEARS; year++){
        output[year] = month_high_rain(arr, year); // Mes con la mayor cantidad de precipitaciones del ano
    }

}
