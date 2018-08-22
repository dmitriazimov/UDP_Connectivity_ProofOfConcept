#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "Engine.h"
#include "Sender.generated.h"

UCLASS()
class UDP_CONNECTIVITY_POC_API ASender : public AActor
{
	GENERATED_BODY()

public:

	ASender();

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = sender) 
	void SendString();
	bool StartUDPSender(const FString& socket_name, const FString& ip, const int32 port, bool UDP = false);
	virtual void EndPlay(const EEndPlayReason::Type reason) override;

	int count;
	FTimerHandle send_timer;
	TSharedPtr<FInternetAddr> remote_address;
	FSocket* sender_socket;
	};
