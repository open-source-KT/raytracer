#pragma once

#include "Vector.h"
#include "Color.h"
#include "Object.h"


class Sphere : public Object{
    Vector centre;
    double radius;
    Color color;

    public:
        Sphere();
        Sphere(Vector,double,Color);

        Vector getSphereCentre(){return centre;}
        double getSphereRadius(){return radius;}
        Color getColor(){return color;}

        Vector getNormalAt(Vector point)
        {
            //Normal always points away from the center of the sphere. Orphographic to the tangent
            Vector normal_vector = point.vectorAdd(centre.getNegative()).getNormalized();//Vector from centre of sphere to point 
            return  normal_vector;

        }

        //Returns the istance of the intersection form ray origin if there is any.
        virtual double findIntersection(Ray ray)
        {
            Vector rayOrigin = ray.getRayOrigin();
            double rayOriginX = rayOrigin.getVectorX();
            double rayOriginY =  rayOrigin.getVectorY();
            double rayOriginZ =  rayOrigin.getVectorZ();

            Vector rayDirection = ray.getRayDirection();
            double rayDirectionX = rayDirection.getVectorX();
            double rayDirectionY =  rayDirection.getVectorY();
            double rayDirectionZ =  rayDirection.getVectorZ();

            Vector sphereCentre = centre;
            double sphereCentreX = sphereCentre.getVectorX();
            double sphereCentreY = sphereCentre.getVectorY();
            double sphereCentreZ = sphereCentre.getVectorZ();


            // (x - centreX) ^ 2 + (y - centreY) ^ 2 + (centreZ ^2) = radius^2   -rayDirXx + rayDirYy - rayDirZz =  rayOriginX + rayOriginY + rayOriginZ 
            // x = rayOriginX/rayDirX - centre ^ 2


            double a = 1; /*Coefficiant of quadratic , 1 because the ray direction is normalised i guess*/
            double b = (2 * (rayOriginX - sphereCentreX) * rayDirectionX) + (2 * (rayOriginY - sphereCentreY) * rayDirectionY)  + (2 * (rayOriginZ - sphereCentreZ) * rayDirectionZ);
            double c =  pow(rayOriginX - sphereCentreX,2) + pow(rayOriginY - sphereCentreY,2) + pow(rayOriginZ - sphereCentreZ,2) - (radius * radius); //Distance squared of the surface of the sphere (why we minus the radius) to the ray origin

            double discriminant = b * b - 4*c;

            if(discriminant > 0) //Ray intersects the sphere (twice), The one that is closer to the camera will be the intersection point
            {
                double root1  = ((-1 * b - sqrt(discriminant))/2) - 0.0000001;
                if(root1 > 0){
                    //First root is the smallest possible root
                    return root1;
                }
                else{
                    double root2 = ((sqrt(discriminant) - b)/2) - 0.0000001; 
                    return root2;
                }
            }
            else{ /* Ray missed the sphere. I guess it could be at a tangent and have one root but doesn't really matter for lighting/casting shadows*/
                return -1;
            }
        }



};


Sphere::Sphere()
: centre(Vector(0,0,0)),radius(1.0), color(Color(1,0,0,1))
{
}
Sphere::Sphere(Vector p,double r, Color c)
:centre(p),radius(r),color(c)
{
}



