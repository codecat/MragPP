#ifndef MRAGPP_XMLFILE_H_INCLUDED
#define MRAGPP_XMLFILE_H_INCLUDED

#include "../StdH.h"
#include "XmlTag.h"

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT XmlFile
{
public:
  XmlTag* Decleration;
  XmlTag* Root;

  XmlFile();
  XmlFile(const Scratch::CString &strFilename);
  ~XmlFile();

  void Load(const Scratch::CString &strFilename);
  void Unload();

  void Save(const Scratch::CString &strFilename);

  void PrintToConsole(XmlTag &root, int depth);
  void PrintToConsole();

  XmlTag* Query(const Scratch::CString &strQuery);
  XmlTag &operator[](const Scratch::CString &strQuery);
};

MRAGPP_NAMESPACE_END;

#endif
