//  g++ -Wall -O2 contrib/html5-printer.cpp -o html5-printer -ltinyxml2

//  This program demonstrates converts xml file to html file without using XSLT template
//  by using tinyxml2 library

//  Author: Rakesh Kumar Reddy Gowra, raki.gowra@gmail.com
//  License: Same as tinyxml2 

/*
This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any
damages arising from the use of this software.

Permission is granted to anyone to use this software for any
purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/


#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include "XMLProcessor.h"
#include "HTMLProcessor.h"

using namespace std;
using namespace tinyxml2;


int main(int argc, char* argv[])
{

   if (argc <= 1)
   {
      // On some operating systems, argv[0] can end up as an empty string instead of the program's name.
      // We'll conditionalize our response on whether argv[0] is empty or not.
      if (argv[0])
         std::cout << "Usage: " << argv[0] << " cd_catalog.xml  htmlStyle.txt" << '\n';
      else
         std::cout << "Usage: XMLtoHTML.exe  inputXMLFileName.xml" << '\n';
   }

   std::cout << "Out put file name will be" << " Output.html" << endl;

    //Create our XML Processor object
    XMLProcessor xmlProc(argv[1]);
    
    //Load XML File
    int result = xmlProc.LoadXML();

    if (result != 0)
    {
       cout << "Could not read XML File due to Error Code " << result << endl;
    }

    //Convert XML element to HTML element objects
    HTMLProcessor::HTMLTableHeader htmlTBHeader;
    std::vector<HTMLProcessor::HTMLTableData> htmlTBData;

    xmlProc.CreateHTMLElements(htmlTBHeader, htmlTBData);
    
    //Now create HTML Processor object
    const char outputFileName[] = "Output.html";

    //if arg[2] is provided we will use it for styling or else we will use default styling
    if (argv[2])
    {
       HTMLProcessor htmlProc(outputFileName, argv[2]);
       htmlProc.GenerateOutputHTML(htmlTBHeader, htmlTBData);
    }
    else
    {
       HTMLProcessor htmlProc(outputFileName,"");
       htmlProc.GenerateOutputHTML(htmlTBHeader, htmlTBData);
    }
    return 0;
}
