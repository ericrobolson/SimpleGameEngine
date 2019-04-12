#include "GameWorld.h"
#include "InputState.h"
#include <stdio.h>
#include <time.h>
#include <thread>
#include <memory>

#include <PlayerAssemblage.h>
#include "GameState.h"
#include "LevelLoader.h"
#include "SystemTimer.h"
#include "Debugger.h"
#include "BucketTree.h"
#include "Aabb.h"
#include "RandomNumberGenerator.h"
#include "PhysicsBodyComponent.h"
#include "InputState.h"

#include <iostream>


GameWorld::GameWorld() : BaseWorld()
{
    SGE_Math::RandomNumberGenerator::Instance().Seed(3);

    _graphicsSystem.DrawHitboxes = true;

    _cycleClock = clock();

    EVector minCoordinate, maxCoordinate;
    minCoordinate.X = 0.0_fp;
    minCoordinate.Y = 0.0_fp;

    maxCoordinate.X = 900.0_fp;
    maxCoordinate.Y = 900.0_fp;

    int levels = 3;

    _bucketTree = std::make_shared<SGE_Physics::BucketTree>(levels, minCoordinate, maxCoordinate);


    // testing for physics
    for (int i = 0; i < 1; i++){
        std::shared_ptr<int> e = entityComponentManager.AddEntity();

        if (e == nullptr){
            continue;
        }

        PhysicsBodyComponent& body = entityComponentManager.AddComponent<PhysicsBodyComponent>(*e.get());

        SGE_Physics::Aabb aabb;
        aabb.HalfHeight = 50.0_fp;
        aabb.HalfWidth = 300.0_fp;

        body.Body.Shape.SetAabb(aabb);
        body.Body.Transform.Position.X = 15.0_fp;
        body.Body.Transform.Position.Y = 600.0_fp;

        body.Body.Material.SetMaterialType(SGE_Physics::MaterialData::MaterialType::StaticObject);
    }

    std::shared_ptr<int> entityId = entityComponentManager.AddEntity();

    if (entityId != nullptr){
        int id = *entityId.get();

        PhysicsBodyComponent& body = entityComponentManager.AddComponent<PhysicsBodyComponent>(id);

        SGE_Physics::Aabb aabb;
        aabb.HalfHeight = 17.5_fp;
        aabb.HalfWidth = 7.5_fp;

        EVector position;
        position.X = 450.0_fp;
        position.Y = 155.0_fp;

        body.Body.Initialize(SGE_Physics::MaterialData::MaterialType::Rock, position, aabb);
    }

    PlayerAssemblage::BuildPlayer(entityComponentManager, 300.0_fp, 0.0_fp);



    LevelLoader loader;
//    loader.LoadLevel("room_001", entityComponentManager);
}

GameWorld::~GameWorld()
{
    _bucketTree.reset();
}

bool GameWorld::Process(){

    SGE_Physics::BucketTree& bt = *_bucketTree.get();


    bool moveKeyPressed = InputState::Instance().ButtonDownIsPressed
        || InputState::Instance().ButtonUpIsPressed
        || InputState::Instance().ButtonLeftIsPressed
        || InputState::Instance().ButtonRightIsPressed
        ;

    if (InputState::Instance().AnyKeyPressed()){
        // Physics loop
        FixedPointInt physicsHz = 120.0_fp;
        if (_physicsTimer.CanRun(physicsHz)){

            _physicsEngine.UpdatePhysics(physicsHz, entityComponentManager, bt);

            _physicsTimer.ResetClock();
        }
    }else{
        // move physics slowly
        // Physics loop
        FixedPointInt physicsHz = 15.0_fp;
        if (_physicsTimer.CanRun(physicsHz)){

            _physicsEngine.UpdatePhysics(physicsHz, entityComponentManager, bt);

            _physicsTimer.ResetClock();
        }
    }



    // todo: Interpolate graphics with physics engine?

    if (_systemTimer.CanRun(60.0_fp)){
        // Input
        _inputSystem.Process(entityComponentManager);
        _actionSystem.Process(entityComponentManager);

        // Graphics
        // this smells...
        bool finishedProcessing = true;
        while(_graphicsSystem.Process(entityComponentManager, bt) != finishedProcessing);

        _systemTimer.ResetClock();
    }

    if (InputState::Instance().Exit == true){
            return false;
    }

    return true;
}
