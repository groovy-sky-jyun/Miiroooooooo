// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MiiroooPlayerController.h"
#include "CollisionQueryParams.h"
#include "BaseItem.h"
#include "ItemComponent.h"

APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WallTrace = CreateDefaultSubobject<USceneComponent>(TEXT("Trace"));
	WallTrace->SetupAttachment(RootComponent);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//플레이어가 뛸 때 카메라가 같이 흔들려서 실제 뛰는 느낌(몰입감)
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 5.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComponent->SetupAttachment(CameraBoom);
	CameraComponent->bUsePawnControlRotation = false;

	MaxSpeed = 500.0f;
	bIsReverse = false;

	// CollisionBox 설정
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	// 충돌감지(물리적x)
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
	CollisionBox->SetGenerateOverlapEvents(true);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapStart);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);

	

	//HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Enhanced Input Subsystem 가져오기
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Input Mapping Context 추가
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	SetOriginSpeed();

	SetWidgetToViewPort();

	ItemComponent = NewObject<UItemComponent>();
}

void APlayerCharacter::SetWidgetToViewPort()
{
	// Game Controller에서 실행하는걸로 수정
	if (WidgetClass) {
		UHUDWidget* PlayerWidget = CreateWidget<UHUDWidget>(GetWorld(), WidgetClass);
		if (PlayerWidget) {
			PlayerWidget->AddToViewport();
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Enhanced Input Component로 캐스팅
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		//LookAround
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LookAround);

		EnhancedInputComponent->BindAction(PressFAction, ETriggerEvent::Started, this, &APlayerCharacter::PickUpItem);

		//EnhancedInputComponent->BindAction(UseItemAction, ETriggerEvent::Started, this, &APlayerCharacter::UseItemKey);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	//반대방향 키 아이템 사용
	if(bIsReverse) {
		MovementVector.X = -MovementVector.X; // 좌우 반전
		MovementVector.Y = -MovementVector.Y; // 상하 반전
	}
	if (Controller) {
		FRotator ControlRotation = Controller->GetControlRotation();
		FRotator YawRotation(0, ControlRotation.Yaw, 0);

		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//Swizzle이라서 Y
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		
	}
}

void APlayerCharacter::LookAround(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y); 
	
	float Pitch = LookVector.Y + CurrentPitch;
	CurrentPitch = FMath::Clamp(Pitch, -45.0f, 45.0f);	
}

void APlayerCharacter::SetSpeed(float Value)
{
	GetCharacterMovement()->MaxWalkSpeed = Value;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerCharacter::SetOriginSpeed, 2, false);
	
}

void APlayerCharacter::SetOriginSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
}

void APlayerCharacter::ReverseKey()
{
	bIsReverse = true;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerCharacter::ReverseOriginKey, 4, false);
}

void APlayerCharacter::ReverseOriginKey()
{
	bIsReverse = false;
}

//---[아이템 오버랩]---
// Overlap 되었을 때 실행
void APlayerCharacter::OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseItem* ItemClass = Cast<ABaseItem>(OtherActor);
	if (ItemClass) {
		ItemClass->SetInteractWidget(true);
		ItemComponent->AddOverlapItem(ItemClass);
	}
}
// Overlap 끝났을 때 실행
void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex)
{
	ABaseItem* ItemClass = Cast<ABaseItem>(OtherActor);
	if (ItemClass) {
		ItemClass->SetInteractWidget(false);
		ItemComponent->RemoveOverlapItem(ItemClass);
	}
}//---------------------


//---[아이템 획득]---
void APlayerCharacter::PickUpItem()
{
	ItemComponent->PickUpAnItem();
}//---------------------


/*---[아이템 사용]---
void APlayerCharacter::UseItemKey()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMiiroooPlayerController* PlayerController = Cast<AMiiroooPlayerController>(PC);

	if (PlayerController->IsInputKeyDown(EKeys::One)) { //1번 슬롯
		//ItemsComponent->PressUseItem(1);
	}
	else if (PlayerController->IsInputKeyDown(EKeys::Two)) { //2번 슬롯
		//ItemsComponent->PressUseItem(2);
	}
	else if (PlayerController->IsInputKeyDown(EKeys::Three)) { //3번 슬롯
		//ItemsComponent->PressUseItem(3);
	}
	else if (PlayerController->IsInputKeyDown(EKeys::Four)) { //4번 슬롯
		//ItemsComponent->PressUseItem(4);
	}
	else if (PlayerController->IsInputKeyDown(EKeys::Five)) { //5번 슬롯
		//ItemsComponent->PressUseItem(5);
	}
}
//---------------------
*/