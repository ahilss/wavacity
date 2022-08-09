/**********************************************************************

Audacity: A Digital Audio Editor

AutoRecoveryDialog.h

Paul Licameli split from AutoRecovery.h

**********************************************************************/

#ifndef __WAVVY_AUTO_RECOVERY_DIALOG__
#define __WAVVY_AUTO_RECOVERY_DIALOG__

class WavvyProject;

//
// Show auto recovery dialog if there are projects to recover. Should be
// called once at Wavvy startup.
//
// This function possibly opens NEW project windows while it recovers all
// projects. If so, it will re-use *pproj, if != NULL and set it to NULL.
//
// Returns: True, if the start of Wavvy should continue as normal
//          False if Wavvy should be quit immediately
//
// The didRecoverAnything param is strictly for a return value.
// Any value passed in is ignored.
//
bool ShowAutoRecoveryDialogIfNeeded(WavvyProject** pproj,
                                    bool *didRecoverAnything);

#endif
