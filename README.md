# so_long
> This repository contains a "So_long" project that is part of the École 42 curriculum.

This is my first graphic project, and it consists of creating a simple 2D game. 

The objective of this project is to learn how to handle windows and use graphic resources, in this case with the MLX42 library. Therefore, it is a quite special project because it's the first time we will see our program go beyond the console boundaries and display itself on the screen.

Too see how do you have to download the library and get started, see the page of Codam regarding [MLX42](https://github.com/codam-coding-college/MLX42).

## Game

In this project, we have to create a 2D game (top down or profile) where the player must collect all the collectibles before being able to access the exit and win. It must follow some rules: \
• The W, A, S and D keys will be used to move the player. \
• The player cannot enter the walls. \
• After each movement, the current number of moves should be displayed in the terminal. \
• The game doesn’t need to be real-time.

<div align="center">
  <img src="https://github.com/MofMiq/so_long/blob/main/gifs/so_long.gif">
</div>

### Map

The program should accept a single argument, which will be the map file with the .ber extension.
It must contain the following elements:
• '0' for the floor. \
• '1' for the walls. \
• 'P' for the player, only one. \
• 'E' for the exit, only one. \
• 'C' for the collectibles, at least one.

• The map must be rectangular. \
• The map must be closed/surrounded by walls. \
• You have to check if there’s a valid path in the map. \
• You must be able to parse any kind of map, as long as it respects the above rules.

### Graphics management

• The program will display the image in a window. \
• Window management should be clean, allowing tasks such as switching between windows, minimizing, etc. \
• Pressing the ESC key should close the window and terminate the program cleanly. \
• Clicking on the red cross button of the window should also close the window and terminate the program cleanly.

## Project structure

1. Check the number of arguments and the file extension.
2. Read and parsing the map into data, mostly in one big struct.
3. Check the validity of the provided map.
4. Initialize a window and create and maintain a loop to keep the window open.
5. Initialize/create the images that we are going to use in our game.
6. Render our game map and necessary elements.
7. Create an event loop to handle input.
8. Create the playable mechanics of the game.
9. Play the game :heart_eyes_cat:

## Approaching MLX42

The first thing to do is to set up a connection between our program and the window  system, which is a windowing system that provides a graphical user interface for Unix-based operating systems (GLFW).
#### mlx_init
The very first step for initialization is to execute the **`mlx_init`** function. Once the connection is established, our program can create windows, handle user input, and perform other graphical operations using the functions provided by the mlx library.
Because **`mlx_init`** returns a pointer to the window instance, that will be used by other MLX42 functions, it must be called at the beginning of the program.
#### mlx_loop
The **`mlx_loop(mlx_t* mlx)`** function only takes a pointer to our window connection and starts an infinite loop that continuously waits for events to occur in the X window system. When an event occurs, the appropriate function specified by the user is called to handle the event.
In other words, puts the program in a state where it is constantly waiting for input from the user, whether it be keyboard input, mouse input, or other types of input from the X window system.
The **`mlx_loop`** function does not return until the program is terminated, either by the user or by the program itself.
#### mlx_key_hook & mlx_loop_hook
In the mlx42 library, **`mlx_loop_hook and mlx_key_hook`** are used to set up callbacks for events that occur during the main event loop. They take three arguments. The pointer to our window connection, a function that will be called whenever one of the event conditions are met and a third of your own choosing. In our case our data struct, which contains all necessary variables to make the callback function actually work. 

**`mlx_loop_hook`** is used to set up a callback that is called each time the event loop runs, allowing you to perform some action or update the display before the next frame is rendered. The function, for example, could change the image of our walls. We could give it a function that changes between a couple of similar, but slightly different images every 5 iteration to give our walls, which are bushes, the illusion to be swaying in the wind. Or we could use it to move our enemies one position for example every 35 iteration of our loop.

**`mlx_key_hook`** is used to set up a callback that is called each time a key is pressed, allowing you to handle keyboard input.

It is important to set up these callbacks before calling **`mlx_loop`**, because once mlx_loop is called, it enters a continuous loop that handles events and updates the display. If you try to set up the callbacks after the loop has started, they may not be registered in time to be called during the event loop.
#### mlx_close_window & mlx_terminate
It is also important to know how to manage the window and the program when they are closed.  **`mlx_close_window`** notifies MLX42 that it should stop rendering and exit the main loop. **`mlx_terminate`** takes care of releasing of all our allocated resources.

<div align="center">
  <img src="https://github.com/MofMiq/so_long/blob/main/gifs/bonus_lose.gif">
</div>

## Rendering images

To be able to make a 2d game we are going to need a visual representations of all the elements on our provided map, like the player or the walls. The MLX42 library requires either an XPM or PNG file, both file formats to store digital images and generate them in our window.

But before we can see the sprites on the screen, we need to understand the differences between images and textures:

• **Images** are pretty much pixel buffers that keep track of how many copies/instances it has on the window, each instance is simply an X Y Z coordinate resulting in a plane that then displays the contents of the pixel buffer.
A change in the buffer results in a change for all currently displayed instances.

• **Textures** are disk loaded images stored in memory and hold a buffer of pixel data along with information about the image such as width, height, and bytes per pixel.
Textures on their own are not displayed to the screen but have to be displayed using images.

To display our sprites on the screen, we will do the following:

#### mlx_load_png
The **`mlx_load_png`** function is used to load a PNG file into a mlx_texture_t struct. This function takes a string that represents the path to the PNG file that you want to load. When this function is called, it reads the file and decodes the pixel data from the PNG format into a format that can be used by the graphics library. This format is an array of bytes that represent the color of each pixel in the image.

The reason why the pixel data needs to be decoded from the PNG format into a texture struct is that PNG files use a compressed format to store the image data. This compression helps to reduce the size of the file on disk, but it also means that the pixel data cannot be directly used by the graphics library without first being decoded.

#### mlx_texture_to_image
After loading our PNG file into an **`mlx_texture_t struct`**, we can't simply draw it on the screen just yet. This is because the graphics library needs to convert the pixel data stored in the struct into a format that can be rendered on the screen. Therefore, we need to create an mlx_image_t structure to represent the transformed image data that the graphics library can use.

The mlx_image_t struct contains information about the format of the transformed image data, such as its width, height, and other details, along with a pointer to the actual transformed pixel data. To create this struct, we use the **`mlx_texture_to_image`** function, which takes a pointer to our currently running window and a pointer to our texture data. This function initializes the image struct so that the graphics library can work with our texture.

Once we have our textures transformed into images, we must manually delete those textures to prevent memory leaks.

#### mlx_image_to_window
It allows us to display an image on the screen by taking a pointer to the specific **`mlx_image_t`**, a pointer to our current graphics window, and the coordinates where the image should be displayed in the window.

The PNG images I used in my game are 32 x 32 pixels in size, so whenever we would like to put an image into our window, we have to multiply the X and Y coordinates.

## Bonus

<div align="center">
  <img src="https://github.com/MofMiq/so_long/blob/main/gifs/bonus1.gif" width="600"/>
</div>


• Add an enemy that causes the player to die if they come into contact with it. \
• Add some sprite animations. \
• Display the movement counter directly on the screen instead of in the terminal.

The bonus part of this project is not very difficult if you have done a solid job on the mandatory part and you don't go overboard. For example, I didn't give the enemy any movement because I was in a bit of a hurry, but it does what it's supposed to do.

To display text on the screen, you simply call the function **`mlx_put_string`**, which essentially draws a string on an image and then displays it on the screen. So, similar to images, it returns a pointer to the image that has been generated with the string.

Regarding animations, just like we used instances for collectibles, we will do the same to provide basic movement animations for the player. Every time the player moves, we set the boolean 'enabled' to 1 (true) for the corresponding image instance based on the direction, and for the other three instances, we change the value of 'enabled' to 0 to deactivate them (example: game->player_d->instance[0].enabled = 1).
