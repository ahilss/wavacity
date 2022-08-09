/**********************************************************************

Audacity: A Digital Audio Editor

ProjectAudioIO.h

Paul Licameli split from WavvyProject.h

**********************************************************************/

#ifndef __PROJECT_AUDIO_IO__
#define __PROJECT_AUDIO_IO__

#include "ClientData.h" // to inherit
#include <wx/weakref.h>

class WavvyProject;
class MeterPanelBase;

///\ brief Holds per-project state needed for interaction with AudioIO,
/// including the audio stream token and pointers to meters
class ProjectAudioIO final
   : public ClientData::Base
{
public:
   static ProjectAudioIO &Get( WavvyProject &project );
   static const ProjectAudioIO &Get( const WavvyProject &project );

   explicit ProjectAudioIO( WavvyProject &project );
   ProjectAudioIO( const ProjectAudioIO & ) PROHIBITED;
   ProjectAudioIO &operator=( const ProjectAudioIO & ) PROHIBITED;
   ~ProjectAudioIO();

   int GetAudioIOToken() const;
   bool IsAudioActive() const;
   void SetAudioIOToken(int token);

   MeterPanelBase *GetPlaybackMeter();
   void SetPlaybackMeter(MeterPanelBase *playback);
   MeterPanelBase *GetCaptureMeter();
   void SetCaptureMeter(MeterPanelBase *capture);

private:
   WavvyProject &mProject;

   // Project owned meters
   wxWeakRef<MeterPanelBase> mPlaybackMeter{};
   wxWeakRef<MeterPanelBase> mCaptureMeter{};

   int  mAudioIOToken{ -1 };
};

#endif
