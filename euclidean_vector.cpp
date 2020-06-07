#include "assignments/ev/euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm
#include <cassert>
#include <cmath>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

// Constructors
EuclideanVector::EuclideanVector(const int dimension, const double num) noexcept
  : magnitudes_{std::make_unique<double[]>(dimension)}, num_dimension_{dimension} {
  for (auto i = 0; i < this->GetNumDimensions(); ++i) {
    magnitudes_[i] = num;
  }
}

EuclideanVector::EuclideanVector(const std::vector<double>::const_iterator begin,
                                 const std::vector<double>::const_iterator end) noexcept
  : EuclideanVector(static_cast<int>(std::distance(begin, end))) {
  int i = 0;
  for (auto it = begin; it != end; ++it) {
    magnitudes_[i] = *it;
    i++;
  }
}

EuclideanVector::EuclideanVector(const EuclideanVector& vector) noexcept
  : EuclideanVector(vector.num_dimension_) {
  for (auto i = 0; i < this->GetNumDimensions(); ++i) {
    magnitudes_[i] = vector.magnitudes_[i];
  }
}

EuclideanVector::EuclideanVector(EuclideanVector&& vector) noexcept
  : magnitudes_{std::move(vector.magnitudes_)}, num_dimension_{vector.num_dimension_} {
  vector.num_dimension_ = 0;
}

// Getter via []
double EuclideanVector::operator[](const int index) const noexcept {
  assert(index < this->GetNumDimensions());
  return magnitudes_[index];
}

// Setter via []
double& EuclideanVector::operator[](const int index) noexcept {
  assert(index < this->GetNumDimensions());
  return magnitudes_[index];
}

// Overloading '=' by copying
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& o) noexcept {
  this->magnitudes_ = std::make_unique<double[]>(o.num_dimension_);
  this->num_dimension_ = o.num_dimension_;
  for (auto i = 0; i < o.num_dimension_; ++i) {
    this->magnitudes_[i] = o.magnitudes_[i];
  }
  return *this;
}

// Overloading '=' by moving
EuclideanVector& EuclideanVector::operator=(EuclideanVector&& o) noexcept {
  this->magnitudes_ = std::move(o.magnitudes_);
  this->num_dimension_ = o.num_dimension_;
  o.num_dimension_ = 0;
  return *this;
}

// '+-*/' overloading
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& o) {
  if (o.GetNumDimensions() != this->GetNumDimensions()) {
    throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(this->GetNumDimensions()) +
                               ") and RHS(" + std::to_string(o.GetNumDimensions()) +
                               ") do not match");
  }

  for (auto i = 0; i < o.num_dimension_; ++i) {
    this->magnitudes_[i] += o.magnitudes_[i];
  }
  return *this;
}

EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& o) {
  if (o.GetNumDimensions() != this->GetNumDimensions()) {
    throw EuclideanVectorError("Dimensions of LHS(" + std::to_string(this->GetNumDimensions()) +
                               ") and RHS(" + std::to_string(o.GetNumDimensions()) +
                               ") do not match");
  }

  for (auto i = 0; i < o.num_dimension_; ++i) {
    this->magnitudes_[i] -= o.magnitudes_[i];
  }
  return *this;
}

EuclideanVector& EuclideanVector::operator*=(const double o) noexcept {
  for (auto i = 0; i < this->num_dimension_; ++i) {
    this->magnitudes_[i] *= o;
  }
  return *this;
}

EuclideanVector& EuclideanVector::operator/=(const double o) {
  if (o == 0) {
    throw EuclideanVectorError("Invalid vector division by 0");
  }

  for (auto i = 0; i < this->num_dimension_; ++i) {
    this->magnitudes_[i] /= o;
  }
  return *this;
}

// Type conversion
EuclideanVector::operator std::vector<double>() const noexcept {
  std::vector<double> result;
  for (auto i = 0; i != this->GetNumDimensions(); ++i) {
    result.push_back(this->magnitudes_[i]);
  }
  return result;
}

EuclideanVector::operator std::list<double>() const noexcept {
  std::list<double> result;
  for (auto i = 0; i != this->GetNumDimensions(); ++i) {
    result.push_back(this->magnitudes_[i]);
  }
  return result;
}

// Getters
double EuclideanVector::at(int i) const {
  if (i < 0 || i >= this->GetNumDimensions()) {
    throw EuclideanVectorError(std::string("Index ") + std::to_string(i) +
                               std::string(" is not valid for this EuclideanVector object"));
  }
  return magnitudes_[i];
}

double& EuclideanVector::at(int i) {
  if (i < 0 || i >= this->GetNumDimensions()) {
    throw EuclideanVectorError(std::string("Index ") + std::to_string(i) +
                               std::string(" is not valid for this EuclideanVector object"));
  }
  return magnitudes_[i];
}

int EuclideanVector::GetNumDimensions() const noexcept {
  return this->num_dimension_;
}

double EuclideanVector::GetEuclideanNorm() const {
  if (this->GetNumDimensions() == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a norm");
  }
  double sum = 0;
  for (auto i = 0; i < this->GetNumDimensions(); ++i) {
    sum += (this->magnitudes_[i] * this->magnitudes_[i]);
  }
  return sqrt(sum);
}

EuclideanVector EuclideanVector::CreateUnitVector() const {
  if (this->GetNumDimensions() == 0) {
    throw EuclideanVectorError("EuclideanVector with no dimensions does not have a unit vector");
  }

  // Get euclidean norm and see if it's zero.
  double norm = this->GetEuclideanNorm();
  if (norm == 0) {
    throw EuclideanVectorError(
        "EuclideanVector with euclidean normal of 0 does not have a unit vector");
  }

  EuclideanVector result(*this);
  for (auto i = 0; i < result.GetNumDimensions(); ++i) {
    result.magnitudes_[i] /= norm;
  }
  return result;
}
