#include <iomanip>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

class Obj
{
    protected:
        float height;
    public:
        Obj(float v) : height(v)
        {
            height = v;
        }
        virtual float volume() const = 0;
};


class Rect_prism : public Obj
{
        float a;
        float b;
    public:
        Rect_prism(float a, float b, float h) : Obj(h)
        {
            a = a;
            b = b;
        }
        float volume() const override
        {
            return a * b * height;
        }
};


class CircFoundation : public Obj
{
    protected:
        float radius;
        CircFoundation(float r, float h) : Obj(h)
        {
            radius = r;
        }
    public:
        float area() const {
            return M_PI * radius * radius;
        }
};


class Cylinder : public CircFoundation
{
    public:
        Cylinder(float r, float h) : CircFoundation(r, h) {}
        float volume() const override
        {
            return area() * height;
        }
};


class Cone : public CircFoundation
{
    public:
        Cone(float r, float h) : CircFoundation(r, h) {}
        float volume() const override
        {
            return area() * height / 3.0f;
        }
};


int main()
{
    return 0;
}