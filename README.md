# Snake

![Green snake](./_Icon.jpg)

## Author

Created by Kirill Rodriguez on 06/2014.

## Program

### Demo

![demo](./_demo/demo.gif)

I believe, this picture ~~snakes~~ speaks for itself.

### Purpose

The purpose of this project was at first to practice C++ OOP and GLUT, but eventually it became a severe challenge of fixing bad code: linkage, compilation, runtime errors, - and all the fun relevant to these processes. It has been a long time since the initial release, but the goal of debugging was only brought to achievement recently.

### Features

* 1 snake
* 5 routing modes (4 simple AIs)
* 5 aiming modes
* Walls
* Fruits
* 8 sets of icons.
* Pause (freezes the game)
* Safe mode (makes the best AI move when the current player about to crash)
* Running mode (moves only when a button is pressed)
* Adjustable delay between iterations (keyboard `io`)
* Adjustable number of fruits (keyboard `nm`)
* Adjustable field dimensions (args)
* Has fixes for unobvious bugs
* Has obvious bugs unfixed

### Possible improvements

* Option to make AI follow the cursor
* Read walls from file
* Mice (running fruits)
* More snakes
* Better snake AIs (for example, one planning to target the best cluster of fruits)
* Remote intelligence

### Contribution

Feel free to submit a pull request or an issue to inform about a bug / error.

## Usage

### Tools

* c++ compiler
* glut
* cmake
* make

### Compilation

	cmake . && make

### Running

	./_snake  [width] [height] [number-of-fruits]
	
#### Controls

* Arrows
* **p** - toggle pause mode
* **r** - toggle running mode
* **g** - toggle safe mode
* **0-4** - change AI (aiming and/or routing)
* **0-9** - change skin
* **n**/**m** - delete/add a fruit
* **o**/**i** - reduce/increase frame interval
* **wasd** - game controls (alternatives to arrows)
* **ESC** - exit