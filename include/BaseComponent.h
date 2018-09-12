#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H


class BaseComponent
{
    public:
        BaseComponent();
        virtual ~BaseComponent();
        int GetId() const;
        bool operator==(const BaseComponent &c1);

    protected:

    private:
        static int nextGlobalId;
        int _id;
};

#endif // BASECOMPONENT_H
