picture_on_terminal is a programm made by MasterOfDevilLP (https://github.com/MasterOfDevilLP) which lets you display an image on the terminal.

The program uses the stb_image library by nothings (https://github.com/nothings/stb/blob/master/stb_image.h) to load the image

How to use:
- you need cmake installed with the minimum version being 3.22
- create the Makefile with "cmake ."
- build the programm with "make"
- call the programm with ./pot and give it the path to the image you want to display

Important informations:
- currently supported is only a max width of 400 pixels to make sure it doesn't wrap around in the terminal (you may zoom out)
- height of the image is not limited (except for the size of your memory)
