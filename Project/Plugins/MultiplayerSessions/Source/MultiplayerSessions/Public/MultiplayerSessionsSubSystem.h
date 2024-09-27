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

private:
		IOnlineSessionPtr SessionInterface;
};
