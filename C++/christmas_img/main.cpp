#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

void setPixel(double h, double s, double l, double a, cs225::HSLAPixel & pixel)
{

    pixel.h = h;
    pixel.s = s;
    pixel.l = l;
    pixel.a = a;

}

int main() 
{
    
    cs225::PNG out = cs225::PNG(1500, 1500);

    // 1.59292, 0.94958, 0.233333, 1

    double h = 1.59292;
    double s = 0.94958;
    double l = 0.233333;
    double a = 1;


    for(unsigned y = 0; y < out.height(); y++)
    {
        for(unsigned x = 0; x < out.width(); x++)
        {

            cs225::HSLAPixel & px = out.getPixel(x , y);

            // base layer of stripes
            if (x % 100 == 0)
            {
                h = 360 - 10;
                s = 0.94958;
                l = 0.20;
                a = 1;
            }
            else if (x % 100 == 25)
            {
                h = 0;
                s = 0.94958;
                l = 0.25;
                a = 1;
            }
            else if (x % 100 == 50)
            {
                h = 10;
                s = 0.94958;
                l = 0.20;
                a = 1;
            }
            else if (x % 100 == 75)
            {
                h = 0;
                s = 0.94958;
                l = 0.25;
                a = 1;
            }
            
            if (y < 500)
            {
                // Green strips
                if (y % 100 <= 5)
                {
                    h = 110;
                    s = 0.90;
                    l = 0.115;
                } 
                else if (y % 100 <= 10)
                {
                    if (y % 100 >= 6 && y % 100 <= 7)
                    {
                        l = 0.0;
                    }
                    if (y % 100 >= 9 && y % 100 <= 10)
                    {
                        l = 0.0;
                    }
                }
                else if (y % 100 <= 20)
                {
                    h = 110;
                    s = 0.90;
                    l = 0.1;
                }
                else if (y % 100 <= 35)
                { 
                    if (y % 8 < 3)
                    {
                        if ((x + 10) % 20 <= 14)
                        {
                            h = 50;
                            s = 1;
                            l = 0.2;
                        } 
                        else 
                        {
                            l = 0;
                        }
                    }
                }
                else if (y % 100 <= 40)
                {
                    if (y % 100 >= 33 && y % 100 <= 37)
                    {
                        if (x % 20 <= 13)
                        {
                            h = 245;
                            s = 1;
                            l = 0.15;
                        }
                        else 
                        {
                            l = 1;
                        }
                    }
                }
                else if (y % 100 <= 55)
                {
                    h = 110;
                    s = 0.90;
                    l = 0.085;
                } else if (y % 100 <= 60) { /* do nothing */ }
                else
                {
                    unsigned curr_x = (x) % 100;
                    unsigned curr_y = (y-60) % 100;
                    unsigned shifter = (y - curr_y + 60) / 100;
                    if (y % 15 < 4)
                    {
                        h = 0;
                        s = 0.5;
                        l = 0.2;
                    } else if (y % 15 <= 6){
                        h = 110;
                        s = 0.85;
                        l = 0.1 - ((x % 100) * 0.0004 - 0.02);
                    }
                    if (2 * curr_x  == curr_y) { l = 1; }
                    if (2 * curr_x + 1 == curr_y)
                    {
                        h = 110;
                        s = 0.9;
                        l = 0.12;
                    }

                    //if (x > y && x - 3 < y){ l = 1; }

                    //if (x+20 > y && x + 17 < y){ l = 1; }
                    /*
                    if ((curr_y <= 5) || (curr_y >= 20 && curr_y < 25))
                    {
                        if (curr_x >= curr_y % 5)
                        {
                            l = 1;
                        }
                    }
                    else if ((curr_y >= 35) || (curr_y >= 15 && curr_y < 20))
                    {
                        if (curr_x >= curr_y % 5)
                        {
                            l = 1;
                        }
                    }
                    */

                }

            }
            
            if ((((x - (out.width()/4))*(x - (out.width()/4))) + ((y - (out.height()/4))*(y - (out.height()/4)))) <= ((out.width()/4)*(out.width()/4) + (out.height()/4)*(out.height()/4)))
            {
                s = (((x - (out.width()/20))*(x - (out.width()/20))) + ((y - (out.height()/20))*(y - (out.height()/20)))) / ((out.width()/20)*(out.width()/20) + (out.height()/4)*(out.height()/20));
                // std::cout << l << std::endl;
            }


            // std::cout << px.h << ", " << px.s << ", " << px.l << ", " << px.a << std::endl;

            // std::cout << x % 100 << std::endl;
            setPixel(h, s, l, a, px);
        }
    }

    out.writeToFile("some_color.png");

}