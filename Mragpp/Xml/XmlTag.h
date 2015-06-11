#ifndef MRAGPP_XMLTAG_H_INCLUDED
#define MRAGPP_XMLTAG_H_INCLUDED

#include "../StdH.h"

MRAGPP_NAMESPACE_BEGIN;

struct XmlQueryPair
{
  Scratch::String strName;
  Scratch::String strAttrib;
  Scratch::String strValue;
  bool bLookingForAttribute;
  bool bLookingForValue;
};

class XmlFile;
class MRAGPP_EXPORT XmlTag
{
  friend class XmlFile;
public:
  bool IsValid;

  Scratch::String Name;
  Scratch::String Value;
  bool IsComment;

  XmlTag* Parent;
  Scratch::Dictionary<Scratch::String, Scratch::String> Attributes;
  Scratch::StackArray<XmlTag> Children;

  XmlTag();
  XmlTag(XmlTag* parent);
  ~XmlTag();

  void SetParent(XmlTag* parent);

  XmlTag* FindTagByName(const Scratch::String &strName);
  XmlTag* FindTagByNameAndAttribute(const Scratch::String &strName, const Scratch::String &strAttrib, const Scratch::String &strValue);
  XmlTag* FindTagByNameAndExistingAttribute(const Scratch::String &strName, const Scratch::String &strAttrib);
  XmlTag* FindTagByAttribute(const Scratch::String &strAttrib, const Scratch::String &strValue);

  XmlTag* FindChildByName(const Scratch::String &strName);

  void FindTagsByName(const Scratch::String &strName, Scratch::StackArray<XmlTag> &result);
  void FindTagsByAttribute(const Scratch::String &strAttrib, const Scratch::String &strValue, Scratch::StackArray<XmlTag> &result);

  void FindChildrenByName(const Scratch::String &strName, Scratch::StackArray<XmlTag> &result);
  void FindChildrenByAttribute(const Scratch::String &strAttrib, const Scratch::String &strValue, Scratch::StackArray<XmlTag> &result);

  XmlTag* Query(const Scratch::String &strQuery);
  XmlQueryPair QueryParse(const Scratch::String &strQuery);
  XmlTag* QueryPairExecute(const XmlQueryPair &pair);
  XmlTag &operator[](const Scratch::String &strQuery);

private:
  void Parse(Scratch::Stream &fs);
};

MRAGPP_NAMESPACE_END;

#endif
