// Fill out your copyright notice in the Description page of Project Settings.


#include "SavePointBase.h"

// Sets default values
ASavePointBase::ASavePointBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TriggerBoxを生成
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));

	// Overlapイベントをバインド
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASavePointBase::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ASavePointBase::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASavePointBase::BeginPlay()
{
	Super::BeginPlay();
	// KeyWidgetを生成
	if (KeyWidgetClass != nullptr)
	{
		KeyWidget = CreateWidget<UUserWidget>(GetWorld(), KeyWidgetClass);
	}
	
	if (KeyWidgetClass != nullptr)
	{
		SavePointWidget = CreateWidget<UUserWidget>(GetWorld(), SavePointClass);
	}
}

// Called every frame
void ASavePointBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// TriggerBoxのOverlapBeginイベント
void ASavePointBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG( LogTemp, Warning, TEXT("OnOverlapBegin.SavePointName:%s"),*SavePointName );
	ShowWidget();
}

// TriggerBoxのOverlapEndイベント
void ASavePointBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG( LogTemp, Warning, TEXT("OnOverlapEnd.SavePointName:%s"),*SavePointName );
	HideWidget();
}

// セーブポイントのUIを表示
void ASavePointBase::ShowWidget()
{
	// 入力を有効にする
	EnableKeyInput();
	
	if(KeyWidget!=nullptr&&!KeyWidget->IsInViewport())
	{
		KeyWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowWidget:WidgetClass is nullptr"));
	}
}

// セーブポイントのUIを非表示
void ASavePointBase::HideWidget()
{
	// 入力を無効にする
	DisableKeyInput();
	
	if(KeyWidget!=nullptr&&KeyWidget->IsInViewport())
	{
		KeyWidget->RemoveFromParent();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HideWidget:WidgetClass is nullptr"));
	}
}

// キー入力を有効にする
void ASavePointBase::EnableKeyInput()
{
	// 入力を有効にする
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	// EキーのPressedをバインドする
	//InputComponent->BindKey(EKeys::E, EInputEvent::IE_Pressed, this, &ASavePointBase::PressKeyEvent);

	// ActionEKeyのPressedにバインドする
	InputComponent->BindAction("ActionEKey", EInputEvent::IE_Pressed, this, &ASavePointBase::PressKeyEvent);
}

// キー入力を無効にする
void ASavePointBase::DisableKeyInput()
{
	// 入力を無効にする
	DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// ActionEKeyをバインドを解除する
	InputComponent->RemoveActionBinding("ActionEKey", EInputEvent::IE_Pressed);
}

// キー入力のイベント
void ASavePointBase::PressKeyEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("PressKeyEvent:Push E Key"));
	
	if(SavePointWidget!=nullptr&&!SavePointWidget->IsInViewport())
	{
		SavePointWidget->AddToViewport();
		HideWidget();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PressKeyEvent:SavePointWidget is nullptr"));
	}
}
