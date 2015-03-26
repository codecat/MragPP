#ifndef MRAGPP_SETTINGS_H_INCLUDED
#define MRAGPP_SETTINGS_H_INCLUDED

#include "StdH.h"

MRAGPP_NAMESPACE_BEGIN;

class MRAGPP_EXPORT CSettings;
class MRAGPP_EXPORT CSettingsValue
{
  friend class CSettings;
private:
  CSettings* owner;
  Scratch::CString value;

public:
  CSettingsValue();
  CSettingsValue(CSettings* pOwner);

  void Set(int iValue);
  void Set(float fValue);
  void Set(bool bValue);
  void Set(const Scratch::CString &strValue);

  int GetInt();
  float GetFloat();
  bool GetBool();
  Scratch::CString GetString();

private:
  void SetChanged();
};

class MRAGPP_EXPORT CSettings
{
  friend class CSettingsValue;
private:
  Scratch::CDictionary<Scratch::CString, CSettingsValue> set_values;
  bool set_saved;

public:
  CSettings();
  CSettings(const Scratch::CString &strFilename);
  ~CSettings();

  void Load(const Scratch::CString &strFilename);
  void Save();

  CSettingsValue &operator [](const Scratch::CString &key);
};

MRAGPP_NAMESPACE_END;

#endif
