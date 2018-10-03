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
#include <mutex>

namespace ECS{
    static const int MAXNUMBEROFENTITIES = 10000; // Until multithreading is implemented, acceptable limit is 100
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
            std::vector<int> SearchAll(){
                std::vector<int> matchingEntityIds;
                std::size_t quarterSize = _takenEntityIds.size() / 4;

                std::thread t1([&]() {
                              Search<TComponent>(_takenEntityIds, 0, quarterSize, matchingEntityIds);
                              });

                std::thread t2([&]() {
                              Search<TComponent>(_takenEntityIds, quarterSize, 2 * quarterSize, matchingEntityIds);
                              });

               std::thread t3([&]() {
                      Search<TComponent>(_takenEntityIds, 2 * quarterSize, 3 * quarterSize, matchingEntityIds);
                      });

                std::thread t4([&]() {
                      Search<TComponent>(_takenEntityIds, 3 * quarterSize, 4 * quarterSize, matchingEntityIds);
                      });


                t1.join();
                t2.join();
                t3.join();
                t4.join();

                return matchingEntityIds;
            }

            /// Get a list of entityIds that have the given component from a list of entities
            template <class TComponent>
            void Search(std::vector<int> entityIds, int searchStartIndex, std::size_t searchEndIndex, std::vector<int>& matchingEntityIds){


                int entityId = -1;
                std::vector<int>::iterator ptr;

                for (ptr = entityIds.begin() + searchStartIndex; ptr < entityIds.begin() + searchEndIndex; ptr++){
                    entityId = *ptr;

                     if (GetComponent<TComponent>(entityId) != nullptr){

                        std::lock_guard<std::mutex> guard(_searchMutex);
                        matchingEntityIds.push_back(entityId);


                        //matchingEntityIds.insert(matchingEntityIds.begin() + insertIndex, entityId);
                        //insertIndex++;

                    }
                }
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
            std::mutex _searchMutex;
            std::vector<int> _inactiveEntityIds; // a list of all entity ids to cleanup
            std::vector<int> _availableEntityIds; // a list of all available entity ids
            std::vector<int>  _takenEntityIds; // a list of entity ids that are taken
            int _componentTypesAdded;
            ComponentTypeMap _componentTables;
    };
}


#endif // ENTITYCOMPONENTMANAGER_H
