#include "../StdH.h"
#include "XmlTag.h"
#include "XmlHelpers.h"

using namespace Scratch;

MRAGPP_NAMESPACE_BEGIN;

XmlTag::XmlTag()
{
  IsValid = false;
  IsComment = false;
  Parent = 0;
  Attributes.dic_bAllowDuplicateKeys = TRUE;
}

XmlTag::XmlTag(XmlTag* parent)
{
  SetParent(parent);
  Attributes.dic_bAllowDuplicateKeys = TRUE;
}

XmlTag::~XmlTag()
{
}

void XmlTag::SetParent(XmlTag* parent)
{
  IsValid = true;
  Parent = parent;
}

XmlTag* XmlTag::FindTagByName(const String &strName)
{
  XmlTag* pChild = FindChildByName(strName);
  if(pChild != 0) {
    return pChild;
  }

  for(int i=0; i<Children.Count(); i++) {
    XmlTag &tag = Children[i];
    if(tag.Children.Count() == 0) {
      continue;
    }

    XmlTag* ret = tag.FindTagByName(strName);
    if(ret != 0) {
      return ret;
    }
  }

  return 0;
}

XmlTag* XmlTag::FindTagByNameAndAttribute(const String &strName, const String &strAttrib, const String &strValue)
{
  StackArray<XmlTag> tags;
  FindTagsByName(strName, tags);

  for(int i=0; i<tags.Count(); i++) {
    XmlTag &tag = tags[i];
    if(tag.Attributes.HasKey(strAttrib) && tag.Attributes[strAttrib] == strValue) {
      return &tag;
    }
  }

  return 0;
}

XmlTag* XmlTag::FindTagByNameAndExistingAttribute(const Scratch::String &strName, const Scratch::String &strAttrib)
{
  StackArray<XmlTag> tags;
  FindTagsByName(strName, tags);

  for(int i=0; i<tags.Count(); i++) {
    XmlTag &tag = tags[i];
    if(tag.Attributes.HasKey(strAttrib)) {
      return &tag;
    }
  }

  return 0;
}

XmlTag* XmlTag::FindTagByAttribute(const String &strAttrib, const String &strValue)
{
  for(int i=0; i<Children.Count(); i++) {
    XmlTag &tag = Children[i];
    if(tag.Attributes.HasKey(strAttrib) && tag.Attributes[strAttrib] == strValue) {
      return &tag;
    }
  }

  for(int i=0; i<Children.Count(); i++) {
    XmlTag &tag = Children[i];
    if(tag.Children.Count() == 0) {
      continue;
    }

    XmlTag* ret = tag.FindTagByAttribute(strAttrib, strValue);
    if(ret != 0) {
      return ret;
    }
  }

  return 0;
}

XmlTag* XmlTag::FindChildByName(const Scratch::String &strName)
{
  for(int i=0; i<Children.Count(); i++) {
    XmlTag &tag = Children[i];
    if(tag.Name == strName) {
      return &tag;
    }
  }

  return 0;
}

void XmlTag::FindTagsByName(const String &strName, StackArray<XmlTag> &result)
{
  FindChildrenByName(strName, result);

  for(int i=0; i<Children.Count(); i++) {
    XmlTag &tag = Children[i];
    if(tag.Children.Count() == 0) {
      continue;
    }

    tag.FindTagsByName(strName, result);
  }
}

void XmlTag::FindTagsByAttribute(const String &strAttrib, const String &strValue, StackArray<XmlTag> &result)
{
  FindChildrenByAttribute(strAttrib, strValue, result);

  for(int i=0; i<Children.Count(); i++) {
    XmlTag &tag = Children[i];
    if(tag.Children.Count() == 0) {
      continue;
    }

    tag.FindTagsByAttribute(strAttrib, strValue, result);
  }
}

void XmlTag::FindChildrenByName(const Scratch::String &strName, Scratch::StackArray<XmlTag> &result)
{
  // force the stack array to only pop, not clear!
  // this is because we add absolute pointers to XmlTag objects in below code and we don't want them to be deleted at the end of the scope
  result.sa_bOnlyPop = TRUE;

  for(int i=0; i<Children.Count(); i++) {
    XmlTag &tag = Children[i];
    if(tag.Name == strName) {
      result.Push(&tag);
    }
  }
}

void XmlTag::FindChildrenByAttribute(const Scratch::String &strAttrib, const Scratch::String &strValue, Scratch::StackArray<XmlTag> &result)
{
  // note comment in FindChildrenByName
  result.sa_bOnlyPop = TRUE;

  for(int i=0; i<Children.Count(); i++) {
    XmlTag &tag = Children[i];
    if(tag.Attributes.HasKey(strAttrib) && tag.Attributes[strAttrib] == strValue) {
      result.Push(&tag);
    }
  }
}

XmlTag* XmlTag::Query(const Scratch::String &strQuery)
{
  StackArray<String> parse;
  strQuery.Split("/", parse, TRUE);

  XmlTag* tag = this;
  for(int i=0; tag!=0 && i<parse.Count(); i++) {
    tag = tag->QueryPairExecute(tag->QueryParse(parse[i]));
  }

  return tag;
}

XmlQueryPair XmlTag::QueryParse(const Scratch::String &strQuery)
{
  XmlQueryPair ret;
  ret.bLookingForAttribute = false;
  ret.bLookingForValue = false;

  bool bReadingName = true;
  bool bReadingAttribValue = false;

  for(int i=0; i<(int)strlen(strQuery); i++) {
    char c = strQuery[i];

    if(bReadingName) {
      if(c == '[') {
        ret.bLookingForAttribute = true;
        bReadingName = false;
      } else {
        ret.strName += c;
      }
    } else {
      if(bReadingAttribValue) {
        if(c == ']') {
          break;
        } else {
          ret.strValue += c;
        }
      } else {
        if(c == '=') {
          ret.bLookingForValue = true;
          bReadingAttribValue = true;
        } else if(c == ']') {
          break;
        } else {
          ret.strAttrib += c;
        }
      }
    }
  }

  return ret;
}

#if !WINDOWS
bool isdigit(char c)
{
  return c >= 48 && c <= 57;
}
#endif

XmlTag* XmlTag::QueryPairExecute(const XmlQueryPair &pair)
{
  ASSERT(pair.strName != "");

  if(!pair.bLookingForAttribute) {
    return FindTagByName(pair.strName);
  } else {
    StackArray<XmlTag> tags;
    FindTagsByName(pair.strName, tags);
    if(!pair.bLookingForValue && isdigit(pair.strAttrib[0])) {
      int iIndex = atoi(pair.strAttrib);
      if(iIndex < tags.Count()) {
        return &tags[iIndex];
      } else {
        return 0;
      }
    }
    if(pair.bLookingForValue) {
      return FindTagByNameAndAttribute(pair.strName, pair.strAttrib, pair.strValue);
    } else {
      return FindTagByNameAndExistingAttribute(pair.strName, pair.strAttrib);
    }
  }
}

XmlTag &XmlTag::operator[](const String &strQuery)
{
  XmlTag* tag = QueryPairExecute(QueryParse(strQuery));
  if(tag == 0) {
    throw "No such tag found";
  } else {
    return *tag;
  }
}

void XmlTag::Parse(Stream &fs)
{
  bool bReadAttributes = true;
  bool bOpenTag = false;

  while(true) {
    if(fs.PeekChar() == '?') {
      // xml decleration is a small exception
      bool bExpected = fs.Expect("?xml ");
      ASSERT(bExpected);

      bReadAttributes = true;
      break;

    } else if(fs.PeekChar() == '!') {
      // xml comment
      bool bExpected = fs.Expect("!--");
      ASSERT(bExpected);

      IsComment = true;
      String strValue;
      String strEnding = "-->";
      int i = 0;
      int iLen = strlen(strEnding);
      while(!fs.AtEOF()) {
        char c = fs.ReadChar();
        if(c == strEnding[i]) {
          i++;
        } else {
          i = 0;
          strValue += c;
        }
        if(i == iLen) {
          break;
        }
      }
      Value = strValue;
      return;

    } else {
      // xml tag
      String strName;
      // read the name of the tag, and get the character we ended with
      char c = fs.ReadUntil(strName, "\r\n\t >/");
      Name = strName;
      if(c == '/') {
        // if it's a slash, it's a closed tag
        bReadAttributes = false;
        bOpenTag = false;
      } else if(c == '>') {
        // if it's an end-of-tag character, it's an open tag
        bReadAttributes = false;
        bOpenTag = true;
      }
      break;
    }
  }

  // read attributes
  if(bReadAttributes) {
    ParseAttributes(fs, Attributes, bOpenTag);
  }

  // if open tag
  if(bOpenTag) {
    // start reading the value
    bool bReadValue = true;
    String strValue;

    while(!fs.AtEOF()) {
      char c = fs.ReadChar();

      // check for tag
      if(c == '<') {
        if(fs.PeekChar() == '/') {
          // end of this tag
          bool bExpected = fs.Expect("/" + Name + ">");
          ASSERT(bExpected);
          break;
        } else {
          // don't bother reading this tag's value anymore
          bReadValue = false;
          strValue = "";
          // new tag nested in this tag
          XmlTag &newTag = Children.Push();
          newTag.SetParent(this);
          newTag.Parse(fs);
        }
      } else {
        // add to value if required
        if(bReadValue) {
          strValue += c;
        }
      }
    }

    // set value property
    if(bReadValue) {
      Value = strValue;
    }
  }
}

MRAGPP_NAMESPACE_END;
