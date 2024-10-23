//#include"UIWindow.h"
//
////constructor
//UIWindow::UIWindow(const std::string& title) : windowTitle(title) {}
//
////add UI component to the given window
//void UIWindow::addComponent(const std::shared_ptr<UIComponent> component) {
//    windowchildren.push_back(component);
//}
//
////drawing: draws each component in the given window (all leaves)
//void UIWindow::draw(){
//    ImGui::Begin(windowTitle.c_str());
//    for (auto& component : windowchildren) {
//        component->draw();
//    }
//    ImGui::End();
//}
