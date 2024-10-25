#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>
#include <algorithm>

class Statistics {
public:
    static double calculateMean(const std::vector<double>& data) {
        double sum = 0.0;
        for (double value : data) {
            sum += value;
        }
        return sum / data.size();
    }

    static double calculateVariance(const std::vector<double>& data) {
        double mean = calculateMean(data);
        double variance = 0.0;
        for (double value : data) {
            variance += (value - mean) * (value - mean);
        }
        return variance / (data.size() - 1);
    }

    static double calculateStandardDeviation(const std::vector<double>& data) {
        return std::sqrt(calculateVariance(data));
    }

    static double calculateZScore(double value, double mean, double stdDev) {
        return (value - mean) / stdDev;
    }

    static double calculateConfidenceInterval(const std::vector<double>& data, double confidenceLevel) {
        double mean = calculateMean(data);
        double stdDev = calculateStandardDeviation(data);
        double z = getZValue(confidenceLevel);
        return z * (stdDev / std::sqrt(data.size()));
    }

    static double probabilityOfValue(const std::vector<double>& data, double value) {
        return std::count(data.begin(), data.end(), value) / static_cast<double>(data.size());
    }

private:
    static double getZValue(double confidenceLevel) {
        if (confidenceLevel == 0.90) return 1.645;
        if (confidenceLevel == 0.95) return 1.96;
        if (confidenceLevel == 0.99) return 2.576;
        return std::numeric_limits<double>::quiet_NaN(); // Handle unknown levels
    }
};

int main() {
    std::vector<double> data;
    double input;

    std::cout << "Enter data values (type 'end' to finish): ";
    while (std::cin >> input) {
        data.push_back(input);
    }

    std::cin.clear(); // Clear the error flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input

    double mean = Statistics::calculateMean(data);
    double variance = Statistics::calculateVariance(data);
    double stdDev = Statistics::calculateStandardDeviation(data);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Sample Mean: " << mean << std::endl;
    std::cout << "Variance: " << variance << std::endl;
    std::cout << "Standard Deviation: " << stdDev << std::endl;

    double z = Statistics::calculateZScore(input, mean, stdDev);
    std::cout << "Z-Score for the last entered value: " << z << std::endl;

    double confidenceLevel;
    std::cout << "Enter confidence level (0.90, 0.95, 0.99): ";
    std::cin >> confidenceLevel;
    double marginOfError = Statistics::calculateConfidenceInterval(data, confidenceLevel);
    std::cout << "Margin of Error at " << confidenceLevel * 100 << "% confidence: " << marginOfError << std::endl;

    double probValue;
    std::cout << "Enter a value to find its probability: ";
    std::cin >> probValue;
    double probability = Statistics::probabilityOfValue(data, probValue);
    std::cout << "Probability of value " << probValue << ": " << probability * 100 << "%" << std::endl;

    return 0;
}
