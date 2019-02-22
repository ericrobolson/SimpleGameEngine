#ifndef MASSDATA_H
#define MASSDATA_H

namespace SGE_Physics{
class MassData
{
    public:
        MassData();
        virtual ~MassData();

        float Mass;
        float InverseMass;

        float Inertia;
        float InverseInertia;

        bool MassIsCalculated; // As this is a storage container for Mass, need to set it based on the Shape + Density and other factors
        bool InertiaIsCalculated; //

    protected:

    private:
};

}

#endif // MASSDATA_H
