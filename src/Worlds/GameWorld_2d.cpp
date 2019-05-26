#include "GameWorld_2d.h"
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


GameWorld_2d::GameWorld_2d() : BaseWorld()
{
    SGE_Math::RandomNumberGenerator::Instance().Seed(3);

    _cycleClock = clock();

    EVector minCoordinate, maxCoordinate;
    minCoordinate.X = 0.0_fp;
    minCoordinate.Y = 0.0_fp;

    maxCoordinate.X = 2560.0_fp;
    maxCoordinate.Y = 1440.0_fp;

    int levels = 4;

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
}

GameWorld_2d::~GameWorld_2d()
{
    _bucketTree.reset();
}

bool GameWorld_2d::Process(){
    SGE_Physics::BucketTree& bt = *_bucketTree.get();

    // Run physics
    if (_physicsTimer.CanRun(_physicsHz)){
        _physicsEngine.UpdatePhysics(_systemHz, entityComponentManager, bt);
        _physicsTimer.ResetClock();
    }

    // Input, output, actions and else should be ran at the same HZ. Otherwise, you may end up slightly out of sync on each player's machine.
    if (_systemTimer.CanRun(_systemHz)){
        // Input
        _inputSystem.Process(entityComponentManager);
        _physicsEngine.UpdatePhysics(_systemHz, entityComponentManager, bt);

        // Network I/O
        _networkSystem.Process(entityComponentManager);

        // AI / Actor input resolution
        // todo

        // Resolve actions, collisions and resolutions
        _actionSystem.Process(entityComponentManager);

        _systemTimer.ResetClock();
    }


    // GFX loop
    if (_gfxTimer.CanRun(_gfxHz)){
        // todo: Interpolate graphics with physics engine?

        _graphicsSystem.Process(entityComponentManager, bt);

        _gfxTimer.ResetClock();
    }

    if (InputState::Instance().Exit == true){
            return false;
    }

    return true;
}
