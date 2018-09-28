#ifndef NEWENTITYCOMPONENTMANAGER_H
#define NEWENTITYCOMPONENTMANAGER_H
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <list>
#include "BaseComponent.h"


namespace ECS{
    static const int MAXNUMBEROFENTITIES = 100'000; // Should be smaller than 2147483647, the maximum int size as that's what's used to declare the size of arrays of components
    static const int MAXNUMBEROFCOMPONENTTABLES = 200;

    typedef std::unordered_map<std::type_index, std::shared_ptr<BaseComponent>[MAXNUMBEROFENTITIES]> ComponentTypeMap;
    class NewEntityComponentManager
    {
        public:
            NewEntityComponentManager();
            virtual ~NewEntityComponentManager();

            /// gets the type of component for that entity, returns null if that component was not found
            template <class TComponent>
            std::shared_ptr<TComponent>& GetComponent(int entityId){
                std::shared_ptr<BaseComponent> componentTable[MAXNUMBEROFENTITIES] = _componentTables[typeid(TComponent)];

                if (componentTable == nullptr){
                    return nullptr;
                }

                std::shared_ptr<TComponent> component = std::dynamic_pointer_cast<TComponent>(componentTable[entityId]);


                return component;
            };


            /// Get a list of entityIds that have the given component
            template <class TComponent>
            std::list<int> Search(){
                return Search<TComponent>(_takenEntityIds);
            }

            /// Get a list of entityIds that have the given component from a list of entities
            template <class TComponent>
            std::list<int> Search(std::list<int> entityIds){
                std::list<int> matchingEntityIds;

                int entityId = -1;

                while (entityIds.empty() == false){
                    entityId = entityIds.front();
                    entityIds.pop_front();

                    if (GetComponent<TComponent>(entityId) != nullptr){
                        matchingEntityIds.push_back(entityId);
                    }
                }

                return matchingEntityIds;
            }


            std::shared_ptr<int> AddEntity();

        private:
            std::list<int> _inactiveEntityIds; // a list of all entity ids to cleanup
            std::list<int> _availableEntityIds; // a list of all available entity ids
            std::list<int>  _takenEntityIds; // a list of entity ids that are taken
            int _componentTypesAdded;
            ComponentTypeMap _componentTables;
    };
}


#endif // NEWENTITYCOMPONENTMANAGER_H
