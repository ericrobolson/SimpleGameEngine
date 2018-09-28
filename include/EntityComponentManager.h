#ifndef ENTITYCOMPONENTMANAGER_H
#define ENTITYCOMPONENTMANAGER_H
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <list>
#include "BaseComponent.h"

static const int MAXNUMBEROFENTITIES = 100'000; // Should be smaller than 2147483647, the maximum int size as that's what's used to declare the size of arrays of components


typedef std::unordered_map<std::type_index, BaseComponent[MAXNUMBEROFENTITIES]> ComponentTypeMap;

class EntityComponentManager
{
    public:
        static const int MAXNUMBEROFCOMPONENTTABLES = 200;
        static bool IsValidId(int id); // returns whether the id is valid or not

        EntityComponentManager();
        virtual ~EntityComponentManager();

        int AddEntity(); // Returns the id of the added entity, which is the first free identity; if no entity was added, return -1. This may be the case if there are no available free ids.

        void MarkEntityInactive(int entityId); // marks the given entity as inactive and adds it to the list of inactiveEntityIds

        int GetEntitiesCount(); // get an count of all active entities

        // deletes all inactive entities and components, and then adds those deleted ids to the free id pool; should always be called at the end of the game loop, during the cleanup phase
        // clears the inactiveEntityIds and takenEntityIds after processing and adds them back to the availableEntityIds
        void DeleteAllInactiveEntities();

        // Add that component to the entity.
        // See if that 'table', or the place in memory for that component type exists.
        // If 'table' does exist, check to see if GetComponent() exists. if so, then return that item.
        // If 'table' does not exist, then initialize a new fixed array of size MAXNUMBEROFENTITIES, for that component type, setting each item to null.
        // Basically, an entity is an index, or arrayComponents[entityId]. If arrayComponents[entityId] is null, that means there's no component for that entity.
        // Now, add the component to the index of 'entityId'takenEntityIds
        // Return the component
        template <class TComponent>
        TComponent& AddComponent(int entityId){
            BaseComponent *componentTable = _componentTables[typeid(TComponent)];

            if (componentTable == nullptr){
                if (_componentTypesAdded >= MAXNUMBEROFCOMPONENTTABLES){
                    throw "component types added has exceeded maximum number of component types in memory.";
                }

                _componentTypesAdded++;
                BaseComponent *newTable = new TComponent[MAXNUMBEROFENTITIES];

                componentTable = newTable;
                for (int i = 0; i < MAXNUMBEROFENTITIES; i++){

//                    componentTable[i] = nullptr;
                }

                //_componentTables[typeid(TComponent)] = componentTable;

            } else{
                TComponent *component = &dynamic_cast<TComponent&>(componentTable[entityId]);

                if (component != nullptr){
                    return *component;
                }
            }

            componentTable[entityId] = *new TComponent();

            return dynamic_cast<TComponent&>(componentTable[entityId]);
        };

        // gets the type of component for that entity, returns null if that component was not found
        template <class TComponent>
        TComponent* GetComponent(int entityId){
            BaseComponent* componentTable = _componentTables[typeid(TComponent)];

            if (componentTable == nullptr){
                return nullptr;
            }

            TComponent *component = &dynamic_cast<TComponent&>(componentTable[entityId]);


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

    private:
        std::list<int> _inactiveEntityIds; // a list of all entity ids to cleanup
        std::list<int> _availableEntityIds; // a list of all available entity ids
        std::list<int>  _takenEntityIds; // a list of entity ids that are taken
        int _componentTypesAdded;
        ComponentTypeMap _componentTables;
};

#endif // ENTITYCOMPONENTMANAGER_H
