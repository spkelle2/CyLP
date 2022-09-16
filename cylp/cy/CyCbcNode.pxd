cimport numpy as np
from libcpp.vector cimport vector

cdef extern from "ICbcNode.hpp":
    cdef cppclass CppICbcNode "ICbcNode":
        int depth()
        int numberUnsatisfied()
        double sumInfeasibilities()
        bint active()
        bint onTree()
        double objectiveValue()
        bint breakTie(CppICbcNode* y)
        int nodeMapLeafStatus()
        vector[int] nodeMapLineage()
        int nodeMapIndex()

cdef class CyCbcNode:
    cdef CppICbcNode* CppSelf
    cdef setCppSelf(self, CppICbcNode* cbcnode)
