//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname: Özberk Hazantekin
//---Student Number: 150200100
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include "utils.h"

// CREATE AND RETURN A DISTRIBUTION DEPENDING ON THE INPUT

StatisticalDistribution* choose_function(int dist_type){
    switch (dist_type){
        case 0:{
            StatisticalDistribution* normal_dist = new NormalDistribution();
            return normal_dist;
            break;
        }
        case 1:{
            StatisticalDistribution* uniform_dist = new UniformDistribution();
            return uniform_dist;
            break;
        }
        case 2:{
            StatisticalDistribution* exponential_dist = new ExponentialDistribution();
            return exponential_dist;
            break;
        }
        default:{
            throw "Unidentified distribution function!";
        }       
    }
}



double many_trials(StatisticalDistribution* dist, std::vector<double> random_sample, double t_value, int trials, int sample_size, int seed_value){

    int local_seed = seed_value; // USE LOCAL VARIABLE TO INCREMENT SEED
    int success = 0;
    double precision;
    std::vector<double> randomSample, confidenceInterval;

    for (int i = 0; i < trials; i++){
        randomSample = dist->sample(sample_size, local_seed); // GET RANDOM SAMPLE
        local_seed += 1; // INCREMENT SEED
        confidenceInterval = dist->calculate_confidence_interval(randomSample, sample_size, t_value); // GET CONFIDENCE INTERVAL

        if (dist->getMean() >= confidenceInterval[0] && dist->getMean() <= confidenceInterval[2]){
            success++; // IF MEAN IS IN THE INTERVAL THEN INCREMENT SUCCESS
        }
    }

    precision = success/(double)trials; // CALCULATE PRECISION

    return precision; // RETURN PRECISION

}