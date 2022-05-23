//--- 2021-2022 Summer Object Oriented Programing Assignment 3 ---//
//--------------------------//
//---Name & Surname: Özberk Hazantekin
//---Student Number: 150200100
//--------------------------//

#ifndef __STATISTICS_H
#define __STATISTICS_H

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include <vector>

class StatisticalDistribution{
    protected:
        double mean;
    public:
        virtual ~StatisticalDistribution();
        double getMean() const;
        virtual std::vector<double> sample(int, int) = 0;
        std::vector<double> calculate_confidence_interval(std::vector<double>, int, double);
};

class NormalDistribution: public StatisticalDistribution{
    private:
        double stddev;
    public:
        NormalDistribution();
        double getStandartDeviation() const;
        std::vector<double> sample(int, int);
};

class UniformDistribution: public StatisticalDistribution{
    private:
        double a;
        double b;
    public:
        UniformDistribution();
        std::vector<double> sample(int, int);
};

class ExponentialDistribution: public StatisticalDistribution{
    private:
        double lambda;
    public:
        ExponentialDistribution();
        std::vector<double> sample(int, int);
};

#endif