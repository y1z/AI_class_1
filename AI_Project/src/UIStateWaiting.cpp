#include <cassert>
#include "UIStateWaiting.h"
#include "util.h"


constexpr static float s_inputDelay = static_cast<float>(1) / 5.0f;



UI_STATE_NAME::E
UIStateWaiting::onUpdate(UIStateData& sceneData) {
  assert(nullptr != ptr_scenes);

  std::vector<UIRectangle>& UISceneElements = ptr_scenes->at(sceneIndex).m_desc.rectangles;
  UISceneDesc& scene = ptr_scenes->at(sceneIndex).m_desc;
  m_timeSinceInput += sceneData.deltaTime;

  const MouseData& data = sceneData.mouseData;
  const auto requiredMouseAccion = (MOUSE_ACCION::kPressing | MOUSE_ACCION::kLeftButton);

  size_t i = 0;
  for (const auto& elem : UISceneElements) {

    const bool canAcceptInput = (m_timeSinceInput > s_inputDelay) &&
                                elem.isInsideRect(util::vec2ToVector2f(data.m_mousePosition)) &&
                                requiredMouseAccion == data.m_mouseAccion;
    if (canAcceptInput) {
      sceneData.lastSceneID = sceneIndex;

      executeCallBack(i, scene);
      sceneIndex = scene.associatedScenes.at(i);
      m_timeSinceInput = 0.0f;

      return UI_STATE_NAME::kCHANGING;
    }

    ++i;
  }
  return UI_STATE_NAME::kWAITING;
}


std::optional<int>
UIStateWaiting::executeCallBack(int32 callbackIndex, const UISceneDesc& scene) {
  UISceneDesc::UICallbackFunction callBack = scene.callbackFunctions.at(callbackIndex);

  auto callIndex = callBack.index();
  if (const auto call = std::get_if<std::function<void(void)>>(&callBack)) {
    (*call)();
    return std::nullopt;
  }

  if (const auto call = std::get_if < UISceneDesc::AppFuncReturnFilePath >(&callBack)) {
    (*call)(editor);
    return std::nullopt;
  }
  if (const auto call = std::get_if<UISceneDesc::AppFuncReturnInt>(&callBack)) {
    return (*call)(editor);
  }
  if (const auto call = std::get_if<std::function<int(void)>>(&callBack)) {
    return (*call)();
  }

  return std::nullopt;
}


UI_STATE_NAME::E
UIStateWaiting::onExit(UIStateData& sceneData) {
  //UISceneDesc& scene = ptr_scenes->at(sceneIndex).m_desc;


  return UI_STATE_NAME::E::kCHANGING;
}

UI_STATE_NAME::E
UIStateWaiting::getCurrentState() const {
  return UI_STATE_NAME::E::kWAITING;
}
