#include "GeneticAlgorithm.h"
#include <algorithm>
#include <random>

GeneticAlgorithm::GeneticAlgorithm(TSP& problem, int populationSize, double mutationRate)
    : problem(problem), populationSize(populationSize), mutationRate(mutationRate) {
    initializePopulation();
    evaluate();
}

void GeneticAlgorithm::initializePopulation() {
    int numCities = problem.distances.size();
    population.resize(populationSize, std::vector<int>(numCities));

    for (auto& individual : population) {
        for (int i = 0; i < numCities; ++i) {
            individual[i] = i;
        }
        std::shuffle(individual.begin(), individual.end(), std::mt19937(std::random_device()()));
    }
}

void GeneticAlgorithm::evaluate() {
    double bestDistance = 1e9;
    for (const auto& individual : population) {
        double distance = problem.calculateDistance(individual);
        if (distance < bestDistance) {
            bestDistance = distance;
            bestSolution = individual;
        }
    }
}

std::vector<int> GeneticAlgorithm::selectParent() {
    return population[rand() % populationSize];
}

std::vector<int> GeneticAlgorithm::crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
    int size = parent1.size();
    std::vector<int> child(size, -1);

    int start = rand() % size, end = rand() % size;
    if (start > end) std::swap(start, end);

    for (int i = start; i <= end; ++i) {
        child[i] = parent1[i];
    }

    int idx = 0;
    for (int i = 0; i < size; ++i) {
        if (std::find(child.begin(), child.end(), parent2[i]) == child.end()) {
            while (child[idx] != -1) ++idx;
            child[idx] = parent2[i];
        }
    }

    return child;
}

void GeneticAlgorithm::mutate(std::vector<int>& individual) {
    if ((rand() / double(RAND_MAX)) < mutationRate) {
        int i = rand() % individual.size();
        int j = rand() % individual.size();
        std::swap(individual[i], individual[j]);
    }
}

void GeneticAlgorithm::run(int generations) {
    for (int i = 0; i < generations; ++i) {
        std::vector<std::vector<int>> newPopulation;
        for (int j = 0; j < populationSize; ++j) {
            std::vector<int> parent1 = selectParent();
            std::vector<int> parent2 = selectParent();
            std::vector<int> child = crossover(parent1, parent2);
            mutate(child);
            newPopulation.push_back(child);
        }
        population = newPopulation;
        evaluate();
    }
}

std::vector<int> GeneticAlgorithm::getBestSolution() const {
    return bestSolution;
}
