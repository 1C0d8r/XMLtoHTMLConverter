#include "CppUnitTest.h"
#include "HTMLProcessor.h"
#include "XMLProcessor.h"
#include "tinyxml2.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:

		TEST_METHOD(TestGoodXMLFileloading)
		{
			
			//to do file operations
			fstream m_OutputFile;
			m_OutputFile.open("cd_sampledata.xml", ios::out);
			if (!m_OutputFile)
			{
				cout << "File creation failed" << endl;
			}
			else
			{
				cout << "New file created" << endl;;

				m_OutputFile << "<CATALOG>" << endl;
				m_OutputFile << "<CD>" << endl;
				m_OutputFile << "<TITLE>Mad Dogsand Englishmen</TITLE>" << endl;
				m_OutputFile << "<ARTIST>Joe Cocker</ARTIST>" << endl;
				m_OutputFile << "<COMPANY>A& amp; M</COMPANY>" << endl;
				m_OutputFile << "<COUNTRY>USA</COUNTRY>" << endl;
				m_OutputFile << "<PRICE>9.80</PRICE >" << endl;
				//m_OutputFile << "<CATALOG>" << endl;
				m_OutputFile << "</CD>" << endl;
				m_OutputFile << "</CATALOG>" << endl;
				m_OutputFile.close();
			}

			
			//stream htmlStylefile(inputFileName);
			XMLProcessor xmlProc("cd_sampledata.xml");

			//Load XML File
			int result = xmlProc.LoadXML();
			Assert::AreEqual(0, result);
			
		}

		TEST_METHOD(TestNonExistXMLfileLoading)
		{
			const char inputFileName[] = "nonexistant";

			//Create our XML Processor object
			XMLProcessor xmlProc(inputFileName);

			//Load XML File
			int result = xmlProc.LoadXML();
			Assert::AreNotEqual(result, 0);
		}

		TEST_METHOD(TestBadFormatXMLfileLoading)
		{
			//to do file operations
			fstream m_OutputFile;
			m_OutputFile.open("cd_sampledata.xml", ios::out);
			if (!m_OutputFile)
			{
				cout << "File creation failed" << endl;
			}
			else
			{
				cout << "New file created" << endl;;

				m_OutputFile << "<CATALOG>" << endl;
				m_OutputFile << "<CD>" << endl;
				m_OutputFile << "<TITLE>Mad Dogsand Englishmen</TITLE>" << endl;
				m_OutputFile << "<ARTIST>Joe Cocker</ARTIST>" << endl;
				m_OutputFile << "<COMPANY>A& amp; M</COMPANY>" << endl;
				m_OutputFile << "<COUNTRY>USA</COUNTRY>" << endl;
				m_OutputFile << "<PRICE>9.80</PRICE >" << endl;
				//m_OutputFile << "<CATALOG>" << endl;
				//intentionally removed
				//m_OutputFile << "</CD>" << endl;
				//m_OutputFile << "</CATALOG>" << endl;
				m_OutputFile.close();
			}

			//Create our XML Processor object
			XMLProcessor xmlProc("cd_sampledata.xml");

			//Load XML File
			int result = xmlProc.LoadXML();
			Assert::AreNotEqual(result, 0);
		}

		TEST_METHOD(VerifyCreatedHTMLTableObjects)
		{
			//create xml
						//to do file operations
			fstream m_OutputFile;
			m_OutputFile.open("cd_sampledata.xml", ios::out);
			if (!m_OutputFile)
			{
				cout << "File creation failed" << endl;
			}
			else
			{
				cout << "New file created" << endl;;

				m_OutputFile << "<CATALOG>" << endl;
				m_OutputFile << "<CD>" << endl;
				m_OutputFile << "<TITLE>Mad Dogsand Englishmen</TITLE>" << endl;
				m_OutputFile << "<ARTIST>Joe Cocker</ARTIST>" << endl;
				m_OutputFile << "<COMPANY>A& amp; M</COMPANY>" << endl;
				m_OutputFile << "<COUNTRY>USA</COUNTRY>" << endl;
				m_OutputFile << "<PRICE>9.80</PRICE >" << endl;
				//m_OutputFile << "<CATALOG>" << endl;
				m_OutputFile << "</CD>" << endl;
				m_OutputFile << "</CATALOG>" << endl;
				m_OutputFile.close();
			}

			//Load all objects
			XMLProcessor xmlProc("cd_sampledata.xml");

			//Load XML File
			int result = xmlProc.LoadXML();

			Assert::AreEqual(0, result);

			//Convert XML element to HTML element objects
			HTMLProcessor::HTMLTableHeader htmlTBHeader;
			std::vector<HTMLProcessor::HTMLTableData> htmlTBData;

			xmlProc.CreateHTMLElements(htmlTBHeader, htmlTBData);

			Assert::AreEqual(std::string("TITLE"), htmlTBHeader.m_headerData[0]);
			Assert::AreEqual(std::string("ARTIST"), htmlTBHeader.m_headerData[1]);
			Assert::AreEqual(std::string("COMPANY"), htmlTBHeader.m_headerData[2]);
			Assert::AreEqual(std::string("COUNTRY"), htmlTBHeader.m_headerData[3]);
			Assert::AreEqual(std::string("PRICE"), htmlTBHeader.m_headerData[4]);

			Assert::AreEqual(std::string("Mad Dogsand Englishmen"), htmlTBData[0].m_tableData["TITLE"]);
			Assert::AreEqual(std::string("Joe Cocker"), htmlTBData[0].m_tableData["ARTIST"]);
			Assert::AreEqual(std::string("A& amp; M"), htmlTBData[0].m_tableData["COMPANY"]);
			Assert::AreEqual(std::string("USA"), htmlTBData[0].m_tableData["COUNTRY"]);
			Assert::AreEqual(std::string("9.80"), htmlTBData[0].m_tableData["PRICE"]);
		}
		
	};
}
