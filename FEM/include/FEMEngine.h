#pragma once
#ifndef FEMENGINE_H
#define FEMENGINE_H

#include <vector>
#include "node.h"
#include "element.h"
#include "bConditions.h"
#include "load.h"
#include "matrix.h"
#include "material.h"
#include "section.h"
#include "lcombination.h"
#include "NodalResponse.h"
#include "ElementResponse.h"


#include <iomanip>
#include "mathlib.h"
#include "writer.h"
#include <iterator>

enum class SFType
{
    AXIAL,
    SHEAR,
    MOMENT
};

class FEMEngine
{
public:
    FEMEngine();
   ~FEMEngine();
    void start(const std::vector<node> &_nodalData,
              const std::vector<element> &_elementData,
              const std::vector<material> &_materialData,
              const std::vector<section> &_sectionData,
              const std::vector<bConditions> &_bcData,
              const std::vector<load> &_loadData,
              const std::vector<lCombination> &_loadComboData);


    void createIDMatrix();
    void createStiffMatrix();
    void createForceMatrix();
    void applyBC();
    void solve();
    void calcElmForces();

    void populateNodalResData();
    void populateElementResData();
    double sectionForce(int _lc, int _elementID, double _dist, SFType _type);


    void printNodeTable();
    void printElementTable();
    void printSectionForces(std::vector<int> _lc, std::vector<int> _elmID, int _div, SFType _type,
                            bool _revSign, bool _ft);

    element & searchID(std::vector<element> &elData,int _id);
    bool searchElm_in_Load(load &_load, int _elmID);

protected:

private:
         //Input Parameters
         std::vector<node> nodalData;
         std::vector<element> elementData;
         std::vector<material> materialData;
         std::vector<section> sectionData;
         std::vector<bConditions> bcData;
         std::vector<load> loadData;
         std::vector<lCombination> loadComboData;


         //Output Parameters
         std::vector<std::vector<NodalResponse>> nodalRData;
         std::vector<std::vector<ElementResponse>> elementRData;

         matrix IDArray;                            //ID matrix
         matrix K;                                  //Stiffness matrix
         matrix Kr;                                 //Reduced Stiffness matrix
         matrix F;                                  //Force matrix
         matrix Fr;                                 //Reduced Force matrix
         matrix d;                                  //Displacement matrix
         matrix R;                                  //Reaction matrix
         matrix force;
         std::vector<matrix> forces;
         matrix ElmForce;                           //Element Force matrix for one load combination
         std::vector<matrix> ElmForces;             //Element Force Matrix for all load combinations


};
#endif // FEMENGINE_H
