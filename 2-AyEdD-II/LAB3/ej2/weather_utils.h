
#ifndef WEATHER_UTILS_H 
    #define WEATHER_UTILS_H
    #include "weather.h"
    #include "array_helpers.h"
    #include <stdio.h>
    #include<stdlib.h>

    // Obtiene la menor temperatura  general registrada (segun los datos del arreglo)
    int low_min_temp(WeatherTable wheatable);
    
    // Registra la maxima temperatura de cada ano
    void procedimiento(WeatherTable a, int output[YEARS]);

    // Registra el mes con mayor cantidad de precipitaciones de cada ano
    void month_more_rain(WeatherTable arr, month_t output[YEARS]);

    // Obtiene la maxima temperatura que hizo en un determinado ano
    int max_temp_year(WeatherTable a, int year);

    // Obtiene el mes que hizo mas cantidad de precipitaciones en un ano
    month_t month_high_rain(WeatherTable arr, int year);
    
#endif 
