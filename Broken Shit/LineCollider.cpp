#include "LineCollider.h"
#include <iostream>
double Dot(Point& a, Point& b)                        { return (a.x()*b.x()) + (a.y()*b.y()); }
double PerpDot(Point& a, Point& b)                    { return (a.y()*b.x()) - (a.x()*b.y()); }

bool LineCollider::getCollision(Collider2D& col, Vector3f& result){

	Point A1(getA().x, getA().z);
	Point A2(getB().x, getB().z);
	Point B1(col.getA().x, col.getA().z);
	Point B2(col.getB().x, col.getB().z);

	Point a(A2 - A1);
	Point b(B2 - B1);

	double f = PerpDot(a, b);
	if (!f) return false; // lines are parallel

	Point c(B2 - A2);
	double aa = PerpDot(a, c);
	double bb = PerpDot(b, c);

	if (f < 0)
	{
		if (aa > 0)     return false;
		if (bb > 0)     return false;
		if (aa < f)     return false;
		if (bb < f)     return false;
	}
	else
	{
		if (aa < 0)     return false;
		if (bb < 0)     return false;
		if (aa > f)     return false;
		if (bb > f)     return false;
	}

	double out = 1.0 - (aa / f);
		
	result = Vector3f((B2.x() - B1.x())*out + B1.x(), result.y, (B2.y() - B1.y())*out + B1.y());
	//std::cout << "ColPos = (" << (B2.x() - B1.x())*out + B1.x() << ", " << result.y << ", " << (B2.y() - B1.y())*out + B1.y() << ")\n";
	//std::cout << "B = (" << B1.x() << ", " << 0 << ", " << B1.y() << ") - (" << B2.x() << ", " << 0 << ", " << B2.y() << ")\n";
	//system("pause");
	return true;
};