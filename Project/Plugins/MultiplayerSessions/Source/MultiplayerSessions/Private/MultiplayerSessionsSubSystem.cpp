#include "MultiplayerSessionsSubSystem.h"

// Online -> OnlineSubsystem
#include "OnlineSubsystem.h"

UMultiplayerSessionsSubSystem::UMultiplayerSessionsSubSystem(const FObjectInitializer& ObjectInitializer) :
    CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
    FindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsComplete)),
    JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
    DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete)),
    StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete))
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    check(Subsystem); // Something very wrong has happened if the OnlineSubsystem does not return a valid ptr.

    SessionInterface = Subsystem->GetSessionInterface();
    ensureAlways(nullptr != SessionInterface);
}

void UMultiplayerSessionsSubSystem::CreateSession(int32 NumPublicConnections, const FString& MatchType)
{
}

void UMultiplayerSessionsSubSystem::FindSessions(int32 MaxSearchResults)
{
}

void UMultiplayerSessionsSubSystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
}

void UMultiplayerSessionsSubSystem::DestroySession()
{
}

void UMultiplayerSessionsSubSystem::StartSession()
{
}

void UMultiplayerSessionsSubSystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void UMultiplayerSessionsSubSystem::OnFindSessionsComplete(bool bWasSuccessful)
{
}

void UMultiplayerSessionsSubSystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void UMultiplayerSessionsSubSystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void UMultiplayerSessionsSubSystem::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
}
