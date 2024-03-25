# Cub3d (Linux version) - 42 School

This is a 42 project whose objective is to create a first-person perspective game in the style of Wolfenstein3D.
The main technique used to create the appearence of a 3D view is called raycasting (https://en.wikipedia.org/wiki/Ray_casting).

## Installation

First, this project will run best on a native Linux distribution (given WSL emulates inputs, mouse movements in the game will not work as intended).
The following commands will work on Ubuntu :)
The project uses a school library - Minilibx (https://github.com/42Paris/minilibx-linux) - which serves as an interface for utilizing the X Window System on Unix-like operating systems. It is essentially a window manager :D

So first off, make sure the Minilibx dependencies are in place by running:

	sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev

Now, we need a C compiler and the Make utility to build the project:

sudo apt-get update
sudo apt-get install build-essential

Then, clone this repo:

	git clone git@github.com:manuel-aguiar/cub3d_42_linux.git [name you want]

The project has two versions, mandatory and bonus, as per the schools rules.
The bonus should be slightly more fun!! So:

	cd [name you want]/bonus ; make

Aaaand the game should be ready to run! On the "maps" folder there are a couple of underdeveloped maps (:D) but should give you a feel of the game.
Run for instance:

	./Cub3d maps/map_cenas.cub

and have fun!!

## Usage and Controls

### Controls
The game works as a first-person shooter (some of the assets you see may look familiar...). So the basic FPS controls apply:

	WASD to move
	X to crouch
	Z to prone
	Backspace to jump (or stand from crouch/prone position)
	Mouse movement to change the perspective
	Left-Click to shoot
	Right-Click to aim
	P for pausing the game
	ESC to exit the game
	1/2/3 to toggle blur/floor/ceiling reflections

### The map
Now, you can create your own maps and use the textures you want!!
Some requirements are needed though, let's take "map_cenas.cub" as an example:

	NO ./assets/xpm_north.xpm
	SO ./assets/xpm_south.xpm
	WE ./assets/xpm_west.xpm
	EA ./assets/xpm_east.xpm

	F ./assets/xpm_margarida.xpm
	C ./assets/xpm_margarida.xpm

	MEDI ./assets/xpm_medikit.xpm
	AMMO ./assets/ammo.xpm
	X_ENEMY ./assets/xpm_mario.xpm
	Y_ENEMY ./assets/xpm_mario.xpm
	Z_ENEMY ./assets/lost_soul.xpm
	MY_BULLET ./assets/xpm_flying_bullet.xpm
	EN_BULLET ./assets/xpm_enemy_bullet.xpm
	WALL_BULLET ./assets/bullethole.xpm
	GUN ./assets/xpm_gun.xpm
	DOOR ./assets/xpm_door.xpm

	        1111111111111111111111111
	        1000000000110MMM0XZ000001
	        10110000011100000XZ100001
	        100100EA0DDD00000Z1000001
	1111111110110000011100Y00Y0000001
	10000000A011000001110111110111111
	11110111111111D11100000010001
	1111D111111111011101010010001
	110000001101010111000Z0010001
	1M000000000000001100000010001
	1A00000A000000001101010Z10001
	1100000111010101111101111000111
	11110111 1110101 101111010001
	11111111 1111111 111111111111

The first few lines specify paths to the textures the game will be loading.

	NO, SO, WE, EA - the wall textures
	F, C - floor and ceiling textures
	MEDI, AMMO, X_ENEMY, Y_ENEMY, Z_ENEMY, MY_BULLET, EN_BULLET, WALL_BULLET, GUN, DOOR - miscelanious textures for the game

Warning: ALL TEXTURES MUST BE .XPM FILES. If they are misconfigured, hopefully Minilibx will sound the alarms and the game will exit safely :D

You can change the textures to any you like as long as they are correctly cconfigured .xpm files, and make your own game!

Then there is the map!

	1 - wall
	0 - empty
	NSWE - player spawn position and direction
		there can only be ONE of these!!!! (player must spawn in only one place!)
	M - medikit to restore health
	A - ammokit to restore ammo
	D - doors, the MUST be between 1s (walls!!)
	X, Y, Z - the enemies!!!

Fell free to make your own maps, if there is a problem running the map, hopefully the error message displayed on the terminal will give you a clue on own to ammend it!

### Game Settings

Do you want the player to move faster? rotate slower? jump higher?

On the srcs/ folder, there is a file named game_settings.h. All the settings are written as macros (with more or less descriptive names), with aaaaall the sensibilities, speed, bullet velocity, window size. Change them, and run:

	make

It should just change a couple of files and relink, no need to re-compile all object files :)

Warning: the game does not perform safety checks on all the input macros, some of the changes might result in a game crash :( So, undo changes if necessary :)

## Sources and algorithms

To make this project, several algorithms where used. For raycasting, the famous Lodev tutorial served as a base:

	https://lodev.org/cgtutor/raycasting.html

For the compass:

	Midpoint Circle algorithm - https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
	Xiaolin Wu's line Algorithm - https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
	Bersenham's Line Algorithm - https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	Gaussian Blur - https://en.wikipedia.org/wiki/Gaussian_blur
	Gamma Correction - https://en.wikipedia.org/wiki/Gamma_correction
		(mainly used for antialiasing of the outter circle)
	Gamma Correction 2.2 polynomial aproximations:
		https://stackoverflow.com/questions/48903716/fast-image-gamma-correction
		https://mimosa-pudica.net/fast-gamma/

Physics:

	Jumps/weapon recoil: https://jsfiddle.net/LyM87/

Map collisions:

	Javidx9 Youtube tutorial: https://www.youtube.com/watch?v=D2a5fHX-Qrs

Bullet collisions and enemy hitbox:

	Liang-Barsky Clipper: https://en.wikipedia.org/wiki/Liang%E2%80%93Barsky_algorithm

On top of that, trigonometry, 2D and 3D vectors, all the fun stuff!!

That's it, enjoy!!!!!
