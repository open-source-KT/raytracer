#pragma once

#include "Vector.h"

class Camera{
    Vector cameraPosition,cameraDirection, cameraRight, cameraDown, lookAtPos;

    public:
        Camera();
        Camera(Vector,Vector,Vector,Vector);
        

        Vector getCameraPosition(){return cameraPosition;}
        Vector getCameraDirection(){return cameraDirection;}
        Vector getCameraRight(){return cameraRight;}
        Vector getCameraDown(){return cameraDown;}


        void lookAt(Vector pos,Vector lookAt, Vector up){
            lookAtPos = lookAt;
            cameraPosition = pos;
            Vector diff_btw(pos.getVectorX() - lookAt.getVectorX(),pos.getVectorY() - lookAt.getVectorY(),pos.getVectorZ() - lookAt.getVectorZ());

            cameraDirection = diff_btw.getNegative().getNormalized();
            cameraRight = up.getCrossProductWith(cameraDirection).getNormalized();
            cameraDown = cameraRight.getCrossProductWith(cameraDirection).getNormalized();
        }

        void cameraUp(float y, bool preserve_dir = false){ 
            cameraPosition = Vector(cameraPosition.getVectorX(),cameraPosition.getVectorY() + y,cameraPosition.getVectorZ());
            
            cameraPosition = cameraPosition.vectorAdd(cameraDown.getNegative().scalarMult(y));

            if(!preserve_dir){
                lookAt(cameraPosition,lookAtPos,cameraDown.getNegative());
                }
            
            }


};


Camera::Camera()
: cameraPosition(Vector(0,0,0)), cameraDirection(Vector(0,0,1)), cameraRight(Vector(0,0,0)),cameraDown(Vector(0,0,0)), lookAtPos(Vector(0,0,0))
{
}
Camera::Camera(Vector pos, Vector dir, Vector right, Vector down)
:cameraPosition(pos), cameraDirection(dir), cameraRight(right), cameraDown(down), lookAtPos(cameraPosition.vectorAdd(cameraDirection))
{
}
