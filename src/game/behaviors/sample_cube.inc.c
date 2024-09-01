#include "src/game/rigid_body.h"
#include "actors/group0.h"
#include "src/game/rigid_body.h"

/*Vec3f Collider_Size = {37.0f, 20.0f, 25.0f};

Vec3f M_Size = {17.0f, 17.0f, 17.0f};

Vec3f Tiny_Size = {17.0f, 17.0f, 17.0f};
Vec3f Arm_Size = {11.0f, 11.0f, 11.0f};*/

Vec3f Collider_Size = {37.0f, 20.0f, 25.0f} //Vec3f Collider_Size = {22.2f, 12.0f, 15.0f};
Vec3f M_Size = {10.2f, 10.2f, 10.2f};

Vec3f Tiny_Size = {10.2f, 10.2f, 10.2f};
Vec3f Arm_Size = {6.6f, 6.6f, 6.6f};

f32 ModelScale = 0.6;

Vec3f M_Body_Verts[13] = {
	{1.0f, 1.4f, 1.0f},
	{1.0f, 1.4f, -1.0f},
    {-1.0f, 1.4f, -1.0f},
    {-1.0f, 1.4f, 1.0f},
    {2.0f, 0.0f, 2.0f},
    {2.0f, 0.0f, -2.0f},
    {3.0f, 0.0f, 0.0f},
    {-2.0f, 0.0f, -2.0f},
    {-2.0f, 0.0f, 2.0f},
    {1.0f, -1.4f, 1.0f},
    {1.0f, -1.4f, -1.0f},
    {-1.0f, -1.4f, -1.0f},
    {-1.0f, -1.4f, 1.0f}
};

Vec3f M_Limb_R_Verts[13] = {
	{1.0f, 1.0f, 2.0f},
	{1.0f, 1.0f, 1.0f},
    {-1.0f, 1.0f, 1.0f},
    {-1.0f, 1.0f, 2.0f},
    {2.0f, 0.0f, 3.0f},
    {2.0f, 0.0f, 0.5f},
    {-2.0f, 0.0f, 0.5f},
    {0.0f, 0.0f, 3.2f},
    {-2.0f, 0.0f, 3.0f},
    {1.0f, -1.0f, 2.0f},
    {1.0f, -1.0f, 1.0f},
    {-1.0f, -1.0f, 1.0f},
    {-1.0f, -1.0f, 2.0f}
};

Vec3f M_Limb_L_Verts[13] = {
	{1.0f, 1.0f, -2.0f},
	{1.0f, 1.0f, -1.0f},
    {-1.0f, 1.0f, -1.0f},
    {-1.0f, 1.0f, -2.0f},
    {2.0f, 0.0f, -3.0f},
    {2.0f, 0.0f, -0.5f},
    {-2.0f, 0.0f, -0.5f},
    {0.0f, 0.0f, -3.2f},
    {-2.0f, 0.0f, -3.0f},
    {1.0f, -1.0f, -2.0f},
    {1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f, -2.0f}
};

Vec3f M_Head_Verts[12] = {
	{1.0f, 0.5f, 1.0f},
	{1.0f, 0.5f, -1.0f},
    {2.0f, 0.5f, -1.0f},
    {2.0f, 0.5f, 1.0f},
    {3.0f, 0.0f, 2.0f},
    {3.0f, 0.0f, -2.0f},
    {0.5f, 0.0f, -2.0f},
    {0.5f, 0.0f, 2.0f},
    {1.0f, -0.5f, 1.0f},
    {1.0f, -0.5f, -1.0f},
    {2.0f, -0.5f, -1.0f},
    {2.0f, -0.5f, 1.0f}
};

Vec3f M_Plane_Verts[8] = {
	{1.0f, 0.2f, 1.0f},
	{1.0f, 0.2f, -1.0f},
    {3.0f, 0.2f, -1.0f},
    {3.0f, 0.2f, 1.0f},
    {1.0f, -0.2f, 1.0f},
	{1.0f, -0.2f, -1.0f},
    {3.0f, -0.2f, -1.0f},
    {3.0f, -0.2f, 1.0f}
};

Vec3f M_Leg_Verts[13] = {
	{-1.0f, 0.5f, 1.0f},
	{-1.0f, 0.5f, -1.0f},
    {-2.0f, 0.5f, -1.0f},
    {-2.0f, 0.5f, 1.0f},
    {0.0f, 0.0f, 2.0f},
    {0.0f, 0.0f, -2.0f},
    {-2.0f, 0.0f, -2.0f},
    {-2.2f, 0.0f, 0.0f},
    {-2.0f, 0.0f, 2.0f},
    {-1.0f, -0.5f, 1.0f},
    {-1.0f, -0.5f, -1.0f},
    {-2.0f, -0.5f, -1.0f},
    {-2.0f, -0.5f, 1.0f}
};

struct MeshInfo Ball_Mesh = {
    M_Body_Verts,
    NULL,
    NULL,
    NULL,
    12, // Number of vertices
    0,
    0,
    0
};

struct MeshInfo Collider_Mesh = {
    M_Body_Verts,
    NULL,
    NULL,
    NULL,
    13, // Number of vertices
    0,
    0,
    0
};

struct MeshInfo M_Body_Mesh = {
    M_Body_Verts,
    NULL,
    NULL,
    NULL,
    13, // Number of vertices
    0,
    0,
    0
};

struct MeshInfo M_Head_Mesh = {
    M_Head_Verts,
    NULL,
    NULL,
    NULL,
    12, // Number of vertices
    0,
    0,
    0
};

struct MeshInfo M_Limb_R_Mesh = {
    M_Limb_L_Verts,
    NULL,
    NULL,
    NULL,
    13, // Number of vertices
    0,
    0,
    0
};

struct MeshInfo M_Limb_L_Mesh = {
    M_Limb_R_Verts,
    NULL,
    NULL,
    NULL,
    13, // Number of vertices
    0,
    0,
    0
};

struct MeshInfo M_Leg_Mesh = {
    M_Leg_Verts,
    NULL,
    NULL,
    NULL,
    13, // Number of vertices
    0,
    0,
    0
};

void bhv_sample_cube_init(void) {
    struct RigidBody *body;

    if (o->oBehParams2ndByte == 90) {
        spawn_object_relative_with_scale(0, 0, 0, 0, ModelScale, o, MODEL_M_BODY, bhvSampleSphere);
        body = allocate_rigid_body_from_object(o, &Collider_Mesh, 20.f, Collider_Size, FALSE);
        body->colOnly = 1;
    }
    else if (o->oBehParams2ndByte == 0) {
        spawn_object_relative_with_scale(5, 0, 0, 0, ModelScale, o, MODEL_M_SHOULDER_R, bhvSampleSphere);
        spawn_object_relative_with_scale(6, 0, 0, 0, ModelScale, o, MODEL_M_HEAD, bhvSampleSphere);
        spawn_object_relative_with_scale(7, 0, 0, 0, ModelScale, o, MODEL_M_THIGH_L, bhvSampleSphere);
        spawn_object_relative_with_scale(8, 0, 0, 0, ModelScale, o, MODEL_M_THIGH_R, bhvSampleSphere);
        spawn_object_relative_with_scale(4, 0, 0, 0, ModelScale, o, MODEL_M_SHOULDER_L, bhvSampleSphere);
        body = allocate_rigid_body_from_object(o, &M_Body_Mesh, 3.f, M_Size, FALSE);

        //gMarioState->ragdoll = o;
    }
    else {
        if (obj_has_model(o, MODEL_M_THIGH_L)) {
            spawn_object_relative_with_scale(7, 0, 0, 0, ModelScale, o, MODEL_M_LEG_L, bhvSampleSphere);
        }
        if (obj_has_model(o, MODEL_M_THIGH_R)) {
            spawn_object_relative_with_scale(7, 0, 0, 0, ModelScale, o, MODEL_M_LEG_R, bhvSampleSphere);
        }
        if (obj_has_model(o, MODEL_M_LEG_L)) {
            spawn_object_relative_with_scale(7, 0, 0, 0, ModelScale, o, MODEL_M_FOOT_L, bhvSampleSphere);
        }
        if (obj_has_model(o, MODEL_M_LEG_R)) {
            spawn_object_relative_with_scale(7, 0, 0, 0, ModelScale, o, MODEL_M_FOOT_R, bhvSampleSphere);
        }
        if (obj_has_model(o, MODEL_M_SHOULDER_L)) {
            spawn_object_relative_with_scale(7, 0, 0, 0, ModelScale, o, MODEL_M_ARM_L, bhvSampleSphere);
        }
        if (obj_has_model(o, MODEL_M_SHOULDER_R)) {
            spawn_object_relative_with_scale(7, 0, 0, 0, ModelScale, o, MODEL_M_ARM_R, bhvSampleSphere);
        }
        if (obj_has_model(o, MODEL_M_ARM_L)) {
            spawn_object_relative_with_scale(7, 0, 0, 0, ModelScale, o, MODEL_M_HAND_L, bhvSampleSphere);
        }
        if (obj_has_model(o, MODEL_M_ARM_R)) {
            spawn_object_relative_with_scale(7, 0, 0, 0, ModelScale, o, MODEL_M_HAND_R, bhvSampleSphere);
        }


        //allocation
        if (obj_has_model(o, MODEL_M_THIGH_L) || obj_has_model(o, MODEL_M_THIGH_R) || obj_has_model(o, MODEL_M_LEG_L) || obj_has_model(o, MODEL_M_LEG_R) || obj_has_model(o, MODEL_M_FOOT_L) || obj_has_model(o, MODEL_M_FOOT_R)) {
            body = allocate_rigid_body_from_object(o, &M_Leg_Mesh, 3.f, Tiny_Size, FALSE);
        }
        else if (obj_has_model(o, MODEL_M_HEAD)) {
            body = allocate_rigid_body_from_object(o, &M_Head_Mesh, 9.2f, Tiny_Size, FALSE);
        }
        else if (obj_has_model(o, MODEL_M_ARM_L) || obj_has_model(o, MODEL_M_SHOULDER_L) || obj_has_model(o, MODEL_M_HAND_L)) {
            body = allocate_rigid_body_from_object(o, &M_Limb_L_Mesh, 3.f, Arm_Size, FALSE);
        }
        else {
            body = allocate_rigid_body_from_object(o, &M_Limb_R_Mesh, 3.f, Arm_Size, FALSE);
        }
        
        body->parentBody = o->parentObj->rigidBody;
    }

    if (0 && (obj_has_model(o, MODEL_M_SHOULDER_L) || obj_has_model(o, MODEL_M_SHOULDER_R) || obj_has_model(o, MODEL_M_THIGH_L) || obj_has_model(o, MODEL_M_THIGH_R))) {
        body->maxYaw = 0x1000;
        body->maxRoll = 0x1000;
        body->maxPitch = 0x1000;
        body->minYaw = -0x1000;
        body->minRoll = -0x1000;
        body->minPitch = -0x1000;
    }

    if (0 && obj_has_model(o, MODEL_M_HEAD)) {
        body->maxYaw = 0x1000;
        body->maxRoll = 0x500;
        body->maxPitch = 0x1000;
        body->minYaw = -0x1000;
        body->minRoll = -0x500;
        body->minPitch = -0x1000;
    }
}

void bhv_sample_cube_loop(void) {
    
    //quat constraints
    if (o->rigidBody->parentBody) {
        if (!((obj_has_model(o, MODEL_M_ARM_L) || obj_has_model(o, MODEL_M_ARM_R) || obj_has_model(o, MODEL_M_HAND_L) || obj_has_model(o, MODEL_M_HAND_R)))) {
            constrain_quaternion(o->rigidBody->parentBody->angleQuat, o->rigidBody->angleQuat, M_PI/1.3f);
        }
    }
    
    //sleep deactivation
    if ((o->rigidBody->parentBody && o->rigidBody->parentBody->asleep == 0) || o->oTimer < 10) {
        o->rigidBody->asleep = 0;
    }
    
    if (o->rigidBody->linearVel[1] > 20) {
        o->rigidBody->linearVel[1] = 20;
    }

    if (o->oBehParams2ndByte == 0) {
       gMarioState->pos[0] = o->oPosX;
       gMarioState->pos[1] = o->oPosY;
       gMarioState->pos[2] = o->oPosZ;

       //gMarioState->action = ACT_WAITING_FOR_DIALOG;
       gMarioObject->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_NONE];
    }

}
