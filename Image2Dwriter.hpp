#ifndef _IMAGE2DWRITER_HPP_
#define _IMAGE2DWRITER_HPP_

#include <iostream>
#include <fstream>
#include <fstream>
#include <ostream>
#include <string>
#include "Color.hpp"
#include "Image2D.hpp"
using namespace std;

template <typename TValue>
class Image2DWriter
{
public:
    typedef TValue Value;
    typedef Image2D<Value> Image;

    static bool write(Image &img, std::ostream &output, bool ascii)
    {
        std::cerr << "[Image2DWriter<TValue>::write] NOT IMPLEMENTED." << std::endl;
        return false;
    }
};

/// Specialization for gray-level images.
template <>
class Image2DWriter<unsigned char>
{
public:
    typedef unsigned char Value;
    typedef Image2D<Value> Image;

    static bool write(Image &img, std::ostream &output, bool ascii)
    {
        output << (ascii ? "P2" : "P5") << endl;
        output << img.w() << " " << img.h() << endl;
        output << "255" << endl;
        // write data
        if (ascii)
        {
            for (int j = 0; j < img.h(); ++j)
            {
                for (int i = 0; i < img.w(); ++i)
                {
                    output << (int)img.at(i, j) << " ";
                }
                output << endl;
            }
        }
        else
        {
            for (Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it)
            {
                output << *it;
            }
        }
        return true;
    }
};

/// Specialization for color images.
template <>
class Image2DWriter<Color>
{
public:
    typedef Color Value;
    typedef Image2D<Value> Image;

    static bool write(Image &img, std::ostream &output, bool ascii)
    {

        // Reprenez la partie sauvegarde de l'exemple précédent testColorImage2D.cpp
        output << "P6" << std::endl; // PPM raw
        output << img.w() << " " << img.h() << std::endl;
        output << "255" << std::endl;

        if (ascii)
        {

            for (int j = 0; j < img.h(); ++j)
            {
                for (int i = 0; i < img.w(); ++i)
                {
                    output << (int)img.at(i, j).red << " ";
                    output << (int)img.at(i, j).green << " ";
                    output << (int)img.at(i, j).blue << " ";
                }
                output << endl;
            }
        }
        else
        {
            for (Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it)
            {
                Color c = *it;
                output << c.red << c.green << c.blue;
            }
        }
        return true;
    }
};

#endif // _IMAGE2DWRITER_HPP_