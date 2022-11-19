# miniRT
Project at [1337](https://1337.ma/en/).
A minimal raytracing engine wrote in C and MiniLibX.<br><br>
<img src="https://github.com/Xperaz/minirt/blob/master/img/Screen%20Shot%202022-09-30%20at%209.40.15%20PM.png">
## Index

* [Description](#description)
* [Raytracing](#raytracing)
* [Installation](#installation)
* [Definitions](#definitions)
* [Images](#images)
* [Ressources](#ressources)

## Description
Summary: This project is an introduction to the beautiful world of Raytracing.
the miniRT is my first ray tracer coded in C, normed and humble but
functionnal.

## Raytracing
Ray tracing is a rendering technique that can produce incredibly realistic lighting effects.
Essentially, an algorithm can trace the path of light, 
and then simulate the way that the light interacts with the virtual objects it ultimately hits in the computer-generated world.
<img src="https://developer.nvidia.com/sites/default/files/pictures/2018/RayTracing/ray-tracing-image-1.jpg">

## Installation
The scene must be correctly formatted.<br>
This project is using the ``Minilibx`` using the Metal framework and therefore should work only on macOS 10.13+.<br>
You should follow [this guide](https://github.com/ilkou/minilibx) if you want to compile it on Linux.

1. Clone the repo:
```
https://github.com/Xperaz/minirt.git
```
2. `cd` into it and run `make bonus` to compile it:
```
cd minirt && make bonus
```
3. Now try some tests:
```
./miniRT_bonus ./maps/aladin_room.rt
```

There are some scenes in the `maps` folder that showcase minirt.

## Definitions

Ambient lighting:	`A {ratio} {color}`
* Ambient lighting ratio in range [0.0,1.0].
* R,G,B colors in range [0-255].

Camera:	`C {position} {orientation} {FOV}`
* X,y,z coordinates of the view point.
* A vector with the the x,y,z axis in the range [-1,1].
* Horizontal field of view in degrees in range [0,180].

Light:	`L {position} {ratio} {color}`
* X,y,z coordinates of the light point.
* The light brightness ratio in range [0.0,1.0].
* R,G,B colors in range [0-255].

Sphere:	`sp {position} {diameter} {color}`
* X,y,z coordinates of the sphere center.
* The sphere diameter.
* R,G,B colors in range [0-255].

Plane:	`pl {position} {orientation} {color}`
* X,y,z coordinates.
* A vector with the the x,y,z axis in the range [-1,1].
* R,G,B colors in range [0-255].

Cylinder:	`cy {position} {orientation} {diameter} {height} {color}`
* X,y,z coordinates for the cylinder center.
* A vector with the the x,y,z axis in the range [-1,1].
* The cylinder diameter.
* The cylinder height.
* R,G,B colors in range [0-255].

Cone:	`{position} {orientation} {diameter} {height} {angle} {color}`
* X,y,z coordinates for the cone center.
* A vector with the the x,y,z axis in the range [-1,1].
* The cone diameter.
* The cone height.
* the tangent of half angle of the cone.
* R,G,B colors in range [0-255].

Example maps/columns.rt file:
```
A 0.2      255,255,255

l     -12,7,-10      0.6      255,255,255
l      12,7,-10      0.6      255,255,255
l      0,7,-10      0.6      255,255,255

C     0,5,-14      0,0,1      70

sp      0,1,-1      1.2          125,25,25

cy      -5,0,-2      0,1,0      2.8     20        140,140,140

cy      -5,0,10      0,1,0      2.8     20         140,140,140

cy      5,0,-2      0,1,0      2.8      20         140,140,140

cy      5,0,10      0,1,0      2.8      20        140,140,140

sp      -5,0,10      4.2         140,140,140

sp      5,0,10      4.2                140,140,140

sp      -5,0,-2      4.2         140,140,140

sp      5,0,-2      4.2          140,140,140

sp      -5,10,10      4.2         140,140,140

sp      5,10,10      4.2         140,140,140

sp      -5,10,-2      4.2         140,140,140

sp      5,10,-2      4.2         140,140,140

pl      0,0,0      0,1,0            104,104,104      

pl      0,0,16      0,0,-1           25,25,178      

pl      0,10,0      0,-1,0            128,0,0
```

### Images
<a><img src="https://github.com/Xperaz/minirt/blob/master/img/Screen%20Shot%202022-09-30%20at%209.40.58%20PM.png" alt="scene image" border="0"></a> <br><br>

<a><img src="https://github.com/Xperaz/minirt/blob/master/img/Screen%20Shot%202022-09-30%20at%209.41.54%20PM.png" alt="scene1.rt image" border="0"></a> <br><br>

<a><img src="https://github.com/Xperaz/minirt/blob/master/img/Screen%20Shot%202022-09-30%20at%209.42.41%20PM.png" alt="scene8.rt image" border="0"></a><br><br>

<a><img src="https://github.com/Xperaz/minirt/blob/master/img/Screen%20Shot%202022-09-30%20at%209.44.05%20PM.png" alt="scene2 image" border="0"></a><br><br>

<a><img src="https://github.com/Xperaz/minirt/blob/master/img/Screen%20Shot%202022-09-30%20at%209.46.21%20PM.png" alt="scene2 image" border="0"></a><br><br>

<br><br>
## Ressources
https://www.gabrielgambetta.com/computer-graphics-from-scratch/basic-ray-tracing.html <br>
https://www.youtube.com/watch?v=1HYhrx9bzP8<br>
https://computergraphicsguide.blogspot.com/2015/08/raycasting-and-phong-shading.html<br>
https://www.youtube.com/playlist?list=PLAqGIYgEAxrUO6ODA0pnLkM2UOijerFPv<br>
http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm<br>
https://www.youtube.com/watch?v=gGKup9tUSrU&ab_channel=CemYuksel<br>
https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing<br>
http://raytracerchallenge.com/<br>
https://mrl.nyu.edu/~dzorin/rend05/lecture2.pdf<br>
https://mrl.nyu.edu/~dzorin/rend05/lecture1a.pdf<br>
https://mrl.nyu.edu/~dzorin/rend05/<br>
