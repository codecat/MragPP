#ifndef MRAGPP_XMLTAG_H_INCLUDED
#define MRAGPP_XMLTAG_H_INCLUDED

#include "../StdH.h"

MRAGPP_NAMESPACE_BEGIN;

struct XmlQueryPair
{
  Scratch::CString strName;
  Scratch::CString strAttrib;
  Scratch::CString strValue;
  bool bLookingForAttribute;
  bool bLookingForValue;
};

class XmlFile;
class MRAGPP_EXPORT XmlTag
{
  friend class XmlFile;
public:
  bool IsValid;

  Scratch::CString Name;
  Scratch::CString Value;
  bool IsComment;

  XmlTag* Parent;
  Scratch::CDictionary<Scratch::CString, Scratch::CString> Attributes;
  Scratch::CStackArray<XmlTag> Children;

  XmlTag();
  XmlTag(XmlTag* parent);
  ~XmlTag();

  void SetParent(XmlTag* parent);

  XmlTag* FindTagByName(const Scratch::CString &strName);
  XmlTag* FindTagByNameAndAttribute(const Scratch::CString &strName, const Scratch::CString &strAttrib, const Scratch::CString &strValue);
  XmlTag* FindTagByNameAndExistingAttribute(const Scratch::CString &strName, const Scratch::CString &strAttrib);
  XmlTag* FindTagByAttribute(const Scratch::CString &strAttrib, const Scratch::CString &strValue);

  XmlTag* FindChildByName(const Scratch::CString &strName);

  void FindTagsByName(const Scratch::CString &strName, Scratch::CStackArray<XmlTag> &result);
  void FindTagsByAttribute(const Scratch::CString &strAttrib, const Scratch::CString &strValue, Scratch::CStackArray<XmlTag> &result);

  void FindChildrenByName(const Scratch::CString &strName, Scratch::CStackArray<XmlTag> &result);
  void FindChildrenByAttribute(const Scratch::CString &strAttrib, const Scratch::CString &strValue, Scratch::CStackArray<XmlTag> &result);

  XmlTag* Query(const Scratch::CString &strQuery);
  XmlQueryPair QueryParse(const Scratch::CString &strQuery);
  XmlTag* QueryPairExecute(const XmlQueryPair &pair);
  XmlTag &operator[](const Scratch::CString &strQuery);

private:
  void Parse(Scratch::CStream &fs);
};

MRAGPP_NAMESPACE_END;

#endif
