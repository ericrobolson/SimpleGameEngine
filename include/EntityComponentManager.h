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
            std::vector<int> Search(){
                return SearchOn<TComponent>(_takenEntityIds);
            }

            template <class TComponent>
            std::vector<int> SearchOn(std::vector<int> entityIds){
                std::vector<int> matchingEntityIds;
                matchingEntityIds.reserve(entityIds.size());

                int entityId = -1;

                std::vector<int>::iterator ptr;
                for (ptr = entityIds.begin(); ptr < entityIds.end(); ptr++){
                    entityId = *ptr;

                    if (GetComponent<TComponent>(entityId) != nullptr){
                        matchingEntityIds.push_back(entityId);
                    }
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
                        }                    }

                    componentTable[entityId] = std::make_shared<TComponent>();

                    std::shared_ptr<TComponent> component = std::dynamic_pointer_cast<TComponent>(componentTable[entityId]);

                return *component.get();
            };

            std::shared_ptr<int> AddEntity();

            void MarkEntityInactive(int entityId); // marks the given entity as inactive and adds it to the list of inactiveEntityIds
            void DeleteAllInactiveEntities();

        private:
            /// Get a list of entityIds that have the given component from a list of entities

            std::vector<int> _inactiveEntityIds; // a list of all entity ids to cleanup


            std::vector<int> _availableEntityIds; // a list of all available entity ids

            std::vector<int>  _takenEntityIds; // a list of entity ids that are taken


            int _componentTypesAdded;


            ComponentTypeMap _componentTables;
    };
}


#endif // ENTITYCOMPONENTMANAGER_H
