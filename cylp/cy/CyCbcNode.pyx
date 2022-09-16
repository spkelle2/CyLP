# cython: embedsignature=True


cimport CyCbcNode

cdef class CyCbcNode:
    def __cinit__(self):
        self.CppSelf = new CppICbcNode()

    cdef setCppSelf(self, CppICbcNode* cbcnode):
        self.CppSelf = cbcnode
        return self

    property depth:
        def __get__(self):
            return self.CppSelf.depth()

    property numberUnsatisfied:
        def __get__(self):
            return self.CppSelf.numberUnsatisfied()

    property sumInfeasibilities:
        def __get__(self):
            return self.CppSelf.sumInfeasibilities()

    property active:
        def __get__(self):
            return self.CppSelf.active()

    property onTree:
        def __get__(self):
            return self.CppSelf.onTree()

    property objectiveValue:
        def __get__(self):
            return self.CppSelf.objectiveValue()

    property isLeaf:
        def __get__(self):
            status_code = self.CppSelf.nodeMapLeafStatus()
            assert status_code in [0, 1], 'CbcModel.persistNodes must be true to use this attribute'
            return bool(status_code)

    property lineage:
        def __get__(self):
            cdef object lineage = self.CppSelf.nodeMapLineage()
            assert lineage, 'CbcModel.persistNodes must be true to use this attribute'
            return lineage

    property index:
        def __get__(self):
            index = self.CppSelf.nodeMapIndex()
            assert index >= 0, 'CbcModel.persistNodes must be true to use this attribute'
            return index

    def breakTie(self, CyCbcNode y):
        return self.CppSelf.breakTie(y.CppSelf)
