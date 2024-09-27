#pragma once

// Runtime -> Core
#include "CoreMinimal.h"

// Runtime -> UMG
#include "Blueprint/UserWidget.h"

// MultiplayerSessions -> MultiplayerSessions
class UMultiplayerSessionsSubSystem;

// Generated
#include "MultiplayerMenu.generated.h"


UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

		UFUNCTION(BlueprintCallable, Category="MultiplayerMenu|Functions")
		void SetupMenu(const int32 InNumPublicConnections = 4, const FString& InTypeOfMatch = FString(TEXT("FreeForAll")));

protected:

		// Begin UUserWidget overrides
		virtual bool Initialize() override;
		virtual void NativeDestruct() override;
		// End UUserWidget overrides

		/**
		 *  Method that will be bound to the OnCreateSessionComplete event in the MultiplayerSessionSubSystem.
		 */
		UFUNCTION()
		void OnCreateSession(const bool bWasSuccessful);
		

private:

		UFUNCTION()
		void HostButtonClicked();
		
		UFUNCTION()
		void JoinButtonClicked();

		void TearDownMenu();

		UPROPERTY(meta=(BindWidget))
		class UButton* HostButton;

		UPROPERTY(meta=(BindWidget))
		class UButton* JoinButton;

		/**
		 * Subsystem designed to handle all online session functionality (e.g: start, stop, create, destroy, find, etc).
		 */
		TObjectPtr<UMultiplayerSessionsSubSystem> MultiplayerSessionsSubsystem;

		int32 NumPublicConnections = 4;
		FString MatchType = FString(TEXT("FreeForAll"));
};
