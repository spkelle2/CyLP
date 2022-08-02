#include "ICbcModel.hpp"
#include "ICbcNode.hpp"

#include "CbcCompareUser.hpp"
#include "CbcSolver.hpp"
#include "CbcNodeInfo.hpp"
#include "CoinWarmStartBasis.hpp"

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
        const char* argv[] = {"ICbcModel", "-solve","-quit"};
        CbcMain0(*this);
	this->setLogLevel(logLevel);
        return CbcMain1(3, argv, *this);
        //const char* argv = "-solve -quit";
        //CbcSolverUsefulData solverData;
        //CbcMain0(*this, solverData);
	//this->setLogLevel(logLevel);
        //return CbcMain1(3, argv, *this, NULL, solverData);
}

std::vector<ICbcNode*> ICbcModel::getCbcNodeList() {
    std::vector<ICbcNode*> recastNodeList;
    for (unsigned int i = 0; i < this->getNodeMap().size(); i++) {
        ICbcNode* node = (ICbcNode*)(this->getNodeMap()[i].first);
        recastNodeList.push_back(node);
    }
    return recastNodeList;
}

std::vector<OsiSolverInterface*> ICbcModel::getOsiSolverInterfaceList() {
    std::vector<OsiSolverInterface*> recastOsiSolverInterfaceList;
    for (unsigned int i = 0; i < this->getNodeMap().size(); i++) {
        OsiSolverInterface* lp = (OsiSolverInterface*)(this->getNodeMap()[i].second);
        recastOsiSolverInterfaceList.push_back(lp);
    }
    return recastOsiSolverInterfaceList;
}
