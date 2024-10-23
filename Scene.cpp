#include"Scene.h"

void Scene::addTriangle(std::unique_ptr<Shapes> triangle) {
	triangleList.push_back(std::unique_ptr<Triangle>(static_cast<Triangle*>(triangle.release())));
    itemCount++; //increases the item count by 1
}
//void Scene::addRectangle(std::unique_ptr<Shapes> rectangle) {
//	rectangleList.push_back(std::unique_ptr<Rectangle>(static_cast<Rectangle*>(rectangle.release())));
//}
void Scene::renderAllShapes() {
    for (const auto& triangle : triangleList) {
        triangle->draw();
    }
}

//get triangle count
int Scene::getTriangleCount() {
    return triangleList.size();
}

//get triangle id by index
//fetches value from triangle class
int Scene::getTriangleIdByIndex(int index) {
    return triangleList[index]->getID();
}

//get count of all items
int Scene::getItemCount() {
    return itemCount;
}

//register observers
void Scene::registerObservers(std::function<void()> observer) {
    observers.push_back(observer);
}

//notify observers
void Scene::notifyObservers() {
    for (auto& observer : observers) {
        observer();
    }
}

//select triangle and notify observers
void Scene::selectTriangle(int index) {
    selectedObjectType = SceneObjectType::TRIANGLE;
    selectedObjectID = index;
    notifyObservers();
}

//a parametrized constructor to assign selected type
//Fills the private field of the scene class
//for the selected object type
//for the selected object Id
Scene::Scene(SceneObjectType type, int index) :selectedObjectType(type),selectedObjectID(index){}

//getting triangle by ID
Triangle* Scene::getTriangleById(int id) {
    for (const auto& triangle : triangleList) {
        if (triangle->getID() == id) {
            return triangle.get();  // Return the raw pointer to the triangle
        }
    }
    return nullptr;  // If no triangle is found with the given ID
}

//delete trinagle by ID
void Scene::deleteTrinagleById(int id) {
    //find the item by id in the list and mark it
    //set the selected object to none
    selectedObjectID = 0;
    selectedObjectType = SceneObjectType::NONE;

    auto it = std::remove_if(triangleList.begin(), triangleList.end(), [id](const std::unique_ptr<Triangle>& triangle) {
        return triangle->getID() == id;
        });
    //handle deletion
    if (it != triangleList.end()) {
        triangleList.erase(it,triangleList.end());
        itemCount--;
    }
    else {
        std::cout << "Triangle to be deleted not found" << endl;
    }
}

