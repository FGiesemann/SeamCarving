# SeamCarving

This project explores and demonstrates _Seam Carving_, a method for content-aware image resizing (also called retargeting).
The algorithm is described in a paper "Seam carving for content-aware image resizing" by S. Avidan and
A. Shamir [DOI: 10.1145/1275808.1276390](https://doi.org/10.1145/1275808.1276390).

Tha basic idea of the algorithm is to shrink an image by removing a _seam_, which is a connected path from the top of the
image to the bottom (if we want to reduce image width) that contains exactly one pixel per image row. By carefully selecting
these seams, the image size can be changed without distorting the image content, as simple scaling would do.

The selection of seams to be removed is controlled by an energy function that is computed on the image and that is high in
areas of 'important content' and low in areas of 'unimportant content'. The implementation for this demonstration uses pixel
gradients (something like edges) in the image, which makes 'smooth' parts of the image 'unimportant' and areas with higher
contrast 'more important'.

Then, using _dynamic programming_, the value for the seams through the image are computed and the seam with lowest accumulated
energy is removed from the image in order to decrease the width.

## The implementation

The demonstration application makes use of the Pixel Game Engine
(see [One Lone Coder](https://community.onelonecoder.com/olcpixelgameengine/)) for display and
interaction. The code can be found in the `Demo.cpp` file.
The algorithm itself is implemented in `SeamCarving.cpp`. Finally, the `main.cpp` just starts the 
application.

This implementation is very basic and used only to explore and demostrate the algorithm. It is not 
'production ready'.

## Building

The application includes all the code it needs and does not depend on external libraries. CMake 
buildfiles are provided. Building should be simple:

```shell
mkdir build
cd build
cmake ..
make
```

## Usage

The program should be called like this:
```
seamcarving <image file> <width> <height>
```

The first parameter specifies the image to be used, the following parameters give the size of the 
input image (in pixels). As an example, you can use the image 
[Broadway_tower_edit](https://upload.wikimedia.org/wikipedia/commons/c/cb/Broadway_tower_edit.jpg) 
(used in the english Wikipedia article on Seam Carving), or any other image. (Of course, the algorithm 
does not perform well on _all_ images).

By default, the program displays the input image. Use the following keys to change the display mode:
- <kbd>C</kbd>: show the pixel energy function (pixel costs)
- <kbd>S</kbd>: show accumulated seam costs
- <kbd>I</kbd>: show the input image

Using the <kbd>D</kbd> key you can toggle displaying the seam. With <kbd>M</kbd> you can toggle 'mouse 
mode'. When mouse mode is _off_, the seam with minimum accumulated costs is shown. When mouse mode is 
_on_, the seam displayed starts at the x-position of the mouse.

With the <kbd>-</kbd> key you can erase a single seam from the image. **Caution**: If mouse mode is 
on, the seam at the current mouse position is removed, not the optimal seam!
Holding <kbd>Space</kbd> will remove one seam after the other.

With the <kbd>R</kbd> key, the original image will be restored. Finally, <kbd>ESC</kbd> quits the 
program.

## Outlook

This demo program only handles reducing image width. Of course the algorithm can be used to reduce 
image height and it can even _increase_ the image dimensions by inserting seams. The original paper 
also demonstrates object removal and other applications.

Different energy functions lead to different performance on different image types. Currently, only 
gradient pixel energy is implemented here.
Additional factors can be integrated into the energy function, as for example [Improved seam carving with forward energy (Avik Das)](https://avikdas.com/2019/07/29/improved-seam-carving-with-forward-energy.html). (The website also contains a nice explanation of the dynamic programming method to accumulate seam costs.)
