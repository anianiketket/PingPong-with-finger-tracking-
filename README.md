# PingPong-with-finger-tracking-
A PingPong game developed on C and integrated with MATLAB using Engine functions to control the bats using finger movements.

HOW TO SETUP AND USE IT

Requirements :
1. Webcam
2. MATLAB with USB webcam hardware support package
3. Microsoft Visual Studio

Procedure :
Clone the repo to a location.
Open the Visual Studio code and set it up to 64 bit or 32 bit whatever matches your MATLAB platform. By default my project is on 64 bit.
Now open the Property Page and :
1. In the VC++ directories, add MATLAB bin folder path to executable directories.
2. In the VC++ directories, add MATLAB extern\include folder path to include directories.
3. In the VC++ directories, add MATLAB extern\win64(win32)\lib\microsoft folder path to library directories.
4. In Debugging, set environment as PATH=($MATLABroot)\bin\win64
5. In Linker, set Enable Incremental Linking to NO and add library path to Additional Library directories
6. In Linker>Input, add the following libraries by placing semi-colon at the end of each,
libmx.lib;libmex.lib;libeng.lib;libmat.lib;

Click OK. For a detailed description on how to do all this visit my blog at http://codedating.blogspot.in/2015/07/integrating-matlab-and-visual-studio.html

Look for the comment in the VS code saying about "cd" command and edit there the path of MATLAB function file. In the "cam=webcam", you can edit webcam(#) where # is the camera input you are using.
On running the progrma might give error of GWL_USERDATA undefined because we changed to 64 bit. (If you did).
To debug, double click on both errors and edit it with GWLP_USERDATA
Run again.

Wear a bright red and good blue band on your finger covering almost three quarters of your finger!

Check Out my blog for each modules' explanation : http://codedating.blogspot.in/
