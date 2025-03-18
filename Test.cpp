#include <iostream>
#include <chrono>
#include <iomanip>

int main() {
    int daysToAdd;
    std::cout << "Enter the number of days to add: ";
    std::cin >> daysToAdd;

    // Get today's date
    auto today = std::chrono::system_clock::now();
    auto todayTimeT = std::chrono::system_clock::to_time_t(today);
    tm todayTm = *std::localtime(&todayTimeT);

    // Add days
    auto futureDate = today + std::chrono::hours(24 * daysToAdd);
    auto futureTimeT = std::chrono::system_clock::to_time_t(futureDate);
    tm futureTm = *std::localtime(&futureTimeT);

    // Display the future date
    std::cout << "Future date: " 
              << std::put_time(&futureTm, "%Y-%m-%d") 
              << std::endl;

    return 0;
}