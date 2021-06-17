#pragma once
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
using namespace tinyxml2;

//Helper class that processes the HTML output
//Support the creation of HTML Table TD (table data) and  TR(table row) objects
//Support the creation of HTML Table TD Tag objects
class	HTMLProcessor
{
public:

   HTMLProcessor(const char* OutputFileName, const char* htmlStyleSheetFileName);

   struct HTMLTableHeader
   {
      //We need to preserve the order can't use map
      //find might be slow but we don't ususally have much header data
      std::vector<string> m_headerData;
   };

   struct HTMLTableData
   {
      //Key is the Header string
      //value is value string 
      std::map<string, string> m_tableData;
   };

   //Finally this is the actual method that can generate the output html file
   void GenerateOutputHTML(HTMLProcessor::HTMLTableHeader& htmlTBHeader, std::vector<HTMLProcessor::HTMLTableData>& htmlTBData);

private:
   //to store output file name
   const char* m_OutputHTMLfileName;

   //to store output file name
   const char* m_StyleSheetFileName;

   //Load HTML Styling document into the current output file
   //Note that this need to be loaded after printing the the <html> tags 
   void GetHTMLStylingSheetToString(std::string& styleString);

   //to do file operations
   fstream m_OutputFile;


};


