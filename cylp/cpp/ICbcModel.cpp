#include "iostream"

#include "ICbcModel.hpp"
#include "ICbcNode.hpp"

#include "CbcCompareUser.hpp"
#include "CbcSolver.hpp"
#include "CbcNodeInfo.hpp"
#include "CoinWarmStartBasis.hpp"
#include "IClpSimplex.hpp"
#include "ICoinPackedMatrix.hpp"

PyObject* ICbcModel::getPrimalVariableSolution(){

    _import_array();
    npy_intp dims = this->solver()->getNumCols();
    double* d = (double*)(this->solver()->getColSolution());
    PyObject *Arr = PyArray_SimpleNewFromData( 1, &dims, PyArray_DOUBLE, d );

    return Arr;
}

ICbcModel::ICbcModel(OsiClpSolverInterface& osiint):CbcModel(osiint){
    _import_array();
}

ICbcModel::ICbcModel(IClpSimplex* ClpModel):CbcModel(ClpModel->getOsiClpSolverInterface()){
    _import_array();
}

void ICbcModel::setNodeCompare(PyObject* obj,
                           runTest_t runTest, runNewSolution_t runNewSolution,
                           runEvery1000Nodes_t runEvery1000Nodes){
    CbcCompareUser compare(obj, runTest,
                           runNewSolution,runEvery1000Nodes);
    setNodeComparison(compare);

}


int ICbcModel::cbcMain(){
    // initialize
    int returnCode = -1;
    int logLevel = this->logLevel();
    const char* argv[] = {"ICbcModel", "-preprocess", "off", "-presolve", "off", "-solve", "-quit"};
    CbcMain0(*this);
    this->setLogLevel(logLevel);
    return CbcMain1(7, argv, *this);
    //const char* argv = "-solve -quit";
    //CbcSolverUsefulData solverData;
    //CbcMain0(*this, solverData);
    //this->setLogLevel(logLevel);
    //return CbcMain1(3, argv, *this, NULL, solverData);
}

std::vector<ICbcNode*> ICbcModel::getCbcNodeList() {
    std::vector<ICbcNode*> nodeList;
    for (unsigned int i = 0; i < this->getNodeMap().size(); i++) {
        std::cout << "node " << i << "\n";
        ICbcNode* node = new ICbcNode(this->getNodeMap()[i].first.get());
        nodeList.push_back(node);
    }
    return nodeList;
}

std::vector<ICoinPackedMatrix*> ICbcModel::getMatrixList() {
    std::vector<ICoinPackedMatrix*> matrixList;
    for (unsigned int i = 0; i < this->getNodeMap().size(); i++) {
        ICoinPackedMatrix* matrix = new ICoinPackedMatrix(this->getNodeMap()[i].second.get()->matrix());
        matrixList.push_back(matrix);
    }
    return matrixList;
}

std::vector<double*> ICbcModel::getColumnLowerList() {
    std::vector<double*> columnLowerList;
    for (unsigned int i = 0; i < this->getNodeMap().size(); i++) {
        columnLowerList.push_back(this->getNodeMap()[i].second.get()->columnLower());
    }
    return columnLowerList;
}

std::vector<double*> ICbcModel::getColumnUpperList() {
    std::vector<double*> columnUpperList;
    for (unsigned int i = 0; i < this->getNodeMap().size(); i++) {
        columnUpperList.push_back(this->getNodeMap()[i].second.get()->columnUpper());
    }
    return columnUpperList;
}

std::vector<double*> ICbcModel::getObjectiveList() {
    std::vector<double*> objectiveList;
    for (unsigned int i = 0; i < this->getNodeMap().size(); i++) {
        objectiveList.push_back(this->getNodeMap()[i].second.get()->objective());
    }
    return objectiveList;
}

std::vector<double*> ICbcModel::getRowLowerList() {
    std::vector<double*> rowLowerList;
    for (unsigned int i = 0; i < this->getNodeMap().size(); i++) {
        rowLowerList.push_back(this->getNodeMap()[i].second.get()->rowLower());
    }
    return rowLowerList;
}

std::vector<double*> ICbcModel::getRowUpperList() {
    std::vector<double*> rowUpperList;
    for (unsigned int i = 0; i < this->getNodeMap().size(); i++) {
        rowUpperList.push_back(this->getNodeMap()[i].second.get()->rowUpper());
    }
    return rowUpperList;
}

std::vector<double*> ICbcModel::getRowObjectiveList() {
    std::vector<double*> rowObjectiveList;
    for (unsigned int i = 0; i < this->getNodeMap().size(); i++) {
        rowObjectiveList.push_back(this->getNodeMap()[i].second.get()->rowObjective());
    }
    return rowObjectiveList;
}