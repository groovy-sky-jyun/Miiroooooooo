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
	//�÷��̾ �� �� ī�޶� ���� ������ ���� �ٴ� ����(���԰�)
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 5.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = false;
	

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComponent->SetupAttachment(CameraBoom);
	CameraComponent->bUsePawnControlRotation = false;

	
	MaxSpeed = 500.0f;
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;

	// CollisionBox ����
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	// �浹����(������x)
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

	// Enhanced Input Subsystem ��������
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Input Mapping Context �߰�
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

	// Enhanced Input Component�� ĳ����
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

		//Swizzle�̶� Y
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

// Overlap �Ǿ��� �� ����
void APlayerCharacter::OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABasicItem* BasicItemClass = Cast<ABasicItem>(OtherActor);
	if (BasicItemClass) {
		ItemInteractionComponent->AddOverlapItem(OtherActor);
	}
}

// Overlap ������ �� ����
void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex)
{
	ItemInteractionComponent->RemoveOverlapItem(OtherActor);
}

void APlayerCharacter::UseItemKey()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController(); 
	AMiiroooPlayerController* PlayerController = Cast<AMiiroooPlayerController>(PC);
	if (PlayerController->IsInputKeyDown(EKeys::One)) {
		//1�� ���� ������ ��� ���� ����
		UseItem(1);
	}
	else if(PlayerController->IsInputKeyDown(EKeys::Two)) {
		//2�� ���� ������ ��� ���� ����
		UseItem(2);
	}
	else if (PlayerController->IsInputKeyDown(EKeys::Three)) {
		//3�� ���� ������ ��� ���� ����
		UseItem(3);
	}
	else if (PlayerController->IsInputKeyDown(EKeys::Four)) {
		//4�� ���� ������ ��� ���� ����
		UseItem(4);
	}
	else if (PlayerController->IsInputKeyDown(EKeys::Five)) {
		//5�� ���� ������ ��� ���� ����
		UseItem(5);
	}
}

void APlayerCharacter::UseItem(int32 KeyNum)
{

}
