#include "XMLProcessor.h"
#include "tinyxml2.h"
#include "HTMLProcessor.h"

XMLProcessor::XMLProcessor(const char* fileName)
{
   this->m_inputXMLfileName = fileName;
}

int XMLProcessor::LoadXML()
{
   m_doc.LoadFile(this->m_inputXMLfileName);

   std::cout << "INPUT:\n" << m_inputXMLfileName << "\n";

   //If no root element found return Error
   XMLElement* pRoot = m_doc.FirstChildElement();
   if (pRoot == nullptr)
   {
      return XML_ERROR_FILE_READ_ERROR;
   }

   return 0;
}

bool XMLProcessor::CreateHTMLElements(HTMLProcessor::HTMLTableHeader& htmlTBHeader, std::vector<HTMLProcessor::HTMLTableData>& htmlTBData)
{
   XMLElement* pRoot = m_doc.FirstChildElement();

   if (pRoot != NULL)
   {
      for (tinyxml2::XMLNode* child = pRoot->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
      {
         HTMLProcessor::HTMLTableData TBdata;
         for (tinyxml2::XMLElement* subChild = child->FirstChildElement(); subChild != NULL; subChild = subChild->NextSiblingElement())
         {
            auto it = find(htmlTBHeader.m_headerData.begin(), htmlTBHeader.m_headerData.end(), subChild->Name());
            if (it == htmlTBHeader.m_headerData.end())
            {
               htmlTBHeader.m_headerData.push_back(subChild->Name());
            }
                       
            TBdata.m_tableData.insert(std::pair<std::string, std::string>(subChild->Name(), subChild->GetText()));
         }

         htmlTBData.push_back(TBdata);
      }
   }

   return true;
}

