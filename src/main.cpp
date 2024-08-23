#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "./includes/utils.hpp"

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "./includes/stb_image.h"
}

/*
    supported resolution of picture: 256x256
*/

std::string rgb_to_pixelstr(int red, int green, int blue)
{
    // returns a std::string containing a string which will correspond to a pixel with the given RGB value
    char *c_r = myitos(red);
    char *c_g = myitos(green);
    char *c_b = myitos(blue);
    std::string r(c_r);
    std::string g(c_g);
    std::string b(c_b);
    delete c_r, delete c_g, delete c_b;
    std::string out = "\033[38;2;";
    out += r + ";" + g + ";" + b + "m██\033[0m";
    return out;
}

bool load_image(std::vector<unsigned char>& image, const std::string& filename, int& x, int &y)
{
    // load the image data into the image vector (only RGB data per pixel)
    // image = vector to store the pixels in
    // filename = string that contains the filename of the image
    // x = width of the pixture
    // y = height of the image

    int n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 3);
    if (!data) {std::cerr << "couldn't open image with filename: " << filename << std::endl; return false;}
    image = std::vector<unsigned char>(data, data + x * y * 3);
    stbi_image_free(data);
    return true;
}

int main(int argc, char *argv[])
{
    // argument check
    if (argc < 2) {std::cerr << "usage: " << argv[0] << " <filename>!" << std::endl; return -1;}

    // declaration of needed variables
    int width, height;
    std::vector<unsigned char> image;
    const size_t RGB = 3;


    // getting the RGBA values of every pixel of the image
    bool success = load_image(image, argv[1], width, height);
    if (!success) return -1;
    if (width > 400) {std::cerr << "image should not be wider then 400px" << std::endl; return -1;}
    
    std::cout << "image: " << argv[1] << std::endl;
    std::cout << "resolution of the image: " << width << "x" << height << std::endl;

    //going through every pixel to get RGB values
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int r, g, b;
            int index = RGB * (x + y*width);
            r = static_cast<int>(image[index + 0]);
            g = static_cast<int>(image[index + 1]);
            b = static_cast<int>(image[index + 2]);
            std::cout << rgb_to_pixelstr(r, g, b);
        }
        std::cout << std::endl;
    }

    return 0;
}