#include "EditorApp.h"
#include <memory>

int main()
{
  std::unique_ptr<BaseApp> app = std::make_unique<EditorApp>();
  return app->run();
}

