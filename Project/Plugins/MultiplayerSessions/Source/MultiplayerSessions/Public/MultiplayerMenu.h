#pragma once

// Runtime -> Core
#include "CoreMinimal.h"

// Runtime -> UMG
#include "Blueprint/UserWidget.h"

// Generated
#include "MultiplayerMenu.generated.h"

UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

		UFUNCTION(BlueprintCallable, Category="MultiplayerMenu|Functions")
		void SetupMenu();
};
