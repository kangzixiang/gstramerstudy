
glReadPixels is the key OpenGL function that reads pixels from screen. Also have a look at the setup under init().

glReadPixels reads the bottom line of pixels first, unlike most image formats, so converting that is usually needed.

---------------------------------------------------------------
sudo apt-get install libpng-dev libavcodec-dev libavutil-dev

Compile with:
gcc -DPPM=1 -DLIBPNG=1 -DFFMPEG=1 -ggdb3 -std=c99 -O0 -Wall -Wextra \
  -o offscreen offscreen.c -lGL -lGLU -lglut -lpng -lavcodec -lswscale -lavutil

----------------------------------------------------------------

Run 10 frames "offscreen" (mostly TODO, works but has no advantage), with size 200 x 100 and all output formats:
./offscreen 1 10 200 100 7


CLI format is:
./offscreen [offscreen [nframes [width [height [output_formats]]]]]


and output_formats is a bitmask:
ppm >> 0 | png >> 1 | mpeg >> 2


Run on-screen (does not limit my FPS either):
./offscreen 0


----------------------------------------------------------------------


Benchmarked on Ubuntu 15.10, OpenGL 4.4.0 NVIDIA 352.63, Lenovo Thinkpad T430.

Also tested on ubuntu 18.04, OpenGL 4.6.0 NVIDIA 390.77, Lenovo Thinkpad P51.

TODO: find a way to do it on a machine without GUI (e.g. X11). It seems that OpenGL is just not made for offscreen rendering, and that reading pixels back to the GPU is implemented on the interface with the windowing system (e.g. GLX). See: OpenGL without X.org in linux

TODO: use a 1x1 window, make it un-resizable, and hide it to make things more robust. If I do either of those, the rendering fails, see code comments. Preventing resize seems impossible in Glut, but GLFW supports it. In any case, those don't matter much as my FPS is not limited by the screen refresh frequency, even when offscreen is off.

Other options besides PBO

render to backbuffer (default render place)
render to a texture
render to a Pixelbuffer object (PBO)
Framebuffer and Pixelbuffer are better than the backbuffer and texture since they are made for data to be read back to CPU, while the backbuffer and textures are made to stay on the GPU and show on screen.

PBO is for asynchronous transfers, so I think we don't need it, see: What are the differences between a Frame Buffer Object and a Pixel Buffer Object in OpenGL?,

Maybe off-screen Mesa is worth looking into: http://www.mesa3d.org/osmesa.html