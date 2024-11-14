#include"ImguiManager.h"

//init imgui
//add imgui as an observer to the scene class
//whenever the selection changes, inspector refreshes
void ImguiManager::initImgui(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	scene.registerObservers([this]() {
		// You can refresh the inspector panel when selection changes
		createInspectorPanel("Inspector", 1620, 20, 300, 1024);
	});
}

//cleanup imgui once the glfw window is destroyed
void ImguiManager::cleanUp() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

//creating hierarchy panel
void ImguiManager::createHierarchyPanel(const char* title, float x, float y, float width, float height) {
    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(title);

	//show the empty scene text if no object in scene graph
	if (scene.getItemCount() == 0) {
		ImGui::Text("Empty scene");
	}

	//create selectable items for each primitive created
	//use the scene class to fetch all primitives
	//boolean being part of UI has to be defined in this class only instead of the scene class
	for (int i = 0; i < scene.getTriangleCount(); i++) {
		string tempName = "Triangle_" + std::to_string(scene.getTriangleIdByIndex(i));
		triangleSelectBoolean.push_back(false);
		if (ImGui::Selectable(tempName.c_str(), triangleSelectBoolean[i])) {

			//toggle the boolean
			//make sure only one item is selected at a time
			setSelectablesFalse();
			triangleSelectBoolean[i] = !triangleSelectBoolean[i];
			if (triangleSelectBoolean[i]) {
				scene.selectTriangle(scene.getTriangleIdByIndex(i));
			}
		}
	}

	ImGui::End();
}

//inspector panel
void ImguiManager::createInspectorPanel(const char* title, float x, float y, float width, float height) {
    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(title);

	//implement a logic to handle all cases based on the type of active object
	//can be fetced from scene script
    //ImGui::Text("Please select an object to manipulate");

	SceneObjectType selectedtype = scene.getSelectedItemType();
	switch (selectedtype) {
	case SceneObjectType::TRIANGLE: {
		int selectedTriangleId = scene.getSelectedItemIndex();
		string tempHeader = "Triangle ID: " + to_string(selectedTriangleId);
		ImGui::Text(tempHeader.c_str());

		//provide space
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();


		ImGui::Text("VERTEX POSITIONS");
		Triangle* selectedTriangle = scene.getTriangleById(selectedTriangleId);
		//define the UI elements to be shown in inspector for triangle
		//vertex 1, x
		//vertices to modify for triangle
		ImGui::SetNextItemWidth(50.0f);
		//vertex 1,x
		string temp1= "x, vertex 1, " + to_string(selectedTriangle->getVertices(0));
		ImGui::InputText(temp1.c_str(), inputBuffer1, sizeof(inputBuffer1));

		//vertex 1, y
		string temp2 = "y, vertex 1, " + to_string(selectedTriangle->getVertices(1));
		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputText(temp2.c_str(), inputBuffer2, sizeof(inputBuffer2));

		//vertex 1, z
		string temp3 = "z, vertex 1, " + to_string(selectedTriangle->getVertices(2));
		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputText(temp3.c_str(), inputBuffer3, sizeof(inputBuffer3));

		ImGui::Spacing();

		//vertex 2, x
		string temp4 = "x, vertex 2, " + to_string(selectedTriangle->getVertices(15));
		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputText(temp4.c_str(), inputBuffer4, sizeof(inputBuffer4));

		//vertex 2, y
		string temp5 = "y, vertex 2, " + to_string(selectedTriangle->getVertices(16));
		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputText(temp5.c_str(), inputBuffer5, sizeof(inputBuffer5));

		//vertex 2, z
		string temp6 = "z, vertex 2, " + to_string(selectedTriangle->getVertices(17));
		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputText(temp6.c_str(), inputBuffer6, sizeof(inputBuffer6));

		ImGui::Spacing();

		//vertex 3, x
		string temp7 = "x, vertex 3, " + to_string(selectedTriangle->getVertices(30));
		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputText(temp7.c_str(), inputBuffer7, sizeof(inputBuffer7));

		//vertex 3, y
		string temp8 = "y, vertex 3, " + to_string(selectedTriangle->getVertices(31));
		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputText(temp8.c_str(), inputBuffer8, sizeof(inputBuffer8));

		//vertex 3, z
		string temp9 = "z, vertex 3, " + to_string(selectedTriangle->getVertices(17));
		ImGui::SetNextItemWidth(50.0f);
		ImGui::InputText(temp9.c_str(), inputBuffer9, sizeof(inputBuffer9));

		ImGui::Spacing();
		ImGui::Spacing();

		//button to change the vertices
		if (ImGui::Button("Change Triangle Vertex Positions")) {

			//create a vertex array out of input text
			float newVertices[9] = {
			stof(inputBuffer1),
			stof(inputBuffer2),
			stof(inputBuffer3),
			stof(inputBuffer4),
			stof(inputBuffer5),
			stof(inputBuffer6),
			stof(inputBuffer7),
			stof(inputBuffer8),
			stof(inputBuffer9)
			};
			selectedTriangle->updateVertices(newVertices);
		}

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		//drop down for vertex color change
		//A color picker determines vertex color
		ImGui::Text("VERTEX COLORS");
		const char* items[] = { "Vertex 1", "Vertex 2", "Vertex 3"};
		static int current_item = 0;  // Index of the currently selected item

		if (ImGui::Combo("Vertex Color", &current_item, items, IM_ARRAYSIZE(items)))
		{
			// Action when a new item is selected
			// Example: current_item stores the index of the selected item
		}
		//color picker
		static float color[4] = { 0.5f, 0.2f, 0.7f, 1.0f };  // RGBA (Purple color with full opacity)

		// Create a color picker with alpha control
		//handle cases how the color values are updated
		if (ImGui::ColorEdit4("Color Picker with Alpha", color)){
			float newVertex[12] = { 0.0f,0.0f,0.0f,0.0f};

			//depending on which vertex is selected, updated the vertex values
			//based on color picker selected color
			switch (current_item) {
			case 0:
				newVertex[0] = color[0];
				newVertex[1] = color[1];
				newVertex[2] = color[2];
				newVertex[3] = color[3];
				selectedTriangle->updateSingleVertexColor(newVertex,0);
				break;
			case 1:
				newVertex[0] = color[0];
				newVertex[1] = color[1];
				newVertex[2] = color[2];
				newVertex[3] = color[3];
				selectedTriangle->updateSingleVertexColor(newVertex, 1);
				break;
			case 2:
				newVertex[0] = color[0];
				newVertex[1] = color[1];
				newVertex[2] = color[2];
				newVertex[3] = color[3];
				selectedTriangle->updateSingleVertexColor(newVertex, 2);
				break;
			default:
				break;
			}
		}
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		//button to delete the triangle
		if (ImGui::Button("Delete Triangle")) {
			scene.deleteTrinagleById(selectedTriangleId);
		}
		break;
	}
	case SceneObjectType::NONE:
		//cout << "Scene object type not determined" << endl;
	default:
		//cout << "Select a valid shape" << endl;
		break;
	}
	ImGui::End();

}

//menu items on top horizontal panel
void ImguiManager::createMenuItems() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("New")) {
				// Handle "New" action
			}
			if (ImGui::MenuItem("Open")) {
				// Handle "Open" action
			}
			ImGui::Separator(); // Optional separator
			if (ImGui::MenuItem("Exit")) {
				// Handle "Exit" action
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Create")) {
			if (ImGui::MenuItem("2D: Triangle")) {
				unique_ptr<Shapes> triangle = shapeFactory.createShape(PrimitiveShapeTypes::TRIANGLE);	//triangle default constructor			
				scene.addTriangle(std::move(triangle)); //triangle added to scene graph
			}
			if (ImGui::MenuItem("2D: Rectangle")) {
				// Handle "Open" action
			}
			if (ImGui::MenuItem("2D: Polygon")) {
				// Handle "Exit" action
			}
			ImGui::Separator(); // Optional separator
			if (ImGui::MenuItem("3D: Cube")) {
				// Handle "Exit" action
			}
			if (ImGui::MenuItem("3D: Cone")) {
				// Handle "Exit" action
			}
			if (ImGui::MenuItem("3D: Sphere")) {
				// Handle "Exit" action
			}
			if (ImGui::MenuItem("3D: Floor")) {
				// Handle "Exit" action
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Settings")) {
			if (ImGui::MenuItem("Background Color")) {
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("Formation Engine: Feature List")) {
				featureWindow = true;
			}
			if (ImGui::MenuItem("Documentation")) {

			}
			if (ImGui::MenuItem("Credits")) {
				creditsWindow = true;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

//function to create frame and create windows
void ImguiManager::createFrame() {
    // Start a new frame for ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    createInspectorPanel("Inspector", 1620, 20, 300, 1024);
    createHierarchyPanel("Hierrachy", 0, 20, 300, 1024);
	createMenuItems();

	//handle sub menu items rendering
	// feature list
	if (featureWindow) {
		ImGui::SetNextWindowSize(ImVec2(1000, 800)); // Set the window size
		ImGui::SetNextWindowPos(ImVec2(450, 100));  // Set the window position

		// Create the window; the second parameter allows ImGui to close the window correctly
		if (ImGui::Begin("Formation Engine: Feature List", &featureWindow)) {
			ImGui::Text("1. Primitive creation: Triangle, Rectangle, Circle, Cone, Cuboid, Capsule, Cylinder");
			// The default close button in the title bar works with the &creditsWindow parameter
		}
		ImGui::End();
	}

	// documentation
	if (documentationWindow) {
		ImGui::SetNextWindowSize(ImVec2(1000, 800)); // Set the window size
		ImGui::SetNextWindowPos(ImVec2(450, 100));  // Set the window position

		// Create the window; the second parameter allows ImGui to close the window correctly
		if (ImGui::Begin("Credits", &creditsWindow)) {
			ImGui::Text("This is a new window with a close button.");
			// The default close button in the title bar works with the &creditsWindow parameter
		}
		ImGui::End();
	}

	//credits window
	if (creditsWindow) {
		ImGui::SetNextWindowSize(ImVec2(1000, 800)); // Set the window size
		ImGui::SetNextWindowPos(ImVec2(450, 100));  // Set the window position

		// Create the window; the second parameter allows ImGui to close the window correctly
		if (ImGui::Begin("Credits", &creditsWindow)) {
			ImGui::Text("This is a new window with a close button.");
			// The default close button in the title bar works with the &creditsWindow parameter
		}
		ImGui::End();
	}

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//set all selectables to false
//before making a selection
void ImguiManager::setSelectablesFalse() {
	for (int i = 0; i < triangleSelectBoolean.size(); i++) {
		triangleSelectBoolean[i] = false;
	}
}

