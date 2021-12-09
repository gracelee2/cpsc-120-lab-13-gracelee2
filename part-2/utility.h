
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include <vector>

#include "rng.h"

/// CalculateAverage calculates the average (arithmetic mean) of all the
/// values stored in \p the_vector. _Must be done using C++ Standard
/// Library functions._
///
/// See https://en.wikipedia.org/wiki/Arithmetic_mean
///
/// The algorithm starts by delcaring and initializing an integer variable
/// which will represent the sum of all the values in \p the_vector. Using
/// [accumulate()](https://en.cppreference.com/w/cpp/algorithm/accumulate)
/// sum the elements of \p the_vector and store the result into an integer
/// variable.
///
/// Calculate the average by promoting the sum and the size of \p the_vector
/// to floats and find the quotient.
///
/// \f[\bar{x} = \frac{1}{n}\sum_{i = 1}^{n} x_i\f]
///
/// \param the_vector The vector of integers created in the main function.
///
/// \returns The average (arithmetic mean) value in the vector as a float
float CalculateAverage(const std::vector<int>& the_vector);

/// CalculateMedian calculates the median of all the values stored in
/// \p the_vector.
/// See https://en.wikipedia.org/wiki/Median
/// \param the_vector The vector of integers created in the main function.
///
/// \returns The median
int CalculateMedian(const std::vector<int>& the_vector);

/// CalculateMode calculates the mode of all the values stored in
/// \p the_vector.
/// See https://en.wikipedia.org/wiki/Mode_(statistics)
/// \param the_vector The vector of integers created in the main function.
///
/// \returns The median
int CalculateMode(const std::vector<int>& the_vector);

/// FillVector filles \p the_vector with \p nelements random numbers given by
/// \p random_number_generator.
///
/// Using [generate()](https://en.cppreference.com/w/cpp/algorithm/generate),
/// \p the_vector is filled with values that are returned by the next()
/// method of \p random_number_generator.
///
/// \param the_vector The vector of integers created in the main function.
/// \param nelements The number of random numbers to generate and insert
/// into \p the_vector.
/// \param random_number_generator The random number generator created in
/// the main function.
/// \sa RandomNumberGenerator::next()
/// \remarks This function uses a [C++ Lambda Expression]
/// (https://en.cppreference.com/w/cpp/language/lambda)
/// as the third parameter to generate.
void FillVector(std::vector<int>& the_vector, const int nelements,
                RandomNumberGenerator& random_number_generator);

/// PrintVector prints out the elements of \p the_vector each on a line of
/// their own.
///
/// This function uses
/// [copy()](https://en.cppreference.com/w/cpp/algorithm/copy) and
/// an
/// [ostream_iterator()]
/// (https://en.cppreference.com/w/cpp/iterator/ostream_iterator)
/// to copy each element of \p the_vector to cout.
///
/// \code
/// std::vector<int> the_vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
/// PrintVector(the_vector);
/// \endcode
///
/// This above code will print:
/// \code
/// 1 2 3 4 5 6 7 8 9 10
/// \endcode
///
/// \param the_vector This is the vector of integers created in
/// the main function.
void PrintVector(const std::vector<int>& the_vector);

/// ErrorMessage prints out \p message first and then prints the standard
/// message
/// \code
/// "There was an error. Exiting.\n".
/// \endcode
///
/// \param message The programmer defined string that specifies the current
/// error.
void ErrorMessage(const std::string& message);

#endif
