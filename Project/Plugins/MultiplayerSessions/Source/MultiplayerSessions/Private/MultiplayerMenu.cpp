#include "MultiplayerMenu.h"

void UMultiplayerMenu::SetupMenu()
{
    AddToViewport();
    SetVisibility(ESlateVisibility::Visible);
    bIsFocusable = true;

    UWorld* World = GetWorld();
    if (!ensureAlwaysMsgf(nullptr != World, TEXT("Unable to fetch a valid world for the Multiplayer Menu Widget.")))
    {
        return;
    }

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!ensureAlwaysMsgf(nullptr != PlayerController, TEXT("Unable to get first player controller from World.")))
    {
        return;
    }

    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputModeData);
}
