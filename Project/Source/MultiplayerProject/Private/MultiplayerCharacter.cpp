
#include "MultiplayerCharacter.h"

// Engine -> Kismet
#include "Kismet/GameplayStatics.h"

// Online -> OnlineSubSystem
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

// Sets default values
AMultiplayerCharacter::AMultiplayerCharacter() 
		: OnCreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete))
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

void AMultiplayerCharacter::CreateGameSession()
{
		// Called when pressing the '1' key:
		check(OnlineSessionInterface.IsValid());

		FNamedOnlineSession* ExistingSession = OnlineSessionInterface->GetNamedSession(NAME_GameSession);
		if (ExistingSession)
		{
				//UE_LOG(LogTemp, Warning, FString::Printf(TEXT("There is an existing session with name: %s, destroying it so we can create a new session."), *ExistingSession->SessionName));
				OnlineSessionInterface->DestroySession(NAME_GameSession);
		}

		// Add to Delegate List:
		OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

		// Create Session:
		TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
		SessionSettings->bIsLANMatch = false;
		SessionSettings->NumPublicConnections = 4;
		SessionSettings->bAllowJoinInProgress = true;
		SessionSettings->bAllowJoinViaPresence = true;
		SessionSettings->bShouldAdvertise = true;
		SessionSettings->bUsesPresence = true;

		const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
		bool bSuccessful = OnlineSessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
		if (!bSuccessful)
		{
				UE_LOG(LogTemp, Warning, TEXT("Unsuccessfully created a session! Please check CreateGameSession()"));
				return;
		}
}

void AMultiplayerCharacter::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
		if (bWasSuccessful)
		{
				GEngine->AddOnScreenDebugMessage(
						-1, 15.f, FColor::Blue,
						FString::Printf(TEXT("Create session with name: %s"), *SessionName.ToString())
				);
		}
		else
		{
				if (GEngine)
				{
						GEngine->AddOnScreenDebugMessage(
								-1, 15.f, FColor::Red,
								FString(TEXT("Failed to create session!"))
						);
				}
		}
}

