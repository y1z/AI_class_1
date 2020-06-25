#include "Timer.h"
#include <iostream>
#include <chrono>
#include "Timer.h"



Timer::Timer()
{
  m_Result = std::chrono::seconds(0);
}

Timer::~Timer()
{
}

void Timer::StartTiming()
{
  m_Start = TimePointNanoSeconds::time_point::clock().now();
}

void Timer::EndTiming()
{
  m_End = TimePointNanoSeconds::time_point::clock().now();

  m_Result = (m_End - m_Start);

}

void Timer::PrintResult()
{
  /*! Other Representations of time*/
  TimeMesuermentSeconds ConverstionSeconds;
  TimeMeasurementSecondsDouble ConversionF64Seconds;
  TimeMeasurementSecondsFloat ConversionF32Seconds;


  // converting to respective times 
  ConverstionSeconds = std::chrono::duration_cast<TimeMesuermentSeconds>(m_Result);
  ConversionF64Seconds = std::chrono::duration_cast<TimeMeasurementSecondsDouble>(m_Result);
  ConversionF32Seconds = std::chrono::duration_cast<TimeMeasurementSecondsFloat>(m_Result);

  printf("\n------------(TIMES)--------------\n");
  std::cout << "Seconds = [" << ConverstionSeconds.count() << "] \n ";
  std::cout << "Seconds f32 [" << ConversionF32Seconds.count() << "] \n ";
  std::cout << "Seconds f64 [" << ConversionF64Seconds.count() << "] \n ";
  printf("--------------------------------\n\n");

}

int64_t Timer::GetResult()
{
  return m_Result.count();
}

int64_t Timer::GetResultMicroSeconds()
{
  std::chrono::microseconds ElapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(m_Result);

  return ElapsedTime.count();
}

int64_t Timer::GetResultMiliSeconds()
{
  std::chrono::milliseconds Milisecons = std::chrono::duration_cast<std::chrono::milliseconds>(m_Result);
  return Milisecons.count();
}

double Timer::GetResultSecondsDouble()
{
  TimeMeasurementSecondsDouble ConverstionSeconds = std::chrono::duration_cast<TimeMeasurementSecondsDouble>(m_Result);

  return ConverstionSeconds.count();
}

float Timer::GetResultSecondsFloat()
{
  TimeMeasurementSecondsFloat ConverstionSeconds = std::chrono::duration_cast< TimeMeasurementSecondsFloat>(m_Result);

  return ConverstionSeconds.count();
}

float
Timer::GetTimeInSecondsFloat(int64_t time)
{
  TimeMeasurementSecondsFloat result = std::chrono::seconds(time);
  return  result.count();
}
