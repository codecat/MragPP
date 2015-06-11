#ifndef MRAGPP_XMLHELPERS_H_INCLUDED
#define MRAGPP_XMLHELPERS_H_INCLUDED

#include "../StdH.h"

MRAGPP_NAMESPACE_BEGIN;

void ParseAttributes(Scratch::Stream &fs, Scratch::Dictionary<Scratch::String, Scratch::String> &out_attrs, bool &out_bOpenTag);

MRAGPP_NAMESPACE_END;

#endif
