#include "TestBoidApp.h"
#include <memory>

int main()
{

auto temp=  Vec2::maxVector2 * 2;
  std::unique_ptr<BaseApp> app = std::make_unique<TestBoidApp>();
  return  app->run();
}

