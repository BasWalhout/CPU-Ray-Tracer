# CPU-Ray-Tracer

## Table of Contents
**[How to create a workspace/solution](#how-to-create-a-workspacesolution)**<br>
**[UML Class Diagram](#uml-class-diagram)**<br>
**[Project Result](#project-result)**<br>

CPU Ray Tracer is a project made during the second quarter (8 weeks) of the first year of my study.
The project was designed to learn and get experience with the following things:
- UML diagrams
- Fundamental C++ concepts such as:
   * Fundamental types
   * User-defined types
   * Pointers
   * References
   * Functions
   * Scopes
   * Standard Library facilities: Containers & Algorithms
   * C++ Core Guidelines
   * OOP concepts
   * Common programming patterns
- Linear Algebra using vectors and matrices to represent transformations in 3D space
- Unit Testing
- Optimizations such as spatial data structures to speed up ray intersections or parallelization
- Analytic solving of ray/line intersections with different types of geometry

## How to create a workspace/solution
- ### Premake5
   [download page](https://premake.github.io/download)
   Premake is used to generate the workspaces/solutions for different IDEs.
   The original IDE that was used is Visual Studio (2017). 
   There are unit tests included in the project that are implemented using the Microsof Unit Testing Framework for C++.
   These unit tests are contained in a separate project in the solution and will only build if the solution is generated for Visual Studio.

### UML Class Diagram
The diagram that I have made at the start of the project to determine the architecture of the program.
![Class Diagram](/Images/ClassDiagram.jpg "Class Diagram")

## Project Result
The renderer that I implemented during the project, a whitted-style ray tracer, is capable of rendering a static 3D scene from a static viewpoint.
The geometry that is supported are; Spheres, Cuboids, and (Finite) Planes.
Shading is calcualated according to the Blinn-Phong shading model and (perfect) reflection and refraction are also implemented.
I started on the implementation of a Bounding-Volume-Hierarchy spation data structure to be able to optimize the efficiency of ray intersection tests.
However, I was unable to get it working correctly before the deadline of the project.

![Result](/Images/Shading_Fresnell_0.jpg "Result: Fresnell")
![Result](/Images/Shading_Refraction_1.jpg "Result: Refraction")
![Result](/Images/WhittedSceneRecreation.jpg "Result: Whitted Scene Recreation")
![Result](/Images/Intersection_Box_2.jpg "Result: Intersection with Sphere, Plane, and Cuboid")