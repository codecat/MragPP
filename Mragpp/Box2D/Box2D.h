/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BOX2D_H
#define BOX2D_H

/**
\mainpage Box2D API Documentation

\section intro_sec Getting Started

For documentation please see http://box2d.org/documentation.html

For discussion please visit http://box2d.org/forum
*/

// These include files constitute the main Box2D API

#include <Mragpp/Box2D/Common/b2Settings.h>
#include <Mragpp/Box2D/Common/b2Draw.h>
#include <Mragpp/Box2D/Common/b2Timer.h>

#include <Mragpp/Box2D/Collision/Shapes/b2CircleShape.h>
#include <Mragpp/Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Mragpp/Box2D/Collision/Shapes/b2ChainShape.h>
#include <Mragpp/Box2D/Collision/Shapes/b2PolygonShape.h>

#include <Mragpp/Box2D/Collision/b2BroadPhase.h>
#include <Mragpp/Box2D/Collision/b2Distance.h>
#include <Mragpp/Box2D/Collision/b2DynamicTree.h>
#include <Mragpp/Box2D/Collision/b2TimeOfImpact.h>

#include <Mragpp/Box2D/Dynamics/b2Body.h>
#include <Mragpp/Box2D/Dynamics/b2Fixture.h>
#include <Mragpp/Box2D/Dynamics/b2WorldCallbacks.h>
#include <Mragpp/Box2D/Dynamics/b2TimeStep.h>
#include <Mragpp/Box2D/Dynamics/b2World.h>

#include <Mragpp/Box2D/Dynamics/Contacts/b2Contact.h>

#include <Mragpp/Box2D/Dynamics/Joints/b2DistanceJoint.h>
#include <Mragpp/Box2D/Dynamics/Joints/b2FrictionJoint.h>
#include <Mragpp/Box2D/Dynamics/Joints/b2GearJoint.h>
#include <Mragpp/Box2D/Dynamics/Joints/b2MotorJoint.h>
#include <Mragpp/Box2D/Dynamics/Joints/b2MouseJoint.h>
#include <Mragpp/Box2D/Dynamics/Joints/b2PrismaticJoint.h>
#include <Mragpp/Box2D/Dynamics/Joints/b2PulleyJoint.h>
#include <Mragpp/Box2D/Dynamics/Joints/b2RevoluteJoint.h>
#include <Mragpp/Box2D/Dynamics/Joints/b2RopeJoint.h>
#include <Mragpp/Box2D/Dynamics/Joints/b2WeldJoint.h>
#include <Mragpp/Box2D/Dynamics/Joints/b2WheelJoint.h>

#endif
