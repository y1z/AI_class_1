#include "TestBoidApp.h"
#include "StateMachineTestApp.h"
#include <memory>

int main()
{
  std::unique_ptr<BaseApp> app = std::make_unique<TestBoidApp>();
  return app->run();
}

