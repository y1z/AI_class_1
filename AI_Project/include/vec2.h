#pragma once

/**
* @brief This class represent a 2d vector
* @bug
*/
class vec2
{
public: // constructors
  vec2();
  vec2(float const& X, float const& Y);
  vec2(vec2 const& other) = default;
  vec2(vec2&& other) noexcept = default;

public:// operators
  /**
  * @brief The default copy assignment operator.
  * @bug no known bugs.
  * @param[in] other : A vector that going to be copied.
  */
  vec2&
  operator=(vec2 const& other) = default;

  /**
  * @brief The default move assignment operator.
  * @bug no known bugs.
  * @param[in] other : A vector that going to be moved.
  */
  vec2&
  operator=(vec2 && other) noexcept = default;

  /**
  * @brief the same as the 'add' function.
  * @param[in] other : the other vector that going to be in the sum.
  */
  vec2 
  operator+(vec2 const& other)const;

  /**
  * @brief the same as the 'addToSelf' function.
  * @param[in] other : the vector that going to be added to the current vector.
  */
  vec2&
  operator+=(vec2 const& other);

  /**
  * @brief the same as the 'subtract' function.
  * @param[in] other : the other vector that going to be in the sum.
  */
  vec2 
  operator-(vec2 const& other)const;

  /**
  * @brief the same as the 'subtractFromSelf' function.
  * @param[in] other : the vector that going to be added to the current vector.
  */
  vec2&
  operator-=(vec2 const& other);

  /**
  * @brief The same as the 'mulScalar' function.
  * @bug no known bugs
  * @param[in] The scalar that multiply's the vector.
  */
  vec2
  operator*(float const & scalar)const;


  /**
  * @brief The same as the 'mulScalar' function.
  * @bug no known bugs
  * @param[in] other : The scalar that multiply's the vector.
  */
  vec2&
  operator*=(float const& scalar);

  /**
  * @brief The same as the 'dot' function.
  * @bug no known bugs
  * @param[in] other : The scalar that multiply's the vector.
  */
  float
  operator*(vec2 const & other)const;

public:// member functions

  /**
  * @returns the sum of the current vector and the input vector.
  * @bug no known bugs.
  * @param[in] other : the other vector to be added.
  */
  vec2 
  add(vec2 const& other)const;

  /**
  * @returns the sum of the current vector and the input vector.
  * @bug no known bugs.
  * @param[in] other : the other vector to be added.
  */
  vec2 
  add(float const& x, float const& y)const;

  /**
  * @brief Adds the input vector to the current one.
  * @bug no known bugs.
  * @param[in] other : the vector that going to be added.
  */
  vec2&
  addToSelf(vec2 const& other);

  /**
  * @brief Adds the input vector to the current one.
  * @bug no known bugs.
  * @param[in] x : the x value being added to the current vector.
  * @param[in] y : the y value being added to the current vector.
  */
  vec2&
  addToSelf(float const& x, float const& y);

  /**
  * @returns The current vector minus the input vector.
  * @bug no known bugs.
  * @param[in] other : The to be subtracted by.
  */
  vec2 
  subtract(vec2 const& other)const;

  /**
  * @returns The sum of the current vector and the input vector.
  * @bug no known bugs.
  * @param[in] other : the other vector to be added.
  */
  vec2 
  subtract(float const& x, float const& y)const;

  /**
  * @brief Adds the input vector to the current one.
  * @bug no known bugs.
  * @param[in] other : The vector thats going to be subtracted from the current one.
  */
  vec2&
  subtractFromSelf(vec2 const& other);

  /**
  * @brief Subtracts the input vector from the current one.
  * @bug no known bugs.
  * @param[in] x : The x value being subtracted from the current vector.
  * @param[in] y : The y value being subtracted from the current vector.
  */
  vec2&
  subtractFromSelf(float const& x, float const& y);

  /**
  * @brief Calculates the dot product.
  * @returns the dot product.
  * @bug no known bugs.
  * @param[in] other : The vector used to get the dot product.
  */
  float
  dot(vec2 const& other)const;

  /**
  * @brief Create a vector that's the result of multiplying the current vector by a scalar.
  * @returns A vector with it's components multiplied.
  * @bug no known bug.
  * @param[in] scalar : The value the components are multiplied by.
  */
  vec2 
  mulScalar(float const &scalar)const;

  /**
  * @brief Multiply's the components of the vector by a scalar.
  * @returns A vector with it's components multiplied.
  * @bug no known bug.
  * @param[in] scalar : The value the components are multiplied by.
  */
  vec2& 
  mulSelfByScalar(float const &scalar);

  /**
  * @brief Calculates the magnitude of the vector.
  * @returns the magnitude of the vector.
  * @bug no known bugs.
  */
  float 
  magnitude()const;

  /**
  * @brief It's the same as 'magnitude' function.
  * @returns the length of the vector.
  * @bug no known bugs.
  */
  float 
  length()const;


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

