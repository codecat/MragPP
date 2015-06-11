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
  Scratch::String value;

public:
  CSettingsValue();
  CSettingsValue(CSettings* pOwner);

  void Set(int iValue);
  void Set(float fValue);
  void Set(bool bValue);
  void Set(const Scratch::String &strValue);

  int GetInt();
  float GetFloat();
  bool GetBool();
  Scratch::String GetString();

private:
  void SetChanged();
};

class MRAGPP_EXPORT CSettings
{
  friend class CSettingsValue;
private:
  Scratch::Dictionary<Scratch::String, CSettingsValue> set_values;
  bool set_saved;

public:
  CSettings();
  CSettings(const Scratch::String &strFilename);
  ~CSettings();

  void Load(const Scratch::String &strFilename);
  void Save();

  CSettingsValue &operator [](const Scratch::String &key);
};

MRAGPP_NAMESPACE_END;

#endif
