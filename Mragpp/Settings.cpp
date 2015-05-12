#include "StdH.h"
#include "Settings.h"

using namespace Scratch;

MRAGPP_NAMESPACE_BEGIN;

CSettingsValue::CSettingsValue()
{
  owner = NULL;
}

CSettingsValue::CSettingsValue(CSettings* pOwner)
{
  owner = pOwner;
}

void CSettingsValue::Set(int iValue)
{
  value.SetF("%d", iValue);
}

void CSettingsValue::Set(float fValue)
{
  value.SetF("%f", fValue);
}

void CSettingsValue::Set(bool bValue)
{
  if(bValue) {
    value = "True";
  } else {
    value = "False";
  }
}

void CSettingsValue::Set(const CString &strValue)
{
  value = strValue;
}

int CSettingsValue::GetInt()
{
  return atoi(value);
}

float CSettingsValue::GetFloat()
{
  return (float)atof(value);
}

bool CSettingsValue::GetBool()
{
  return value.ToLower() == "true";
}

Scratch::CString CSettingsValue::GetString()
{
  return value;
}

void CSettingsValue::SetChanged()
{
  if(owner != NULL) {
    owner->set_saved = false;
  }
}

CSettings::CSettings()
{
  set_saved = false;
}

CSettings::CSettings(const CString &strFilename)
{
  Load(strFilename);
}

CSettings::~CSettings()
{
  ASSERT(set_saved);
}

void CSettings::Load(const CString &strFilename)
{
  CFileStream fs;
  if(!fs.Open(strFilename, "r")) {
    return;
  }

  while(!fs.AtEOF()) {
    CString strLine = fs.ReadLine();

    if(strlen(strLine) == 0 || strLine[0] == '#') {
      continue;
    }

    CStackArray<CString> aParse;
    strLine.Split("=", aParse);

    CSettingsValue &val = set_values[aParse[0]];
    val.owner = this;
    if(aParse.Count() == 2) {
      val.value = aParse[1];
    }
  }

  fs.Close();

  set_saved = true;
}

void CSettings::Save()
{
  set_saved = true;
}

CSettingsValue &CSettings::operator [](const CString &key)
{
  return set_values[key];
}

MRAGPP_NAMESPACE_END;
