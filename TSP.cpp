#include "TSP.h"
#include <cmath>
#include <cstdlib>

TSP::TSP(int numCities) : numCities(numCities) {
    generateRandomDistances();
}

void TSP::generateRandomDistances() {
    distances.resize(numCities, std::vector<double>(numCities));
    for (int i = 0; i < numCities; ++i) {
        for (int j = i + 1; j < numCities; ++j) {
            distances[i][j] = distances[j][i] = rand() % 100 + 1;
        }
    }
}

double TSP::calculateDistance(const std::vector<int>& path) const {
    double totalDistance = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        totalDistance += distances[path[i]][path[i + 1]];
    }
    totalDistance += distances[path.back()][path.front()];
    return totalDistance;
}
