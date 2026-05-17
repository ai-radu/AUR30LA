# AUR30LA Engine Pre-Alpha v.0.3.1.2.4
---------
AUR30LA is an open-source experimental game engine developed as a passion project, emulating the 'internal use only' mindset.\
Made using Visual Studio Code 1.119.1 on Ubuntu 26.04 LTS, the project is provided free of charge and royalty-free.\
Projects, games, tools, assets, and other content created with AUR30LA remain the sole property of their respective creators. AUR30LA claims no ownership over user-created content. See LICENSE.txt for more informations.\
AUR30LA and its associated branding, logos, and visual identity are the property of their respective owner unless otherwise stated.\
Community screenshots, videos, tutorials, and non-commercial showcases using the AUR30LA name or logo are generally permitted.

*Pull requests, unsolicited patches, and external roadmap demands are not accepted.*

Current Status
- Experimental software.
- Breaking changes may occur at any time.
- Documentation may be incomplete or completely absent.
- Features may change, disappear, or remain unfinished indefinitely.

No guarantee is provided regarding
- Stability
- Compatibility
- Availability
- Security
- Data integrity
- Fitness for production use
- Long-term maintenance
- Future updates

Users are responsible for verifying their own builds, dependencies, operating system behavior, third-party tooling, and deployment environments.

Platform Scope
- Linux only.
- Offline only.
- No sideloading.
- No mandatory online services.
- No account system.
- No launcher.
- No DRM.
- No anti-cheat.
- No advertisements.
- No integrated payment systems.
- No subscriptions.
- No cloud saves.
- No cloud tooling.
- No telemetry.
- No analytics.
- No crash reporting.
- No background data collection.
- No IP address logging.
- No hardware fingerprinting.
- No generative AI integrations or cloud AI services.

Privacy\
AUR30LA is designed to operate without collecting, storing, processing, transmitting, or monetizing personal data.

The engine does not intentionally collect
- IP addresses.
- Hardware identifiers.
- Usage analytics.
- Behavioral metrics.
- Personal accounts.
- Tracking data.
- Advertising identifiers.

Third-Party Components\
AUR30LA may include or depend on third-party libraries, frameworks, tools, shaders, or assets distributed under their own respective licenses.
All third-party software remains the property of its respective authors and contributors. Relevant notices and licenses should be available within licenses f0lder.
Users are responsible for complying with all applicable third-party licenses.

Warranty Disclaimer\
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, RELIABILITY, SECURITY, OR PERFORMANCE.

Liability Limitation\
IN NO EVENT SHALL THE AUTHORS, CONTRIBUTORS, COPYRIGHT HOLDERS, OR DISTRIBUTORS BE LIABLE FOR ANY CLAIM, DAMAGES, LOSSES, OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT, OR OTHERWISE, ARISING FROM OR RELATED TO THE SOFTWARE OR THE USE OF THE SOFTWARE.

This includes, but is not limited to
- Data loss.
- Project corruption.
- Build failures.
- System instability.
- Security issues.
- Hardware damage.
- Financial losses.
- Downtime.
- Loss of productivity.

Libraries used
- Dear ImGui https://github.com/ocornut/imgui
- Glad https://github.com/Dav1dde/glad
- GLFW https://github.com/glfw/glfw
- GLM https://github.com/g-truc/glm
- Khronos https://www.khronos.org/
- OpenGL https://www.opengl.org/
- stb https://github.com/nothings/stb

Formats supported (internally)
- .jpeg
- .jpg
- .png
- .bmp
- .psd
- .tga
- .hdr
- .pic
- .ppm
- .pgm

If you agree to all of the above

Prerequisites:\
*for a fresh install*

    sudo apt update
    sudo apt upgrade
    sudo apt install build-essential
    sudo apt install g++ // version i use 15.2.0
    sudo apt install cmake // 4.2.3
    sudo apt install ninja-build // 1.13.2
    sudo apt install pkg-config // 2.5.1
    sudo apt install libglfw3-dev // 3.4-4
    sudo apt install git // 2.53.0

QuickStart:

1. Download the source archive or clone the repository:

       git clone https://github.com/ai-radu/AUR30LA

2. Build:

        rm -rf build && cmake -S . -B build -G Ninja && cmake --build build && cd build && ./AUR30LA

3. Optional:

    inside CMakeLists.txt:

        target_compile_definitions(AUR30LA PRIVATE
            AUR_DEBUG=0
        )

    AUR_DEBUG=1 > Development mode, faster iterations, terminal debugs enabled\
    AUR_DEBUG=0 > Release-like behaviour