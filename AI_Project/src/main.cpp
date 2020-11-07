#include "TestBoidApp.h"
#include "ExamApp.h"
#include "StateMachineTestApp.h"
#include <memory>

int main()
{
  std::unique_ptr<BaseApp> app = std::make_unique<ExamApp>();
  return app->run();
}

