# Battlefield Respawn Project #
A Project Reality (Refractor 2) data compatible Game recreation

## What is this Project ##

The Battlefield Respawn Project is an effort to create a free and open source recreation of the Refractor & Refractor 2 Game Engine.
The Refractor Game Engine's are famous for having powered most of the Original Battlefield Games such as:

* Battlefield 1942
* Battlefield Vietnam
* Battlefield 2
* Battlefield 2142
* Battlefield Heroes
* Battlefield Play 4 Free

All of these titles (with the exception of the last 2) are now over 10 years old and considered abandonware since DICE/EA have shut down all original GameSpy powered online servers and ceased use of the Refractor 2 engine in favour of the more capable Frostbite engine.

Many Battlefield games, in particular Battlefield 2 still have an active modding community supporting projects such as Project Reality and Forgotten Hope 2.
However the modding efforts of these Community Projects can only go so far given the aging capabilities of the Refractor 2 engine.

To Solve this the Battlefield Respawn Project aims to create a data compatible game engine of a modern standard with new features and rendering methods.

---More Detail---

## Details ##

### File Format Reverse Engineering ###
 1. [Mesh File Headers](../blob/master/File_Headers.md)


## TODO ##

### Reverse Engineering ###
 1. Refractor 2 Engine Mesh File Formats
	1. .bundlemesh - 90% (Loader)
	2. .skinnedmesh - 90% (Loader)
	3. .colissionmesh - 50% (Header)
	4. .staticmesh - 90% (Loader)
 2. Refractor 2 Animation File Formats
	1. .ske Skeleton Definition - 50% (Header)
	2. .baf Battlefield Animation File - 50% (Header)
 3. Level Formats - 0%
 4. .con Object Definition Files - 0%
 5. .tweak Object Files -0%
 6. Gameplay Rules and scripted behaviour
 7. Look and Feel

### Major milestone Engineering Tasks ###
 Note: Each of the listed steps itself are Minor milestones that will be further detailed.

#### Pre-alpha 0.1 (Major) ####
 0. Documentation and Game Design Document
 1. Blender Plugin (read/write) for all mesh and Animation Formats
 2. Design an efficient engine architecture for the Battlefield data
 3. Develop game base class structures
    1. Implement Game loop & Object State tracking
    2. Lua Script interface to classes
    3. User Input system (SDL)
    4. Drawing system (OpenGL)
    5. Sound system
    6. Implement Initial Network layer (Extensive

#### Pre-alpha 0.2 (Major) ####
 0. Detailing the Animation System implementation
 1. Design Player System
    1. Classes
    2. Inventory based Kit system (Allows for sharing of individual items)
 2. Implement first terrain loader & renderer of the Battlefield terrain data
 3. Implement first level static geometry loading & rendering
 4. Implement first collision and physics model (Bullet Physics Library)
 5. Implement first Player Rig
 6. Develop initial GUI system
 7. Test and optimize exisiting code
 
#### Alpha 0.3 (Major) ####
 0. Design Vehicle System
    1. Ground Vehicles
    2. Sea & Submersible
    3. Fixed Wing and Rotor Wing aircraft

#### Alpha 0.4 (Major) ####
 0. Design Projectile and Munitions System
 1. Improvements to Network features (Network performance)
 
#### Beta 0.5 (Major) ####
 0. WIP


