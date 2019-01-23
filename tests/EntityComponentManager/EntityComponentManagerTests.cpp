#include "catch.hpp"
#include "EntityComponentManager.h"
#include <vector>
#include <memory>

using namespace ECS;

class TestComponent : public BaseComponent{
public:
    const bool TestFlagDefaultValue = true;
    const int TestNumberDefaultValue = 1;

    virtual ~TestComponent(){};
    TestComponent(): BaseComponent(){ TestFlag = TestFlagDefaultValue; TestNumber = TestNumberDefaultValue;};
    bool TestFlag;
    int TestNumber;
};

//tests todo:
    //             std::vector<int> Search(std::function<bool(TComponent c)> const& filterLambda)
    //             std::vector<int> Search()
    //             std::vector<int> SearchOn(std::vector<int> entityIds)
    //             std::vector<int> SearchOn(std::vector<int> entityIds, std::function<bool(TComponent c)> const& filterLambda){
    //             void RemoveComponent(int entityId)
    //             void MarkEntityInactive(int entityId)
    //             void DeleteAllInactiveEntities()
    //             void Reset()


//tests in progress:

// std::shared_ptr<TComponent> GetComponent(int entityId)


SCENARIO("EntityComponentManager::AddComponent_ExistingComponent_ReturnsExistingComponentForEntity"){
    EntityComponentManager ecs;
    std::shared_ptr<int> entityPtr = ecs.AddEntity();
    int entityId = *entityPtr.get();

    TestComponent& testComponent1 = ecs.AddComponent<TestComponent>(entityId);
    testComponent1.TestNumber = 0;
    testComponent1.TestFlag = !testComponent1.TestFlag;


    TestComponent& testComponent2 = ecs.AddComponent<TestComponent>(entityId);

    REQUIRE(testComponent2.TestNumber != testComponent2.TestNumberDefaultValue);
    REQUIRE(testComponent2.TestNumber == testComponent1.TestNumber);

    REQUIRE(testComponent2.TestFlag != testComponent2.TestFlagDefaultValue);
    REQUIRE(testComponent2.TestFlag == testComponent1.TestFlag);
}

SCENARIO("EntityComponentManager::AddComponent_NewComponent_CreatesNewComponentForEntity"){
    EntityComponentManager ecs;
    std::shared_ptr<int> entityPtr = ecs.AddEntity();
    int entityId = *entityPtr.get();

    TestComponent& testComponent = ecs.AddComponent<TestComponent>(entityId);

    REQUIRE(testComponent.TestNumber == testComponent.TestNumberDefaultValue);
    REQUIRE(testComponent.TestFlag == testComponent.TestFlagDefaultValue);
}

SCENARIO("EntityComponentManager::AddEntity_SingleEntity_ReturnsId"){
    EntityComponentManager ecs;

    int expectedId = MAXNUMBEROFENTITIES -1;
    std::shared_ptr<int> actualId = ecs.AddEntity();

    REQUIRE(actualId != nullptr);
    REQUIRE(*actualId.get() == expectedId);
}

SCENARIO("EntityComponentManager::AddEntity_AddEntitiesPastMaxEntitities_ReturnsNullId"){
    EntityComponentManager ecs;

    // adding entities past max entity capacity returns nullptr
    for (int i = 0; i < (MAXNUMBEROFENTITIES * 2); i++){
        ecs.AddEntity();
    }

    std::shared_ptr<int> actualId = ecs.AddEntity();

    REQUIRE(actualId == nullptr);
}




