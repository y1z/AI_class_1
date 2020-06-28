#pragma once
#include <ostream> // for the '<<' operator overloading

/**
* @brief This class represent a 2d vector that can either be modified
* or return a vector that is the result of the operation applied to
* the current vector.
*/
class Vec2
{
public: // constructors
  Vec2() = default;
  ~Vec2() = default;
  explicit  Vec2(const float  x_, const float  y_ = 0.0f);
  Vec2(Vec2 const& other) = default;
  Vec2(Vec2&& other) noexcept = default;
public:// static constants 

  /**@brief a vector that points up*/
  static const Vec2 upVector2;

  /**@brief a vector that points down*/
  static const Vec2 downVector2;

  /**@brief a vector that points left*/
  static const Vec2 leftVector2;

  /**@brief a vector that points right*/
  static const Vec2 rightVector2;

  /**@brief a vector with the value zero in every component*/
  static const Vec2 zeroVector2;

  /**@brief a vector with the value one in every component*/
  static const Vec2 oneVector2;

  /**@brief a vector with the minimum value for floats in every component*/
  static const Vec2 minVector2;

  /**@brief a vector with the maximum value for floats in every component*/
  static const Vec2 maxVector2;

  /**@brief a vector with the lowest value for floats in every component*/
  static const Vec2 lowestVector2;


public:// operators
  /**
  * @brief The default copy assignment operator.
  * @bug no known bugs.
  * @param[in] other : A vector that going to be copied.
  */
  Vec2&
  operator=(Vec2 const& other) = default;

  /**
  * @brief The default move assignment operator.
  * @bug no known bugs.
  * @param[in] other : A vector that going to be moved.
  */
  Vec2&
  operator=(Vec2&& other) noexcept = default;

  /**
  * @brief the same as the 'add' function.
  * @param[in] other : the other vector that going to be in the sum.
  */
   Vec2
  operator+(Vec2 const& other)const;

  /**
  * @brief the same as the 'addToSelf' function.
  * @param[in] other : the vector that going to be added to the current vector.
  */
  Vec2&
  operator+=(Vec2 const& other);

  /**
  * @brief the same as the 'subtract' function.
  * @param[in] other : the other vector that going to be in the sum.
  */
  Vec2
  operator-(Vec2 const& other)const;

  /**
  * @brief the same as the 'subtractFromSelf' function.
  * @param[in] other : the vector that going to be added to the current vector.
  */
   Vec2&
  operator-=(Vec2 const& other);

  /**
  * @brief The same as the 'mulScalar' function.
  * @bug no known bugs
  * @param[in] The scalar that multiply's the vector.
  */
   Vec2
  operator*(const float  scalar)const;


  /**
  * @brief The same as the 'mulScalar' function.
  * @bug no known bugs
  * @param[in] other : The scalar that multiply's the vector.
  */
   Vec2&
  operator*=(const float  scalar);

  /**
  * @brief The same as the 'dot' function.
  * @bug no known bugs
  * @param[in] other : The scalar that multiply's the vector.
  */
   float
  operator*(Vec2 const& other)const;

  /**
  * @brief Checks if two vectors are similar enough to be considered the same.
  * @returns 'true' if they are similar enough, returns 'false' otherwise.
  * @bug no known bugs.
  * @param[in] other : The vector to be compared.
  */
   bool
  operator==(Vec2 const& other)const;

  /**
  * @brief Checks if two vectors are similar enough to be considered the same.
  * @returns 'false' if they are similar enough, returns 'true' otherwise.
  * @bug no known bugs.
  * @param[in] other : The vector to be compared.
  */
   bool
  operator!=(Vec2 const& other)const;

  /**
  * @brief Compares the magnitude of the vectors.
  * @bug no known bugs.
  * @param[in] other : The vector to be compared.
  */
   bool
  operator<(Vec2 const& other)const;

  /**
  * @brief Compares the magnitude of the vectors.
  * @bug no known bugs.
  * @param[in] other : The vector to be compared.
  */
   bool
  operator>(Vec2 const& other)const;

  /**
  * @brief Prints the values of the vector on to console.
  * @param[in] os : An output stream.
  * @param[in] vector : The vector in question.
  */
  friend std::ostream&
  operator <<(std::ostream& os, Vec2 const& vector);

public:// member functions

  /**
  * @returns the sum of the current vector and the input vector.
  * @bug no known bugs.
  * @param[in] other : the other vector to be added.
  */
  Vec2
  add(Vec2 const& other)const;

  /**
  * @returns the sum of the current vector and the input vector.
  * @param[in] x_ : The x value that going to be added to the vector.
  * @param[in] y_ : The y value that going to be added to the vector.
  * @bug no known bugs.
  */
  Vec2
  add(const float  x_, const float  y_)const;

  /**
  * @brief Adds the input vector to the current one.
  * @bug no known bugs.
  * @param[in] other : the vector that going to be added.
  */
  Vec2&
  addToSelf(Vec2 const& other);

  /**
  * @brief Adds the input vector to the current one.
  * @param[in] x_ : the x value being added to the current vector.
  * @param[in] y_ : the y value being added to the current vector.
  * @bug no known bugs.
  */
  Vec2&
  addToSelf(const float  x_, const float  y_);

  /**
  * @returns The current vector minus the input vector.
  * @param[in] other : The to be subtracted by.
  * @bug no known bugs.
  */
  Vec2
  subtract(Vec2 const& other)const;

  /**
  * @returns The sum of the current vector and the input vector.
  * @param[in] x_ : the x value being added to subtracted from the vector.
  * @param[in] y_ : the y value being added to subtracted from the vector.
  * @bug no known bugs.
  */
  Vec2
  subtract(const float  x_, const float  y_)const;

  /**
  * @brief Adds the input vector to the current one.
  * @param[in] other : The vector thats going to be subtracted from the current one.
  * @bug no known bugs.
  */
  Vec2&
  subtractFromSelf(Vec2 const& other);

  /**
  * @brief Subtracts the input vector from the current one.
  * @param[in] x_ : The x value being subtracted from the current vector.
  * @param[in] y_ : The y value being subtracted from the current vector.
  * @bug no known bugs.
  */
  Vec2&
  subtractFromSelf(const float  x_, const float  y_);

  /**
  * @brief Calculates the dot product.
  * @returns the dot product.
  * @param[in] other : The vector used to get the dot product.
  * @bug no known bugs.
  */
  float
  dot(Vec2 const& other)const;

  /**
  * @brief Create a vector that's the result of multiplying the current vector by a scalar.
  * @returns A vector with it's components multiplied.
  * @param[in] scalar : The value the components are multiplied by.
  * @bug no known bug.
  */
  Vec2
  mulScalar(const float  scalar)const;

  /**
  * @brief Multiply's the components of the vector by a scalar.
  * @returns A vector with it's components multiplied.
  * @param[in] scalar : The value the components are multiplied by.
  * @bug no known bug.
  */
  Vec2&
  mulSelfByScalar(const float  scalar);

  /**
  * @brief Calculates the magnitude of the vector.
  * @returns The magnitude of the vector.
  * @bug no known bugs.
  */
  float
  magnitude()const;

  /**
  * @brief It's the same as 'magnitude' function.
  * @returns The length of the vector.
  * @bug no known bugs.
  */
  float
  length()const;

  /**
  * @brief Calculates the squared magnitude of the vector.
  * @returns The squared magnitude of the vector.
  * @bug no known bugs.
  */
  float
  magnitudeSqr()const;

  /**
  * @brief It's the same as 'magnitudeSqr' function.
  * @returns The squared length of the vector.
  * @bug no known bugs.
  */
  float
  lengthSqr()const;

  /**
  * @brief Calculates the inverse magnitude of the current vector.
  * @returns The inverse magnitude.
  * @bug no known bugs.
  */
  float
  inverseMagnitude() const;

  /**
  * @brief The same as the 'inverseMagnitude' function.
  */
  float
  inverseLength()const;

  /**
  * @brief Calculates a normalized version of the current vector.
  * @returns The current vector normalized.
  * @bug no known bugs.
  */
  Vec2
  normalize()const;

  /**
  * @brief Normalizes the current vector.
  * @returns A reference to the normalized vector.
  * @bug no known bugs.
  */
  Vec2&
  normalizeSelf();

  /**
  * @brief Calculates a rotated version of the current vector.
  * @returns The rotated version of the current vector.
  * @bug no known bugs.
  * @param[in] radians : The Amount of radians to rotate by.
  */
  Vec2
  rotate(const float  radians) const;

  /**
  * @brief Calculates a rotated version of the current vector.
  * @returns The rotated version of the current vector.
  * @bug no known bugs.
  * @param[in] radians : The Amount of radians to rotate by.
  */
  Vec2&
  rotateSelfBy(const float  radians);

  /**
  * @returns The angle of the current vector.
  * @bug no known bugs.
  */
  float
  getAngle()const;

  /**
  * @brief Calculates a vector that's perpendicularly counter clock-wise to the current one.
  * @bug no known bugs.
  */
  Vec2
  perpendicularCounterClockWise()const;


  /**
  * @brief Calculates a vector that's perpendicularly clock-wise to the current one.
  * @bug no known bugs.
  */
  Vec2
  perpendicularClockWise()const;

  /**
  * @brief Applies the Vec2::perpendicularClockWise to the current vector.
  */
  Vec2&
  selfPerpendicularCounterClockWise();

  /**
  * @brief Applies the Vec2::perpendicularClockWise operation to the current vector.
  */
  Vec2&
  selfPerpendicularClockWise();

  /**
  * @brief Calculates the projection of the current vector on to a different vector.
  * @bug no known bugs.
  * @param[in] projectedOn : The vector that's being projected on to.
  */
  Vec2
  projectOnTo(const Vec2& projectedOn)const;


public://variables

  /**
  * @brief Represent the 'x' component of the vector
  */
  float x;

  /**
  * @brief Represent the 'y' component of the vector
  */
  float y;

}; 
