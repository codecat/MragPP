#ifndef MRAGPP_XMLHELPERS_H_INCLUDED
#define MRAGPP_XMLHELPERS_H_INCLUDED

#include "../StdH.h"

MRAGPP_NAMESPACE_BEGIN;

void ParseAttributes(Scratch::CStream &fs, Scratch::CDictionary<Scratch::CString, Scratch::CString> &out_attrs, bool &out_bOpenTag);

MRAGPP_NAMESPACE_END;

#endif
