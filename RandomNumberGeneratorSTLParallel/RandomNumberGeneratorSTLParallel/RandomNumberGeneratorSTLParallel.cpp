#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <execution>
#include <random>

static unsigned long long midSquareRandom(unsigned long long seed, int iterations) {
    unsigned long long num = seed;
    unsigned long long result = 0;
    for (int i = 0; i < iterations; ++i) {
        num *= num;
        num /= 100;
        result = result * 10 + (num % 10);
    }
    return result;
}

static unsigned long long linearCongruentialRandom(unsigned long long seed, unsigned long long a, unsigned long long c, unsigned long long m, int iterations) {
    unsigned long long num = seed;
    unsigned long long result = 0;
    for (int i = 0; i < iterations; ++i) {
        num = (a * num + c) % m;
        result = result * 10 + (num % 10);
    }
    return result;
}

int main() {
    unsigned long long seed = std::time(0);
    int iterations = 5;
    int size = 4;

    std::vector<unsigned long long> seeds(size);
    std::generate(seeds.begin(), seeds.end(), [&seed]() { return seed++; });

    std::vector<unsigned long long> midSquareResults(size);
    std::vector<unsigned long long> linearCongruentialResults(size);

    auto policy = std::execution::par;

    std::transform(policy, seeds.begin(), seeds.end(), midSquareResults.begin(), [iterations](unsigned long long seed) {
        return midSquareRandom(seed, iterations);
        });

    std::cout << "Metoda patratului mijlociu:\n";
    for (int i = 0; i < size; ++i) {
        std::cout << "Proces " << i << ": " << midSquareResults[i] << std::endl;
    }

    unsigned long long a = 1664525;
    unsigned long long c = 1013904223;
    unsigned long long m = 4294967296;

    std::transform(policy, seeds.begin(), seeds.end(), linearCongruentialResults.begin(), [iterations, a, c, m](unsigned long long seed) {
        return linearCongruentialRandom(seed, a, c, m, iterations);
        });

    std::cout << "\nGeneratorul liniar congruential:\n";
    for (int i = 0; i < size; ++i) {
        std::cout << "Proces " << i << ": " << linearCongruentialResults[i] << std::endl;
    }

    return 0;
}
