

#include "utility"

#include <algorithm>
#include <iostream>
#include <iterator>

#include "rng.h"

void ErrorMessage(const std::string& message) {
  std::cout << message << "\n";
  std::cout << "There was an error. Exiting.\n";
}

void PrintVector(const std::vector<int>& the_vector) {
  std::copy(the_vector.begin(), the_vector.end(),
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
}

void FillVector(std::vector<int>& the_vector, const int nelements,
                RandomNumberGenerator& random_number_generator) {
  for (int i = 1; i <= nelements; i++) {
    the_vector[i] = random_number_generator.next();
  }
}

float CalculateAverage(const std::vector<int>& the_vector) {
  int sum = accumulate(the_vector.begin(), the_vector.end(), 0);
  float average = float(sum) / float(the_vector.size());
}

int CalculateMedian(const std::vector<int>& the_vector) {
  std::vector<int> local_copy{the_vector};
  std::sort(local_copy.begin(), local_copy.end());
  int median;
  try {
    median = local_copy.at(local_copy.size() / 2);
  } catch (std::exception const& problem) {
    std::cout << problem.what() << "\n";
    ErrorMessage("Couldn't access the middle of the vector.");
    exit(1);
  }
}

int CalculateMode(const std::vector<int>& the_vector) {
  std::vector<int> local_copy{the_vector};
  std::sort(local_copy.begin(), local_copy.end());
  int current = local_copy[0];
  int count = 1;
  int mode = current;
  int mode_count = count;

  for (int i = 1; i <= 1000; i++) {
    if (local_copy[i] == current) {
      count++;
    } else {
      if (count > mode_count) {
        mode_count = count;
        mode = current;
      }
      current = local_copy[i];
      count = 1;
    }
  }
}
