/*

  == Explanation and rational of testing ==

  We aim to test each function separately. We make assumption on tests written first must be passed
  before preceding to subsequent tests. With one exception on: we assume at is correct when testing
  the constructors.
  We also test the correctness of the output by its dimensionality, its content, as well as the
  exception it throws.
  Test cases are divided as per each function or constructor. Sections are divided as per each
  aspect of the correctness of output, as well as repetitive semantic of test cases but different
  input.

*/

#include "assignments/ev/euclidean_vector.h"

#include <sstream>
#include <utility>

#include "catch.h"

TEST_CASE("Euclidean Vector Constructors Using Dimensionality and Constant") {
  const double constant = 1.0;
  const int numDim = 5;
  EuclideanVector a(numDim, constant);

  SECTION("Euclidean Vector constructed has the right size") {
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("Euclidean Vector contains the right constant") {
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant);
    }
  }
}

TEST_CASE("Euclidean Vector Constructor Using Only Dimensionality") {
  const int numDim = 10;
  EuclideanVector b(numDim);

  SECTION("Euclidean Vector constructed has the right size") {
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("Euclidean Vector contains the right constant 0.0") {
    for (auto i = 0; i < b.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == 0.0);
    }
  }
}

TEST_CASE("Euclidean Vector Constructor Using a STD Vector") {
  std::vector<double> l{1, 2, 3, 5, 6, 7, 8, 11};
  EuclideanVector c{l.begin(), l.end()};
  SECTION("Euclidean Vector constructed has the right size") {
    REQUIRE(c.GetNumDimensions() == l.size());
  }

  SECTION("Euclidean Vector contains the right content aka the vector") {
    int i = 0;
    for (auto it = l.begin(); it != l.end(); ++it) {
      REQUIRE(c.at(i) == *it);
      i++;
    }
  }
}

TEST_CASE("Euclidean Vector Constructor by Copying Another Euclidean Vector") {
  const double constant = 1.0;
  const int numDim = 5;
  EuclideanVector a(numDim, constant);
  EuclideanVector b(a);
  SECTION("Euclidean Vector has the same size as the original euclidean vector") {
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("Euclidean Vector contains the right content aka the vector") {
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == constant);
    }
  }

  SECTION("The Euclidean vector which the constructor is copied from still remains the same") {
    REQUIRE(a.GetNumDimensions() == numDim);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant);
    }
  }
}

TEST_CASE("Euclidean Vector Constructor by Moving Another Euclidean Vector") {
  const double constant = 1.0;
  const int numDim = 5;
  EuclideanVector a(numDim, constant);
  EuclideanVector b = std::move(a);
  SECTION("Euclidean Vector has the same size as the original euclidean vector") {
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("Euclidean Vector contains the right content aka the vector") {
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == constant);
    }
  }

  SECTION("The Euclidean vector which the constructor is moved from is now empty") {
    REQUIRE(a.GetNumDimensions() == 0);
  }
}

TEST_CASE("Test operator overloading '=' by copying") {
  SECTION("TEST CASE 1: Euclidean Vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = a;
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 1: Euclidean Vector b has the right content") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = a;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == constant);
    }
  }

  SECTION("TEST CASE 1: Euclidean Vector b has the right dimension after copying") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = a;
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 1: Euclidean Vector b has the right content after copying") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = a;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant);
    }
  }

  SECTION("TEST CASE 2 Euclidean Vector b has the right dimension") {
    const double constant = 2.0;
    const int numDim = 100;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = a;
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 2 Euclidean Vector b has the right content") {
    const double constant = 2.0;
    const int numDim = 100;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = a;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == constant);
    }
  }

  SECTION("TEST CASE 2 Euclidean Vector b has the right dimension after copying") {
    const double constant = 2.0;
    const int numDim = 100;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = a;
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 2 Euclidean Vector b has the right content after copying") {
    const double constant = 2.0;
    const int numDim = 100;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = a;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant);
    }
  }
}

TEST_CASE("Overloading '=' by moving") {
  SECTION("TEST CASE 1: Euclidean vector b contains the right dimension") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = std::move(a);
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 1: Euclidean Vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = std::move(a);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == constant);
    }
  }

  SECTION("TEST CASE 1: Euclidean Vector a contains nothing") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = std::move(a);
    REQUIRE(a.GetNumDimensions() == 0);
  }

  SECTION("TEST CASE 2: Euclidean vector b contains the right dimension") {
    const double constant = -1.0;
    const int numDim = 10;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = std::move(a);
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 2: Euclidean Vector b contains the right content") {
    const double constant = -1.0;
    const int numDim = 10;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = std::move(a);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == constant);
    }
  }

  SECTION("TEST CASE 2: Euclidean Vector a contains nothing") {
    const double constant = -1.0;
    const int numDim = 10;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = std::move(a);
    REQUIRE(a.GetNumDimensions() == 0);
  }
}

TEST_CASE("Overloading '+='") {
  SECTION("TEST CASE 1 Euclidean vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b += a;
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 1 Euclidean vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b += a;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == 2 * constant);
    }
  }

  SECTION("TEST CASE 1 Euclidean vector a contains still remain the same") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b += a;
    REQUIRE(a.GetNumDimensions() == numDim);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == 1.0);
    }
  }

  SECTION("TEST CASE 2 Exception will be thrown when dimension of lhs does not equal to left hand "
          "side") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector c(numDim - 1, constant);
    REQUIRE_THROWS_WITH(c += a, Catch::Contains("Dimensions of LHS"));
  }

  SECTION("TEST CASE 3 Euclidean vector b has the right dimension") {
    const double constant = -1.0;
    const int numDim = 101;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b += a;
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 3 Euclidean vector b contains the right content") {
    const double constant = -1.0;
    const int numDim = 101;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b += a;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == 2 * constant);
    }
  }

  SECTION("TEST CASE 3 Euclidean vector a contains still remain the same") {
    const double constant = -1.0;
    const int numDim = 101;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b -= a;
    REQUIRE(a.GetNumDimensions() == numDim);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant);
    }
  }
}

TEST_CASE("Overloading '-='") {
  SECTION("TEST CASE 1 Euclidean vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b -= a;
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 1 Euclidean vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b -= a;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == 0.0);
    }
  }

  SECTION("TEST CASE 1 Euclidean vector a contains still remain the same") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b -= a;
    REQUIRE(a.GetNumDimensions() == numDim);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == 1.0);
    }
  }

  SECTION("TEST CASE 2 Exception will be thrown when dimension of lhs does not equal to left hand "
          "side") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector c(numDim - 1, constant);
    REQUIRE_THROWS_WITH(c -= a, Catch::Contains("Dimensions of LHS"));
  }

  SECTION("TEST CASE 3 Euclidean vector b has the right dimension") {
    const double constant = -1.0;
    const int numDim = 101;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b -= a;
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 3 Euclidean vector b contains the right content") {
    const double constant = -1.0;
    const int numDim = 101;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b -= a;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == 0.0);
    }
  }

  SECTION("TEST CASE 3 Euclidean vector a contains still remain the same") {
    const double constant = -1.0;
    const int numDim = 101;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b -= a;
    REQUIRE(a.GetNumDimensions() == numDim);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant);
    }
  }
}

TEST_CASE("Overloading '*='") {
  SECTION("TEST CASE 1 Euclidean vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = 2.0;
    a *= b;
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 1 Euclidean vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = 2.0;
    a *= b;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == b * constant);
    }
  }

  SECTION("TEST CASE 2 Euclidean vector b has the right dimension") {
    const double constant = 37.4;
    const int numDim = 50;
    EuclideanVector a(numDim, constant);
    double b = 7.4;
    a *= b;
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 2 Euclidean vector b contains the right content") {
    const double constant = 37.4;
    const int numDim = 50;
    EuclideanVector a(numDim, constant);
    double b = 7.4;
    a *= b;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == b * constant);
    }
  }
}

TEST_CASE("Overloading '/='") {
  SECTION("TEST CASE 1 Euclidean vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = 2.0;
    a /= b;
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 1 Euclidean vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = 2.0;
    a /= b;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant / b);
    }
  }

  SECTION("TEST CASE 2 Euclidean vector b has the right dimension") {
    const double constant = 37.4;
    const int numDim = 50;
    EuclideanVector a(numDim, constant);
    double b = 7.4;
    a /= b;
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 2 Euclidean vector b contains the right content") {
    const double constant = 37.4;
    const int numDim = 50;
    EuclideanVector a(numDim, constant);
    double b = 7.4;
    a /= b;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant / b);
    }
  }

  SECTION("TEST CASE 2 Exception will be thrown when the divisor is 0") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = 0.0;
    EuclideanVector c(numDim - 1, constant);
    REQUIRE_THROWS_WITH(a /= b, Catch::Contains("Invalid vector division by 0"));
  }
}

TEST_CASE("Overloading '<<'") {
  SECTION("TEST CASE 1 os stream print out the right content") {
    EuclideanVector a(5, 3.0);
    std::ostringstream os;
    os << a;
    REQUIRE(os.str() == "[3 3 3 3 3]");
  }

  SECTION("TEST CASE 2 os stream print out the right content") {
    EuclideanVector a(5, 3.4);
    std::ostringstream os;
    os << a;
    REQUIRE(os.str() == "[3.4 3.4 3.4 3.4 3.4]");
  }

  SECTION("TEST CASE 3 os stream print out the right content") {
    EuclideanVector a(0);
    std::ostringstream os;
    os << a;
    REQUIRE(os.str() == "[]");
  }

  SECTION("TEST CASE 4 os stream print out the right content") {
    std::vector<double> l{1, 2, 3, 5, 6, 7, 8, 11};
    EuclideanVector a{l.begin(), l.end()};
    std::ostringstream os;
    os << a;
    REQUIRE(os.str() == "[1 2 3 5 6 7 8 11]");
  }
}

TEST_CASE("Overloading friend function '+'") {
  SECTION("TEST CASE 1 Euclidean vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b = a + a;
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 1 Euclidean vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b = a + a;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == 2 * constant);
    }
  }

  SECTION("TEST CASE 1 Euclidean vector a contains still remain the same") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b = a + a;
    REQUIRE(a.GetNumDimensions() == numDim);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == 1.0);
    }
  }

  SECTION("TEST CASE 2 Exception will be thrown when dimension of lhs does not equal to left hand "
          "side") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector c(numDim - 1, constant);
    REQUIRE_THROWS_WITH(a + c, Catch::Contains("Dimensions of LHS"));
  }

  SECTION("TEST CASE 3 Euclidean vector b has the right dimension") {
    const double constant = -1.0;
    const double constant_2 = 1.0;
    const int numDim = 101;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(numDim, constant_2);
    EuclideanVector c = a + b;
    REQUIRE(c.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 3 Euclidean vector b contains the right content") {
    const double constant = -1.0;
    const double constant_2 = 1.0;
    const int numDim = 101;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(numDim, constant_2);
    EuclideanVector c = a + b;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(c.at(i) == constant_2 + constant);
    }
  }

  SECTION("TEST CASE 3 Euclidean vector a contains still remain the same") {
    const double constant = -1.0;
    const double constant_2 = 1.0;

    const int numDim = 101;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(numDim, constant_2);
    EuclideanVector c = a + b;
    REQUIRE(a.GetNumDimensions() == numDim);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant);
    }

    REQUIRE(b.GetNumDimensions() == numDim);
    for (auto i = 0; i < b.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == constant_2);
    }
  }
}

TEST_CASE("Overloading friend function '-'") {
  SECTION("TEST CASE 1 Euclidean vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b = a + a;
    REQUIRE(b.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 1 Euclidean vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b = a - a;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == 0.0);
    }
  }

  SECTION("TEST CASE 1 Euclidean vector a contains still remain the same") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(a);
    b = a - a;
    REQUIRE(a.GetNumDimensions() == numDim);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == 1.0);
    }
  }

  SECTION("TEST CASE 2 Exception will be thrown when dimension of lhs does not equal to left hand "
          "side") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector c(numDim - 1, constant);
    REQUIRE_THROWS_WITH(a - c, Catch::Contains("Dimensions of LHS"));
  }

  SECTION("TEST CASE 3 Euclidean vector b has the right dimension") {
    const double constant = -1.0;
    const double constant_2 = 1.0;
    const int numDim = 101;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(numDim, constant_2);
    EuclideanVector c = a - b;
    REQUIRE(c.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 3 Euclidean vector b contains the right content") {
    const double constant = -1.0;
    const double constant_2 = 1.0;
    const int numDim = 101;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(numDim, constant_2);
    EuclideanVector c = a - b;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(c.at(i) == constant - constant_2);
    }
  }

  SECTION("TEST CASE 3 Euclidean vector a contains still remain the same") {
    const double constant = -1.0;
    const double constant_2 = 1.0;

    const int numDim = 101;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(numDim, constant_2);
    EuclideanVector c = a - b;
    REQUIRE(a.GetNumDimensions() == numDim);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant);
    }

    REQUIRE(b.GetNumDimensions() == numDim);
    for (auto i = 0; i < b.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == constant_2);
    }
  }
}

TEST_CASE("Overloading friend function '*': dot product of two vectors") {
  SECTION("TEST CASE 1") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = a * a;
    REQUIRE(b == 5.0);
  }

  SECTION("TEST CASE 2") {
    const double constant = 1.0;
    const int numDim = 6;
    EuclideanVector a(numDim, constant);
    double b = a * a;
    REQUIRE(b == 6.0);
  }

  SECTION("TEST CASE 1 Euclidean vector a still remains the same") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(numDim, constant + 3);
    double c = a * b;
    REQUIRE(c == 20.0);
  }

  SECTION("TEST CASE 2 Exception will be thrown when dimension of lhs does not equal to left hand "
          "side") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector c(numDim - 1, constant);
    REQUIRE_THROWS_WITH(a * c, Catch::Contains("Dimensions of LHS"));
  }
}

TEST_CASE("Overloading friend function '*': scaling the euclidean vector") {
  SECTION("TEST CASE 1 Euclidean vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = 3;
    a = b * a;
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 1 Euclidean vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = 3;
    a = b * a;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == b * constant);
    }
  }

  SECTION("TEST CASE 2 Euclidean vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 100;
    EuclideanVector a(numDim, constant);
    double b = 7.999;
    a = b * a;
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 2 Euclidean vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 100;
    EuclideanVector a(numDim, constant);
    double b = 7.999;
    a = b * a;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant * b);
    }
  }

  SECTION("TEST CASE 3 Euclidean vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = 3;
    a = a * b;
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 3 Euclidean vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = 3;
    a = a * b;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == b * constant);
    }
  }

  SECTION("TEST CASE 4 Euclidean vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 100;
    EuclideanVector a(numDim, constant);
    double b = 7.999;
    a = a * b;
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 4 Euclidean vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 100;
    EuclideanVector a(numDim, constant);
    double b = 7.999;
    a = a * b;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant * b);
    }
  }
}

TEST_CASE("Overloading friend function '/': scaling the euclidean vector") {
  SECTION("TEST CASE 1 Euclidean vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = 3;
    a = a / b;
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 1 Euclidean vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = 3;
    a = a / b;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant / b);
    }
  }

  SECTION("TEST CASE 2 Euclidean vector b has the right dimension") {
    const double constant = 1.0;
    const int numDim = 100;
    EuclideanVector a(numDim, constant);
    double b = 7.999;
    a = a / b;
    REQUIRE(a.GetNumDimensions() == numDim);
  }

  SECTION("TEST CASE 2 Euclidean vector b contains the right content") {
    const double constant = 1.0;
    const int numDim = 100;
    EuclideanVector a(numDim, constant);
    double b = 7.999;
    a = a / b;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant / b);
    }
  }

  SECTION("TEST CASE 3 Exception will be thrown when divisor is zero") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    double b = 0;
    REQUIRE_THROWS_WITH(a / b, Catch::Contains("Invalid vector division by 0"));
  }
}

TEST_CASE("Overloading friend function '==' and '!='") {
  SECTION("TEST CASE 1 Two Equivalent EuclideanVector by copying") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = a;
    bool c = b == a;
    bool d = b != a;
    REQUIRE(c == true);
    REQUIRE(d == false);
  }

  SECTION("TEST CASE 2 Two Equivalent EuclideanVector using a different constructor") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(numDim, constant);
    bool c = b == a;
    bool d = b != a;
    REQUIRE(c == true);
    REQUIRE(d == false);
  }

  SECTION("TEST CASE 3 Two Euclidean vector with different dimensions") {
    const double constant = 1.0;
    const int numDim = 100;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(numDim + 1000, constant);
    bool c = b == a;
    bool d = b != a;
    REQUIRE(d == true);
    REQUIRE(c == false);
  }

  SECTION("TEST CASE 4 Two Euclidean vector with different content") {
    const double constant = 1.0;
    const int numDim = 100;
    EuclideanVector a(numDim, constant);
    EuclideanVector b(numDim, constant + 100.0);
    bool c = b == a;
    bool d = b != a;
    REQUIRE(d == true);
    REQUIRE(c == false);
  }
}

TEST_CASE("Getter and setter method at") {
  SECTION("TEST CASE 1 Testing const at") {
    const double constant = 7.5;
    const int numDim = 90;
    EuclideanVector a(numDim, constant);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant);
    }
  }

  SECTION("TEST CASE 2 Testing const at") {
    const double constant = 7.5;
    const int numDim = 6;
    EuclideanVector a(numDim, constant);
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      REQUIRE(a.at(i) == constant);
    }
  }

  SECTION("TEST CASE 3 Testing non-const at") {
    const double constant = 7.5;
    const int numDim = 90;
    EuclideanVector a(numDim, constant);
    a.at(7) = 1.0;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      if (i == 7) {
        REQUIRE(a.at(7) == 1.0);
      } else {
        REQUIRE(a.at(i) == constant);
      }
    }
  }

  SECTION("TEST CASE 4 Testing non-const at") {
    const double constant = 7.5;
    const int numDim = 6;
    EuclideanVector a(numDim, constant);
    a.at(5) = 1.0;
    for (auto i = 0; i < a.GetNumDimensions(); ++i) {
      if (i == 5) {
        REQUIRE(a.at(5) == 1.0);
      } else {
        REQUIRE(a.at(i) == constant);
      }
    }
  }

  SECTION("TEST CASE 5 Exception will be thrown when index is out of range") {
    const double constant = 1.0;
    const int numDim = 5;
    EuclideanVector a(numDim, constant);
    REQUIRE_THROWS_WITH(a.at(5), Catch::Contains("Index "));
  }
}

TEST_CASE("Getting Euclidean Norm") {
  SECTION("TEST CASE 1 Euclidean norm on a vector with all values being the same") {
    const double constant = 1.0;
    const int numDim = 4;
    EuclideanVector a(numDim, constant);
    REQUIRE(a.GetEuclideanNorm() == 2);
  }

  SECTION("TEST CASE 2 Euclidean norm on a vector with values being the different") {
    std::vector<double> l{1, 2, 3, 1, 1};
    EuclideanVector b{l.begin(), l.end()};
    REQUIRE(b.GetEuclideanNorm() == 4);
  }

  SECTION("Exception will be thrown if euclidean vector's dimension is zero") {
    EuclideanVector b(0);
    REQUIRE_THROWS_WITH(b.GetEuclideanNorm(),
                        Catch::Contains("EuclideanVector with no dimensions does not have a norm"));
  }
}

TEST_CASE("Creating Unit Vector") {
  SECTION("TEST CASE 1 Euclidean Unit Vector on a vector with all values being the same") {
    const double constant = 1.0;
    const int numDim = 4;
    EuclideanVector a(numDim, constant);
    EuclideanVector b = a.CreateUnitVector();
    for (auto i = 0; i < b.GetNumDimensions(); ++i) {
      REQUIRE(b.at(i) == constant / 2);
    }
  }

  SECTION("TEST CASE 2 Euclidean Unit Vector on a vector with values being the different") {
    std::vector<double> l{1, 2, 3, 1, 1};
    EuclideanVector b{l.begin(), l.end()};
    EuclideanVector c = b.CreateUnitVector();
    for (auto i = 0; i < c.GetNumDimensions(); ++i) {
      REQUIRE(c.at(i) == l[i] / 4);
    }
  }

  SECTION("Exception will be thrown if euclidean norm is zero") {
    const double constant = 0;
    const int numDim = 4;
    EuclideanVector a(numDim, constant);
    REQUIRE_THROWS_WITH(
        a.CreateUnitVector(),
        Catch::Contains("EuclideanVector with euclidean normal of 0 does not have a unit vector"));
  }

  SECTION("Exception will be thrown if euclidean vector's dimension is zero") {
    EuclideanVector b(0);
    REQUIRE_THROWS_WITH(
        b.CreateUnitVector(),
        Catch::Contains("EuclideanVector with no dimensions does not have a unit vector"));
  }
}
