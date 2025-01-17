// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameData.h"

#include "PlantableObject.generated.h"

class ATile;
class UStaticMesh;

UCLASS()
class TEAMWOLVERINEPROJECT_API APlantableObject : public AActor
{
	GENERATED_BODY()
	public:	
		APlantableObject();

		virtual void Tick(float DeltaTime) override;

		void SetNeighbor(APlantableObject* newNeighbor, ENeighborLocationType locationType);
		void Grow();
		void OnSpawn(ATile* closestTile, const TMap<ENeighborLocationType, APlantableObject*>& neighbors);
		void OnInteractWithNeighbor(ENeighborLocationType locationTypeForNeighbor);
		void OnInteractWithTile();

		ETileType GetTileTypeForCurrentTile() const;
		EPlantableObjectType GetObjectType() const { return mObjectType; }
		const TMap<ENeighborLocationType, APlantableObject*>& GetNeighbors() { return mNeighbors; }
		bool HasInteractedWithNeighborBefore(ENeighborLocationType neighborLocationType) const;
		bool HasInteractedWithCurrentTileBefore() const;
		EGrowingStage mCurrentGrowingStage;

		static ENeighborLocationType GetOppositeLocationType(ENeighborLocationType originalType);

		UPROPERTY(EditAnywhere, meta = (DisplayName = "Journal Index"))
		int32 mIndex;

		UPROPERTY(EditAnywhere, meta = (DisplayName = "Spawn Tier"))
		ESpawnTier mSpawnTier;

		UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
		void OnGrow();

		UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
		void OnFinalGrow();

	protected:
		virtual void BeginPlay() override;

	private:
		bool SetMeshToMatchGrowingState();

		TMap<ENeighborLocationType, APlantableObject*> mNeighbors;
		TArray<ENeighborLocationType> mNeighborsWeHaveHadInteractionWith;

		UPROPERTY(EditAnywhere, meta = (DisplayName = "Plantable Meshes", Tooltip = "The meshes that will be used for the different stages"))
		TMap<EGrowingStage, UStaticMesh*> mPlantableMeshes;

		ATile* mCurrentTile;

		UPROPERTY(EditAnywhere, meta = (DisplayName = "Object Type"))
		EPlantableObjectType mObjectType;

		UPROPERTY(EditAnywhere, meta = (DisplayName = "Time Until Next Growing Stage", Tooltip = "How much time it should take to get to the next growing stage, in seconds"))
		float mTimeUntilNextGrowingStage; //TODO.PKH: Maybe add a different time for each stage??

		float mTimeSpentInCurrentStage;
};
