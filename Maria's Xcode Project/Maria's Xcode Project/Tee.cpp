#include "Tee.h"
#include "CircleCollider.h"
#include <gl/freeglut.h>

Tee::Tee(int id, Vector3f pos)
: pos(pos)
, tileID(id)
{
	color = { 0.0, 1.0, 1.0, 1.0 };
	dimensions.height = .05;
	dimensions.slices = 7;
	dimensions.radius = .02;
	dimensions.stacks = 3;

	setCollider(CircleCollider(pos, dimensions.radius));
}

void Tee::update(float dt)
{
	// Update children
	std::vector<SceneNode*> children = getChildren();
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->update(dt);
	}
}

void Tee::draw()
{
	glPushMatrix();

	// create the quadratic
	GLUquadricObj *quadratic2;
	quadratic2 = gluNewQuadric();

	// Move the cylinder
	glTranslatef(pos.x, pos.y + .05, pos.z);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

	// Set the color
	glColor4f(color.x, color.y, color.z, color.w);

	// Draw the cylinder
	gluCylinder(quadratic2, dimensions.radius, dimensions.radius, dimensions.height, dimensions.slices, dimensions.stacks);

	glPopMatrix();

	// Draw children
	std::vector<SceneNode*> children = getChildren();
	for (auto itr = children.begin(); itr != children.end(); itr++) {
		(*itr)->draw();
	}
}