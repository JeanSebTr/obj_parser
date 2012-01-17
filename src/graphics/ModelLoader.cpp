/* 
 * File:   ModelLoader.cpp
 * Author: jeansebtr
 * 
 * Created on 12 février 2011, 23:41
 */

#include "ModelLoader.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
	#ifdef _WIN32
	  #include <windows.h>
	#endif
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif

#include "../debug.h"
#include "../Convert.h"


std::vector<std::string> split(std::string s, char c)
{
    //Eclate une chaîne au niveau de ses espaces.
    std::vector<std::string> ret;
    std::string s1="";
    for(unsigned int i=0;i<s.size();i++)
    {
        if(s[i]==c||i==s.size()-1)
        {
            if(i==s.size()-1)
                s1+=s[i];
            ret.push_back(s1);
            s1="";
        }
        else
            s1+=s[i];
    }
    return ret;
}

int ModelLoader::ModelId = 1;
std::vector<ModelContener> ModelLoader::models;

int ModelLoader::Load(std::string file)
{
    dbg("Check for already loaded model '"+file+"'");
    int i;
    for(i = 0; i < models.size(); i++)
    {
        if(models.at(i).name == file)
            return models.at(i).id;
    }
    return LoadFromFile(file);
}

int ModelLoader::LoadFromFile(std::string file)
{
    std::ifstream f;
    std::stringstream buf;
    ModelContener model;
    model.loaded = false;
    model.name = file;
    dbg("Try opening file "+file);
    f.open(file.c_str());
    if(f)
    {
        dbg("File opened.");
        f.seekg(0, std::ios::end);
        int length = f.tellg();
        f.seekg(0, std::ios::beg);
        dbg("File is "+Convert::itos(length)+" bits long.");
        std::vector<Vertex> vList;
        std::vector<Line> flList;
        std::vector<Triangle> ftList;
        std::vector<Quads> fqList;
        std::string l;
        int num = 0;
        char c1[10], c2[10], c3[10];
        while(f)
        {
            std::getline(f, l);
            try
            {
                if(l.at(0) == 'v')
                {
                    if(l.at(1) == ' ')
                    {
                        // vertex
                        Vertex v;
                        sscanf(l.c_str(), "v %s %s %s", c1, c2, c3);
                        v.x = atof(c1);
                        v.y = atof(c2);
                        v.z = atof(c3);
                        vList.push_back(v);
                    }
                    else if(l.at(1) == 't')
                    {
                        
                    }
                }
                else if(l.at(0) == 'f')
                {
                    // Face
                    std::vector<std::string> vf = split(l.substr(2), ' ');
                    switch(vf.size())
                    {
                        case 2:
                            Line fl;
                            fl.v1 = vList.at(atoi(split(vf[0],'/')[0].c_str())-1);
                            fl.v2 = vList.at(atoi(split(vf[1],'/')[0].c_str())-1);
                            flList.push_back(fl);
                            break;
                        case 3:
                            Triangle ft;
                            ft.v1 = vList.at(atoi(vf[0].c_str())-1);
                            ft.v2 = vList.at(atoi(vf[1].c_str())-1);
                            ft.v3 = vList.at(atoi(vf[2].c_str())-1);
                            ftList.push_back(ft);
                            break;
                        case 4:
                            Quads fq;
                            fq.v1 = vList.at(atoi(vf[0].c_str())-1);
                            fq.v2 = vList.at(atoi(vf[1].c_str())-1);
                            fq.v3 = vList.at(atoi(vf[2].c_str())-1);
                            fq.v4 = vList.at(atoi(vf[3].c_str())-1);
                            fqList.push_back(fq);
                            break;
                    }
                }
                else if(l.at(0) == 'm')
                {
                    
                }
            }
            catch(std::exception e)
            {
                
            }
            num++;
        }
        f.close();
        dbg("Read : "+Convert::itos(num)+" lines.");
        ModelV02* _m = new ModelV02;
        int i;
        _m->nbLines = flList.size();
        _m->l = new Line[_m->nbLines];
        for(i = 0; i < _m->nbLines; i++)
        {
            _m->l[i] = flList.at(i);
        }
        _m->nbTriangles = ftList.size();
        _m->t = new Triangle[_m->nbTriangles];
        for(i = 0; i < _m->nbTriangles; i++)
        {
            _m->t[i] = ftList.at(i);
        }
        _m->nbQuads = fqList.size();
        _m->q = new Quads[_m->nbQuads];
        for(i = 0; i < _m->nbQuads; i++)
        {
            _m->q[i] = fqList.at(i);
        }
        dbg("Model loaded : "+Convert::itos(_m->nbLines)+" lines, "+Convert::itos(_m->nbTriangles)+" triangles, "+Convert::itos(_m->nbQuads)+" quads");
        model.model = _m;
        model.id = ModelId++;
        model.loaded = true;
        models.push_back(model);
        return ModelId-1;
    }
    else
    {
        f.close();
        return NULL;
    }
}

void ModelLoader::Render(int modelID)
{
    if(modelID < 1)
        return;
    int i;
    for(i = 0; i < models.size(); i++)
    {
        if(models.at(i).id == modelID)
            break;
    }
    if(i >= models.size())
        return;
    ModelV02* m = (ModelV02*)models.at(i).model;
    //dbg("Model contain : "+Convert::itos(m->nbVertex)+" vertices "+Convert::itos(m->nbFace)+" faces");
    int f;
    for(f = 0; f < m->nbLines; f++)
    {
        glBegin(GL_LINE);
            glColor3ub(0,0,255);
            glVertex3d(m->l[f].v1.x, m->l[f].v1.y, m->l[f].v1.z);
            glVertex3d(m->l[f].v2.x, m->l[f].v2.y, m->l[f].v2.z);
        glEnd();
    }
    for(f = 0; f < m->nbTriangles; f++)
    {
        glBegin(GL_TRIANGLES);
            glColor3ub(0,0,255);
            glVertex3d(m->t[f].v1.x, m->t[f].v1.y, m->t[f].v1.z);
            glVertex3d(m->t[f].v2.x, m->t[f].v2.y, m->t[f].v2.z);
            glVertex3d(m->t[f].v3.x, m->t[f].v3.y, m->t[f].v3.z);
        glEnd();
    }
    for(f = 0; f < m->nbQuads; f++)
    {
        glBegin(GL_QUADS);
            glColor3ub(0,0,255);
            glVertex3d(m->q[f].v1.x, m->q[f].v1.y, m->q[f].v1.z);
            glVertex3d(m->q[f].v2.x, m->q[f].v2.y, m->q[f].v2.z);
            glVertex3d(m->q[f].v3.x, m->q[f].v3.y, m->q[f].v3.z);
            glVertex3d(m->q[f].v4.x, m->q[f].v4.y, m->q[f].v4.z);
        glEnd();
    }
    //dbg("Render done !!! :D");
}

void ModelLoader::LoadMTL(std::string file)
{
    
}
