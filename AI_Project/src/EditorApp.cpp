#include "EditorApp.h"

namespace fs = std::filesystem;

EditorApp::EditorApp()
  : BaseApp()
{
  m_path = fs::current_path();
}
