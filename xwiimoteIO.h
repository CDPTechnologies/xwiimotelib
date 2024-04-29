#ifndef XWIIMOTELIB_XWIIMOTEIO_H
#define XWIIMOTELIB_XWIIMOTEIO_H

#include <CDPSystem/Base/CDPComponent.h>
#include <CDPSystem/Base/CDPProperty.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>
#include "xwiimote/lib/xwiimote.h"

#include <optional>

namespace xwiimotelib {

class xwiimoteIO : public CDPComponent
{
public:
  xwiimoteIO();
  ~xwiimoteIO() override;

  void Create(const char* fullName) override;
  void CreateModel() override;
  void Configure(const char* componentXML) override;
  void ProcessNull() override;
  void Destroy() override;

protected:
  CDPProperty<std::string> m_device;
  CDPSignal<bool> m_home;
  CDPSignal<bool> m_a;
  CDPSignal<bool> m_left;
  CDPSignal<bool> m_right;
  CDPSignal<bool> m_up;
  CDPSignal<bool> m_down;
  CDPSignal<bool> m_one;
  CDPSignal<bool> m_two;
  CDPSignal<int> m_accelX;
  CDPSignal<int> m_accelY;
  CDPSignal<int> m_accelZ;
  CDPSignal<bool> m_nunchukC;
  CDPSignal<bool> m_nunchukZ;
  CDPSignal<int> m_nunchukJoyX;
  CDPSignal<int> m_nunchukJoyY;
  CDPSignal<int> m_nunchukAccelX;
  CDPSignal<int> m_nunchukAccelY;
  CDPSignal<int> m_nunchukAccelZ;
  CDPSignal<bool> m_rumble;

  struct xwii_iface *m_iface{nullptr};
  std::optional<bool> m_lastRumble;
};

} // namespace xwiimotelib

#endif
