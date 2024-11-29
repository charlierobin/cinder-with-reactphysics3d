# Using Cinder with the ReactPhysics3D physics engine library in Xcode
 
A *simple* **Xcode** project integrating the open source **Cinder** (OpenGL) library with the **ReactPhysics3D** library.

All this is really just intended to be the jumping off point for your own work ...

## Both Cinder and ReactPhysics3D are already included, in different forms:

Cinder is supplied as the pre-built `libcinder.a` provided in the `Cinder/include/lib/macosx` directory. (And of course with the header files.)

ReactPhysics3D is supplied as full source (and headers), as when I was trying to use a compiled library I started getting some weird exceptions when destroying rigid bodies, and I couldn’t solve the problem. So to see if I could track the issue down, I linked in the full source and compiled everything from scratch. The exceptions disappeared. So, there we go ... (Mind you, I still had to comment out one assertion for `Transforms` for some reason which I still haven’t got around to looking more closely at. Maybe in the New Year...)

So if you want to link in your own Cinder install, you will need to update the Cinder path (`CINDER_PATH` in `User-Defined` in `Build Settings` of the project) in Xcode to your own installation, and then you can dump all the supplied stuff. (Download Cinder from their web site.)

(The Xcode project was originally generated using *TinderBox*, the Cinder-supplied utility.)

The ReactPhysics3D header and source files can also be replaced with more recent versions without too much trouble. (Download the source files, makes files etc from the ReactPhysics3D site.)

https://github.com/user-attachments/assets/38318e3e-23a7-4242-b40e-9c2e46ac6c00

*Cinder version used:* 0.9.2

*ReactPhysics3D version used:* 0.8.0

The **Cinder** site: https://libcinder.org/ (Cinder is a free and open source library for professional-quality creative coding in C++.)

The **ReactPhysics3D** site: https://www.reactphysics3d.com/ (ReactPhysics3D is a C++ physics engine library that can be used in 3D simulations and games. The library is developed by Daniel Chappuis and is released under the open-source ZLib license.)

Although there’s no license/restrictions on the few little bits I’ve done, please note that both Cinder and ReactPhysics3D have their own separate licenses:

## Cinder

**Copyright (c) 2010, The Cinder Project**

This code is intended to be used with the Cinder C++ library, http://libcinder.org

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

## ReactPhysics3D

**Copyright (c) 2010-2020 Daniel Chappuis** http://www.reactphysics3d.com

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.


