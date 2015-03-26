#include "../StdH.h"
#include "XmlHelpers.h"

using namespace Scratch;

MRAGPP_NAMESPACE_BEGIN;

void ParseAttributes(CStream &fs, CDictionary<CString, CString> &out_attrs, bool &out_bOpenTag)
{
  CString strKey;
  CString strValue;
  bool bReadingKey = true;
  bool bReadingString = false;

  while(!fs.AtEOF()) {
    char c = fs.ReadChar();

    if(bReadingKey) {
      if(c == '=') {
        bReadingKey = false;
        if(fs.PeekChar() == '"') {
          bReadingString = true;
          fs.ReadChar();
        }

      } else if(c == ' ') {
        if(strlen(strKey) > 0) {
          // add empty attribute
          out_attrs.Add(strKey, "");
          strKey = "";
        }

      } else if(c == '/' || c == '?') {
        bool bExpected = fs.Expect(">");
        ASSERT(bExpected);
        out_bOpenTag = false;
        break;

      } else if(c == '>') {
        out_bOpenTag = true;
        break;

      } else {
        if(c != '\r' && c != '\n' && c != '\t') {
          strKey += c;
        }
      }

    } else {
      bool bAddAttrib = false;

      if(c == '"' || (c == ' ' && !bReadingString) || (c == '/' && !bReadingString)) {
        bAddAttrib = true;
      } else {
        strValue += c;
      }

      if(bAddAttrib) {
        bReadingKey = true;
        bReadingString = false;

        // add attribute with value
        out_attrs.Add(strKey, strValue);

        strKey = "";
        strValue = "";
      }
    }
  }
}

MRAGPP_NAMESPACE_END;
