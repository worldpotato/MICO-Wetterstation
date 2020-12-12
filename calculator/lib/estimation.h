/**
 * @author      : worldpotato (worldpotato@$HOSTNAME)
 * @file        : estimation
 * @created     : Friday Nov 20, 2020 10:21:50 CET
 */

#ifndef ESTIMATION_H

#define ESTIMATION_H

#include <math.h> 

namespace estimation {

    float estimateTaupunkt(float* temp, float* relHum) {

        float SDD = 6.1078 * pow(10,(7.5 * *temp)/(237.3 + *temp));
        float DD = *relHum/100.0 * SDD;

        double a = 7.5;
        double b = 237.3;
        float v = (float) log10(DD/6.1078);
        float taupunkt = b*v/(a-v);
        return taupunkt;
    }

    float estimateQuality(float* sensorData){
        int factorTemp = 10;
        int factorLight = 10;
        int factorDruck = 5;
        int factorLuftfeuchte = 7;

        float normTemp = sensorData[0]/25.0;
        float normLF = sensorData[1]/35;
        float normDruck = sensorData[2]/98460;
        float normLight = sensorData[3]/3000;

#ifdef DEBUG
        Serial.println("NormData:");
        Serial.println(normTemp);
        Serial.println(normLF);
        Serial.println(normDruck);
        Serial.println(normLight);
#endif

        float quality = factorTemp * normTemp +
            factorLight * normLight +
            factorLuftfeuchte * normLF +
            factorDruck * normDruck;

        quality = quality/32 * 100;

#ifdef DEBUG
        Serial.println("Quality:");
        Serial.println(quality);
#endif
        return quality;

    }

    float estimateAkkuProzent(float u) {
        float norm_u = u - 3.4;
        float max_u = 4.2 - 3.4;

        float percent = norm_u/max_u * 100;
#ifdef DEBUG
        Serial.println("Percent:");
        Serial.println(percent);
#endif
        return percent;
    }
}

#endif /* end of include guard ESTIMATION_H */

