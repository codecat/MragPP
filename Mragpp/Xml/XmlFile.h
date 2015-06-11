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
  XmlFile(const Scratch::String &strFilename);
  ~XmlFile();

  void Load(const Scratch::String &strFilename);
  void Unload();

  void Save(const Scratch::String &strFilename);

  void PrintToConsole(XmlTag &root, int depth);
  void PrintToConsole();

  XmlTag* Query(const Scratch::String &strQuery);
  XmlTag &operator[](const Scratch::String &strQuery);
};

MRAGPP_NAMESPACE_END;

#endif
