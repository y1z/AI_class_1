#include <cassert>

#include "UIStateWaiting.h"



UI_STATE_NAME::E
UIStateWaiting::onUpdate(UIStateData& sceneData) {
  assert(nullptr != ptr_scenes);
  std::vector<UIRectangle>& UISceneElements = ptr_scenes->at(sceneIndex).m_desc.rectangles;
  UISceneDesc& scene = ptr_scenes->at(sceneIndex).m_desc;
  size_t i = 0;
  for (const auto& elem : UISceneElements) {

    const bool isIsideUI = elem.isInsideRect(sceneData.mousePosition);
    if (isIsideUI && sf::Mouse::Left == sceneData.mouseAccion) {
      sceneData.lastSceneID = sceneIndex;

      executeCallBack(i, scene);
      sceneIndex = scene.associatedScenes.at(i);

      return UI_STATE_NAME::E::kCHANGING;
    }

    ++i;
  }

  return UI_STATE_NAME::E::kWAITING;
}


std::optional<int>
UIStateWaiting::executeCallBack(int32 callbackIndex, const UISceneDesc& scene)
{
  UISceneDesc::UICallbackFunction callBack = scene.callbackFunctions.at(callbackIndex);

  auto callIndex = callBack.index();
  if (auto call = std::get_if<std::function<void(void)>>(&callBack)) {
    (*call)();
    return std::nullopt;
  }
  else if (auto call = std::get_if < UISceneDesc::AppFuncReturnFilePath >(&callBack)) {
    (*call)(editor);
    return std::nullopt;
  }
  else if (auto call = std::get_if<UISceneDesc::AppFuncReturnInt>(&callBack)) {
    return (*call)(editor);
  }
  else if(auto call = std::get_if<std::function<int(void)>>(&callBack))
  {
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
