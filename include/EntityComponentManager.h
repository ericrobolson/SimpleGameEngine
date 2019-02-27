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
    static const int MAXNUMBEROFENTITIES = 500; // Until multithreading is implemented, acceptable limit is 100
    static const int MAXNUMBEROFCOMPONENTTABLES = 200;

    typedef std::unordered_map<std::type_index, std::shared_ptr<BaseComponent>[MAXNUMBEROFENTITIES]> ComponentTypeMap;

    class EntityComponentManager
    {
        public:
            EntityComponentManager(){
                // Initialize the list of free entity ids
                for (int i = 0; i < MAXNUMBEROFENTITIES; i++){
                    _availableEntityIds.push_back(i);
                }

                _componentTypesAdded = 0;
            }



            virtual ~EntityComponentManager(){
                // mark all entities as inactive, so that they are marked for cleanup
                std::unique_lock<std::mutex> lock(_resourceMutex);

                while(_takenEntityIds.empty() == false){
                    int entityId = _takenEntityIds.back();

                    _takenEntityIds.pop_back();

                    MarkEntityInactive_ThreadSafe(entityId);
                }

                DeleteAllInactiveEntities_ThreadSafe();
            }

            /// gets the type of component for that entity, returns null if that component was not found
            template <class TComponent>
            std::shared_ptr<TComponent> GetComponent(int entityId){
                std::unique_lock<std::mutex> lock(_resourceMutex);
                return GetComponent_ThreadSafe<TComponent>(entityId);
            };

            /// Get a list of entityIds that have the given component while applying the filter lambda
            template <class TComponent>
            std::vector<int> Search(std::function<bool(TComponent c)> const& filterLambda){
                std::unique_lock<std::mutex> lock(_resourceMutex);
                return SearchOn_ThreadSafe<TComponent>(_takenEntityIds, filterLambda);
            }

            /// Get a list of entityIds that have the given component
            template <class TComponent>
            std::vector<int> Search(){
                std::unique_lock<std::mutex> lock(_resourceMutex);
                return SearchOn_ThreadSafe<TComponent>(_takenEntityIds);
            }

            template <class TComponent>
            std::vector<int> SearchOn(std::vector<int> entityIds){
                std::unique_lock<std::mutex> lock(_resourceMutex);
                return SearchOn_ThreadSafe<TComponent>(entityIds);
            }

            template <class TComponent>
            std::vector<int> SearchOn(std::vector<int> entityIds, std::function<bool(TComponent c)> const& filterLambda){
                std::unique_lock<std::mutex> lock(_resourceMutex);
                return SearchOn_ThreadSafe<TComponent>(entityIds, filterLambda);
            }


            template <class TComponent>
            TComponent& AddComponent(int entityId){
                std::unique_lock<std::mutex> lock(_resourceMutex);
                return AddComponent_ThreadSafe<TComponent>(entityId);
            };

            template <class TComponent>
            void RemoveComponent(int entityId){
                std::unique_lock<std::mutex> lock(_resourceMutex);
                RemoveComponent_ThreadSafe<TComponent>(entityId);
            };

            std::shared_ptr<int> AddEntity(){
                std::unique_lock<std::mutex> lock(_resourceMutex);
                return AddEntity_ThreadSafe();
            }

            void MarkEntityInactive(int entityId){
                std::unique_lock<std::mutex> lock(_resourceMutex);
                MarkEntityInactive_ThreadSafe(entityId);
            }

            void DeleteAllInactiveEntities(){
                std::unique_lock<std::mutex> lock(_resourceMutex);
                DeleteAllInactiveEntities_ThreadSafe();
            }

            void Reset(){
                std::unique_lock<std::mutex> lock(_resourceMutex);
                while(_takenEntityIds.empty() == false){
                    int entityId = _takenEntityIds.back();

                    _takenEntityIds.pop_back();

                    MarkEntityInactive_ThreadSafe(entityId);
                }

                DeleteAllInactiveEntities_ThreadSafe();
            }


        private:
            std::mutex _resourceMutex;

            std::vector<int> _inactiveEntityIds; // a list of all entity ids to cleanup
            std::vector<int> _availableEntityIds; // a list of all available entity ids
            std::vector<int>  _takenEntityIds; // a list of entity ids that are taken

            int _componentTypesAdded;
            ComponentTypeMap _componentTables;

            //Note: Private functions assume control of the lock
            void DeleteAllInactiveEntities_ThreadSafe(){
                int entityId = -1;

                while (_inactiveEntityIds.empty() == false){
                    entityId = _inactiveEntityIds.back();

                    // Delete components for entity
                    for (auto it = _componentTables.begin(); it != _componentTables.end(); ++it){
                        if (it->second[entityId] != nullptr){
                            delete it->second[entityId].get();
                        }
                    }

                    _inactiveEntityIds.pop_back();
                    _availableEntityIds.push_back(entityId);
                }

                _takenEntityIds.clear();
            }

            void MarkEntityInactive_ThreadSafe(int entityId){
                _inactiveEntityIds.push_back(entityId);
            }

            std::shared_ptr<int> AddEntity_ThreadSafe(){
                int entityId = -1;

                if (_availableEntityIds.empty() == false){
                    entityId = _availableEntityIds.back();

                    _availableEntityIds.pop_back();
                    _takenEntityIds.push_back(entityId);
                }

                if (entityId == -1){
                    return nullptr;
                }

                return std::make_shared<int>(entityId);
            }

            template <class TComponent>
            std::shared_ptr<TComponent> GetComponent_ThreadSafe(int entityId){
                    if (_componentTables[typeid(TComponent)] == nullptr){
                        return nullptr;
                    }

                    std::shared_ptr<TComponent> component = std::dynamic_pointer_cast<TComponent>(_componentTables[typeid(TComponent)][entityId]);
                return component;
            };

            template <class TComponent>
            TComponent& AddComponent_ThreadSafe(int entityId){
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
                    std::shared_ptr<TComponent> component = GetComponent_ThreadSafe<TComponent>(entityId);

                    if (component != nullptr){
                        return *component.get();
                    }
                 }

                componentTable[entityId] = std::make_shared<TComponent>();

                std::shared_ptr<TComponent> component = std::dynamic_pointer_cast<TComponent>(componentTable[entityId]);

                return *component.get();
            };

            template <class TComponent>
            std::vector<int> SearchOn_ThreadSafe(std::vector<int> entityIds, std::function<bool(TComponent c)> const& filterLambda){
                std::vector<int> matchingEntityIds;
                matchingEntityIds.reserve(entityIds.size());

                int entityId = -1;

                std::vector<int>::iterator ptr;
                for (ptr = entityIds.begin(); ptr < entityIds.end(); ptr++){
                    entityId = *ptr;

                    std::shared_ptr<TComponent> componentPtr = GetComponent_ThreadSafe<TComponent>(entityId);

                    if (componentPtr != nullptr){
                        if (filterLambda(*componentPtr.get())){
                            matchingEntityIds.push_back(entityId);
                        }
                    }
                }

                return matchingEntityIds;
            }

            template <class TComponent>
            std::vector<int> SearchOn_ThreadSafe(std::vector<int> entityIds){
                return SearchOn_ThreadSafe<TComponent>(entityIds, [](TComponent c){return true;} );
            }

            template <class TComponent>
            void RemoveComponent_ThreadSafe(int entityId){
                std::shared_ptr<BaseComponent> *componentTable = _componentTables[typeid(TComponent)];

                if (componentTable[entityId] != nullptr){
                    delete componentTable[entityId].get();
                }
            }

    };
}


#endif // ENTITYCOMPONENTMANAGER_H
