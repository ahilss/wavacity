/**********************************************************************

  Audacity: A Digital Audio Editor

  DeviceChange.h

  Leland Lucius

**********************************************************************/

#ifndef __WAVACITY_DEVICECHANGE_H__
#define __WAVACITY_DEVICECHANGE_H__

#include "Wavacity.h" // for HAVE_LIBUDEV_H

#include "Experimental.h"

#if defined(EXPERIMENTAL_DEVICE_CHANGE_HANDLER)

#include "MemoryX.h"

#if defined(__WXMSW__) || defined(__WXMAC__) || defined(HAVE_LIBUDEV_H)
#define HAVE_DEVICE_CHANGE
#endif

#if defined(HAVE_DEVICE_CHANGE)

#include <wx/timer.h> // member variable

class DeviceChangeInterface /* not final */
{
public:
   virtual ~DeviceChangeInterface() {};

   virtual bool SetHandler(wxEvtHandler *handler) = 0;
   virtual void Enable(bool enable = true) = 0;
};

class DeviceChangeHandler : public wxEvtHandler
{
public:
   DeviceChangeHandler();
   virtual ~DeviceChangeHandler();

   void Enable(bool enable = true);

   virtual void DeviceChangeNotification() = 0;

private:
   void OnChange(wxCommandEvent & evt);
   void OnTimer(wxTimerEvent & evt);

   std::unique_ptr<DeviceChangeInterface> mListener;
   wxTimer mTimer;

   DECLARE_EVENT_TABLE()
};

#endif

#endif

#endif
