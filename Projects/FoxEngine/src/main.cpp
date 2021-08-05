#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Mesh.h"
#include "Square.h"
#include "Cube.h"
#include "CubeMap.h"+
#include "Framebuffer.h"
#include "Renderbuffer.h"

#include "Model.h"
#include "utils.h"

using namespace std;

int main() {
	GLFWwindow* window;
	int width, height;

	// GLFW Initialisierung
	// --------------------
	if (!glfwInit()) {
		cout << "Initalisierung von GLFW3 fehlgeschlagen." << endl;
		return -1;
	}

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.2
	// -------------------------------------------
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	// Window initialization
	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "OpenGL Tutorial", NULL, NULL);
	if (!window) {
		cout << "Erstellung des Fensters fehlgeschlagen." << endl;
		return -1;
	}

	// set callback functions
	// ----------------------
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouseButton_callback);

	// tell GLFW to capture our mouse
	// ------------------------------
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_CURSOR_DISABLED);


	// Initialize OpenGL loader
	// ------------------------
	bool err = glewInit() != GLEW_OK;

	cout << glGetString(GL_VERSION) << endl;

	// background color
	// ----------------
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

	// enable the depth buffer
	// -----------------------
	glEnable(GL_DEPTH_TEST);

	///////////////////////////////////////////////////////////////////////////////
	// Create geometry
	///////////////////////////////////////////////////////////////////////////////

	Cube cube;
	Cube quad;
	Cube lightCube;
	Cube secondQuad;
	Square ground;
	Square postFXSquare;
	CubeMap cubeMap;


	///////////////////////////////////////////////////////////////////////////////
	// Create Frame / Render Buffers
	///////////////////////////////////////////////////////////////////////////////

	Framebuffer fbo(WIN_WIDTH, WIN_HEIGHT);
	fbo.createColorTexture();
	Renderbuffer rbo(WIN_WIDTH, WIN_HEIGHT);
	fbo.attachRenderBuffer(rbo.getID());
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	fbo.Unbind();

	///////////////////////////////////////////////////////////////////////////////
	// Setup Shader
	///////////////////////////////////////////////////////////////////////////////

	Shader simpleMeshShader("../Data/simpleMeshShader.vert", "../Data/simpleMeshShader.frag");
	Shader lightShader("../Data/lightShader.vert", "../Data/lightShader.frag");
	Shader modelShader("../Data/modelShader.vert", "../Data/modelShader.frag");
	Shader simpleMaterialShader("../Data/simpleMaterialShader.vert", "../Data/simpleMaterialShader.frag");
	Shader skyboxShader("../Data/skyboxShader.vert", "../Data/skyboxShader.frag");
	Shader simpleColorShader("../Data/simpleMaterialShader.vert", "../Data/simpleColorShader.frag");
	Shader postFXShader("../Data/postFX.vert", "../Data/postFX.frag");

	///////////////////////////////////////////////////////////////////////////////
	// Setup Textures
	///////////////////////////////////////////////////////////////////////////////

	ground.addTexture("../Data/uvw.png", "");

	///////////////////////////////////////////////////////////////////////////////
	// Setup Materal
	///////////////////////////////////////////////////////////////////////////////

	Material m;
	m.ambient = glm::vec3(0.3f, 0.3f, 0.3f);
	m.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	m.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	m.shininess = 232.0f;

	///////////////////////////////////////////////////////////////////////////////
	// Setup Model
	///////////////////////////////////////////////////////////////////////////////

	unique_ptr<Model> sun = make_unique<Model>("../Data/Models/sun/sun.obj");
	unique_ptr<Model> earth = make_unique<Model>("../Data/Models/earth/earth.obj");
	unique_ptr<Model> moon = make_unique<Model>("../Data/Models/moon/moon.obj");
	unique_ptr<Model> mars = make_unique<Model>("../Data/Models/mars/mars.obj");
	unique_ptr<Model> venus = make_unique<Model>("../Data/Models/venus/venus.obj");
	unique_ptr<Model> mercury = make_unique<Model>("../Data/Models/mercury/mercury.obj");

	///////////////////////////////////////////////////////////////////////////////
	// Setup Dear ImGui context
	///////////////////////////////////////////////////////////////////////////////
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	// ----------------------
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	// --------------------------------
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	glm::vec3 translationA(0, 0, 0);
	glm::vec3 translationB(0, 0, 0);
	glm::vec3 scaleA(1, 1, 1);
	glm::vec4 clear_color = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);

	// initialize light source
	// -----------------------
	shared_ptr<Light> cubeLight = make_unique<Light>();
	cubeLight->type = POINT_LIGHT;
	cubeLight->position = glm::vec3(1.2f, 1.0f, 2.0f);
	cubeLight->constant = 1.0f;
	cubeLight->linear = 0.9f;
	cubeLight->quadratic = 0.032f;

	shared_ptr<Light> sunLight = make_unique<Light>();
	sunLight->type = POINT_LIGHT;
	sunLight->position = glm::vec3(0.0f, 8.0f, 0.0f);
	sunLight->constant = 1.0f;
	sunLight->linear = 0.001f;
	sunLight->quadratic = 0.0001f;

	shared_ptr<Light> globalLight = make_unique<Light>();
	globalLight->type = DIRECTIONAL_LIGHT;
	globalLight->direction = glm::vec3(0.0f, -1.0f, 0.0f);

	// initialize world coordinate system
	// ----------------------------------
	glm::mat4 wcs;

	moon->addLightSource(sunLight);
	earth->addLightSource(sunLight);
	mars->addLightSource(sunLight);
	venus->addLightSource(sunLight);
	mercury->addLightSource(sunLight);

	sun->addLightSource(globalLight);
	moon->addLightSource(globalLight);
	earth->addLightSource(globalLight);
	mars->addLightSource(globalLight);
	venus->addLightSource(globalLight);
	mercury->addLightSource(globalLight);

	cube.addLightSource(cubeLight);
	quad.addLightSource(cubeLight);
	secondQuad.addLightSource(cubeLight);
	ground.addLightSource(cubeLight);
	// main Rendering loop
	// -------------------
	while (!glfwWindowShouldClose(window)) {
		fbo.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		// gets the size of the window in pixels
		glfwGetFramebufferSize(window, &width, &height);
		// Specify the viewport of OpenGL in the Window
		// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
		glViewport(0, 0, width, height);

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0x00);

		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		// -----
		processInput(window);

		// inform the camera about the updated window size
		// -----------------------------------------------
		if (height != 0) 
		{
			camera.updateCameraWindow(width, height);
		}
		

		// initialize imgui frame
		// ----------------------
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		// world coordinate system
		// -----------------------
		wcs = glm::mat4(1.0f);

		cubeLight->position = glm::vec3(1.2f, 1.0f, 2.0f);
		
		// light source
		// ------------
		{	
			// cube transformations
			// --------------------
			cubeLight->position = glm::translate(wcs, translationB) * glm::vec4(cubeLight->position, 1.0);
			lightCube.translate(wcs, cubeLight->position);
			lightCube.scale(lightCube.getModelMatrix(), glm::vec3(0.2f));

			lightCube.setColor(glm::vec3(1.0f));

			// draw the mesh
			// -------------
			lightCube.Draw(lightShader, camera);
		}

		{	
			earth->translate(wcs, glm::vec3(0.0, 0.0f, 0.0f));
			earth->rotate(earth->getModelMatrix(), glm::vec3(0.0f, glfwGetTime() * 25, 0.0f));
			earth->translate(earth->getModelMatrix(), glm::vec3(0.0f, 8.0f, 14.96f));
			
			// draw the mesh
			// -------------
			earth->Draw(simpleMaterialShader, camera);
		}

		{
			moon->translate(earth->getModelMatrix(), glm::vec3(0.0f, 0.0f, 0.0f));
			moon->rotate(moon->getModelMatrix(), glm::vec3(0.0f, glfwGetTime() * 50, 0.0f));
			moon->translate(moon->getModelMatrix(), glm::vec3(0.0f, 0.0f, 2.0f));
			
			// draw the mesh
			// -------------
			moon->Draw(simpleMaterialShader, camera);
		}

		{
			mars->translate(wcs, glm::vec3(0.0f, 0.0f, 0.0f));
			mars->rotate(mars->getModelMatrix(), glm::vec3(0.0f, glfwGetTime() * 50, 0.0f));
			mars->translate(mars->getModelMatrix(), glm::vec3(0.0f, 8.0f, 22.79f));

			// draw the mesh
			// -------------
			mars->Draw(simpleMaterialShader, camera);
		}

		{
			venus->translate(wcs, glm::vec3(0.0f, 0.0f, 0.0f));
			venus->rotate(venus->getModelMatrix(), glm::vec3(0.0f, glfwGetTime() * 50, 0.0f));
			venus->translate(venus->getModelMatrix(), glm::vec3(0.0f, 8.0f, 10.81f));

			// draw the mesh
			// -------------
			venus->Draw(simpleMaterialShader, camera);
		}

		{
			mercury->translate(wcs, glm::vec3(0.0f, 0.0f, 0.0f));
			mercury->rotate(mercury->getModelMatrix(), glm::vec3(0.0f, glfwGetTime() * 50, 0.0f));
			mercury->translate(mercury->getModelMatrix(), glm::vec3(0.0f, 8.0f, 5.79f));

			// draw the mesh
			// -------------
			mercury->Draw(simpleMaterialShader, camera);
		}


		// first cube
		// ----------
		{
			// cube transformations
			// --------------------
			cube.translate(wcs, translationA);
			cube.scale(cube.getModelMatrix(), scaleA);
			cube.translate(cube.getModelMatrix(), glm::vec3(0.0f, 0.5f, 0.0f));
			
			cube.setColor(glm::vec3(clear_color.x, clear_color.y, clear_color.z));;

			cube.setMaterial(m);

			// draw the mesh
			// -------------
			cube.Draw(simpleMaterialShader, camera);
		}

		// first quad
		// -----------
		{	
			// cube transformations
			// --------------------
			quad.translate(wcs, glm::vec3(1.2f, 0.0f, 0.0f));
			quad.rotate(quad.getModelMatrix(), glm::vec3(0.0f, 0.0f, 35.0f));
			quad.scale(quad.getModelMatrix(), glm::vec3(1.0f, 2.0f, 1.0f));
			quad.translate(quad.getModelMatrix(), glm::vec3(0.5f, 0.5f, 0.0f));

			quad.setColor(glm::vec3(0.8f, 0.5f, 0.5f));
			quad.setMaterial(m);

			// draw the mesh
			// -------------
			quad.Draw(simpleMaterialShader, camera);
		}

		// second quad
		// -----------
		{
			// cube transformations
			// --------------------
			secondQuad.translate(wcs, glm::vec3(-0.5f, 0.0f, 0.25f));
			secondQuad.rotate(secondQuad.getModelMatrix(), glm::vec3(0.0f, 0.0f, 90.0f));
			secondQuad.scale(secondQuad.getModelMatrix(), glm::vec3(0.5f, 1.0f, 0.5f));
			secondQuad.translate(secondQuad.getModelMatrix(), glm::vec3(0.5f, 0.5f, 0.0f));

			secondQuad.setColor(glm::vec3(0.5f, 0.8f, 0.8f));
			secondQuad.setMaterial(m);

			// draw the mesh
			// -------------
			secondQuad.Draw(simpleMaterialShader, camera);
		}

		// ground
		// ------
		{
			// ground transformations
			// --------------------
			
			ground.scale(wcs, glm::vec3(20.f));
			ground.rotate(ground.getModelMatrix(), glm::vec3(-90.0f, 0.0f, 0.0f));
			ground.setColor(glm::vec3(1.0f, 1.0f, 1.0f));

			ground.setMaterial(m);
			// draw the mesh
			// -------------
			ground.Draw(simpleMaterialShader, camera);
		}

	

		// imgui
		// -----
		{
			// Create a window called "Hello, world!" and append into it.
			ImGui::Begin("Cube Controll");

			// Edit 3 floats representing a color
			ImGui::ColorEdit3("clear color", (float*)&clear_color); 
			// edit 3 floats to represent translation vector
			ImGui::SliderFloat3("Translation cube", &translationA.x, -1.0f, 1.0f);
			ImGui::SliderFloat3("Translation light", &translationB.x, -15.0f, 15.0f);
			ImGui::SliderFloat3("Scale", &scaleA.x, -15.0f, 15.0f);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Lightpos.X =%.1f // Lightpos.Y =%.1f // Lightpos.Z =%.1f", cubeLight->position.x, cubeLight->position.y, cubeLight->position.z);
			ImGui::End();
		}
		{
			cubeMap.Draw(skyboxShader, camera);
		}

		{
			sun->translate(wcs, glm::vec3(0.0f, 8.0f, 0.0f));
			sun->rotate(sun->getModelMatrix(), glm::vec3(0.0f, glfwGetTime() * 25, 0.0f));
			sun->setColor(glm::vec3(0.9f, 0.6f, 0.0f));
			//sun->scale(sun->getModelMatrix(), glm::vec3(2.0f));
			// draw the mesh
			// -------------

			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
			sun->Draw(simpleMaterialShader, camera);
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);
			//glDisable(GL_DEPTH_TEST);
			sun->scale(sun->getModelMatrix(), glm::vec3(1.03f));
			sun->Draw(simpleColorShader, camera);
			glStencilMask(0xFF);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glEnable(GL_DEPTH_TEST);
		}


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		fbo.Unbind();
		postFXShader.Bind();
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, fbo.getColorTextureID());
		postFXSquare.Draw(postFXShader, camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// cleanup
	// destroy window and release resources
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}