#pragma once

#include "Vector.h"
#include "Color.h"
#include "Object.h"
#include "Ray.h"
#include "Source.h"
#include <vector>

class World{
    private:
        Vector O;
        Vector X;
        Vector Y;
        Vector Z;

        Color backgroundColor;
    public:
        std::vector<Object*>worldObjects;
        std::vector<Source*>worldLights;




        World()
        :O(Vector(0,0,0)), X(Vector(1,0,0)), Y(Vector(0,1,0)), Z(Vector(0,0,1)), backgroundColor(Color(0,0,0,0))
        {}

        World(Vector origin, Vector Xaxis, Vector Yaxis, Vector Zaxis, Color color)
        :O(origin), X(Xaxis), Y(Yaxis), Z(Zaxis), backgroundColor(color)
        {}

        std::vector<double> findIntersections(Ray cameraRay)
        {
            std::vector<double> intersections;
            for(int i = 0; i < worldObjects.size(); i++)
            {
                intersections.push_back(worldObjects[i]->findIntersection(cameraRay));
            }
            return intersections;
        }

        Vector getO(){
            return O;
        }
        Vector getX(){
            return X;
        }

        Vector getY(){
            return Y;
        }
           
        Vector getZ(){
            return Z;
        }

        Color getBackgroundColor(){
            return backgroundColor;
        }


};
