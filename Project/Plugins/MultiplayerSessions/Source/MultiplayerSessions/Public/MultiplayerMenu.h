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
		void SetupMenu();

protected:

		virtual bool Initialize() override;

private:

		UFUNCTION()
		void HostButtonClicked();
		
		UFUNCTION()
		void JoinButtonClicked();

		UPROPERTY(meta=(BindWidget))
		class UButton* HostButton;

		UPROPERTY(meta=(BindWidget))
		class UButton* JoinButton;

		/**
		 * Subsystem designed to handle all online session functionality (e.g: start, stop, create, destroy, find, etc).
		 */
		TObjectPtr<UMultiplayerSessionsSubSystem> MultiplayerSessionsSubsystem;
};
