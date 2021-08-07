# README #

Semester long assignment for COMP371 at Concordia University

## General structure ##

* `doc` is for documentation, report, etc. Create a dir for your team there, e.g., `teamX`, and initialize the report document there.

### Requirements ###

* CMake 3.17+
* VCPKG
* OpenGL
* 64-bit Libraries
    - GLFW
    - GLEW
    - GLM

### How do I get set up? ###

1. Download and Install [VCPKG](https://github.com/Microsoft/vcpkg)
2. Install the libraries from VCPKG using commandline argument "--triplet x64-windows" for 64-bit libraries on windows; "--help" to find equivalent for other OS
3. Set the CMake toolchain file for your IDE to ".../vcpkg-master/scripts/buildsystems/vcpkg.cmake"
4. Generate CMake cache
5. Build

### Controls ###

- `WASD` will move the camera relative to the direction you are looking at.
- `Left Shift` will make you move faster.
- `Space` will move you vertically up along the `y-axis`.
- `Left Control` will move you down along the `y-axis`.
- `Arrow Key Up` & `Arrow Key Down` will rotate the world around `y-axis`.
- `Arrow Key Left` & `Arrow Key Right` will rotate the world around `x-axis`.
- `Home` will reset all world and camera transformations.
- `Left Mouse Button` will make all vertical mouse movements a zoom in/out of the scene.
- `Z` will reset the zoom to its default value.
- `1 to 5` will select a model on the map. Default is `0`, which is the model at the center.
	- `I` will scale the model up by 5% of its current size.
	- `K` will scale the model down by 5% of its current size.
	- `Y` will move the model along `x`.
	- `H` will move the model along `-x`.
	- `G` will move the model along `z`.
	- `J` will move the model along `-z`.
	- `F` will move the model along `y`.
	- `V` will move the model along `-y`.
	- `B` & `N` will rotate the model on its `y` by 0.5 degrees.
	- `R` to randomly position the model on the grid
	- `,` and `.` to shear the model continuously
	- `;` and `'` to shear the model by an increment of 0.1 units
- `Mouse Button 4` will make mouse movements move the camera only along its `x-axis` and `y-axis` plane.
- `Middle Mouse Button` will make all vertical mouse movements change the camera's pitch.
- `Left Mouse Button` will make all horizontal mouse movements change the camera's yaw.
- `[` will unlock the mouse cursor from the window.
- `X` will toggle the textures on and off of all the models
