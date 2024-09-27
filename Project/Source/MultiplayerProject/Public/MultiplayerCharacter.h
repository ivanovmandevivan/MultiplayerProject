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

	/* Begin ACharacter overrides */
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/* End ACharacter overrides */
};
