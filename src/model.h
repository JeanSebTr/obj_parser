/* 
 * File:   model.h
 * Author: jeansebtr
 *
 * Created on 16 février 2011, 18:03
 */

#ifndef _MODEL_H
#define	_MODEL_H

struct Vertex
{
    double x;
    double y;
    double z;
};


struct Face
{
    int v[3];
};

struct Line
{
    Vertex v1;
    Vertex v2;
};

struct Triangle
{
    Vertex v1;
    Vertex v2;
    Vertex v3;
};

struct Quads
{
    Vertex v1;
    Vertex v2;
    Vertex v3;
    Vertex v4;
};

typedef struct model_basic_v01 ModelV01;
struct model_basic_v01
{
    Vertex* v;
    int nbVertex;
    Face* f;
    int nbFace;
};

typedef struct model_basic_v02 ModelV02;
struct model_basic_v02
{
    int nbLines;
    Line* l;
    int nbTriangles;
    Triangle* t;
    int nbQuads;
    Quads* q;
};


#endif	/* _MODEL_H */

