#pragma once
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include"HTMLProcessor.h"

using namespace std;
using namespace tinyxml2;

class	XMLProcessor
{
public:
   XMLProcessor(const char* fileName);
   int LoadXML();

   //Iterate through the XML and create the Header and Data objects
   bool CreateHTMLElements(HTMLProcessor::HTMLTableHeader& htmlTBHeader, std::vector<HTMLProcessor::HTMLTableData>& htmlTBData);

protected:
   const char* m_inputXMLfileName;
   XMLDocument m_doc;


};