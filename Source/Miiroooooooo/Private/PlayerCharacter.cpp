// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "MiiroooPlayerController.h"
#include "BasicItem.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ItemInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
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
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;

	// CollisionBox 설정
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	// 충돌감지(물리적x)
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapStart);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);

	ItemInteractionComponent = CreateDefaultSubobject<UItemInteractionComponent>(TEXT("ItemInteractionComponent"));
	ItemsComponent = CreateDefaultSubobject<UItemsComponent>(TEXT("ItemsComponent"));
}

// Called when the game starts or when spawned
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

	CurrentPitch = Controller->GetControlRotation().Pitch;

	//GetMesh()->SetOwnerNoSee(true);

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
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

		EnhancedInputComponent->BindAction(UseItemAction, ETriggerEvent::Started, this, &APlayerCharacter::UseItemKey);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

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

void APlayerCharacter::PickUpItem()
{
	ItemInteractionComponent->AddItemToPlayer();
}

// Overlap 되었을 때 실행
void APlayerCharacter::OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABasicItem* BasicItemClass = Cast<ABasicItem>(OtherActor);
	if (BasicItemClass) {
		ItemInteractionComponent->AddOverlapItem(OtherActor);
	}
}

// Overlap 끝났을 때 실행
void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex)
{
	ItemInteractionComponent->RemoveOverlapItem(OtherActor);
}

void APlayerCharacter::UseItemKey()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController(); 
	AMiiroooPlayerController* PlayerController = Cast<AMiiroooPlayerController>(PC);
	if (PlayerController->IsInputKeyDown(EKeys::One)) {
		//1번 슬롯 아이템 사용 로직 구현
		UseItem(1);
	}
	else if(PlayerController->IsInputKeyDown(EKeys::Two)) {
		//2번 슬롯 아이템 사용 로직 구현
		UseItem(2);
	}
	else if (PlayerController->IsInputKeyDown(EKeys::Three)) {
		//3번 슬롯 아이템 사용 로직 구현
		UseItem(3);
	}
	else if (PlayerController->IsInputKeyDown(EKeys::Four)) {
		//4번 슬롯 아이템 사용 로직 구현
		UseItem(4);
	}
	else if (PlayerController->IsInputKeyDown(EKeys::Five)) {
		//5번 슬롯 아이템 사용 로직 구현
		UseItem(5);
	}
}

void APlayerCharacter::UseItem(int32 KeyNum)
{

}
