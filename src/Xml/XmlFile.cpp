#include "../StdH.h"
#include "XmlFile.h"

using namespace Scratch;

MRAGPP_NAMESPACE_BEGIN;

XmlFile::XmlFile()
{
  Decleration = 0;
  Root = 0;
}

XmlFile::XmlFile(const CString &strFilename)
{
  Decleration = 0;
  Root = 0;
  Load(strFilename);
}

XmlFile::~XmlFile()
{
  Unload();
}

void XmlFile::Load(const CString &strFilename)
{
  Unload();

  Root = new XmlTag(0);

  CFileStream fs;
  fs.Open(strFilename, "r");
  while(!fs.AtEOF()) {
    char c = fs.ReadChar();

    if(c == '<') {
      if(fs.PeekChar() == '?') {
        ASSERT(Decleration == 0);
        Decleration = new XmlTag();
        Decleration->Parse(fs);
      } else {
        XmlTag &newTag = Root->Children.Push();
        newTag.SetParent(Root);
        newTag.Parse(fs);
      }
    }
  }
  fs.Close();
}

void XmlFile::Unload()
{
  if(Decleration != 0) {
    delete Decleration;
    Decleration = 0;
  }
  if(Root != 0) {
    delete Root;
    Root = 0;
  }
}

void XmlFile::Save(const CString &strFilename)
{
  //TODO
}

void XmlFile::PrintToConsole(XmlTag &root, int depth)
{
  CString strStart;
  for(int i=0; i<depth; i++) {
    strStart += "-- ";
  }

  for(int i=0; i<root.Children.Count(); i++) {
    XmlTag &tag = root.Children[i];
    printf("%s%s\n", (const char*)strStart, (const char*)(tag.IsComment ? "(comment)" : tag.Name));

    if(tag.Children.Count() > 0) {
      PrintToConsole(tag, depth + 1);
    }
  }
}

void XmlFile::PrintToConsole()
{
  if(Root->Children.Count() > 0) {
    PrintToConsole(*Root, 0);
  }
}

XmlTag* XmlFile::Query(const Scratch::CString &strQuery)
{
  return Root->Query(strQuery);
}

XmlTag &XmlFile::operator[](const CString &strQuery)
{
  return (*Root)[strQuery];
}

MRAGPP_NAMESPACE_END;
