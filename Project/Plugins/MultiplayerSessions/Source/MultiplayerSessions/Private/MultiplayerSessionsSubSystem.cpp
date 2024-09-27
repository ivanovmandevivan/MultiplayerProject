#include "MultiplayerSessionsSubSystem.h"

// Online -> OnlineSubsystem
#include "OnlineSubsystem.h"

UMultiplayerSessionsSubSystem::UMultiplayerSessionsSubSystem(const FObjectInitializer& ObjectInitializer)
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    check(Subsystem); // Something very wrong has happened if the OnlineSubsystem does not return a valid ptr.

    SessionInterface = Subsystem->GetSessionInterface();
    ensureAlways(nullptr != SessionInterface);
}
