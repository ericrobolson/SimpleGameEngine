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
#include "SpatialHashMap.h"
#include "Aabb.h"
#include "RandomNumberGenerator.h"
#include "PhysicsBodyComponent.h"

#include <iostream>

GameWorld::GameWorld() : BaseWorld()
{
    SGE_Math::RandomNumberGenerator::Instance().Seed(3);

    _graphicsSystem.DrawHitboxes = true;

    _cycleClock = clock();

    // testing for physics
    for (int i = 0; i < 1; i++){
        std::shared_ptr<int> e = entityComponentManager.AddEntity();

        if (e == nullptr){
            continue;
        }

        PhysicsBodyComponent& body = entityComponentManager.AddComponent<PhysicsBodyComponent>(*e.get());

        SGE_Physics::Aabb aabb;
        aabb.HalfHeight = 10.0_fp;
        aabb.HalfWidth = 10.0_fp;

        body.Body.Shape.SetAabb(aabb);
        body.Body.Transform.Position.X = 20.0_fp;
        body.Body.Transform.Position.Y = 20.0_fp;

        body.Body.Mass.Mass = 2.0_fp;
        body.Body.Material.Density = 4.0_fp;
        body.Body.Material.Restitution = 0.2_fp;
        body.Body.Velocity.X = 3.0_fp;
        body.Body.Velocity.Y = 0.00_fp;
    }
        std::shared_ptr<int> e = entityComponentManager.AddEntity();

        PhysicsBodyComponent& body = entityComponentManager.AddComponent<PhysicsBodyComponent>(*e.get());

        SGE_Physics::Aabb aabb;
        aabb.HalfHeight = 10.0_fp;
        aabb.HalfWidth = 10.0_fp;
body.Body.Mass.Mass = 2.0_fp;
        body.Body.Material.Density = 4.0_fp;
        body.Body.Material.Restitution = 0.2_fp;
        body.Body.Shape.SetAabb(aabb);
        body.Body.Transform.Position.X = 320.0_fp;
        body.Body.Transform.Position.Y = 20.0_fp;


        body.Body.Velocity.X = -1.0_fp;
        body.Body.Velocity.Y = -0.0_fp;




    LevelLoader loader;
//    loader.LoadLevel("room_001", entityComponentManager);
}

GameWorld::~GameWorld()
{
    //dtor
}

bool GameWorld::Process(){
    if (_systemTimer.CanRun(60.0_fp)){
        _inputSystem.Process(entityComponentManager);

      //  _networkSystem.Process(entityComponentManager);


        // Run physics updates at 30hz?
        // todo: fix
        EVector ev;
        SGE_Physics::SpatialHashMap hashMap(ev, ev);
        _physicsEngine.UpdatePhysics(1.0_fp, entityComponentManager, hashMap);

        bool finishedProcessing = true;
        while(_graphicsSystem.Process(entityComponentManager) != finishedProcessing);

        if (InputState::Instance().Exit == true){
            return false;
        }

        _systemTimer.ResetClock();
    }

    return true;
}
