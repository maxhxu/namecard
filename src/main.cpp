#include <Magick++.h>
#include <iostream>
#include <regex>
#include <string>

using namespace std;
using namespace Magick;

int main(int argc, char **argv) {
    (void)argc;
    InitializeMagick(*argv);

    double scaleFactor = 2.0; 
    int baseWidth = 900;
    int baseHeight = 300;
    int targetWidth = static_cast<int>(baseWidth * scaleFactor);
    int targetHeight = static_cast<int>(baseHeight * scaleFactor);
    
    string densityValue = to_string(static_cast<int>(72 * scaleFactor));

    string svgTemplate = R"(<?xml version='1.0' encoding='UTF-8' standalone='no'?>
<svg width='900' height='300' viewBox='0 0 900 300' xmlns='http://www.w3.org/2000/svg'>
    <defs>
        <pattern id='stripes' width='8' height='8' patternUnits='userSpaceOnUse' patternTransform='rotate(45)'>
            <line x1='0' y1='0' x2='0' y2='8' style='stroke:#252525; stroke-width:4' />
        </pattern>
    </defs>
    <style>
        .bg { fill: #121212; }
        .dither-layer { fill: url(#stripes); }
        .accent { fill: #ff3e00; }
        .accent-stroke { stroke: #ff3e00; stroke-width: 4; fill: none; }
        .border-line { stroke: #333333; stroke-width: 2; fill: none; }
        .main-text { font-family: 'Courier New', monospace; font-weight: bold; font-size: 50px; fill: #ffffff; text-transform: uppercase; }
        .sub-text { font-family: 'Courier New', monospace; font-size: 20px; fill: #ff3e00; letter-spacing: 2px; }
        .contact-text { font-family: 'Courier New', monospace; font-size: 14px; fill: #bbbbbb; }
        .tagline-text { font-family: 'Courier New', monospace; font-size: 14px; fill: #888888; font-style: italic; }
    </style>
    <rect width='900' height='300' class='bg' />
    <rect width='900' height='300' class='dither-layer' />
    
    <path d='M 30 30 L 870 30 L 870 270 L 30 270 Z' class='border-line' />
    
    <rect x='30' y='30' width='120' height='15' class='accent' />
    <line x1='60' y1='80' x2='60' y2='160' class='accent-stroke' />
    
    <text x='80' y='120' class='main-text'>{{NAME}}</text>
    <text x='80' y='155' class='sub-text'>// {{TITLE}}</text>
    
    <text x='60' y='195' class='contact-text'>{{EMAIL}}</text>
    <text x='60' y='215' class='contact-text'>{{WEBSITE}}</text>
    
    <line x1='50' y1='250' x2='70' y2='250' class='accent-stroke' style='stroke-width: 2;' />
    <text x='80' y='255' class='tagline-text'>{{TAGLINE}}</text>
    
    <rect x='800' y='200' width='30' height='30' class='accent-stroke' />
    <rect x='750' y='270' width='120' height='15' class='accent' />
</svg>)";

    string name = "Max Xu", title = "Full Stack Developer", tagline = "Student at UofT";
    string email = "hmaxxu@gmail.com", website = "maxxu.vercel.app";

    string customizedSvg = regex_replace(svgTemplate, regex("\\{\\{NAME\\}\\}"), name);
    customizedSvg = regex_replace(customizedSvg, regex("\\{\\{TITLE\\}\\}"), title);
    customizedSvg = regex_replace(customizedSvg, regex("\\{\\{TAGLINE\\}\\}"), tagline);
    customizedSvg = regex_replace(customizedSvg, regex("\\{\\{EMAIL\\}\\}"), email);
    customizedSvg = regex_replace(customizedSvg, regex("\\{\\{WEBSITE\\}\\}"), website);

    try {
        Image image;
        image.density(densityValue); 
        image.size(Geometry(targetWidth, targetHeight));
        image.magick("SVG");
        image.backgroundColor("none");

        Blob blob(customizedSvg.c_str(), customizedSvg.length());
        image.read(blob);

        image.magick("PNG");
        image.write("namecard.png");
        
        cout << "Output dimensions: " << targetWidth << "x" << targetHeight << " (3:1 aspect ratio)" << endl;
    } catch (Exception &error) {
        cerr << "ImageMagick Error: " << error.what() << endl;
        return 1;
    }

    return 0;
}
