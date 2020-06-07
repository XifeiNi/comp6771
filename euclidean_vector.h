#ifndef ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
#define ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_

#include <exception>
#include <list>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept { return what_.c_str(); }

 private:
  std::string what_;
};

class EuclideanVector {
 public:
  EuclideanVector() noexcept : EuclideanVector(1) {}

  /*
   * Default constructor
   * A constructor that takes the number of dimensions (as a int) but no magnitudes, sets the
   * magnitude in each dimension as 0.0. assume the integer input will always be non-negative.
   */
  explicit EuclideanVector(const int dimension) noexcept : EuclideanVector(dimension, 0.0) {}

  /*
   * A constructor that takes the number of dimensions (as a int) and initialises the magnitude in
   * each dimension as the second argument (a double). You can assume the integer input will always
   * be non-negative.
   */
  EuclideanVector(const int dimension, const double num) noexcept;

  /*
   * A constructor (or constructors) that takes the start and end of an iterator to a std:vector and
   * works out the required dimensions, and sets the magnitude in each dimension according to the
   * iterated values.
   */
  EuclideanVector(const std::vector<double>::const_iterator begin,
                  const std::vector<double>::const_iterator end) noexcept;
  /*
   * A constructor (or constructors) that takes another euclidean vector and make a copy of it.
   */
  EuclideanVector(const EuclideanVector& vector) noexcept;

  /*
   * A constructor (or constructors) that takes another euclidean vector and move resources from it.
   * After moving, the original vector it moves from will no longer exist.
   */
  EuclideanVector(EuclideanVector&& vector) noexcept;

  /*
   * Destructor: free all the memory spaces.
   */
  ~EuclideanVector() noexcept = default;

  /*
   * A copy assignment operator overload
   * Example: a = b;
   */
  EuclideanVector& operator=(const EuclideanVector& o) noexcept;
  /*
   * A move assignment operator overload
   * Example: a = std::move(b);
   */
  EuclideanVector& operator=(EuclideanVector&& o) noexcept;

  /*
   * Allows to get the value in a given dimension of the Euclidean Vector.
   */
  double operator[](const int index) const noexcept;

  /*
   * Allows to set the value in a given dimension of the Euclidean Vector.
   */
  double& operator[](const int index) noexcept;

  /*
   * For adding vectors of the same dimension.
   * Given: X = a.GetNumDimensions(), Y = b.GetNumDimensions()
   * When: X != Y
   * Throw: "Dimensions of LHS(X) and RHS(Y) do not match"
   */
  EuclideanVector& operator+=(const EuclideanVector& o);

  /*
   * For subtracting vectors of the same dimension.
   * Given: X = a.GetNumDimensions(), Y = b.GetNumDimensions()
   * When: X != Y
   * Throw: "Dimensions of LHS(X) and RHS(Y) do not match"
   */
  EuclideanVector& operator-=(const EuclideanVector& o);

  /*
   * For scalar multiplication, e.g. [1 2] * 3 = [3 6]
   */
  EuclideanVector& operator*=(const double o) noexcept;

  /*
   * For scalar division, e.g. [3 6] / 2 = [1.5 3]
   * When: b == 0
   * Throw: "Invalid vector division by 0"
   */
  EuclideanVector& operator/=(const double o);

  /*
   * Operators for type casting to a constant std::vector
   */
  explicit operator std::vector<double>() const noexcept;

  /*
   * Operators for type casting to a const std::list
   */
  explicit operator std::list<double>() const noexcept;

  /*
   * Returns the value of the magnitude in the dimension given as the function parameter
   * When: For Input X: when X is < 0 or X is >= number of dimensions
   * Throw: "Index X is not valid for this EuclideanVector object"
   */
  double at(int i) const;

  /*
   * Returns the reference of the magnitude in the dimension given as the function parameter
   * When: For Input X: when X is < 0 or X is >= number of dimensions
   * Throw: "Index X is not valid for this EuclideanVector object"
   */
  double& at(int);

  /*
   * Return the number of dimensions in a particular EuclideanVector
   */
  int GetNumDimensions() const noexcept;

  /*
   * Returns the Euclidean norm of the vector as a double. The Euclidean norm is the square root of
   * the sum of the squares of the magnitudes in each dimension. E.g, for the vector [1 2 3] the
   * Euclidean norm is sqrt(1*1 + 2*2 + 3*3) = 3.74. When: this->GetNumDimensions() == 0 Throw:
   * "EuclideanVector with no dimensions does not have a norm"
   */
  double GetEuclideanNorm() const;

  /*
   * Returns a Euclidean vector that is the unit vector of *this vector. The magnitude for each
   * dimension in the unit vector is the original vector's magnitude divided by the Euclidean norm.
   * When: this->GetNumDimensions() == 0
   * Throw: "EuclideanVector with no dimensions does not have a unit vector"
   * When: this->GetEuclideanNorm() == 0
   * Throw: "EuclideanVector with euclidean normal of 0 does not have a unit vector"
   */
  EuclideanVector CreateUnitVector() const;

  /*
   * Prints out the magnitude in each dimension of the Euclidean Vector (surrounded by [ and ]),
   * e.g. for a 3-dimensional vector: [1 2 3]
   */
  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) noexcept {
    os << "[";
    for (auto i = 0; i < v.GetNumDimensions(); ++i) {
      if (i == v.GetNumDimensions() - 1) {
        os << v.at(i);
      } else {
        os << v.at(i) << " ";
      }
    }
    os << "]";
    return os;
  }

  /*
   * True if the two vectors are equal in the number of dimensions and the magnitude in each
   * dimension is equal.
   */
  friend bool operator==(const EuclideanVector& rhs, const EuclideanVector& lhs) noexcept {
    if (rhs.GetNumDimensions() != lhs.GetNumDimensions()) {
      return false;
    }
    for (auto i = 0; i < rhs.GetNumDimensions(); ++i) {
      if (rhs[i] != lhs[i]) {
        return false;
      }
    }
    return true;
  }

  /*
   * True if the two vectors are not equal in the number of dimensions or the magnitude in each
   * dimension is not equal.
   */
  friend bool operator!=(const EuclideanVector& rhs, const EuclideanVector& lhs) noexcept {
    return !(rhs == lhs);
  }

  /*
   * For adding vectors of the same dimension.
   */
  friend EuclideanVector operator+(const EuclideanVector& rhs, const EuclideanVector& lhs) {
    if (rhs.GetNumDimensions() != lhs.GetNumDimensions()) {
      throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(rhs.GetNumDimensions()) +
                                 ") and RHS(" + std::to_string(lhs.GetNumDimensions()) +
                                 ") do not match");
    }

    EuclideanVector result(rhs);
    for (auto i = 0; i < rhs.GetNumDimensions(); ++i) {
      result[i] += lhs[i];
    }
    return result;
  }

  /*
   * For substracting vectors of the same dimension.
   */
  friend EuclideanVector operator-(const EuclideanVector& rhs, const EuclideanVector& lhs) {
    if (rhs.GetNumDimensions() != lhs.GetNumDimensions()) {
      throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(rhs.GetNumDimensions()) +
                                 ") and RHS(" + std::to_string(lhs.GetNumDimensions()) +
                                 ") do not match");
    }

    EuclideanVector result(rhs);
    for (auto i = 0; i < rhs.GetNumDimensions(); ++i) {
      result[i] -= lhs[i];
    }
    return result;
  }

  /*
   * For dot-product multiplication, returns a double.
   * E.g., [1 2] * [3 4] = 1 * 3 + 2 * 4 = 11
   */
  friend double operator*(const EuclideanVector& rhs, const EuclideanVector& lhs) {
    if (rhs.GetNumDimensions() != lhs.GetNumDimensions()) {
      throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(rhs.GetNumDimensions()) +
                                 ") and RHS(" + std::to_string(lhs.GetNumDimensions()) +
                                 ") do not match");
    }

    double result = 0;
    for (auto i = 0; i < rhs.GetNumDimensions(); ++i) {
      result += (rhs[i] * lhs[i]);
    }
    return result;
  }

  /*
   * For scalar multiplication, e.g. [1 2] * 3 = 3 * [1 2] = [3 6].
   */
  friend EuclideanVector operator*(const EuclideanVector& rhs, double scalar) noexcept {
    EuclideanVector result(rhs);
    for (auto i = 0; i < rhs.GetNumDimensions(); ++i) {
      result[i] *= scalar;
    }
    return result;
  }

  /*
   * For scalar multiplication, e.g. [1 2] * 3 = 3 * [1 2] = [3 6].
   */
  friend EuclideanVector operator*(double scalar, const EuclideanVector& rhs) noexcept {
    EuclideanVector result(rhs);
    for (auto i = 0; i < rhs.GetNumDimensions(); ++i) {
      result[i] = result[i] * scalar;
    }
    return result;
  }

  /*
   * For scalar division, e.g. [3 6] / 2 = [1.5 3]
   *  When: c == 0
   *  Throw: "Invalid vector division by 0"
   */
  friend EuclideanVector operator/(const EuclideanVector& rhs, double scalar) {
    if (scalar == 0) {
      throw EuclideanVectorError("Invalid vector division by 0");
    }

    EuclideanVector result(rhs);
    for (auto i = 0; i < rhs.GetNumDimensions(); ++i) {
      result[i] = result[i] / scalar;
    }
    return result;
  }

 private:
  std::unique_ptr<double[]> magnitudes_;
  int num_dimension_;
};

#endif  // ASSIGNMENTS_EV_EUCLIDEAN_VECTOR_H_
