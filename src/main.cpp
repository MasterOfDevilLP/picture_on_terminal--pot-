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
    Max supported width: 400
*/

std::vector<unsigned char> transparent_rgb = {0, 0, 0};

std::string rgb_to_pixelstr(int red, int green, int blue, int alpha)
{
    // returns a std::string containing a string which will correspond to a pixel with the given RGB value
    char *c_r;
    char *c_g;
    char *c_b;
    if (alpha == 0)
    {

        // if the alpha is 0 (transparent pixel) it take the opposite RGB of the average RGB value of all pixels as the color
        // this is supposed to help with visibility if transparent pixels are used
        c_r = myitos(255-transparent_rgb[0]);
        c_g = myitos(255-transparent_rgb[1]);
        c_b = myitos(255-transparent_rgb[2]);
    } else
    {
        c_r = myitos(red);
        c_g = myitos(green);
        c_b = myitos(blue);
    }
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
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 4);
    if (!data) {std::cerr << "couldn't open image with filename: " << filename << std::endl; return false;}
    image = std::vector<unsigned char>(data, data + x * y * 4);
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
    const size_t RGBA = 4;


    // getting the RGBA values of every pixel of the image
    bool success = load_image(image, argv[1], width, height);
    if (!success) return -1;
    if (width > 400) {std::cerr << "image should not be wider then 400px" << std::endl; return -1;}

    // calculating the average RGB value of all Pixels
    u_int64_t avg_r, avg_g, avg_b;
    avg_r = avg_g = avg_b = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = RGBA * (x + y*width);
            avg_r += static_cast<u_int64_t>(image[index + 0]);
            avg_g += static_cast<u_int64_t>(image[index + 1]);
            avg_b += static_cast<u_int64_t>(image[index + 2]);
        }
    }
    transparent_rgb[0] = avg_r/(width*height);
    transparent_rgb[1] = avg_g/(width*height);
    transparent_rgb[2] = avg_b/(width*height);

    // informative printouts before the picture
    std::cout << "image: " << argv[1] << std::endl;
    std::cout << "resolution of the image: " << width << "x" << height << std::endl;
    std::cout << "avg RGB: " << myitos(static_cast<int>(transparent_rgb[0])) << " " << myitos(static_cast<int>(transparent_rgb[1])) << " " << myitos(static_cast<int>(transparent_rgb[2])) << std::endl;

    // going through every pixel to get RGBA values and print out a pixel with the RGBA value
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int r, g, b, a;
            int index = RGBA * (x + y*width);
            r = static_cast<int>(image[index + 0]);
            g = static_cast<int>(image[index + 1]);
            b = static_cast<int>(image[index + 2]);
            a = static_cast<int>(image[index + 3]);
            std::cout << rgb_to_pixelstr(r, g, b, a);
        }
        std::cout << std::endl;
    }

    return 0;
}