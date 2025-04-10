#ifndef TSP_H
#define TSP_H

#include <vector>

class TSP {
public:
    TSP(int numCities);
    double calculateDistance(const std::vector<int>& path) const;
    std::vector<std::vector<double>> distances;

private:
    int numCities;
    void generateRandomDistances();
};

#endif
