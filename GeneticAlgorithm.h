#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include "TSP.h"
#include <vector>

class GeneticAlgorithm {
public:
    GeneticAlgorithm(TSP& problem, int populationSize, double mutationRate);
    void run(int generations);
    std::vector<int> getBestSolution() const;

private:
    TSP& problem;
    int populationSize;
    double mutationRate;
    std::vector<std::vector<int>> population;
    std::vector<int> bestSolution;

    void initializePopulation();
    void evaluate();
    std::vector<int> selectParent();
    std::vector<int> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2);
    void mutate(std::vector<int>& individual);
};

#endif
