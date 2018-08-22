#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "Engine.h"
#include "TransferableData.h"
#include "Receiver.generated.h"

UCLASS()
class UDP_CONNECTIVITY_POC_API AReceiver : public AActor
{
	GENERATED_BODY()
	
public:	

	AReceiver();

	UFUNCTION(BlueprintImplementableEvent) 
	void BPEvent_DataReceived(const FTransferableData& data);

	virtual void BeginPlay() override;

	FSocket* listen_socket;

	FUdpSocketReceiver* receiver = nullptr; 
	void Receive(const FArrayReaderPtr& array_reader, const FIPv4Endpoint& end_point);

	bool StartReceiver(const FString& socket_name, const FString& ip, const int32 port);

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};