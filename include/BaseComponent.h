#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H


class BaseComponent
{
    public:
        BaseComponent();
        virtual int GetType();
        virtual ~BaseComponent();
        int GetId() const;
        bool operator==(const BaseComponent &c1);

    private:
        static int nextGlobalId;
        int _id;
};

#endif // BASECOMPONENT_H
