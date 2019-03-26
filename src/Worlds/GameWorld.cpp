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

    maxCoordinate.X = 1920.0_fp;
    maxCoordinate.Y = 1080.0_fp;

    int levels = 5;

    _bucketTree = std::make_shared<SGE_Physics::BucketTree>(levels, minCoordinate, maxCoordinate);


    // testing for physics
    for (int i = 0; i < 1; i++){
        std::shared_ptr<int> e = entityComponentManager.AddEntity();

        if (e == nullptr){
            continue;
        }

        PhysicsBodyComponent& body = entityComponentManager.AddComponent<PhysicsBodyComponent>(*e.get());

        SGE_Physics::Aabb aabb;
        aabb.HalfHeight = 20.0_fp;
        aabb.HalfWidth = 300.0_fp;

        body.Body.Shape.SetAabb(aabb);
        body.Body.Transform.Position.X = 15.0_fp;
        body.Body.Transform.Position.Y = 400.0_fp;

        body.Body.Mass.Mass = 0.0_fp;
        body.Body.Material.Density = 0.0_fp;
        body.Body.Material.Restitution = 0.2_fp;
        body.Body.GravityScale = 0.0_fp;
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
        if (_systemTimer.CanRun(60.0_fp)){
        _inputSystem.Process(entityComponentManager);

        _actionSystem.Process(entityComponentManager);
      //  _networkSystem.Process(entityComponentManager);


        // Run physics updates at 30hz?
        // todo: fix

        SGE_Physics::BucketTree& bt = *_bucketTree.get();

       // if (InputState::Instance().ButtonDownIsPressed){
            _physicsEngine.UpdatePhysics(1.0_fp, entityComponentManager, bt);
     //   }



        bool finishedProcessing = true;
        while(_graphicsSystem.Process(entityComponentManager, bt) != finishedProcessing);

        if (InputState::Instance().Exit == true){
            return false;
        }

        _systemTimer.ResetClock();

    }



    return true;
}
