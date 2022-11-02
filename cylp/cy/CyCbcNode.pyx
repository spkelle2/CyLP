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
            assert status_code in [0, 1], 'status code should be 0, 1'
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

    property branchVariable:
        def __get__(self):
            branch_variable = self.CppSelf.branchVariable()
            return None if branch_variable < 0 else branch_variable

    property branchWay:
        def __get__(self):
            branch_way = self.CppSelf.branchWay()
            return 'left' if branch_way == -1 else 'right' if branch_way == 1 else None

    property lpFeasible:
        def __get__(self):
            status = self.CppSelf.lpFeasible()
            assert status in [0, 1, 2]
            return None if status == 0 else True if status == 1 else False

    def breakTie(self, CyCbcNode y):
        return self.CppSelf.breakTie(y.CppSelf)
