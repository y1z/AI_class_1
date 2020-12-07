#include "Timer.h"
#include <iostream>


Timer::Timer()
  : m_Result(std::chrono::seconds(0)),
  m_Start( std::chrono::seconds(0)),
  m_End(std::chrono::seconds(0))
{}

Timer::Timer(const std::chrono::milliseconds& startingTime)
  : m_Result(std::chrono::duration_cast< TimeMeasurementNano >(startingTime)),
  m_Start(std::chrono::seconds(0)),
  m_End(std::chrono::seconds(0))
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
  const TimeMeasurementSeconds ConverstionSeconds =
    std::chrono::duration_cast< TimeMeasurementSeconds >(m_Result);

  const TimeMeasurementSecondsDouble ConversionF64Seconds =
    std::chrono::duration_cast< TimeMeasurementSecondsDouble >(m_Result);;

  const TimeMeasurementSecondsFloat ConversionF32Seconds =
    std::chrono::duration_cast< TimeMeasurementSecondsFloat >(m_Result);;

  printf("\n------------(TIMES)--------------\n");
  std::cout << "Seconds = [" << ConverstionSeconds.count() << "] \n ";
  std::cout << "Seconds f32 [" << ConversionF32Seconds.count() << "] \n ";
  std::cout << "Seconds f64 [" << ConversionF64Seconds.count() << "] \n ";
  printf("--------------------------------\n\n");

}

uint64_t Timer::GetResult()const
{
  return m_Result.count();
}

int64_t Timer::GetResultMicroseconds()const
{
  return std::chrono::duration_cast< std::chrono::microseconds >(m_Result).count();
}

int64_t Timer::GetResultMilliseconds()const
{
  return std::chrono::duration_cast< std::chrono::milliseconds >(m_Result).count();
}

double Timer::GetResultSecondsDouble()const
{
  return std::chrono::duration_cast< TimeMeasurementSecondsDouble >(m_Result).count();
}

float Timer::GetResultSecondsFloat()const
{
  return std::chrono::duration_cast< TimeMeasurementSecondsFloat >(m_Result).count();
}
