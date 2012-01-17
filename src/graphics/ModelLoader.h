/* 
 * File:   ModelLoader.h
 * Author: jeansebtr
 *
 * Created on 12 février 2011, 23:41
 */

#include <string>
#include <vector>

#include "../model.h"

#ifndef _MODELLOADER_H
#define	_MODELLOADER_H


enum model_type
{
    BASIC_V01 = 0,
    BASIC_V02 = 1,
    LAST = 1
};
typedef enum model_type ModelType;


typedef struct basic_model ModelContener;
struct basic_model
{
    ModelType type;
    int id;
    std::string name;
    bool loaded;
    void* model;
};

std::vector<std::string> split(std::string s, char c);

class ModelLoader {
public:
    static int Load(std::string file);
    static int Load(std::string file, ModelType type);
    static void LoadMTL(std::string file);

    static void Render(int modelID);

private:
    ModelLoader();
    ModelLoader(const ModelLoader& orig);
    virtual ~ModelLoader();

    static int ModelId;
    static std::vector<ModelContener> models;

    static int LoadFromFile(std::string file);
    static Vertex ReadVertex(std::string l);
    static Face ReadFace(std::string l);
};

#endif	/* _MODELLOADER_H */

