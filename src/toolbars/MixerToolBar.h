/**********************************************************************

  Audacity: A Digital Audio Editor

  MixerToolbar.h

  Dominic Mazzoni

**********************************************************************/

#ifndef __WAVVY_MIXER_TOOLBAR__
#define __WAVVY_MIXER_TOOLBAR__

#include "ToolBar.h"

class wxSize;
class wxPoint;

class ASlider;
class WavvyProject;

class MixerToolBar final : public ToolBar {

 public:

   MixerToolBar( WavvyProject &project );
   virtual ~MixerToolBar();

   static MixerToolBar &Get( WavvyProject &project );
   static const MixerToolBar &Get( const WavvyProject &project );

   void Create(wxWindow * parent) override;

   void UpdatePrefs() override;
   void UpdateControls();
   void SetMixer(wxCommandEvent &event);

   void Populate() override;
   void Repaint(wxDC * WXUNUSED(dc)) override {};
   void EnableDisableButtons() override {};
   int GetMinToolbarWidth() override { return 250; }
   int GetInitialWidth()  override { return 327; }

   void OnFocus(wxFocusEvent &event);
   void OnCaptureKey(wxCommandEvent &event);

   void OnSlider(wxCommandEvent & event);

   void OnAudioCapture(wxCommandEvent & event);

   void ShowOutputGainDialog();
   void ShowInputGainDialog();

   void AdjustOutputGain(int adj);
   void AdjustInputGain(int adj);

   void RegenerateTooltips() override {};

 protected:
   float mInputSliderVolume;
   float mOutputSliderVolume;

 private:

   void InitializeMixerToolBar();
   void SetToolTips();

   ASlider *mInputSlider;
   ASlider *mOutputSlider;
   bool mEnabled;

 public:

   DECLARE_CLASS(MixerToolBar)
   DECLARE_EVENT_TABLE()
};

#endif

