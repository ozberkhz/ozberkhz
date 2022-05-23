//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname: Özberk Hazantekin
//---Student Number: 150200100
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include "statistics.h"
#include <random>
#include <iostream>

double StatisticalDistribution::getMean() const{
    return mean; // MEAN GETTER
}

std::vector<double> StatisticalDistribution::calculate_confidence_interval(std::vector<double> random_sample, int sample_size, double t_value){
    std::vector<double> confidence_interval;

    double sample_variation = 0;
    double sample_standart_deviation = 0;
    double random_sample_sum = 0;

    for (auto& n: random_sample){
        random_sample_sum += n; // SUM OF ALL VALUES IN THE SAMPLE
    }

    double sample_mean = random_sample_sum / random_sample.size(); // CALCULATE MEAN

    for (auto& n: random_sample){                                   // CALCULATE VARIANCE
        sample_variation += (n - sample_mean) * (n - sample_mean);  //
    }                                                               //
    sample_variation /= random_sample.size();                       //

    sample_standart_deviation = sqrt(sample_variation); // CALCULATE STANDART DEVIATION

    confidence_interval.push_back(sample_mean - t_value * (sample_standart_deviation / (float)sqrt(sample_size)));  //
    confidence_interval.push_back(sample_mean);                                                                     // GET CONFIDENCE INTERVAL
    confidence_interval.push_back(sample_mean + t_value * (sample_standart_deviation / (float)sqrt(sample_size)));  //

    return confidence_interval;
}

StatisticalDistribution::~StatisticalDistribution(){
    delete this; // DESTRUCTOR
}

// NORMAL DISTRIBUTION METHODS

NormalDistribution::NormalDistribution(){
    mean = 0.0;
    stddev = 1.0;
}

std::vector<double> NormalDistribution::sample(int sample_size, int seed_value){
    std::vector<double> sample_vector;

    // GET THE RANDOM NUMBER GENERATOR READY

    std::default_random_engine generator;
    generator.seed(seed_value);
    std::normal_distribution<double> distribution(mean,stddev);
    double number;

    // GENERATE RANDOM NUMBERS AND PUSH THEM INTO THE VECTOR

    for (int i = 0; i < sample_size; i++){
        number = distribution(generator);
        sample_vector.push_back(number);
    }

    return sample_vector;
}

// UNIFORM DISTRIBUTION METHODS

UniformDistribution::UniformDistribution(){
    mean = 0.0;
    a = -1.0;
    b = 1.0;
}

std::vector<double> UniformDistribution::sample(int sample_size, int seed_value){
    std::vector<double> sample_vector;

    // GET THE RANDOM NUMBER GENERATOR READY

    std::default_random_engine generator;
    generator.seed(seed_value);
    std::uniform_real_distribution<double> distribution(a, b);
    double number;

    // GENERATE RANDOM NUMBERS AND PUSH THEM INTO THE VECTOR

    for (int i = 0; i < sample_size; i++){
        number = distribution(generator);
        sample_vector.push_back(number);
    }

    return sample_vector;
}

// EXPONENTIAL DISTRIBUTION METHODS

ExponentialDistribution::ExponentialDistribution(){
    mean = 1.0;
    lambda = 1.0;
}

std::vector<double> ExponentialDistribution::sample(int sample_size, int seed_value){
    std::vector<double> sample_vector;

    // GET THE RANDOM NUMBER GENERATOR READY

    std::default_random_engine generator;
    generator.seed(seed_value);
    std::exponential_distribution<double> distribution(lambda);
    double number;

    // GENERATE RANDOM NUMBERS AND PUSH THEM INTO THE VECTOR

    for (int i = 0; i < sample_size; i++){
        number = distribution(generator);
        sample_vector.push_back(number);
    }

    return sample_vector;
}