#pragma once

#include <memory> // std::unique_ptr
#include <filesystem> // std::filesystem::path
#include "BaseApp.h"

/**
 * Is an editor for manipulating AI agents (Boids)
 */
class EditorApp : public BaseApp
{

 public:
  EditorApp();
  EditorApp(const EditorApp& other) = delete;
  EditorApp(EditorApp&& other) noexcept = delete;
  ~EditorApp() = default;

 private:
  std::filesystem::path m_path;

};

