# BENgine - 3D Game Engine
This 3D engine was coded over the course of 2 quarters (6 months) at DePaul University and included a math library, collision testing, terrain generation from height maps, input handling, alarms, update and draw processing, asset loading and managment, scenes, and debug and visualization tools. The second quarter involved taking on a personal project that I would design, manage, and plan. I chose to add more functions to sprites, including animation, rigging, layers, draw order, sprite groups, and 2 variants of sprites that were optimized for either staying still or moving frequently.

Recently I got back to work on the engine, particularly in regards to the sprites.

Some major changes include:
- Decreased the memory footprint of BENgineSprite from 384 bytes and 16 byte alignment to 88 bytes and 4 byte alignment.
- Added the ability to flip sprites and sprite collections over their local x and or y axis using reflection and scaling as opposed to rotation about the x or y axis
- Eliminated the sprite variants and instead gave each sprite the ability to change when its graphics object's world matrix is calculated.
- Decreased user access to animation timer related code and made it easier for users to create custom animation commands.
- MUCH MORE!

To get started please refer to BENgine Setup.pdf

I plan to keep updating this as I improve the engine further. To see what I plan to work on check To Do.txt

I do not take credit for the mem tracker, FBX converter, 3D models, or any of the code located in the dist folder.
