# MultiFocusFusionAndDepth
Project to find focus measure for a stack of images, and extract depth if images are sorted ascending by focus.
Algorithms implemented partly: 
Laplacian Variance similar to:
Pech Pacheco, G. Cristobal, J. Chamorro Martinez, J. Fernandez Valdivia, Diatom autofocusing in brightfield microscopy: a comparative study, in Proceedings of the International Conference on Pattern Recognition, vol. 3, 2000, pp. 314–317.
Sum of modified laplacians and depth extimation similar to:
S. Nayar, Y. Nakagawa, Shape from focus, IEEE Transactions on Pattern Analysis and Machine Intelligence 16 (1994) 824–831.

# Running
OpenCV is needed for building. Commands:
cmake .
make
./MultiFocusFusionAndDepth

Results are in the results folder - Depth.png and FocusMax.png.
