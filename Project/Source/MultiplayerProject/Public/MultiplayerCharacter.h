#pragma once

// Engine -> Runtime
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Generated
#include "MultiplayerCharacter.generated.h"

UCLASS()
class MULTIPLAYERPROJECT_API AMultiplayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMultiplayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void OpenLobby();

	UFUNCTION(BlueprintCallable)
	void CallOpenLevel(const FString& InAddress);

	UFUNCTION(BlueprintCallable)
	void CallClientTravel(const FString& InAddress);

};
