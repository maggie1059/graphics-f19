Final Project Readme

For our final project, we created a scene with trees and a light source producing god/crepuscular rays with an environment map as the background. 
IMPORTANT NOTE: We weren't able to get the program running correctly on a non-
department machine and were unable to figure out why, so we included a screen
recording of us running the demo on the department machine titled FINAL_DEMO.mp4
and included it in this handin (in the root folder).


We used the final stencil code as the foundation for our project, and imported in OpenGLShape, uniforms, the orbiting camera, gl (including textures, data types, and shaders), lib (with error checker and resourceloader), and some of the shapes from our past projects and labs. We especially relied on lab 7 (FBOs) and lab 9 (which used an environment map) for much of our set up.

We used L-systems in order to create 3D trees which is separated into three parts in three different files: StringGenerator, StringParser, and SimpleTree. StringGenerator is where the rules are generated that will be used to make the string. We start with a vector holding a single rule (it starts with 0), and use a predetermined rule to recursively create a tree with more levels.
Then, that vector of rules is sent to the StringParser, which goes through the vector and compiles a vector of vertices representing the start and endpoints of each branch and trunk. Depending on the rule read in, it will add vertices to the vector, alter the phi and theta values, or keep track of the given level in order to make sure the branches are extending in the way we want. Also, because the rule generation is recursive, the vector of rules allows for repeated vertices to show up. To prevent backtracking and redrawing, we keep track of a list of skipped vertices that should not be used when actually drawing the tree. 
Finally, we sent the vector of vertices to SimpleTree to draw the tree. We draw the trees by getting the circles around the points representing the start and end points of the given branch. When we do so, we use the direction of the vector from the start point to the end point to define the tilt of the circle on the endpoint in order to prevent the branches from being flat. Once we have the circles, we draw the barrel around the circles by connecting points on each circle in triangle formats. All of the points of the barrel are stored in a vector of vectors that will be used to draw the trees.

For crepuscular rays, we implemented a ray shader according to https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch13.html. We have two passes through the scene: the occlusion pass and the normal phong pass. The occlusion colors everything black except from the light source, and stores that information in an FBO (the occludeFBO). Then, the scene is rendered normally with phong lighting and stored in another FBO (the phongFBO), along with our environment map. Both of these passes are then sent to the ray shader for processing, and blended together for the final scene.

The environment map is created using the skybox, and we used the strategies from lab 9 in order to implement it.

Known Bugs:
The set up and implementation of the L-system took longer than anticipated, so we were not able to make the system work generically for multiple levels. Right now, it works as expected for up to 2 levels of recursion but not for other levels.
It had been working generically before for all different levels. However, we changed the implementation because we noticed that all the vertices were being drawn twice, which was messing up how we were trying to tilt the circles around branch start and end points. We decided that since we wanted to implement a stationary scene, we would rather have the circles tilt than use multiple different levels of recursion. We wanted to revisit it later to make it more generic, but we ultimately ran out of time. 


Note: The rays in the environment map from that sun are just part of the jpg (not our code)! We were unable to find a better-fitting environment map for our scene, so we ended up going with one that already had a sun in it.

