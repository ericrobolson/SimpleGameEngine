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

class TestComponent2 : public BaseComponent{
public:
    const bool TestFlagDefaultValue = true;
    const int TestNumberDefaultValue = 1;

    virtual ~TestComponent2(){};
    TestComponent2(): BaseComponent(){ TestFlag = TestFlagDefaultValue; TestNumber = TestNumberDefaultValue;};
    bool TestFlag;
    int TestNumber;
};

SCENARIO("EntityComponentManager::Reset_GetComponentOnDeletedEntity_ReturnsNull"){
    EntityComponentManager ecs;

    std::shared_ptr<int> entityPtr1 = ecs.AddEntity();
    int entityId1 = *entityPtr1.get();

    ecs.AddComponent<TestComponent>(entityId1);

    REQUIRE(ecs.GetComponent<TestComponent>(entityId1) != nullptr);

    ecs.Reset();

    REQUIRE(ecs.GetComponent<TestComponent>(entityId1) == nullptr);
}

SCENARIO("EntityComponentManager::Reset_NoEntities_DoesNothing"){
    EntityComponentManager ecs;

    ecs.Reset();

    REQUIRE(true == true);
}

SCENARIO("EntityComponentManager::DeleteAllInactiveEntities_NoEntities_DoesNothing"){
    EntityComponentManager ecs;

    ecs.DeleteAllInactiveEntities();

    REQUIRE(true == true);
}

SCENARIO("EntityComponentManager::MarkEntityInactive_ReturnsEntityComponentsIfNotDeleted"){
    EntityComponentManager ecs;

    std::shared_ptr<int> entityPtr1 = ecs.AddEntity();
    int entityId1 = *entityPtr1.get();

    ecs.AddComponent<TestComponent>(entityId1);

    REQUIRE(ecs.GetComponent<TestComponent>(entityId1) != nullptr);

    ecs.MarkEntityInactive(entityId1);

    REQUIRE(ecs.GetComponent<TestComponent>(entityId1) != nullptr);
}

SCENARIO("EntityComponentManager::RemoveComponent_ExistantComponent_DeletesComponent"){
    EntityComponentManager ecs;

    std::shared_ptr<int> entityPtr1 = ecs.AddEntity();
    int entityId1 = *entityPtr1.get();

    ecs.AddComponent<TestComponent>(entityId1);

    REQUIRE(ecs.GetComponent<TestComponent>(entityId1) != nullptr);

    ecs.RemoveComponent<TestComponent>(entityId1);

    REQUIRE(ecs.GetComponent<TestComponent>(entityId1) == nullptr);
}

SCENARIO("EntityComponentManager::RemoveComponent_NonExistantComponent_DoesNothing"){
    EntityComponentManager ecs;

    std::shared_ptr<int> entityPtr1 = ecs.AddEntity();
    int entityId1 = *entityPtr1.get();

    ecs.RemoveComponent<TestComponent>(entityId1);

    std::shared_ptr<TestComponent> entity1Component = ecs.GetComponent<TestComponent>(entityId1);

    REQUIRE(entity1Component == nullptr);
}



SCENARIO("EntityComponentManager::SearchOn_UsingLambda_ReturnsOnlyFilteredResults"){
    EntityComponentManager ecs;

    std::shared_ptr<int> entityPtr1 = ecs.AddEntity();
    int entityId1 = *entityPtr1.get();

    TestComponent& component = ecs.AddComponent<TestComponent>(entityId1);
    component.TestNumber = 666;

    std::shared_ptr<int> entityPtr2 = ecs.AddEntity();
    int entityId2 = *entityPtr2.get();

    ecs.AddComponent<TestComponent>(entityId2);

    ecs.AddEntity();

    std::vector<int> allMatchingEntityIds = ecs.Search<TestComponent>();


    std::vector<int> matchingEntityIds = ecs.SearchOn<TestComponent>(allMatchingEntityIds,
        [](TestComponent c){
            return (c.TestNumber != c.TestNumberDefaultValue);
        });

    REQUIRE(matchingEntityIds.empty() == false);
    REQUIRE(matchingEntityIds.size() == 1);
    REQUIRE(matchingEntityIds[0] == entityId1);
}

SCENARIO("EntityComponentManager::Search_UsingLambda_ReturnsOnlyFilteredResults"){
    EntityComponentManager ecs;

    std::shared_ptr<int> entityPtr1 = ecs.AddEntity();
    int entityId1 = *entityPtr1.get();

    TestComponent& component = ecs.AddComponent<TestComponent>(entityId1);
    component.TestNumber = 666;

    std::shared_ptr<int> entityPtr2 = ecs.AddEntity();
    int entityId2 = *entityPtr2.get();

    ecs.AddComponent<TestComponent>(entityId2);

    std::vector<int> matchingEntityIds = ecs.Search<TestComponent>(
        [](TestComponent c){
            return (c.TestNumber != c.TestNumberDefaultValue);
        });

    REQUIRE(matchingEntityIds.empty() == false);
    REQUIRE(matchingEntityIds.size() == 1);
    REQUIRE(matchingEntityIds[0] == entityId1);
}


SCENARIO("EntityComponentManager::SearchOn_MatchingEntityIds_ReturnsExpectedResults"){
    EntityComponentManager ecs;

    std::shared_ptr<int> entityPtr1 = ecs.AddEntity();
    int entityId1 = *entityPtr1.get();

    ecs.AddComponent<TestComponent>(entityId1);

    std::shared_ptr<int> entityPtr2 = ecs.AddEntity();
    int entityId2 = *entityPtr2.get();

    ecs.AddComponent<TestComponent>(entityId2);
    ecs.AddComponent<TestComponent2>(entityId2);

    std::vector<int> entitiesToSearchOn = ecs.Search<TestComponent>();

    std::vector<int> matchingEntityIds = ecs.SearchOn<TestComponent2>(entitiesToSearchOn);

    REQUIRE(matchingEntityIds.empty() == false);
    REQUIRE(matchingEntityIds.size() == 1);
    REQUIRE(matchingEntityIds[0] == entityId2);
}

SCENARIO("EntityComponentManager::SearchOn_EmptyEntityIds_ReturnsEmptyVector"){
    EntityComponentManager ecs;

    std::vector<int> entitiesToSearchOn;;

    std::vector<int> matchingEntityIds = ecs.SearchOn<TestComponent>(entitiesToSearchOn);

    REQUIRE(matchingEntityIds.empty() == true);
}

SCENARIO("EntityComponentManager::Search_MatchingEntities_ReturnsVectorWithMatchingIds"){
    EntityComponentManager ecs;

    std::shared_ptr<int> entityPtr = ecs.AddEntity();
    int entityId = *entityPtr.get();

    ecs.AddComponent<TestComponent>(entityId);

    ecs.AddEntity();

    std::vector<int> matchingEntityIds = ecs.Search<TestComponent>();

    REQUIRE(matchingEntityIds.empty() == false);
    REQUIRE(matchingEntityIds.size() == 1);
    REQUIRE(matchingEntityIds[0] == entityId);
}

SCENARIO("EntityComponentManager::Search_NoMatchingEntities_ReturnsEmptyVector"){
    EntityComponentManager ecs;

    std::vector<int> matchingEntityIds = ecs.Search<TestComponent>();

    REQUIRE(matchingEntityIds.empty() == true);
}

SCENARIO("EntityComponentManager::GetComponent_NonExistingComponent_ReturnsNull"){
    EntityComponentManager ecs;
    std::shared_ptr<int> entityPtr = ecs.AddEntity();
    int entityId = *entityPtr.get();

    std::shared_ptr<TestComponent> testComponentPtr = ecs.GetComponent<TestComponent>(entityId);
    REQUIRE(testComponentPtr == nullptr);
}

SCENARIO("EntityComponentManager::GetComponent_ExistingComponent_ReturnsExistingComponentForEntity"){
    EntityComponentManager ecs;
    std::shared_ptr<int> entityPtr = ecs.AddEntity();
    int entityId = *entityPtr.get();

    ecs.AddComponent<TestComponent>(entityId);

    std::shared_ptr<TestComponent> testComponentPtr = ecs.GetComponent<TestComponent>(entityId);
    REQUIRE(testComponentPtr != nullptr);
}

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
