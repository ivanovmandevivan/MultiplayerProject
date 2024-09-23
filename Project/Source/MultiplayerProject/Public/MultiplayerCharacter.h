#pragma once

// Engine -> Runtime
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Online -> OnlineSubSystem
#include "Interfaces/OnlineSessionInterface.h"

// Generated
#include "MultiplayerCharacter.generated.h"

UCLASS()
class MULTIPLAYERPROJECT_API AMultiplayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMultiplayerCharacter();

	/* Begin ACharacter overrides */
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/* End ACharacter overrides */

	UFUNCTION(BlueprintCallable)
	void OpenLobby();

	UFUNCTION(BlueprintCallable)
	void CallOpenLevel(const FString& InAddress);

	UFUNCTION(BlueprintCallable)
	void CallClientTravel(const FString& InAddress);

	/* Pointer to the online session interface */
	IOnlineSessionPtr OnlineSessionInterface;

protected:
		UFUNCTION(BlueprintCallable)
		void CreateGameSession();

		UFUNCTION(BlueprintCallable)
		void JoinGameSession();

		/* Callback On Create Session Completed */
		void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
		
		/* Callback On Find Session Completed */
		void OnFindSessionsComplete(bool bWasSuccessful);

private:
		// Delegates for Session Creation:
		FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

		// Delegate for Finding Session:
		FOnFindSessionsCompleteDelegate OnFindSessionCompleteDelegate;

		/* Session Search Query: */
		TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
