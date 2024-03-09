#include "shape.h"
class Factory {
    Factory(TypeNewObject FindPointWithRatio, Shape* obj1,Shape* obj2, double ratio) {
        Point* pnt1 = dynamic_cast<Point*>(obj1);
        Point* pnt2 = dynamic_cast<Point*>(obj2);
        newObject = new PointByTwoPoints(pnt1, pnt2, ratio);
    }
    
   Shape* createNewObject();


   Shape* newObject;
};
