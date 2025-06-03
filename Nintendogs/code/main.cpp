/**
This application renders a textured mesh that was loaded with Assimp.
*/

#include <iostream>
#include <memory>
#include "glad/glad.h"
#include "Mesh3D.h"
#include "Object3D.h"
#include "AssimpImport.h"
#include "Animator.h"
#include "ShaderProgram.h"
#include "TranslationAnimation.h"
#include "RotationAnimation.h"
#include "PauseAnimation.h"
#include "BezierTranslationAnimation.h"
#include "LoopingRotationAnimation.h"
#include "TiltAnimation.h"
#include <SFML/Audio.hpp>
#include <glm/glm.hpp>


using namespace std;

bool rayIntersectsBoundingBox(const BoundingBox& box, const glm::vec3& rayOrigin, const glm::vec3& rayDirection) {
	// Implement the ray-box intersection using the slab method
	float tMin = (box.min.x - rayOrigin.x) / rayDirection.x;
	float tMax = (box.max.x - rayOrigin.x) / rayDirection.x;
	if (tMin > tMax) std::swap(tMin, tMax);

	float tyMin = (box.min.y - rayOrigin.y) / rayDirection.y;
	float tyMax = (box.max.y - rayOrigin.y) / rayDirection.y;
	if (tyMin > tyMax) std::swap(tyMin, tyMax);

	if ((tMin > tyMax) || (tyMin > tMax)) return false;

	tMin = std::max(tMin, tyMin);
	tMax = std::min(tMax, tyMax);

	float tzMin = (box.min.z - rayOrigin.z) / rayDirection.z;
	float tzMax = (box.max.z - rayOrigin.z) / rayDirection.z;
	if (tzMin > tzMax) std::swap(tzMin, tzMax);

	return !((tMin > tzMax) || (tzMin > tMax));
}

bool rayIntersectsObject(const Object3D& object, const glm::vec3& rayOrigin, const glm::vec3& rayDirection) {
	// Get the bounding box of the object
	BoundingBox box = object.getBoundingBox();
	return rayIntersectsBoundingBox(box, rayOrigin, rayDirection);
}

/**
 * @brief Defines a collection of objects that should be rendered with a specific shader program.
 */
struct Scene {
	ShaderProgram defaultShader;
	std::vector<Object3D> objects;
	std::vector<Animator> animators;
};

/**
 * @brief Constructs a shader program that renders textured meshes in the Phong reflection model.
 * The shaders used here are incomplete; see their source codes.
 * @return
 */
ShaderProgram phongLighting() {
	ShaderProgram program;
	try {
		program.load("C:/Users/reyna/OneDrive/Desktop/NintendoDog/shaders/light_perspective.vert", "C:/Users/reyna/OneDrive/Desktop/NintendoDog/shaders/lighting.frag");
	}
	catch (std::runtime_error& e) {
		std::cout << "ERROR: " << e.what() << std::endl;
		exit(1);
	}
	return program;
}

/**
 * @brief Constructs a shader program that renders textured meshes without lighting.
 */
ShaderProgram textureMapping() {
	ShaderProgram program;
	try {
		program.load("C:/Users/reyna/Downloads/projectBasics/shaders/texture_perspective.vert", "C:/Users/reyna/Downloads/projectBasics/shaders/texturing.frag");
	}
	catch (std::runtime_error& e) {
		std::cout << "ERROR: " << e.what() << std::endl;
		exit(1);
	}
	return program;
}

/**
 * @brief Loads an image from the given path into an OpenGL texture.
 */
Texture loadTexture(const std::filesystem::path& path, const std::string& samplerName = "baseTexture") {
	sf::Image i;
	i.loadFromFile(path.string());
	return Texture::loadImage(i, samplerName);
}



Scene shibaInu() {

	// shiba inu model
	auto shibaInuModel = assimpLoad("C:/Users/reyna/Downloads/3DS/Shiba_Inu/Shiba.obj", true);
	shibaInuModel.grow(glm::vec3(1.15, 1.15, 1.15));
	shibaInuModel.move(glm::vec3(0, -1.75, -4.5));

	// house model
	 auto houseModel = assimpLoad("C:/Users/reyna/Downloads/3DS/Coletta/Coletta/Room.obj", true);
	 houseModel.move(glm::vec3(-4, -3, -20));

	// biscuit model
	auto biscuitModel = assimpLoad("C:/Users/reyna/Downloads/3DS/Bone_Biscuits/bone.obj", false);
	biscuitModel.grow(glm::vec3(1.05, 1.05, 1.05));
	biscuitModel.move(glm::vec3(-2.5, -2.25, -2));
	biscuitModel.rotate(glm::vec3(1, 0, 0));

	// birthday hat model
	auto hatModel = assimpLoad("C:/Users/reyna/Downloads/3DS/PartyHat/Party_Hat/hat.obj", true);
	hatModel.grow(glm::vec3(0.45, 0.45, 0.45));
	hatModel.move(glm::vec3(0, 3.195, 1.6));
	hatModel.rotate(glm::vec3(0.1, 4.5, 0));
	shibaInuModel.addChild(std::move(hatModel));

	// piano object
	auto pianoModel = assimpLoad("C:/Users/reyna/Downloads/3DS/Keyboard/Keyboard/white_piano.obj", true);
	pianoModel.grow(glm::vec3(0.45, 0.45, 0.45));
	pianoModel.rotate(glm::vec3(0, 0, 0)); // -0.7
	pianoModel.move(glm::vec3(2.5, -2.25, -2));

	std::vector<Object3D> objects;
	objects.push_back(std::move(houseModel));
	objects.push_back(std::move(shibaInuModel));
	objects.push_back(std::move(biscuitModel));
	objects.push_back(std::move(pianoModel));


	Animator dogAnimation; 

	/*dogAnimation.addAnimationFactory(
		[&shibaInuModel = objects[0]]() {
			return std::make_unique<LoopingRotationAnimation>(shibaInuModel, 10, glm::vec3(0, 6.26, 0));
		});*/
	dogAnimation.addAnimationFactory(
		[&shibaInuModel = objects[1]]() {
			return std::make_unique<PauseAnimation>(shibaInuModel, 2.0f);
		});

	Animator biscuitAnimation;

	biscuitAnimation.addAnimationFactory(
		[&biscuitModel = objects[2]]() {
			return std::make_unique<PauseAnimation>(biscuitModel, 2.0f);
		});
	
	// biscuitAnimation.setLoop(true);
	
	Animator pianoAnimation;

	pianoAnimation.addAnimationFactory(
		[&pianoModel = objects[3]]() {
			return std::make_unique<PauseAnimation>(pianoModel, 2.0f);
		});


	std::vector<Animator> animators;
	animators.push_back(std::move(dogAnimation));
	animators.push_back(std::move(biscuitAnimation));
	animators.push_back(std::move(pianoAnimation));

	return Scene{
		phongLighting(),
		std::move(objects),
		std::move(animators)
	};

}

//Scene bunny() {
//	auto bunny = assimpLoad("C:/Users/reyna/Downloads/projectBasics/models/bunny_textured.obj", true);
//	bunny.grow(glm::vec3(9, 9, 9));
//	bunny.move(glm::vec3(0.2, -1, 0));
//
//
//	std::vector<Object3D> objects;
//	objects.push_back(std::move(bunny));
//
//	Animator bunnyAnimation;
//
//	// glm::vec3 cp0(-0.5, -1, 0), cp1(1, -3, 0), cp2(1.80, 0.30, 0);
//	//bunnyAnimation.addAnimation(std::make_unique<BezierTranslationAnimation>(objects[0], 10, cp0, cp1, cp2)); // bezier
//	//bunnyAnimation.addAnimation(std::make_unique<PauseAnimation>(objects[0], 5.0f));  // pause 
//	//bunnyAnimation.addAnimation(std::make_unique<RotationAnimation>(objects[0], 10, glm::vec3(0, 6.28, 0)));  // rotate
//
//	// FACTORY
//
//	bunnyAnimation.addAnimationFactory(
//		[&bunny = objects[0]]() {
//			return std::make_unique<BezierTranslationAnimation>(bunny, 10, glm::vec3(-0.5, -1, 0), glm::vec3(1, -3, 0), glm::vec3(1.80, 0.30, 0));
//		});
//
//	bunnyAnimation.addAnimationFactory(
//		[&bunny = objects[0]]() {
//			return std::make_unique<PauseAnimation>(bunny, 5.0f);
//		});
//
//	bunnyAnimation.addAnimationFactory(
//		[&bunny = objects[0]]() {
//			return std::make_unique<RotationAnimation>(bunny, 10, glm::vec3(0, 6.26, 0));
//		});
//
//
//	// The Animators will be destroyed when leaving this function, so we move them into
//	// a list to be returned.
//	std::vector<Animator> animators;
//	animators.push_back(std::move(bunnyAnimation));
//
//	return Scene{
//		textureMapping(),
//		std::move(objects),
//		std::move(animators)
//	};
//}

int main() {
	// Initialize the window and OpenGL
	sf::ContextSettings Settings;
	Settings.depthBits = 24;
	Settings.stencilBits = 8;
	Settings.antialiasingLevel = 2;
	sf::RenderWindow window(sf::VideoMode{ 1200, 800 }, "SFML Demo", sf::Style::Resize | sf::Style::Close, Settings);
	gladLoadGL();
	glEnable(GL_DEPTH_TEST);

	// Initialize the scene
	auto scene = shibaInu();  // Example function to create your scene


	auto& shibaInuModel = scene.objects[1];
	auto& biscuitModel = scene.objects[2];
	auto& pianoModel = scene.objects[3];

	glm::vec3 targetPosition = glm::vec3(2.5f, 3.1f, 0.8f);

	// load the bark sound
	sf::SoundBuffer barkBuffer;
	sf::Sound barkSound;
	if (!barkBuffer.loadFromFile("C:/Users/reyna/Downloads/3DS/happy-puppy-barks.wav")) {
		std::cerr << "Error loading bark sound!" << std::endl;
		return -1;
	}
	barkSound.setBuffer(barkBuffer);

	// load birthday sound
	sf::SoundBuffer birthdayBuffer;
	if (!birthdayBuffer.loadFromFile("C:/Users/reyna/Downloads/3DS/happy-birthday-to-you-bossa-nova-style-arrangement-21399.wav")) {
		std::cerr << "Error loading birthday song!" << std::endl;
		return -1;
	}
	sf::Sound birthdaySound;
	birthdaySound.setBuffer(birthdayBuffer);


	// Set up the camera and perspective
	auto cameraPosition = glm::vec3(0, 0, 5);
	auto camera = glm::lookAt(cameraPosition, glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));
	auto perspective = glm::perspective(glm::radians(45.0), static_cast<double>(window.getSize().x) / window.getSize().y, 0.1, 100.0);

	ShaderProgram& mainShader = scene.defaultShader;

	mainShader.activate();
	mainShader.setUniform("view", camera);
	mainShader.setUniform("projection", perspective);

	
	// Set ambient light properties
	mainShader.setUniform("ambientColor", glm::vec3(0.8f, 0.8f, 0.8f));  // white dim light

	// Set directional light properties
	mainShader.setUniform("directionalLight", glm::normalize(glm::vec3(0.0f, -1.0f, -0.5f)));  // light direction
	mainShader.setUniform("directionalColor", glm::vec3(0.3f, 0.3f, 0.3f));  

	// Set material properties (k_a, k_d, k_s, shininess)
	mainShader.setUniform("material", glm::vec4(1.0f, 1.0f, 1.0f, 2.0f));

	// Pass the camera position for specular calculations
	mainShader.setUniform("viewPos", cameraPosition);
	


	// Start all animators
	for (auto& animator : scene.animators) {
		animator.start();
	}

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);

	bool running = true;
	sf::Clock clock;
	auto last = clock.getElapsedTime();

	/*Animator biscuitAnimator;
	Animator dogAnimator;
	Animator pianoAnimator; */
	Animator biscuitBirthdayAnimator;
	Animator pianoBirthdayAnimator;
	Animator dogBirthdayAnimator;
	Animator biscuitAnimator;
	Animator dogAnimator;


	// animation check boundaries
	float windowWidth = 1200.0f; 
	float windowHeight = 800.0f;

	bool isBiscuitClicked = false;
	bool lightChanged = false;  
	bool bPressed = false;



	// color handler for birthday song
	// the song is 15 seconds long 
	bool startLightColorTransition = false;
	int colorTransitionNum = 0;
	sf::Clock colorClock;
	std::vector<glm::vec3> lightColors = {
	glm::vec3(0.0f, 0.0f, 0.7f),  // Blue
	glm::vec3(0.5f, 0.0f, 0.5f),  // Pink
	glm::vec3(0.0f, 0.3f, 0.0f)   // Purple
	};

	
	while (running) {
		sf::Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				running = false;
			}
			else if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
				// Get the mouse position in window coordinates
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

				// Convert to normalized device coordinates
				float mouseX = (2.0f * mousePosition.x) / window.getSize().x - 1.0f;
				float mouseY = 1.0f - (2.0f * mousePosition.y) / window.getSize().y;
				glm::vec4 rayClip(mouseX, mouseY, -1.0f, 1.0f);

				// Transform to eye coordinates
				glm::vec4 rayEye = glm::inverse(perspective) * rayClip;
				rayEye.z = -1.0f;
				rayEye.w = 0.0f;

				// Convert to world coordinates
				glm::vec3 rayWorld = glm::normalize(glm::vec3(glm::inverse(camera) * rayEye));

				// Check if the ray intersects the bone biscuit (implement ray-object intersection logic)
				if (rayIntersectsObject(biscuitModel, cameraPosition, rayWorld)) {
					isBiscuitClicked = true;
				}
			}

			else if (ev.type == sf::Event::KeyPressed) {
				

				if (ev.key.code == sf::Keyboard::B) {
					// play birthday sound
					birthdaySound.play();
					
					// set flag to true
					startLightColorTransition = true;
					colorTransitionNum = 0;

					bPressed = true;

					colorClock.restart();

				}

			}
		}

		if (isBiscuitClicked && !lightChanged) {
			// change the light color from white to pink
			//mainShader.activate();
			mainShader.setUniform("directionalColor", glm::vec3(0.5f, 0.0f, 0.5f));
			lightChanged = true;  
		}

		if (startLightColorTransition) {
			if (colorClock.getElapsedTime().asSeconds() >= 1.0f) {
				int colorIndex = colorTransitionNum % 3;
				mainShader.activate(); 
				mainShader.setUniform("directionalColor", lightColors[colorIndex]);

				colorTransitionNum++;
				if (colorTransitionNum >= 15) {
					startLightColorTransition = false;
					colorTransitionNum = 0;

				}
				colorClock.restart(); // Reset the clock after updating color
			}
		}

		if (bPressed) {
			// hop animation
			// tilt
			bPressed = false;

			
			//biscuitBirthdayAnimator.tick(clock.getElapsedTime().asSeconds());


			dogBirthdayAnimator.addAnimationFactory([&shibaInuModel]() {
				return std::make_unique<TiltAnimation>(shibaInuModel, 14.0f, 0.02f, 1.0f);
				});

			biscuitBirthdayAnimator.addAnimationFactory([&biscuitModel]() {
					return std::make_unique<TiltAnimation>(biscuitModel, 14.0f, 0.2f, 1.0f);  

				});
			pianoBirthdayAnimator.addAnimationFactory([&pianoModel]() {
				return std::make_unique<TiltAnimation>(pianoModel, 14.0f, 0.2f, 1.0f);

				});

			pianoBirthdayAnimator.start();
			biscuitBirthdayAnimator.start();
			pianoBirthdayAnimator.start();



			
		}


	
		// If the biscuit was clicked, play the bark sound
		if (isBiscuitClicked) {
			biscuitAnimator.tick(clock.getElapsedTime().asSeconds());

			glm::vec3 biscuitFinalPosition(0.0f, 0.0f, 0.0f);
			barkSound.play();

			biscuitAnimator.addAnimationFactory([&biscuitModel, targetPosition]() {
				return std::make_unique<TranslationAnimation>(biscuitModel, 2.0f, targetPosition); 
				});
			biscuitAnimator.addAnimationFactory([&biscuitModel]() {
				return std::make_unique<PauseAnimation>(biscuitModel, 1.0f);
				});
			biscuitAnimator.addAnimationFactory([&biscuitModel]() {
				return std::make_unique<TranslationAnimation>(biscuitModel, 2.0f, glm::vec3(-2.5f, -3.1f, -0.8f));
				});
			dogAnimator.addAnimationFactory([&shibaInuModel, &biscuitFinalPosition]() {
				return std::make_unique<PauseAnimation>(shibaInuModel, 5.0f); 
				});
			dogAnimator.addAnimationFactory([&shibaInuModel]() {
				return std::make_unique<RotationAnimation>(shibaInuModel, 4, glm::vec3(0, 6.26, 0));
			});

			// Start both animators
			biscuitAnimator.start();
			dogAnimator.start();

			isBiscuitClicked = false;  // Reset the click state

			

		}

		// Update the elapsed time and tick each animator
		auto now = clock.getElapsedTime();
		auto diff = now - last;
		auto diffSeconds = diff.asSeconds();
		last = now;

		biscuitBirthdayAnimator.tick(diffSeconds);
		pianoBirthdayAnimator.tick(diffSeconds);
		dogBirthdayAnimator.tick(diffSeconds);
		biscuitAnimator.tick(diffSeconds);
		dogAnimator.tick(diffSeconds);

		for (auto& animator : scene.animators) {
			animator.tick(diffSeconds);
		}

		// Clear the OpenGL context and render each object in the scene
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& o : scene.objects) {
			o.render(window, mainShader);
		}
		window.display();
	}

	return 0;
}


