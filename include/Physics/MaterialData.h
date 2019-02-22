#ifndef MATERIAL_H
#define MATERIAL_H

namespace SGE_Physics{
    class MaterialData
    {
        public:
            MaterialData();
            virtual ~MaterialData();

            float Density;
            float Restitution;
    };
}

#endif // MATERIAL_H
