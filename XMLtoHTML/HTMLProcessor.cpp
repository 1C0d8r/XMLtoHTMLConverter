#include "HTMLProcessor.h"
#include <fstream>

HTMLProcessor::HTMLProcessor(const char* OutputFileName, const char* htmlStyleSheetFileName)
{
   this->m_OutputHTMLfileName = OutputFileName;

   m_OutputFile.open(m_OutputHTMLfileName, ios::out);
   if (!m_OutputFile)
   {
      cout << "File creation failed" << endl;
      
   }
   else
   {
      cout << "New file created" << endl;;
   }

   m_StyleSheetFileName = htmlStyleSheetFileName;

}


void HTMLProcessor::GetHTMLStylingSheetToString(std::string &styleString)
{
   styleString = "";

   if(m_StyleSheetFileName != "")
   {
      ifstream htmlStylefile(m_StyleSheetFileName);      
      int i;

      for (i = 0; htmlStylefile.eof() != true; i++) // get content of infile
         styleString += htmlStylefile.get();

      i--;
      styleString.erase(styleString.end() - 1);     // erase last character

      cout << i << " characters read...\n";
      htmlStylefile.close();
   }
   else
   {
      styleString.append("<style>\n");
      styleString.append("table, th, td {\n");
      styleString.append("  border: 1px solid black;\n");
      styleString.append("  border-collapse: collapse;\n");
      styleString.append("}\n");
      styleString.append("</style>\n");
/*
         th, td{
           padding: 5px;
           text - align: left;
      }
         < / style>*/
   }

}
void HTMLProcessor::GenerateOutputHTML(HTMLProcessor::HTMLTableHeader& htmlTBHeader, std::vector<HTMLProcessor::HTMLTableData>& htmlTBData)
{
   //Writing to file
   m_OutputFile << "<!DOCTYPE html>" << endl;
   m_OutputFile << "<html>" << endl;
   m_OutputFile << "<head>" << endl;
   std::string styleContent;
   GetHTMLStylingSheetToString(styleContent);

   m_OutputFile << styleContent << endl;
   m_OutputFile << "<body>" << endl;
   m_OutputFile << "<table>" << endl;

   m_OutputFile << "<tr>" << endl;
   // Need to print out header data into the HTML file 
   for (auto it = std::begin(htmlTBHeader.m_headerData); it != std::end(htmlTBHeader.m_headerData); ++it)
   {
      //we need off the format
      std::string hdString= "<th>";
      hdString.append(*it);
      hdString.append("</th>");

      m_OutputFile << hdString << endl;
   }
   m_OutputFile << "</tr>" << endl;

   //Now we need to print out the actual Tabale data to the file
   //This solution is generic enough that it can work on any kind of XML files
   //Iterate through all of the Table data
   for (auto it = std::begin(htmlTBData); it != std::end(htmlTBData); ++it) 
   {
      m_OutputFile << "<tr>" << endl;
      // Need to print out the data in order otherwise so we will try to print based on the order in Header data vector
      for (auto headerDataiter = std::begin(htmlTBHeader.m_headerData); headerDataiter != std::end(htmlTBHeader.m_headerData); ++headerDataiter)
      {
         auto tableDataIter = it->m_tableData.find(*headerDataiter);

         if (tableDataIter != it->m_tableData.end())
         {
            //we need off the format
            std::string tdString = "<td>";
            tdString.append(tableDataIter->second);
            tdString.append("</td>");
            m_OutputFile << tdString << endl;
         }
      }
      m_OutputFile << "</tr>" << endl;
   }

   //close remaining tags
   m_OutputFile << "</table>" << endl;
   m_OutputFile << "</body>" << endl;
   m_OutputFile << "</html>" << endl;

   //finally close the file
   m_OutputFile.close();
   cout << "Data Conversion finished" << endl;;
}

