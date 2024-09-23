
#include "MultiplayerCharacter.h"

// Engine -> Kismet
#include "Kismet/GameplayStatics.h"

// Online -> OnlineSubSystem
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"

// Sets default values
AMultiplayerCharacter::AMultiplayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
			OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
	}

}

// Called when the game starts or when spawned
void AMultiplayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMultiplayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMultiplayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMultiplayerCharacter::OpenLobby()
{
		UWorld* World = GetWorld();
		if (World)
		{
				World->ServerTravel("/Game/Levels/Lobby?listen");
		}
}

void AMultiplayerCharacter::CallOpenLevel(const FString& InAddress)
{
		UGameplayStatics::OpenLevel(this, *InAddress);
}

void AMultiplayerCharacter::CallClientTravel(const FString& InAddress)
{
		APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
		if (nullptr == PlayerController)
		{
				return;
		}

		PlayerController->ClientTravel(InAddress, ETravelType::TRAVEL_Absolute);
}

