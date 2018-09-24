#ifndef ENTITYCOMPONENTMANAGER_H
#define ENTITYCOMPONENTMANAGER_H


class EntityComponentManager
{
    public:
        const int MAXNUMBEROFENTITIES = 1'000'000; // Should be smaller than 2147483647, the maximum int size as that's what's used to declare the size of arrays of components

        EntityComponentManager();
        virtual ~EntityComponentManager();

        int? AddEntity(){
            // get first available id from id pool


        }; // Returns the id of the added entity; if no entity was added, return null. This may be the case if there are no available free ids

        // Add that component to the entity.
        // See if that 'table', or the place in memory for that component type exists.
        // If 'table' does exist, check to see if GetComponent() exists. if so, then return that item.
        // If 'table' does not exist, then initialize a new fixed array of size MAXNUMBEROFENTITIES, for that component type, setting each item to null.
        // Basically, an entity is an index, or arrayComponents[entityId]. If arrayComponents[entityId] is null, that means there's no component for that entity.
        // Now, add the component to the index of 'entityId'
        // Return the component
        template <class TComponent>
        TComponent& AddComponent(int entityId){
            TComponent[]  componentTable = _componentTables.Find(typeid(TComponent).name());

            if (componentTable == nullptr){
                componentTable = new TComponent[MAXNUMBEROFENTITIES];
                for (int i = 0; i < MAXNUMBEROFENTITIES; i++){
                    componentTable[i] = nullptr;
                }
            } else{
                TComponent component = componentTable[entityId];

                if (component != nullptr){
                    return component;
                }
            }

            componentTable[entityId] = new TComponent();

            return componentTable[entityId];
        };

        TComponent& GetComponent(int entityId, TComponentType) // gets the type of component for that entity, returns null if that component was not found

        void MarkEntityInactive(int entityId); // marks the given entity as inactive and adds it to the list of inactiveEntityIds

        int GetEntitiesCount(); // get an count of all active entities

        void AddSearch(TComponent) // adds to the end of _typesOfComponentsToSearch the type of component to search on
        list int ExecuteSearch() // returns a list of entity ids with the given search; starts off by calling ExecuteSearch(list int idsToSearch) on all entity ids
        {
            list int matchingIds = ExecuteSearch(allIds);

            // Always reset the search, in case the list of matching entities was empty and there are still search terms left. This allows it to always start fresh so other classes don't have to call reset.
            _typesOfComponentsToSearch.clear();


            return matchingIds;
        }


        // deletes all inactive entities and components, and then adds those deleted ids to the free id pool; should always be called at the end of the game loop, during the cleanup phase
        // clears the inactiveEntityIds and takenEntityIds after processing and adds them back to the availableEntityIds
        void DeleteInactiveEntites();


    protected:

    private:
        list <BaseComponent[], componenttypename> _componentTables; // a list of tuples, one containing the typeid(componentTye).name() string and one containing an array of those pointers
        list TypesOfComponentsToSearch _typesOfComponentsToSearch; // the list of types of components to search for; implemented as a queue

        list int inactiveEntityIds; // a list of all entity ids to cleanup

        list int availableEntityIds; // a list of all available entity ids
        list int takenEntityIds; // a list of entity ids that are taken

        // given the list of ids to search, dequeue the the next _typesOfComponentsToSearch item,
        // then return a subset of idsToSearch that meet the _typesOfComponentsToSearch item.
        // Use the GetComponent(entityId, TComponentTYpe) to see if the entity has that component
        // If _typepsOfComponentsToSearch is empty, reeturn the entity ids. If the idsToSearch is empty, then return empty list
        list int ExecuteSearch(list int idsToSearch)
};

#endif // ENTITYCOMPONENTMANAGER_H
