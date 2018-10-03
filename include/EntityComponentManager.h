#ifndef ENTITYCOMPONENTMANAGER_H
#define ENTITYCOMPONENTMANAGER_H
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <list>
#include "BaseComponent.h"
#include <vector>
#include <thread>
#include "JobQueue.h"



namespace ECS{
    static const int MAXNUMBEROFENTITIES = 1000; // Until multithreading is implemented, acceptable limit is 100
    static const int MAXNUMBEROFCOMPONENTTABLES = 2000;

    typedef std::unordered_map<std::type_index, std::shared_ptr<BaseComponent>[MAXNUMBEROFENTITIES]> ComponentTypeMap;

    class EntityComponentManager
    {
        public:
            EntityComponentManager();
            virtual ~EntityComponentManager();

            /// gets the type of component for that entity, returns null if that component was not found
            template <class TComponent>
            std::shared_ptr<TComponent> GetComponent(int entityId){

                if (_componentTables[typeid(TComponent)] == nullptr){
                    return nullptr;
                }

                std::shared_ptr<TComponent> component = std::dynamic_pointer_cast<TComponent>(_componentTables[typeid(TComponent)][entityId]);

                return component;
            };

            /// Get a list of entityIds that have the given component
            template <class TComponent>
            std::list<int> Search(){
                std::list<int> matchingEntityIds;

                // split up all entities into sections to search on concurrently
                const int sections = 4;
                std::size_t sizeOfSection = _takenEntityIds.size() / sections;

                std::future<std::list<int>> results[sections] = {};
                std::vector<int> sectionsNotFinished;
                sectionsNotFinished.reserve(sections);

                for (int i = 0; i < sections; i++){
                    sectionsNotFinished.push_back(i);

                    results[i] = JobQueue::Instance().enqueue([this, i,sizeOfSection](){
                                                            return Search<TComponent>(_takenEntityIds, i* sizeOfSection, (i + 1) * sizeOfSection);
                                                            });
                }

                for (int i = 0; i < sections; i++){
                    matchingEntityIds.splice(matchingEntityIds.begin(), results[i].get());
                }


                return matchingEntityIds;
            }

            template <class TComponent>
            TComponent& AddComponent(int entityId){
                std::shared_ptr<BaseComponent> *componentTable = _componentTables[typeid(TComponent)];

                if (componentTable == nullptr){
                    if (_componentTypesAdded >= MAXNUMBEROFCOMPONENTTABLES){
                        throw "component types added has exceeded maximum number of component types in memory.";
                    }

                    _componentTypesAdded++;

                    for (int i = 0; i < MAXNUMBEROFENTITIES; i++){
                       _componentTables[typeid(TComponent)][i] = nullptr;
                    }

                } else{
                    std::shared_ptr<TComponent> component = GetComponent<TComponent>(entityId);

                    if (component != nullptr){
                        return *component.get();
                    }
                }

                componentTable[entityId] = std::make_shared<TComponent>();

                std::shared_ptr<TComponent> component = std::dynamic_pointer_cast<TComponent>(componentTable[entityId]);

                return *component.get();
            };

            std::shared_ptr<int> AddEntity();

            void MarkEntityInactive(int entityId); // marks the given entity as inactive and adds it to the list of inactiveEntityIds
            void DeleteAllInactiveEntities();

        private:
            /// Get a list of entityIds that have the given component from a list of entities
            template <class TComponent>
            std::list<int> Search(std::vector<int> entityIds, int searchStartIndex, std::size_t searchEndIndex){
                std::list<int> matchingEntityIds;

                int entityId = -1;
                std::vector<int>::iterator ptr;

                for (ptr = entityIds.begin() + searchStartIndex; ptr < entityIds.begin() + searchEndIndex; ptr++){
                    entityId = *ptr;

                     if (GetComponent<TComponent>(entityId) != nullptr){
                        matchingEntityIds.push_back(entityId);
                    }
                }

                return matchingEntityIds;
            }

            std::vector<int> _inactiveEntityIds; // a list of all entity ids to cleanup
            std::vector<int> _availableEntityIds; // a list of all available entity ids
            std::vector<int>  _takenEntityIds; // a list of entity ids that are taken
            int _componentTypesAdded;
            ComponentTypeMap _componentTables;
    };
}


#endif // ENTITYCOMPONENTMANAGER_H
