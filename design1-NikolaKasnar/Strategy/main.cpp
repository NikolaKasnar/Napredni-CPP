#include "circle.h"
#include "square.h"

#include "OpenGLCircleStrategy.h"
#include "OpenGLSquareStrategy.h"
#include "VulkanCircleStrategy.h"
#include "VulkanSquareStrategy.h"

//#include <GLFW/glfw3.h> // Sluzi za pokretanje prozora u koje se ispisuju likovi

#include <vector>
#include <memory>

#include <iostream>

/* Originalno sam napisao kod da iscrtava likove na ekran pomocu GLWF biblioteke; na kraju sam preuredio kod tako da samo ispise poruku na ekran
sa imenom lika kojeg ispisuje i metotodom koju koristi.*/

int main(){

  // Za ispis likova OpenGL-om
  // Inicijaliziram GLFW
  /*if (!glfwInit()) {
      return -1;
  }*/

  // Napravim likove
  std::vector<Shape*> shapes;
  shapes.push_back(new Circle(30, {0, 0}, OpenGLCircleStrategy{}));
  shapes.push_back(new Square(50, {30, 4}, OpenGLSquareStrategy{}));
  shapes.push_back(new Circle(30, {0, 0}, VulkanCircleStrategy{}));
  shapes.push_back(new Square(100, {30, 0}, VulkanSquareStrategy{}));

  //std::cout << "(Za ispis sljedeceg lika ugasite prozor trenutno ispisanog lika.)" << std::endl;

// Moze se koristiti samo uz GLFW library
  // Glavna petlja za ispis likova
  // Dijelovi implementacije preuzeta za GLFW stranice
  /*for (size_t i = 0; i < shapes.size(); ++i) {
        // Stvorim prozor sa odredenim dimenzijama
        GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Shape", NULL, NULL);
        if (!window) {
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);

        // Uzmem trenutni lik
        Shape* currentShape = shapes[i];

        // Postavim novi prozor
        glfwMakeContextCurrent(window);

        // Uzmem duljinu prozora
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // Postavim viewpoint
        glViewport(0, 0, width, height);

        // Postavim srediste u (0, 0)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, -1, 1);

        // Vratim na modelview
        glMatrixMode(GL_MODELVIEW);

        // Ocistim framebuffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Nacrta trenutni lik
        currentShape->draw();

        // Zamijeni prednji i zadnji buffer
        glfwSwapBuffers(window);

        // Cekam da user zatvori trenutno otvoreni prozor
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }

        // Izbrisem trenutni lik
        delete currentShape;

        // Zatvorim trenutni prozor
        glfwDestroyWindow(window);
    }

  // Terminiram GLFW
  glfwTerminate();*/

    for (size_t i = 0; i < shapes.size(); ++i){
        shapes[i]->draw();
    }

  return 0;
}
