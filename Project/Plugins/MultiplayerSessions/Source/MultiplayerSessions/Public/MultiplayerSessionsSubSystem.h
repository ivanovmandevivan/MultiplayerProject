#pragma once

// Runtime -> Core
#include "CoreMinimal.h"

// Runtime -> Engine
#include "Subsystems/GameInstanceSubsystem.h"

// Online -> OnlineSubsystem
#include "Interfaces/OnlineSessionInterface.h"

// Generated
#include "MultiplayerSessionsSubSystem.generated.h"

UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionsSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
		UMultiplayerSessionsSubSystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
		virtual ~UMultiplayerSessionsSubSystem() = default;

		/**
		 * These methods are going to be used by the UI/BP to be able to execute the functionality in regards to Session code.
		 */

		/**
		 * Method binded to the 'CreateSessionCompleteDelegate' delegate to handle creation of sessions. 
		 */
		void CreateSession(int32 NumPublicConnections, const FString& MatchType);
		
		/**
		 * Method binded to the 'FindSessionsCompleteDelegate' delegate to find sessions.
		 */
		void FindSessions(int32 MaxSearchResults);
		
		/**
		 * Method binded to the 'JoinSessionCompleteDelegate' delegate to join sessions.
		 */
		void JoinSession(const FOnlineSessionSearchResult& SessionResult);
		
		/**
		 * Method binded to the 'DestroySessionCompleteDelegate' delegate to destroy sessions.
		 */
		void DestroySession();
		
		/**
		 * Method binded to the 'StartSessionCompleteDelegate' delegate to start sessions.
		 */
		void StartSession();

protected:
		
		/**
		 * Internal callback for the delegates that will be added to the Online Session Interface Delegate List.
		 * Called whenever the creation of a session is completed.
		 */
		void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

		/**
		 * Internal callback for the delegates that will be added to the Online Session Interface Delegate List.
		 * Called whenever a find query for a session is completed.
		 */
		void OnFindSessionsComplete(bool bWasSuccessful);

		/**
		 * Internal callback for the delegates that will be added to the Online Session Interface Delegate List.
		 * Called whenever the join of a session is completed.
		 */
		void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

		/**
     * Internal callback for the delegates that will be added to the Online Session Interface Delegate List.
     * Called whenever a session destroy is completed.
     */
		void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

		/**
		 * Internal callback for the delegates that will be added to the Online Session Interface Delegate List.
		 * Called whenever the start of a session is completed.
		 */
		void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

private:
		/**
		 * Pointer to a TSharedPtr<class IOnlineSession>
		 * Main bridge class with which to create, destroy, find, start and stop sessions.
		 */
		IOnlineSessionPtr SessionInterface;

		/**
		 * Delegate fired when a session create request has completed.
		 */
		FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;

		/**
		* Delegate handle for the 'CreateSessionCompleteDelegate' event.
		*/
		FDelegateHandle CreateSessionCompleteDelegateHandle;

		/**
		 * Delegate fired when the search for an online session has completed.
		 */
		FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;

		/**
		* Delegate handle for the 'FindSessionsCompleteDelegate' event.
		*/
		FDelegateHandle FindSessionsCompleteDelegateHandle;

		/**
		 * Delegate fired when the joining process for an online session has completed.
		 */
		FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;

		/**
		* Delegate handle for the 'JoinSessionCompleteDelegate' event.
		*/
		FDelegateHandle JoinSessionCompleteDelegateHandle;

		/**
		 * Delegate fired when a destroying an online session has completed.
		 */
		FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;

		/**
		* Delegate handle for the 'DestroySessionCompleteDelegate' event.
		*/
		FDelegateHandle DestroySessionCompleteDelegateHandle;

		/**
		 * Delegate fired when the online session has transitioned to the started state.
		 */
		FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;

		/**
		* Delegate handle for the 'StartSessionCompleteDelegate' event.
		*/
		FDelegateHandle StartSessionCompleteDelegateHandle;
};
