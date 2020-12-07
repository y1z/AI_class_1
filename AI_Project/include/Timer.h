#pragma once
#include <chrono>
#include <cinttypes>

/*!
 * \author Yhaliff said Barraza Zubia
 * \brief measures time and prints to the screen can also receive the time 
 elapsed in other time measurement.
 **/
class Timer
{
	/*! used for measuring durations in terms of nanoseconds */
	using TimeMeasurementNano = std::chrono::duration<uint64_t, std::nano>;

	//measurement
  using TimeMeasurementSeconds = std::chrono::duration<uint64_t, std::ratio<1,1>>;
  
	/*! this duration has seconds that can have a decimal point
	(just because I get confused with other Representation)*/
	using TimeMeasurementSecondsDouble = std::chrono::duration<double, std::ratio<1, 1>>;

  /*! \returns the measured time in seconds*/
	using TimeMeasurementSecondsFloat = std::chrono::duration<float, std::ratio<1, 1>>;

	/*! making a typedef to be used with the chrono library*/
	using TimePointNanoSeconds = std::chrono::time_point<std::chrono::steady_clock, TimeMeasurementNano>;
public:// constructor
	Timer();
  explicit Timer(const std::chrono::milliseconds& startingTime);
  Timer(const Timer& other) = default;
  Timer(Timer&& other)noexcept = default;

public: // functions 

	uint64_t StartTiming();
	uint64_t EndTiming();

	uint64_t GetResult()const ;
	int64_t GetResultMicroseconds()const;
	int64_t GetResultMilliseconds()const;

	double GetResultSecondsDouble()const;
	float GetResultSecondsFloat()const;

	void PrintResult();
private:

private:// variables
	TimeMeasurementNano m_Result;

	TimePointNanoSeconds m_Start;
	TimePointNanoSeconds m_End;
};

