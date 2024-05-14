#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void FlyDron();
void CircuitDron();

// Window dimensions
const GLuint WIDTH = 900, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 3.5f, 100.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active = true;
glm::vec3 spotLightPosicion = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 spotLightDireccion = glm::vec3(0.0f, 0.0f, -1.0f);
//Variable de tiempo para animación de bandera
float tiempo;
//Variables para animación de Macbook
float openMac = 0;
bool activeMac = false;
bool closeMac = false;
//Variables para animación de caraR
float cashRegister = 0;
bool activeCashRegister = false;
bool closeCashRegister = false;
//Variables para animación  de ipad
float rotateIpad = 0.0f;
float translateIpad = 2.3f;
bool showIpad = false;
bool activeRotateIpad = false;
//variables de animación de puerta
bool openDoors = false;
string flagDoor = "open";
float doorLeftValue = 0;
float doorRightValue = 0;
//varaibles dron
bool activeDron = false;
float rotateHeli = 0.0f;
float rotateDron = 0.0f;
float elevateDron = 2.3f;
float desZ = 10.0f;
float desX = -5.5f;
bool r1 = true;
bool r2 = false;
bool r3 = false;
bool r4 = false;
bool r5 = false;
glm::vec3 lightDron = glm::vec3(0);
glm::vec3 lightColorDron;
//variables cafeteria
bool openCafe = false;
float puertaCafeValue = 50.0f;
string flagDoorCafe = "open";


// Positions of the point lights
glm::vec3 pointLightPositions[] = {
glm::vec3(-10.0f,15.2f, 10.0f),
glm::vec3(10.0f,15.2f, 10.0f),
glm::vec3(4.0f,15.2f, 10.0f),
glm::vec3(-4.0f,15.2f, 10.0f),
glm::vec3(-10.0f,15.2f, -10.0f),
glm::vec3(10.0f,15.2f, -10.0f),
glm::vec3(4.0f,15.2f, -10.0f),
glm::vec3(-4.0f,15.2f, -10.0f),
glm::vec3(-10.0f,15.2f, 0.0f),
glm::vec3(10.0f,15.2f, 0.0f),
glm::vec3(4.0f,15.2f, 0.0f),
glm::vec3(-4.0f,15.2f, 0.0f),
glm::vec3(50.0f,9.0f, 50.0f),
glm::vec3(-50.0f,9.0f, 50.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



glm::vec3 Light1 = glm::vec3(0);



glm::vec3 lightColor;



int esferaActual = 1; 
bool bandera = false;
int colorStep = 0;


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Apple Store", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	//Animación bandera
	Shader Ban("Shaders/anim.vs", "Shaders/anim.frag");
	
	//Carga de objetos---------------------------------
	Model Table((char*)"Models/table/table.obj");
	Model Table2((char*)"Models/table2/table2.obj");
	Model Fachada((char*)"Models/fachada/structurev2/structurev2.obj");
	Model FrontGlass((char*)"Models/fachada/frontGlass1/frontGlass1.obj");
	Model BackGlass((char*)"Models/fachada/backGlass/backGlass.obj");
	Model ScreenStore((char*)"Models/screen/screen.obj");
	Model FocoBody((char*)"Models/foco/focoBody.obj");
	Model Bandera((char*)"Models/bandera/bandera/bandera.obj");
	Model DoorRight((char*)"Models/doors/doorRight/doorRight.obj");
	Model DoorLeft((char*)"Models/doors/doorLeft/doorLeft.obj");
	Model Asta((char*)"Models/bandera/asta/asta.obj");
	//Macbook
	Model LaptopTapa((char*)"Models/macbook/pantalla/pantalla.obj");
	Model LaptopTeclado((char*)"Models/macbook/teclado/teclado.obj");
	Model Ipad((char*)"Models/ipad/ipad.obj");
	Model Estante((char*)"Models/estante/estante.obj");
	Model CajaR((char*)"Models/cajaRegistradora/caja1/caja.obj");
	Model Cajon((char*)"Models/cajaRegistradora/cajon/cajon.obj");
	Model Bag((char*)"Models/bag/bag.obj");
	Model Tree((char*)"Models/tree/tree.obj");
	Model DronBody((char*)"Models/dron/body.obj");
	Model Helice((char*)"Models/dron/helices/helice.obj");

	//cafeteria
	
	Model CafeteriaFachada((char*)"Models/cafeteria/fachada/fachada.obj");
	Model CafeCristal((char*)"Models/cafeteria/fachada/cristal/cristal.obj");
	Model CafeDoor((char*)"Models/cafeteria/door/door.obj");
	Model Silla((char*)"Models/cafeteria/chair/chair.obj");
	Model LogoCafe((char*)"Models/cafeteria/logo/logo.obj");
	Model TableCafe((char*)"Models/cafeteria/table/table.obj");
	Model MesaCobro((char*)"Models/cafeteria/mesaCobro/mesaCobro.obj");
	Model Postres((char*)"Models/cafeteria/refri/refri.obj");
	Model CritalRefri((char*)"Models/cafeteria/refri/refriCristal/refriCristal.obj");

	//gameStore
	Model GameStore((char*)"Models/gameStore/gameStore.obj");
	Model GameScreen((char*)"Models/gameStore/screen/screen.obj");
	Model XboxStan((char*)"Models/gameStore/xboxStan/xboxStan.obj");
	Model XboxStanX((char*)"Models/gameStore/xboxStanX/xboxStanX.obj");
	Model XboxStanX2((char*)"Models/gameStore/xboxStanX2/xboxStanX2.obj");

	//exteriores
	Model FloorExterior((char*)"Models/floorExterior/floorExterior.obj");
	Model FloorCenter((char*)"Models/floorCenter/floorCenter.obj");
	Model TreeExterior((char*)"Models/treeExterior/TreeExterior.obj");
	Model Letrero((char*)"Models/letrero/letrero.obj");

	//extras
	Model Store1((char*)"Models/store1/store1.obj");
	Model Store2((char*)"Models/store2/store2.obj");


	


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();


	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		FlyDron();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		
		
		//Load Model
	

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

                  glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
				glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light -- (sol)
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"),0.4f,0.4f,0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"),0.5f, 0.5f, 0.5f);


		// Point light 1 -- (foco)
		lightColor.x= Light1.x;
		lightColor.y = Light1.y;
		lightColor.z= Light1.z;

		lightColorDron.x = lightDron.x;
		lightColorDron.y = lightDron.y;
		lightColorDron.z = lightDron.z;

		
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x,lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x,lightColor.y,lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"),   0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"),0.44f);



		// Point light 2 -- (foco)
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.44f);

		// Point light 3 -- (foco)
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.44f);

		// Point light 4 -- (foco)
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.44f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].position"), pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[4].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[4].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[4].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[4].quadratic"), 0.44f);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[5].position"), pointLightPositions[5].x, pointLightPositions[5].y, pointLightPositions[5].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[5].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[5].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[5].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[5].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[5].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[5].quadratic"), 0.44f);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[6].position"), pointLightPositions[6].x, pointLightPositions[6].y, pointLightPositions[6].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[6].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[6].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[6].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[6].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[6].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[6].quadratic"), 0.44f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[7].position"), pointLightPositions[7].x, pointLightPositions[7].y, pointLightPositions[7].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[7].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[7].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[7].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[7].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[7].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[7].quadratic"), 0.44f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[8].position"), pointLightPositions[8].x, pointLightPositions[8].y, pointLightPositions[8].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[8].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[8].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[8].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[8].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[8].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[8].quadratic"), 0.44f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[9].position"), pointLightPositions[9].x, pointLightPositions[9].y, pointLightPositions[9].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[9].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[9].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[9].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[9].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[9].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[9].quadratic"), 0.44f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[10].position"), pointLightPositions[10].x, pointLightPositions[10].y, pointLightPositions[10].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[10].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[10].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[10].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[10].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[10].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[10].quadratic"), 0.44f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[11].position"), pointLightPositions[11].x, pointLightPositions[11].y, pointLightPositions[11].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[11].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[11].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[11].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[11].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[11].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[11].quadratic"), 0.44f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[12].position"), pointLightPositions[12].x, pointLightPositions[12].y, pointLightPositions[12].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[12].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[12].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[12].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[12].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[12].linear"), 0.35f);		
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[12].quadratic"), 0.44f);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[13].position"), pointLightPositions[13].x, pointLightPositions[13].y, pointLightPositions[13].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[13].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[13].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[13].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[13].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[13].linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[13].quadratic"), 0.44f);

		
		

		// SpotLight -- lampara
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), desX, elevateDron, desZ);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), 0.0f, -1.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), lightDron.x, lightDron.y, lightDron.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), lightDron.x, lightDron.y, lightDron.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), lightDron.x, lightDron.y, lightDron.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.44f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(6.0f)));//dentro
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(22.0f)));//  fuera

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 300.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);

	

        view = camera.GetViewMatrix();	
		//---------------------------------------------------------------------------------
		//------------------------Carga de fachadas----------------------------------------
		//---------------------------------------------------------------------------------
		//Carga de modelo fachada
		model = glm::mat4(1);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.9f, 1.9f, 1.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Fachada.Draw(lightingShader);

		//cafeteria
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(2.9f, 2.5f, 2.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CafeteriaFachada.Draw(lightingShader);

		//gameStore
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(49.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(2.9f, 2.5f, 2.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		GameStore.Draw(lightingShader);

		//---------------------------------------------------------------------------------
		//---------------------Carga de exteriores-----------------------------------------
		//---------------------------------------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.0f));
		model = glm::scale(model, glm::vec3(6.8f, 7.8f, 5.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FloorExterior.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 35.0f));
		model = glm::scale(model, glm::vec3(3.8f, 1.0f, 3.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FloorCenter.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 70.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Letrero.Draw(lightingShader);
		//---------------------------------------------------------------------------------
		//---------------------Tiendas extras----------------------------------------------
		//---------------------------------------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-34.0f, 0.0f, 16.0f));
		model = glm::rotate(model, glm::radians(-225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Store1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(34.0f, 0.0f, 16.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Store2.Draw(lightingShader);

		//arboles---------------------------------------------------------

		//derechos
		
		for (float x = 10.0f; x <= 70.0f; x += 20.0f) { 
			model = glm::mat4(1);
			model = glm::translate(model, glm::vec3(x, 0.0f, -25.0f));
			model = glm::scale(model, glm::vec3(5.8f, 6.8f, 5.8f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			TreeExterior.Draw(lightingShader);
		}
	
		for (float x = -10.0f; x >= -70.0f; x -= 20.0f) { 
			model = glm::mat4(1);
			model = glm::translate(model, glm::vec3(x, 0.0f, -25.0f));
			model = glm::scale(model, glm::vec3(5.8f, 6.8f, 5.8f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			TreeExterior.Draw(lightingShader);
		}

		for (float z = 5.0f; z <= 70.0f; z += 20.0f) { 
			model = glm::mat4(1);
			model = glm::translate(model, glm::vec3(70, 0.0f, z));
			model = glm::scale(model, glm::vec3(5.8f, 6.8f, 5.8f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			TreeExterior.Draw(lightingShader);
		}

		for (float z = 5.0f; z <= 70.0f; z += 20.0f) { 
			model = glm::mat4(1);
			model = glm::translate(model, glm::vec3(-70, 0.0f, z));
			model = glm::scale(model, glm::vec3(5.8f, 6.8f, 5.8f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			TreeExterior.Draw(lightingShader);
		}


		//---------------------------------------------------------------------------------
		//---------------------Carga de objetos Apple store--------------------------------
		//---------------------------------------------------------------------------------
		//pantalla
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 5.5f, -15.5f));
		model = glm::scale(model, glm::vec3(1.8f, 1.8f, 1.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		ScreenStore.Draw(lightingShader);

		
		//cuerpo de foco -----------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-10.0f, 15.0f, 10.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FocoBody.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10.0f, 15.0f, 10.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FocoBody.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.0f, 15.0f, 10.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FocoBody.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-4.0f, 15.0f, 10.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FocoBody.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-10.0f, 15.0f, -10.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FocoBody.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10.0f, 15.0f, -10.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FocoBody.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.0f, 15.0f, -10.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FocoBody.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-4.0f, 15.0f, -10.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FocoBody.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-10.0f, 15.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FocoBody.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10.0f, 15.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FocoBody.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.0f, 15.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FocoBody.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-4.0f, 15.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.8f, 4.8f, 4.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		FocoBody.Draw(lightingShader);

		//Plantas-----------------------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(12.5f, 0.1f, 13.0f));
		model = glm::scale(model, glm::vec3(3.8f, 3.8f, 3.8f));
		model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tree.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-12.5f, 0.1f, 13.0f));
		model = glm::scale(model, glm::vec3(3.8f, 3.8f, 3.8f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tree.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(6.0f, 0.1f, 14.0f));
		model = glm::scale(model, glm::vec3(3.8f, 3.8f, 3.8f));
		model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tree.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-6.0f, 0.1f, 14.0f));
		model = glm::scale(model, glm::vec3(3.8f, 3.8f, 3.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tree.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-12.5f, 0.1f, -13.0f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tree.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(12.5f, 0.1f, -13.0f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tree.Draw(lightingShader);
		

		//mesas--------------------------------------------------------------------
		//mesa de cobro
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -11.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activeTransparecia"), 0);
		Table2.Draw(lightingShader);

		//mesas mostradores
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Table.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Table2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(5.5f, 0.0f, 10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Table2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-5.5f, 0.0f, 10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Table2.Draw(lightingShader);

		//objetos - zona de cobro----------------------------------------------------
		//caja registradora
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, -11.0f));
		model = glm::scale(model, glm::vec3(5.0f, 4.6f, 5.0f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CajaR.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 2.5f, -11.0f));
		model = glm::scale(model, glm::vec3(5.0f, 4.6f, 5.0f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, cashRegister));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cajon.Draw(lightingShader);
		//mac de cobro
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-2.0f, 2.3f, -11.0f));
		model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTapa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-2.0f, 2.3f, -11.0f));
		model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTeclado.Draw(lightingShader);
		//bolsa de compras
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(2.0f, 2.3f, -11.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.6f, 1.0f));
		model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Bag.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.0f, 2.3f, -11.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.6f, 1.3f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Bag.Draw(lightingShader);
		//Ipad
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.0f, translateIpad, -11.0f));
		model = glm::rotate(model, glm::radians(rotateIpad), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ipad.Draw(lightingShader);

		//Asta---------------------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(11.0f, 0.0f, 17.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Asta.Draw(lightingShader);

		//macbook------------------------------------------------------------
		//mac 1
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.5f, 2.3f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTapa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.5f, 2.3f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTeclado.Draw(lightingShader);
		//mac 2
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.5f, 2.3f, 2.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		model = glm::rotate(model, glm::radians(openMac), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTapa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.5f, 2.3f, 2.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTeclado.Draw(lightingShader);
		//mac 3
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.5f, 2.3f, -2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTapa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.5f, 2.3f, -2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTeclado.Draw(lightingShader);
		//mac 4
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.5f, 2.3f, -2.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTapa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.5f, 2.3f, -2.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTeclado.Draw(lightingShader);
		//mac5
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.5f, 2.3f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTapa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.5f, 2.3f, 0.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTeclado.Draw(lightingShader);
		//mac6
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.5f, 2.3f, 2.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTapa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.5f, 2.3f, 2.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTeclado.Draw(lightingShader);

		//Ipad----------------------------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-4.0f, 2.3f, -2.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ipad.Draw(lightingShader);
		//ipad2
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-4.0f, 2.3f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ipad.Draw(lightingShader);
		//ipad3
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-4.0f, 2.3f, 2.0f));
		model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ipad.Draw(lightingShader);


		//mesa horizontal iphones ---------------------------------------------------
	
		
		//---------dron------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(desX, elevateDron, desZ));
		model = glm::rotate(model, glm::radians(rotateDron), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.9f, 1.9f, 1.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DronBody.Draw(lightingShader);

		//--------helices----------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(desX, elevateDron, desZ));
		model = glm::rotate(model, glm::radians(rotateHeli), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.9f, 1.9f, 1.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Helice.Draw(lightingShader);

		
		
		//ipad5
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-7.5f, 2.3f, 11.0f));
		model = glm::scale(model, glm::vec3(0.46f, 0.6f, 0.4f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ipad.Draw(lightingShader);
		//ipad6
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-3.5f, 2.3f, 11.0f));
		model = glm::scale(model, glm::vec3(0.66f, 0.8f, 0.4f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ipad.Draw(lightingShader);
		////ipad7
	
		//ipad8
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-7.5f, 2.3f, 9.3f));
		model = glm::scale(model, glm::vec3(0.46f, 0.6f, 0.4f));
		model = glm::rotate(model, glm::radians(210.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ipad.Draw(lightingShader);

		//ipad9
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-3.5f, 2.3f, 9.3f));
		model = glm::scale(model, glm::vec3(0.66f, 0.8f, 0.4f));
		model = glm::rotate(model, glm::radians(210.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ipad.Draw(lightingShader);

		//mesa horizontal derecha -------------------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.5f, 2.3f, 10.0f));
		model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
		model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ipad.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(5.5f, 2.3f, 10.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Bag.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.5f, 2.3f, 10.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, glm::radians(-130.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTapa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.5f, 2.3f, 10.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, glm::radians(-130.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTeclado.Draw(lightingShader);

		//estante derecho-------------------------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(13.9f, 2.0f, 4.8f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 2.6f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Estante.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(13.9f, 2.0f, -4.8f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 2.6f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Estante.Draw(lightingShader);

		//estante izquierdo
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-13.35f, 2.0f, 4.8f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 2.6f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Estante.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-13.35f, 2.0f, -4.8f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 2.6f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Estante.Draw(lightingShader);

		//---------------------------------------------------------------------------------
		//---------------------Carga de objetos game store---------------------------------
		//---------------------------------------------------------------------------------

		//screens
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(58.2f, 7.0f, 42.65f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		GameScreen.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(58.2f, 7.0f, 57.65f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		GameScreen.Draw(lightingShader);

		//mesa de cobro -------------------------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(57.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(1.2f, 1.3f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Table2.Draw(lightingShader);

		// stan de juegos

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(52.0f, 0.0f, 43.0f));
		model = glm::scale(model, glm::vec3(3.2f, 3.3f, 3.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		XboxStan.Draw(lightingShader);

			model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(46.3f, 0.0f, 56.0f));
		model = glm::scale(model, glm::vec3(3.2f, 3.3f, 3.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		XboxStanX.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(52.0f, 0.0f, 56.0f));
		model = glm::scale(model, glm::vec3(3.2f, 3.3f, 3.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		XboxStan.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(46.3f, 0.0f, 43.0f));
		model = glm::scale(model, glm::vec3(3.2f, 3.3f, 3.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		XboxStanX2.Draw(lightingShader);

		//---------------------------------------------------------------------------------
		//---------------------Carga de objetos Cafeteria----------------------------------
		//---------------------------------------------------------------------------------

		//mesa lateral--------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-51.5f, 0.0f, 36.65f));
		model = glm::scale(model, glm::vec3(2.0f, 1.3f, 1.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Table.Draw(lightingShader);
		//Decoracion---------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-73.0f, -4.5f, 25.65f));
		model = glm::scale(model, glm::vec3(2.9f, 2.9f, 2.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LogoCafe.Draw(lightingShader);

		//sillas-------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-47.5f, 0.0f, 38.80f));
		model = glm::scale(model, glm::vec3(3.5f, 3.8f, 3.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-50.5f, 0.0f, 38.80f));
		model = glm::scale(model, glm::vec3(3.5f, 3.8f, 3.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-53.6f, 0.0f, 38.80f));
		model = glm::scale(model, glm::vec3(3.5f, 3.8f, 3.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-56.6f, 0.0f, 38.80f));
		model = glm::scale(model, glm::vec3(3.5f, 3.8f, 3.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla.Draw(lightingShader);

		//mesa de cobro -----------------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-57.0f, 0.0f, 57.80f));
		model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MesaCobro.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-57.0f, 4.0f, 53.80f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTapa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-57.0f, 4.0f, 53.80f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTeclado.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-57.0f, 4.2f, 55.80f));
		model = glm::scale(model, glm::vec3(5.0f, 4.6f, 5.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CajaR.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-57.0f, 4.2f, 55.80f));
		model = glm::scale(model, glm::vec3(5.0f, 4.6f, 5.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, cashRegister));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cajon.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-57.0f, 3.0f, 57.80f));
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 4.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Postres.Draw(lightingShader);

	

		//mesas pequeñas y sillas---------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-47.0f, 0.0f, 56.80f));
		model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		TableCafe.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-47.9f, 2.9f, 56.80f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTapa.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-47.9f, 2.9f, 56.80f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LaptopTeclado.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-44.6f, 0.0f, 56.80f));
		model = glm::scale(model, glm::vec3(3.5f, 3.8f, 3.5f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-49.0f, 0.0f, 56.80f));
		model = glm::scale(model, glm::vec3(3.5f, 3.8f, 3.5f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-47.0f, 0.0f, 62.00f));
		model = glm::scale(model, glm::vec3(3.0f, 4.0f, 3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		TableCafe.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-44.6f, 0.0f, 62.00f));
		model = glm::scale(model, glm::vec3(3.5f, 3.8f, 3.5f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-49.0f, 0.0f, 62.00f));
		model = glm::scale(model, glm::vec3(3.5f, 3.8f, 3.5f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla.Draw(lightingShader);


		//planta-------------------------------------------------
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-42.0f, 0.1f, 36.65f));
		model = glm::scale(model, glm::vec3(3.8f, 3.8f, 3.8f));
		model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tree.Draw(lightingShader);

		//---------------------------------------------------------------------------------
		//------------------------Carga de cristales---------------------------------------
		//---------------------------------------------------------------------------------
		
		//fachada cristal - aplicación de transparencias -----------------------------------
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.9f, 1.9f, 1.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activeTransparecia"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.35);
		FrontGlass.Draw(lightingShader);
		glDisable(GL_BLEND);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.9f, 1.9f, 1.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activeTransparecia"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.35);
		BackGlass.Draw(lightingShader);
		glDisable(GL_BLEND);

		//puertas------------------------------------------------------------------------------------

		

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-57.0f, 1.0f, 57.80f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 4.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activeTransparecia"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.20);
		CritalRefri.Draw(lightingShader);
		glDisable(GL_BLEND);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(2.9f, 2.5f, 2.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activeTransparecia"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.45);
		CafeCristal.Draw(lightingShader);
		glDisable(GL_BLEND);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-50.15f, 0.0f, puertaCafeValue));
		model = glm::scale(model, glm::vec3(2.9f, 2.5f, 2.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activeTransparecia"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.40);
		CafeDoor.Draw(lightingShader);
		glDisable(GL_BLEND);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(doorLeftValue, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.9f, 1.9f, 1.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activeTransparecia"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.70);
		DoorLeft.Draw(lightingShader);
		glDisable(GL_BLEND);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(doorRightValue, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.9f, 1.9f, 1.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activeTransparecia"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.70);
		DoorRight.Draw(lightingShader);
		glDisable(GL_BLEND);
			
		glBindVertexArray(0);

		//Bandera - animación ---------------------------------------------------------------------
		Ban.Use();

		float tiempo = glfwGetTime(); 
		GLint timeLoc = glGetUniformLocation(Ban.Program, "time");
		glUniform1f(timeLoc, tiempo);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10.97f, 0.0f, 17.0f));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Bandera.Draw(Ban);


		glBindVertexArray(0);
	

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}



	if (active)
	{
		Light1 = glm::vec3(1.0f, 1.0f, 1.0f);
	}


	//animaciones
	if (activeMac)
	{
		if (openMac >= -91 && closeMac == false) {
			openMac = openMac - 1.0f;
			if (openMac == -91) {
				activeMac = false;
				closeMac = true;
			}
		}

		if ( openMac < 0 && closeMac == true) {
			openMac = openMac + 1.0f;
			if (openMac == 0) {
				activeMac = false;
				closeMac = false;
			}
		}
	}
	
	if (activeCashRegister)
	{
		if (!closeCashRegister && cashRegister < 0.2)
		{
			cashRegister += 0.01f;
			if (abs(cashRegister - 0.2) < 0.01) {
				cashRegister = 0.2f; 
				activeCashRegister = false; 
				closeCashRegister = true;
			}
		}
		else if (closeCashRegister && cashRegister > 0)
		{
			cashRegister -= 0.01f;
			if (abs(cashRegister) < 0.01) {
				cashRegister = 0.0f; 
				activeCashRegister = false;
				closeCashRegister = false;
			}
		}
	}
	
	if (showIpad)
	{
		if (translateIpad < 4 && activeRotateIpad == false)
		{
			translateIpad += 0.1f;
			if (abs(translateIpad - 4.1f) < 0.01f)
			{
				activeRotateIpad = true;
			}

		}

		if (activeRotateIpad)
		{
			if (rotateIpad < 360) {
				rotateIpad += 1.0f;
			
			}
			else {
				if (translateIpad > 2.3)
				{
					translateIpad -= 0.1f;
				}
				else {
					rotateIpad = 0.0f;
					activeRotateIpad = false;
					showIpad = false;
				}
			}
		}
	}

	if (openDoors) {
		if (flagDoor == "open") {
			if (doorLeftValue > -3) {
				doorLeftValue -= 0.01f;
			}
			if (doorRightValue < 3) {
				doorRightValue += 0.01f;
			}

			if (doorLeftValue <= -3 && doorRightValue >= 3) {
				flagDoor = "close"; 
				openDoors = false; 
			}
		}
		else if (flagDoor == "close") {
			if (doorLeftValue < 0) {
				doorLeftValue += 0.01f;
			}

			if (doorRightValue > 0) {
				doorRightValue -= 0.01f;
			}

			if (doorLeftValue >= 0 && doorRightValue <= 0) {
				flagDoor = "open";
				openDoors = false;
			}
		}

	}

	if (openCafe)
	{
		if (flagDoorCafe == "open")
		{
			puertaCafeValue -= 0.1f;
			if (puertaCafeValue <= 46.0f)
			{
				flagDoorCafe = "close";
				openCafe = false;  
			}
		}
		else if (flagDoorCafe == "close")
		{
			puertaCafeValue += 0.1f;
			if (puertaCafeValue >= 50.0f)
			{
				flagDoorCafe = "open";
				openCafe = false;  
			}
		}
	}

	

	
}

void FlyDron()
{
	if (activeDron)
	{
		lightDron = glm::vec3(0.0f, 1.0f, 1.0f);
		rotateHeli += 10.0f;
		if (elevateDron < 5)
		{
			elevateDron += 0.01f;
			if (rotateDron > -90)
			{
				rotateDron -= 1.0f;
			}
		}
		if (elevateDron >= 5)
		{
			CircuitDron();

		}
	}

	if (activeDron == false && elevateDron > 2.3f)
	{
		lightDron = glm::vec3(1.0f, 0.0f, 0.0f);
		if (elevateDron > 2.3)
		{
			rotateHeli += 10.0f;
			elevateDron -= 0.01f;
		}
		if (elevateDron == 2.3f) {
			rotateHeli = 0.0f;
			lightDron = glm::vec3(0.0f, 0.0f, 0.0f);
		}
	}



}


void CircuitDron()
{
	if (r1)
	{
		desX += 0.02f;
		if (desX > 5.5f)
		{
			r1 = false;
			r2 = true;
		}
	}

	if (r2)
	{
		desZ -= 0.02f;
		if(desZ < -11.0f )
		{
			r2 = false;
			r3 = true;
		}
		if (rotateDron < 0)
		{
			rotateDron += 1.0f;
		}
	}

	if (r3)
	{
		desX -= 0.02f;
		if (desX < -5.5f)
		{
			r3 = false;
			r4 = true;
		}
		if (rotateDron < 90)
		{
			rotateDron += 1.0f;
		}
	}

	if (r4)
	{
		desZ += 0.02f;
		if (desZ > 11.0f)
		{
			r4 = false;
			r5 = true;
		}
		if (rotateDron < 180)
		{
			rotateDron += 1.0f;
		}
	}

	if (r5)
	{
		r5 = false;
		r1 = true;
		rotateDron = -90.0f;
	
	}
}


// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_M])
	{
		activeMac = !activeMac;
	}
	if (keys[GLFW_KEY_C]) {
		activeCashRegister = !activeCashRegister;
	}
	if (keys[GLFW_KEY_V]) {
		showIpad = !showIpad;
	}
	if (keys[GLFW_KEY_SPACE]) {
		openDoors = !openDoors;
	}
	if (keys[GLFW_KEY_F]) {
		activeDron = !activeDron;
	}

	if (keys[GLFW_KEY_R]) {
		openCafe = !openCafe;
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}