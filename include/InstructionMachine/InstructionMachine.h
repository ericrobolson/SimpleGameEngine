#ifndef INSTRUCTIONMACHINE_H
#define INSTRUCTIONMACHINE_H


/*
    Example instruction for attacking:
        int p = SelectPlayerEntity()
        int e = SelectEnemyEntity(GetEntityPosition(p), GetEntityRange(p))
        if (IsValidId(e){
            SetEntityWounds(GetEntityWounds(e) - GetEntityStrength(i))
        }

    Example instruction for moving:
        SetEntityPosition(SelectMove(SelectPlayerEntity()))

    Example cards:
        Move target unit you control up to it's movement
        Target unit you control makes an attack against target unit
        Gain 4 energy
        Draw 1 card, discard 1 card
        Next attack you make has Poison
        Next attack you make has Stun
        Next attack you make has Blind
        Protect target unit you control from next attack
        Target unit gains 1 STR
        Target unit gains 4 HP
        Target unit gains 4 Shield
        Create Aura (4), all units within it have +3 STR (Aura's have size X, which decreases by 1 each round until it vanishes)
*/

namespace SGE{
class InstructionMachine
{
    public:
        InstructionMachine();
        virtual ~InstructionMachine();

        enum Instructions{
            Literal = 0x00,
            Add = 0x01,
            Subtract = 0x02,
            Multiply = 0x03,
            Divide = 0x04
        };

        void Execute(char bytecode[], int sizeOfInstructions);

        int Peek();

    protected:

    private:
        static const int MAXSTACK = 128;
        int _stackSize = 0;
        int _stack[MAXSTACK];

        void Push(int i);
        int Pop();

/*
        int TargetUnitYouControl();
        int TargetUnitYouDontControl();
        int TargetUnit();

        void UnitAttacksOtherUnit(int unit1Id, int unit2Id);

        int GetUnitStrength(int unitId);
        int SetUnitStrength(int unitId, int amount);
        int ResetUnitStrength(int unitId);

        int GetUnitHealth(int unitId);
        int SetUnitHealth(int unitId, int amount);
        int ResetUnitHealth(int unitId);

        int GetUnitRange(int unitId);
        int SetUnitRange(int unitId, int amount);
        int ResetUnitRange(int unitId);

        int GetUnitMovement(int unitId);
        int SetUnitMovement(int unitId, int amount);
        int ResetUnitMovement(int unitId);

        int GetUnitWeaponSkill(int unitId);
        int SetUnitWeaponSkill(int unitId, int amount);
        int ResetUnitWeaponSkill(int unitId);

        int DrawCards(int playerId, int numberOfCards);
        int DiscardCards(int playerId, int numberOfCards);
        int DiscardHand(int playerId);

        int GetEnergy(int playerId);
        int SetEnergy(int playerId);

        */
};


}

#endif // INSTRUCTIONMACHINE_H
