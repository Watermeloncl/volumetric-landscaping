
### Introduction

![Intro Image; Basic Landscape](/ReadmePictures/image1.png)

This project was part of my master's degree, and shows procedural, volumetric rendering using a form of marching cubes and marching rays. This project follows these steps:
1. Generate a 3D data field based on input parameters; each data point in the field represents a density at that location
2. Run marching cubes to generate triangles and an isosurface using a provided isovalue
3. Run efficient ray tracing against the triangles to generate realistic lighting and shading
4. Texture ray intersection points according to triangle normal and absolute position

### Usage

This project using a simple mingw makefile. Simply run

```mingw32-make```

And then run the project with 

```.\main.exe demo```

"demo" is a parameter source file, found within "DataCenter\DataFiles\Inputs\". The program contains default values for all parameters, as shown in config.h. Any parameter can be changed by specifying within the parameter source file. There is no need to recompile when changing the parameter files, unless the defaults need to be changed.

### Results

This project can work on both small and large landscapes, and both with or without textures. An example of without textures:

![Untextured Image; Basic Landscape](/ReadmePictures/image2.jpg)

Two examples of the same seed but different noise values:

![Medium Landscape, smooth golf course](/ReadmePictures/image3.png)

![Medium Landscape, same as previous but more rugged, forms a mountain](/ReadmePictures/image4.png)

Larger examples:

![Large Landscape 1](/ReadmePictures/image5.jpg)
![Large Landscape 2](/ReadmePictures/image6.jpg)
![Large Landscape 3](/ReadmePictures/image7.jpg)

### Bugs

Currently, there is some memory issue somewhere in ray tracing the isosurface. The program usually does not have an issue; however, it can occasionally, seemingly randomly crash after generating the surface. The larger the isosurface, the more likely it will crash.

### Future Work

Other than bug fixes, this project is largly finished. Future work could be spent cleaning the mesh (no floating triangles), improving random distributions and realism, or on-demand isosurface generation.

Originally, this project intended to include special procedural features: buildings, caves, volcanoes, weathering (including of buildings), etc. These features were scrapped for time constraints. 

###### Written by Devin Frandsen; April 2026