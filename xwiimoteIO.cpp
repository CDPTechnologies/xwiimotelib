#include "xwiimoteIO.h"

using namespace xwiimotelib;

namespace  {

#if INSTALLATION == LINUX
std::string GetWiimoteDevicePath(unsigned char num)
{
  struct xwii_monitor *mon;
  char *ent;
  int i = 0;

  mon = xwii_monitor_new(false, false);
  if (!mon)
  {
    CDPMessage("ERROR: Cannot create xwii_monitor\n");
    return {};
  }

  while ((ent = xwii_monitor_poll(mon)))
  {
    if (++i == num)
      break;
    free(ent);
  }
  xwii_monitor_unref(mon);
  return ent;
}
#endif

}

/*!
  \class xwiimotelib::xwiimoteIO
  \inmodule xwiimotelib

  \section1 Usage

  Add documentation for xwiimoteIO here.
*/

/*!
  \internal
  \brief Component constructor. The first function to be called. Can be used to initialize member variables, etc.
*/
xwiimoteIO::xwiimoteIO()
{
}


/*!
  \internal
  \brief Component destructor. The last function to be called. Typically used to clean up when stopping, like freeing
  allocated memory, etc.
*/
xwiimoteIO::~xwiimoteIO()
{
}

/*!
  \internal
  \brief Creates the component instance and other related CDP objects. Called after constructor

  Note, that this function is normally filled automatically by the code generator.
*/
void xwiimoteIO::Create(const char* fullName)
{
  CDPComponent::Create(fullName);
  m_device.Create("Device", this);
  m_home.Create("Home",this);
  m_a.Create("A",this);
  m_left.Create("Left",this);
  m_right.Create("Right",this);
  m_up.Create("Up",this);
  m_down.Create("Down",this);
  m_one.Create("One",this);
  m_two.Create("Two",this);
  m_accelX.Create("AccelX",this);
  m_accelY.Create("AccelY",this);
  m_accelZ.Create("AccelZ",this);
  m_nunchukC.Create("NunchukC",this);
  m_nunchukZ.Create("NunchukZ",this);
  m_nunchukJoyX.Create("NunchukJoyX",this);
  m_nunchukJoyY.Create("NunchukJoyY",this);
  m_nunchukAccelX.Create("NunchukAccelX",this);
  m_nunchukAccelY.Create("NunchukAccelY",this);
  m_nunchukAccelZ.Create("NunchukAccelZ",this);
  m_rumble.Create("Rumble",this);
}

/*!
  \internal
  \brief Creates a model instance for this class and fills model data. Registers messages, states and state transitions.

  Note, that this function is normally filled automatically by the code generator.
*/
void xwiimoteIO::CreateModel()
{
  CDPComponent::CreateModel();

  RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&xwiimoteIO::ProcessNull, "Initial Null state");
}

/*!
  \internal
  \brief Configures the component by reading the configuration. Called after Create()/CreateModel().

  Note, that this function is normally filled automatically by the code generator.
*/
void xwiimoteIO::Configure(const char* componentXML)
{
  CDPComponent::Configure(componentXML);
#if INSTALLATION == LINUX
  std::string devicePath;
  try {
    unsigned char wiiNum = std::stod((std::string)m_device);
    devicePath = GetWiimoteDevicePath(wiiNum);
  }
  catch(...)
  {
  }
  if (devicePath.empty())
    devicePath = m_device;
  if (auto ret = xwii_iface_new(&m_iface, devicePath.c_str()))
  {
    CDPMessage("ERROR: Cannot create xwii_iface for device '%s': err: %d\n", devicePath.c_str(), ret);
    return;
  }
  if (auto ret = xwii_iface_open(m_iface, xwii_iface_available(m_iface) | XWII_IFACE_WRITABLE))
  {
    CDPMessage("ERROR: Cannot open xwii_iface for device '%s': err: %d\n", devicePath.c_str(), ret);
    return;
  }
#else
  CDPMessage("ERROR: xwiimotelib was started on unsupported target type!\n");
#endif
}

/*!
 \brief Component Null state processing function
        Read any Xwii new event to signal values.

 Note, that state processing functions are not allowed to block (i.e. read files, sleep, communicate with network in
 blocking mode etc.) For blocking code use the 'Threaded Component Model' wizard instead.
*/
void xwiimoteIO::ProcessNull()
{
#if INSTALLATION == LINUX
  if (m_iface)
  {
    struct xwii_event event;
    int ret{-1};
    do {
      ret = xwii_iface_dispatch(m_iface, &event, sizeof(event));
      if (ret == 0)
      {
        switch (event.type) {
        case XWII_EVENT_KEY:
        case XWII_EVENT_NUNCHUK_KEY:
          switch (event.v.key.code)
          {
          case XWII_KEY_HOME:
            m_home = (event.v.key.state != 0);
            break;
          case XWII_KEY_A:
            m_a = (event.v.key.state != 0);
            break;
          case XWII_KEY_RIGHT:
            m_right = (event.v.key.state != 0);
            break;
          case XWII_KEY_LEFT:
            m_left = (event.v.key.state != 0);
            break;
          case XWII_KEY_UP:
            m_up = (event.v.key.state != 0);
            break;
          case XWII_KEY_DOWN:
            m_down = (event.v.key.state != 0);
            break;
          case XWII_KEY_ONE:
            m_one = (event.v.key.state != 0);
            break;
          case XWII_KEY_TWO:
            m_two = (event.v.key.state != 0);
            break;
          case XWII_KEY_C:
            m_nunchukC = (event.v.key.state != 0);
            break;
          case XWII_KEY_Z:
            m_nunchukZ = (event.v.key.state != 0);
            break;
          }
          break;
        case XWII_EVENT_ACCEL:
          m_accelX = event.v.abs[0].x;
          m_accelY = event.v.abs[0].y;
          m_accelZ = event.v.abs[0].z;
          break;
        case XWII_EVENT_NUNCHUK_MOVE:
          m_nunchukJoyX = event.v.abs[0].x;
          m_nunchukJoyY = event.v.abs[0].y;
          m_nunchukAccelX = event.v.abs[1].x;
          m_nunchukAccelY = event.v.abs[1].y;
          m_nunchukAccelZ = event.v.abs[1].z;
          break;
        }
      }
    } while (ret == 0);
  }
  if (!m_lastRumble || m_rumble != m_lastRumble.value())
  {
    xwii_iface_rumble(m_iface, m_rumble);
    m_lastRumble = m_rumble;
  }
#endif
}

void xwiimoteIO::Destroy()
{
#if INSTALLATION == LINUX
  if (m_iface)
    xwii_iface_unref(m_iface);
#endif
}
