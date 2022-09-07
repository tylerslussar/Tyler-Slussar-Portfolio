### Computer Graphics
* set of classes to use for writing cross-platform (Windows and Mac) OpenGL code; it is mainly intended for educational use to learn computer graphics concepts
	* the Windows version has been tested with Visual Studio 2019 on Windows 10 
	* the macOS version has been tested with Xcode 13 on with macOS Big Sur  with an Intel Mac and macOS Monterey with an Apple Silicon Mac
	* As of December 2021, OpenGL is deprecated on macOS but is still available on macOS Monterey
* this repository contains both an Xcode project (on a Mac, double-click on the **ComputerGraphics.xcodeproj** file to open in Xcode) and a Visual Studio project (on a Windows computer, double-click on the **ComputerGraphics.sln** file to open in Visual Studio)
* it uses [GLFW](https://www.glfw.org) and [OpenGL Extension Wrangler (GLEW)](http://glew.sourceforge.net)
	* the Windows version gets them via NuGet packages
	* this repository includes fat libraries (both Arm and Intel architectures) for the macOS versions of libGLEW.a and libglfw3.a so it should work on both Intel and Apple Silicon Macs. 

### Usage
* create a subclass of the **Renderer** class 
	* in the constructor create data structures for what you want to draw, etc. and use the various **add...** methods such as (**addLines**) of the **Renderer** class to add them so they are drawn
	* you can override the various mouse and keyboard callbacks from the **GLFWBase** class that the **Renderer** class subclasses to handle them for your program
* change the **main.cpp** file to use your new subclass
* see the **demo** branch for an example
